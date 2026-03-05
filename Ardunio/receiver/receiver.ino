#include <esp_now.h>
#include <WiFi.h>



// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
    int id;
    float temperature;
    float humidity;
} struct_message;

// Creating an array that contains each esp32 
const int number_boards = 3;
struct_message boards[number_boards]; //Array of boards 

void OnDataRecv(const esp_now_recv_info_t *info,
                const uint8_t *incomingData, int len) {
  blink(); // When Data Is received flash LED 
  struct_message msg;
  memcpy(&msg, incomingData, sizeof(msg)); // Copy the incoming data 

  boards[msg.id - 1] = msg; // No iterating, instead we store the contents of the material 

  Serial.printf("Board %d: T=%.2f  H=%.2f\n",
                msg.id, msg.temperature, msg.humidity);
  }

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  set_led(); //Initialize LED
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
