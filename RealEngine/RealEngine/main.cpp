#include "RealEngine.h"

using namespace RealEngine;
namespace RealEngine 
{
	extern IApplication* g_pApp;
}
int main(int argc, char** argv)
{
	int ret;

	if ((ret = g_pApp->Initialize()) != 0)
	{
		printf("RealEngine:app initialize faild, will exit.");
		return ret;
	}

	while (!g_pApp->IsQuit())
	{
		g_pApp->Tick();
	}

	g_pApp->Finalize();

	return 0;
}