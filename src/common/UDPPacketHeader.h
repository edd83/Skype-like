#pragma once

struct		UDPPacketHeader
{
        char	magicA;
        char	magicB;
        char	magicC;
        char	senderID;
        int		payloadSize;
};

