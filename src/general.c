#include <stdio.h>

#include "./general.h"

void systemSpecificOpen() {
#if defined(VITA)
	SDL_setenv("VITA_DISABLE_TOUCH_BACK", "1", 1);
#elif defined(SWITCH)
	chdir("/switch/BlockamokRemix");
#elif defined(WII)
	fatInitDefault();
	PAD_Init();
#elif defined(XBOX)
	XVideoSetMode(640, 480, 32, REFRESH_DEFAULT);
#elif defined(XBOX360)
	/* libxenon: nothing extra needed; video mode set by the loader */
	(void)0;
#elif defined(PS3)
	/* PSL1GHT: initialise pad subsystem */
	ioPadInit(4);
#endif
}

void systemSpecificClose() {
#if defined(WII_U)
	WHBUnmountSdCard();
	WHBProcInit();
	WHBProcShutdown();
#elif defined(VITA)
	sceKernelExitProcess(0);
#elif defined(WII) || defined(GAMECUBE)
	exit(EXIT_SUCCESS);
#elif defined(PSP)
	sceKernelExitGame();
#elif defined(PS3)
	sys_process_exit(0);
#endif
}
