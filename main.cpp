#include "_INCLUDES_.h"
#include "Shell/Shell.h"

int main()
{
	Shell& s = Shell::GetInstance();
	s.Loop();
	return 0;
}
