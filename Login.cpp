#include "Password.h"

void Password::GetPassword()
{
	// mask field
	
	char c = 0;
	while (c = cin.get()) {
		if (c == 8) { // BACKSPACE

		}
		else if (c == 13) { // RETURN

		}
		else if (c == 0 || c == 224) { // CONTROL CHARS

		}
		else {

		}
	}

	// băm
}

bool Password::operator==(const Password& x)
{
	return (data == x.data);
}
