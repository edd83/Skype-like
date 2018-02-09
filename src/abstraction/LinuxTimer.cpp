#ifndef _WIN32

#include "LinuxTimer.h"

LinuxTimer::LinuxTimer()
{
}

LinuxTimer::~LinuxTimer()
{
}

void	LinuxTimer::run(int mSec)
{
  usleep(mSec * 1000);
}

#endif
