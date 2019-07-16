#include "Provider.h"

Provider* Provider::Instance = nullptr;

Provider* Provider::GetInstance()
{
	if (Instance == nullptr) Instance = new Provider;
	return Instance;
}
