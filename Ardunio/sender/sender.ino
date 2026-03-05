#include <esp_now.h> //Node Communication architecture 
#include <WiFi.h>
#include <Wire.h> // I2C communication Protocol

 const int id = 2;
 float temp = 0;
 float hum = 0;

// REPLACE WITH YOUR RECEIVER MAC Address
uint8_t broadcastAddress[] = {0xE4, 0x65, 0xB8, 0x14, 0xA2,0xB4};

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
  int id; // Unqiue identifier for each board 
  float temperature;
  float humidity;
} struct_message;

// Create a struct_message called myData
struct_message myData;

esp_now_peer_info_t peerInfo;

// Callback function that is called when data is sent
void OnDataSent(const wifi_tx_info_t *info, esp_now_send_status_t status) {
  // Only useful for debugging: When sending data for Python Processing keep uncommented 
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
 
void setup() {
  Serial.begin(115200); // Begin serial communicaitons 
  set_led(); // Initializing LED
  initialize_temp_sensor(); //Initializing temperature & humidity sensor 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Transmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}
 
void loop() {
  // Unique ID for each ESP32 sending data to receiver 
  myData.id = id;

  // Gather data from sensors 
  gather_temp(); // Get temperature and humidity values

  // Store data obtained from sensors in data structure 
  myData.temperature = temp;
  myData.humidity = hum;

  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   
  if (result == ESP_OK) {
    blink();
    Serial.println("Data sent with success");
    // Printing the data sent 
    Serial.print("Temperature:");
    Serial.println(temp);
    Serial.print("Humidity:");
    Serial.println(hum);
  }
  else {
    Serial.println("Error sending the data");
  }
  delay(100);
}