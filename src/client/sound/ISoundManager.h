#pragma once

class ISoundManager
{
public:
	~ISoundManager() {}

	virtual int		start() = 0;
    virtual bool    isActive() const = 0;
};
