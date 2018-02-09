#pragma once

# include "IReadable.h"
# include "IWritable.h"

class ITCPClient : public IReadable, public IWritable
{
public:
	virtual ~ITCPClient() {}

	virtual int 		getWriteFd() const = 0;
	virtual int 		getReadFd() const = 0;
	virtual bool 		somethingToWrite() const = 0;
	virtual int 		closeSock() = 0;

	virtual int 		connectTo(std::string const &, short) = 0;

	virtual int 		receiveMsg(std::string &) = 0;

	virtual void 		prepareMsg(std::string const &, int) = 0;
	virtual int 		send() = 0;
};
