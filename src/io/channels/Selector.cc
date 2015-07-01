#include<cstdlib>
#include"Selector.h"

using namespace zNet;

Selector::Selector()
{	
}

Selector::~Selector()
{
}

int Selector::Select()
{
	return 0;
}

int Selector::Select(long timeout)
{
	return 0;
}

bool Selector::isReadable(const SelectionKey& key)
{
	return false;
}
