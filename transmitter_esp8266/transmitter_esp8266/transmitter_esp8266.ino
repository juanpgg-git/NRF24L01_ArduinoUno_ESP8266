#include <SPI.h>  
#include <RH_NRF24.h>

RH_NRF24 nrf24(2,4); //CSN and CE in D2 and D4 
 
void setup() 
{
  Serial.begin(9600);
  
  if (!nrf24.init()){
  
    Serial.println("init failed");
  }
  else{
   
    Serial.println("init succeed");
  }
    
  if (!nrf24.setChannel(1)){
    
    Serial.println("setChannel failed");
  }
  else{
    
    Serial.println("setChannel succeed");
  }
    
  if (!nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm)){
    
    Serial.println("setRF failed");
  }
  else{
    Serial.println("setRF succeed");
  }

  Serial.println("NRF24L01 ready to go");
     
}
 
void loop()
{
  Serial.println("Sending to nrf24_server");
  // Send a message to nrf24_server
  uint8_t data[] = "Hello World!";
  nrf24.send(data, sizeof(data));
  
  nrf24.waitPacketSent();
  // Now wait for a reply
  uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);

  if (nrf24.waitAvailableTimeout(500))
  { 
    // Should be a reply message for us now   
    if (nrf24.recv(buf, &len))
    {
      Serial.print("got reply: ");
      Serial.println((char*)buf);
    }
    else
    {
      Serial.println("recv failed");
    }
  }
  else
  {
    Serial.println("No reply, is nrf24_server running?");
  }
  delay(2000);
}
