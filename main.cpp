#include "_INCLUDES_.h"
#include "Product/ProductProvider.h"

int main()
{
	AccountProvider& a = AccountProvider::GetInstance();

	a.Delete("h00000001");
	a.WriteFile();
	
	return 0;
}
