#include "PacketHelper.h"
#include "constant.h"
#include "Serializer.hpp"

bool        PacketHelper::readTcpHeader(std::istringstream &st, TCPPacketHeader &header)
{
    header.magicA = Serializer::deserialize<char>(st);
    header.magicB = Serializer::deserialize<char>(st);
    header.magicC = Serializer::deserialize<char>(st);
    header.commandId = Serializer::deserialize<char>(st);
    header.payloadSize = Serializer::deserialize<int>(st);

    if (header.magicA == TCP_MAGIC_A && header.magicB == TCP_MAGIC_B && header.magicC == TCP_MAGIC_C
            && header.commandId >= MIN_COMMAND_ID && header.commandId <= MAX_COMMAND_ID)
        return (true);
    return (false);
}

void        PacketHelper::writeTcpHeader(std::string &dest, eCommandId cmd)
{
    dest = Serializer::serialize<char>(TCP_MAGIC_A);
    dest = dest.append(Serializer::serialize<char>(TCP_MAGIC_B));
    dest = dest.append(Serializer::serialize<char>(TCP_MAGIC_C));
    dest = dest.append(Serializer::serialize<char>(cmd));
    dest = dest.append(Serializer::serialize<int>(0));
}

void        PacketHelper::writeTcpHeaderSize(std::string &msg)
{
    msg = msg.replace(4, 4, Serializer::serialize<int>(msg.length() - sizeof(struct TCPPacketHeader)));
}

void        PacketHelper::writeUdpHeader(std::string &dest, char id, int size)
{
    dest = Serializer::serialize<char>(UDP_MAGIC_A);
    dest = dest.append(Serializer::serialize<char>(UDP_MAGIC_B));
    dest = dest.append(Serializer::serialize<char>(UDP_MAGIC_C));
    dest = dest.append(Serializer::serialize<char>(id));
    dest = dest.append(Serializer::serialize<int>(size));
}

bool        PacketHelper::readUdpHeader(std::istringstream &st, UDPPacketHeader &header)
{
    header.magicA = Serializer::deserialize<char>(st);
    header.magicB = Serializer::deserialize<char>(st);
    header.magicC = Serializer::deserialize<char>(st);
    header.senderID = Serializer::deserialize<char>(st);
    header.payloadSize = Serializer::deserialize<int>(st);

    if (header.magicA == UDP_MAGIC_A && header.magicB == UDP_MAGIC_B && header.magicC == UDP_MAGIC_C)
        return (true);
    return (false);
}

int			PacketHelper::getUnreadSize(std::istringstream& st)
{
	std::streampos pos = st.tellg();
	st.seekg(0, st.end);
	int length = (int)(st.tellg() - pos);
	st.seekg(pos, st.beg);
	return length;
}
