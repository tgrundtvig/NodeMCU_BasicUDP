/*
  Author: Tobias Grundtvig
*/

#ifndef BasicUDP_h
#define BasicUDP_h

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#define _MAX_PACKET_SIZE 1024


class BasicUDP
{
public:
    BasicUDP();
    void begin(uint16_t port);
    void update(unsigned long curTime);
    void stop();
    bool sendPacket(IPAddress dstAddress, uint16_t dstPort, uint8_t* pData, uint16_t size);
    virtual void onPacketReceived(unsigned long curTime, IPAddress srcAddress, uint16_t srcPort, uint8_t* pData, uint16_t size)
    {
        Serial.print("Packet received from ");
        Serial.print(srcAddress.toString());
        Serial.print(":");
        Serial.print(srcPort);
        Serial.print(" Packetsize: ");
        Serial.println(size);
        for(uint16_t i = 0; i < size; ++i)
        {
            Serial.print(i);
            Serial.print("\t: ");
            Serial.println(pData[i]);
        }
        Serial.println();
    }
private:
    WiFiUDP _udp;
    uint8_t _receiveBuffer[_MAX_PACKET_SIZE];
};

#endif