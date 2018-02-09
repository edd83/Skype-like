#pragma once

#include <sstream>
#include "eCommandId.h"
#include "TCPPacketHeader.h"
#include "UDPPacketHeader.h"

class PacketHelper
{
public:
	~PacketHelper() {}
	static bool readTcpHeader(std::istringstream &, struct TCPPacketHeader &);
	static void writeTcpHeader(std::string &, eCommandId);
	static void writeTcpHeaderSize(std::string &);

	static void writeUdpHeader(std::string &, char, int);
	static bool readUdpHeader(std::istringstream &, struct UDPPacketHeader &);
	static int getUnreadSize(std::istringstream&);

private:
    PacketHelper() {}
};
