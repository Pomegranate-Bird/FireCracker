#include <esp_now.h> //Node Communication architecture 
#include <WiFi.h>
#include <Wire.h> // I2C communication Protocol

 const int id = 2; // Change for each ESP32 
 float temp = 0;
 float hum = 0;
 float air_quality_reading = 0;
 unsigned long curr_time;
 unsigned long buffer;

// REPLACE WITH YOUR RECEIVER MAC Address
uint8_t broadcastAddress[] = {0x10, 0x20, 0xBA, 0x0D, 0xB4,0xC8};

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
  int id; // Unqiue identifier for each board 
  float temperature;
  float humidity;
  float pm25;
} struct_message;

// Create a struct_message called myData
struct_message myData;

esp_now_peer_info_t peerInfo;

// Callback function that is called when data is sent
void OnDataSent(const wifi_tx_info_t *info, esp_now_send_status_t status) {
  // Only useful for debugging: When sending data for Python Processing keep uncommented 
  blink();
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
 
void setup() {
  Serial.begin(115200); // Begin serial communicaitons 

  // Initializing Sensors:
  set_led(); // Initializing LED
  initialize_temp_sensor(); //Initializing temperature & humidity sensor 
  initializePM25(); //Initializing Pm2.5 Sesnor

  //ESP-NOW Communication 
  WiFi.mode(WIFI_STA); // Set device as a Wi-Fi Station

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
  gather_temp_humidity(); // Get temperature and humidity values
  gather_pm25_data(); // Getting Air Quality measurements 


  // Store data obtained from sensors in data structure 
  myData.temperature = temp;
  myData.humidity = hum;
  myData.pm25 = air_quality_reading;


  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));


  curr_time = millis();
  if (result == ESP_OK && curr_time - buffer >= 1000) {
     buffer = curr_time;
    
  }
}