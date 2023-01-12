#pragma once

#undef DEBUG
//#define DEBUG 
#undef DEBUGMPDMESSAGES 

#ifdef DEBUG
#define DPRINT(x) Serial.println(x);
#else
#define DPRINT(x)
#endif

