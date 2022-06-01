#ifndef _DEBUG_H_
#define _DEBUG_H_

// place DEBUG_DO anywhere in the code to 
// enable debug output to stderr
// enable debug output by using -DDEBUG on compilation
// RIGHT NOW IT LOOKS LIKE __VA_ARGS__ CAN 
// BE USED AS A SUBSTITUTE FOR ANY COMMAND
// AS STATED!!!

#ifdef DEBUG
#define DEBUG_DO(...) __VA_ARGS__
#else
#define DEBUG_DO(...) // nothing to see here!
#endif


#endif
