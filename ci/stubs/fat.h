#pragma once
typedef struct { int (*startup)(void); int (*isInserted)(void); } DISC_INTERFACE;
int fatInitDefault(void);
int fatMountSimple(const char *name,const DISC_INTERFACE *iface);
