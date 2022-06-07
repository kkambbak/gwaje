void setup() {
  Serial.begin(115200);

  
  BLEDevice::init(“myGPIO");
  BLEServer *pServer = BLEDevice::createServer();

  BLEService *pService = pServer->createService(SERVICE_UUID);

  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  pCharacteristic->setCallbacks(new MyCallbacks());

  pCharacteristic->setValue("Hello World");
  pService->start();

  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
}  
void setup() {
Serial.begin(115200);
  pinMode(key, INPUT_PULLUP);
  pinMode(greenLed, OUTPUT);
  pinMode(redLed,  OUTPUT);
  BLEDevice::init("myGPIO"); // Create the BLE Device
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
