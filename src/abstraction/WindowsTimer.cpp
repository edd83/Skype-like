#ifdef _WIN32

#include "WindowsTimer.h"

WindowsTimer::WindowsTimer()
{
}

WindowsTimer::~WindowsTimer()
{
}

void	WindowsTimer::run(int sec)
{
  Sleep(sec);
}

#endif
