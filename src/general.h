#pragma once

#include <stdlib.h>
#if defined(WII_U)
#include <unistd.h>
#include <whb/sdcard.h>
#include <whb/proc.h>
#elif defined(VITA)
#include <psp2/kernel/processmgr.h>
#elif defined(SWITCH)
#include <unistd.h>
#include <switch.h>
#elif defined(WII)
#include <gccore.h>
#include <dirent.h>
#include <fat.h>
#elif defined(GAMECUBE)
#include <gccore.h>
#include <dirent.h>
#include <fat.h>
#elif defined(PSP)
#include <pspkernel.h>
#include <pspdebug.h>
#elif defined(XBOX)
#include <hal/debug.h>
#include <hal/xbox.h>
#include <hal/video.h>
#include <hal/audio.h>
#include <windows.h>
#include <xboxkrnl/xboxkrnl.h>
#elif defined(XBOX360)
/* libxenon SDK headers */
#include <xenon_smc/xenon_smc.h>
#include <xenon_sound/sound.h>
#include <input/input.h>
#elif defined(PS3)
/* PSL1GHT / ps3toolchain headers */
#include <io/pad.h>
#include <sys/process.h>
#include <sysutil/sysutil_sysparam.h>
#elif defined(LINUX)
#include <sys/stat.h>
#endif

extern void systemSpecificOpen();
extern void systemSpecificClose();
