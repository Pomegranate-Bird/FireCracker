#include <esp_now.h>
#include <WiFi.h>

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
    int id;
    float temperature;
    float humidity;
} struct_message;


// Creating a structure to hold values from each board 
struct_message board1;
struct_message board2;
struct_message board3;

// Creating an array that contains each esp32 
struct_message boards[3] = {board1, board2, board3};

void OnDataRecv(const esp_now_recv_info_t *info,
                const uint8_t *incomingData, int len) {
  memcpy(&board1, incomingData, sizeof(board1));
  Serial.print("Temperature: ");
  Serial.println(board1.temperature);
  Serial.print("Humidity: ");
  Serial.println(board1.humidity);
  }

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {

}