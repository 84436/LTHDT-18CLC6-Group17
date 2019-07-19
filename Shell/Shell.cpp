#include "Shell.h"

Shell::Shell()
{

}

Shell& Shell::GetInstance()
{
	static Shell Instance;
	return Instance;
}
