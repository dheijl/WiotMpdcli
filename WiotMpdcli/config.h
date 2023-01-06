#pragma once

#define DEBUG 1
#undef DEBUGMPDMESSAGES 

#ifdef DEBUG
#define DPRINT(x) Serial.println(x);
#else
#define DPRINT(x)
#endif