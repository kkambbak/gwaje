#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>
using namespace std;

const int redLed   = 14;
const int greenLed = 12;
const int key      = 27;

BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;
bool deviceConnected      = false;
bool oldDeviceConnected = false;
uint32_t value = 0;


#define SERVICE_UUID               "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID  "beb5483e-36e1-4688-b7f5-ea07361b26a8"

class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      string value = pCharacteristic->getValue();
      if (value.length() > 0) {
      switch(value[0]) {
        case 0: digitalWrite(greenLed, LOW); digitalWrite(redLed, LOW); 
                    break;
        case 1: digitalWrite(greenLed,HIGH); digitalWrite(redLed, LOW); 
                    break;
        case 2: digitalWrite(greenLed, LOW); digitalWrite(redLed,HIGH); 
                    break;
        case 3: digitalWrite(greenLed,HIGH); digitalWrite(redLed,HIGH); 
                    break;
      }
    } // if
  }  // onWrite
};
class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };
    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

void setup() {
Serial.begin(115200);
  pinMode(key, INPUT_PULLUP);
  pinMode(greenLed, OUTPUT);
  pinMode(redLed,  OUTPUT);
  BLEDevice::init("20192960"); // Create the BLE Device학번사용
  pServer = BLEDevice::createServer();   // Create the BLE Server
  pServer->setCallbacks(new MyServerCallbacks());
  BLEService *pService = pServer->createService(SERVICE_UUID);   // Create the BLE Service

  // Create a BLE Characteristic
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                    );
                    
  pCharacteristic->addDescriptor(new BLE2902());  // Create a BLE Descriptor
  pCharacteristic->setCallbacks(new MyCallbacks());

  pService->start();   // Start the service
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();   // Start advertising
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(false);
  pAdvertising->setMinPreferred(0x0);  // set value to 0x00 to not advertise this parameter
  BLEDevice::startAdvertising();
  Serial.println("start advertising");
  Serial.println("Waiting a client connection to notify...");
}

uint8_t readValue  = 0;
void loop() {
    // notify changed value
 // notify changed value
    if (deviceConnected) {
        if(digitalRead(key))   readValue = 1;
        else                 { readValue = 0; Serial.println("Key Pressed.."); }
        pCharacteristic->setValue((uint8_t*)&readValue, 1);
        pCharacteristic->notify();
        delay(3); // bluetooth stack will go into congestion, if too many packets are sent, in 6 hours test i was able to go as low as 3ms
    }
    // disconnecting
    if (!deviceConnected && oldDeviceConnected) {
        delay(500); // give the bluetooth stack the chance to get things ready
        pServer->startAdvertising(); // restart advertising
        Serial.println("start advertising");
        oldDeviceConnected = deviceConnected;
    }
    // connecting
    if (deviceConnected && !oldDeviceConnected) {
        // do stuff here on connecting
        oldDeviceConnected = deviceConnected;
    }
}
