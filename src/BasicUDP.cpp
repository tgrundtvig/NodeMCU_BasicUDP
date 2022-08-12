/*
  Author: Tobias Grundtvig
*/

#include <Arduino.h>

#include "BasicUDP.h"

BasicUDP::BasicUDP()
{
}

void BasicUDP::begin(uint16_t port)
{
    _udp.begin(port);
}

void BasicUDP::stop()
{
    _udp.stop();
}

void BasicUDP::update(unsigned long curTime)
{
    int size = _udp.parsePacket();
    if(size > 0)
    {
        if(size <= _MAX_PACKET_SIZE)
        {
            _udp.read(_receiveBuffer, size);
            onPacketReceived(curTime, _udp.remoteIP(), _udp.remotePort(), _receiveBuffer, size);
        }
        else
        {
            Serial.print("Packet of size: ");
            Serial.print(size);
            Serial.print(" is too large. Maximum is ");
            Serial.print(_MAX_PACKET_SIZE);
            Serial.println(". Packet was dropped!");
        }
    }
}

bool BasicUDP::sendPacket(IPAddress dstAddress, uint16_t dstPort, uint8_t* pData, uint16_t size)
{
    if(size > _MAX_PACKET_SIZE)
    {
        return false;
    }
    if(!_udp.beginPacket(dstAddress, dstPort))
    {
        return false;
    }
    _udp.write(pData, size);
    _udp.endPacket();
    return true;
}