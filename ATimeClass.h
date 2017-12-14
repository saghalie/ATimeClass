/*
**   Filename: ATimeClass.h
**
**   Author: Troy E Bouchard
**
**   Header Module for Amiga Time Class
**
**   Copyright © 2005, TroyB Software, All Rights Reserved.
**
**   C++ Amiga Time Class.
**
**   Description:
**	The C++ Amiga Time Class is freeware.  This means that you can use these
**	routines in any program that you wish, you just have to give me credit
**	somewhere in the documents.  And an acknowledgement email that I'm a guy
**	with a vision (money helps too). ;)
**
**	I believe that this class will help reduce the amount of time YOU have to
**	think up of some type of routine for displaying the time.  All routines in
**	ATimeClass.cpp should be self explanitory.
*/

#ifndef ATIME_CPP_H
#define ATIME_CPP_H

extern "C" {
   #include <exec/types.h>
   #include <exec/ports.h>
   #include <intuition/intuition.h>
   #include <libraries/dos.h>
   #include <devices/timer.h>
   #include <clib/exec_protos.h>
   #include <clib/dos_protos.h>

   #include "stdio.h"
   #include "stdlib.h"
   #include "time.h"
}

class ATimeClass
{
   public:
      ATimeClass();	       // Constructor
      ~ATimeClass();	       // Destructor

      char * DisplaySysTime(); // Display system time in WeekDay Month Day H:M:S Year format
      char * DisplayGmtTime(); // Display the Greenwich Mean Time (GMT) in WeekDay Month Day H:M:S year format
      char * Display2DTime();  // same as system time but with a 2 digit year (05) ...
      char * DisplayHMSTime(); // Display Hour Minutes Seconds
      char * DisplayHMTime();  // Display Hour Minutes
      char * DisplayHTime();   // Display Hour
      char * DisplayMTime();   // Display Minutes
      char * DisplaySTime();   // Display Seconds

// NOT TESTED
      char * TimeTicks();      // Display time with seconds ticking off.  Use with IDCMP
      long CloseTimeTicks();   // Close the time ticker.

   private:
      long t;
      tm *p;
      char date[25];
      MsgPort * Timer_Port;
      timerequest Time_Req;
};

#endif // ATIME_CPP_H
