#pragma once

#define DEBUG 1
#undef DEBUGMPDMESSAGES 

#ifdef DEBUG
#define DPRINT(x) x;
#else
#define DPRINT(x)
#endif