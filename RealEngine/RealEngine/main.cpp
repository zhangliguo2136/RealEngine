#include "RealEngine.h"

using namespace RealEngine;
namespace RealEngine 
{
	extern IApplication* g_pApp;
}
int main(int argc, char** argv)
{
	int ret;

	ret = g_pApp->Initialize();

	if (ret != 0)
	{
		printf("RealEngine:: app initialize faild, will exit.");
		return ret;
	}

	while (!g_pApp->IsQuit())
	{
		g_pApp->Tick();
	}

	g_pApp->Finalize();

	return 0;
}