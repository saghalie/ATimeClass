/*
**   Filename: ATimeClass.cpp
**
**   Author: Troy E Bouchard
**
**   DESC: C++ Module for Amiga Time Class
**
**   Copyright © 2005, Troy E Bouchard, All Rights Reserved.
**
**   C++ Amiga Time Class.
**
**   Description:
**	I created all these classes because I wanted to
**	keep it simple.  I could have created one routine
**	and made the programer create work arounds for
**	hours minutes seconds displays (and dates) but I
**	thought that this would be alot simpler for everyone.
**	Including me!
*/

#include "ATimeClass.h"

// Constructor
ATimeClass::ATimeClass()
{
   return;
}

// Destructor
ATimeClass::~ATimeClass()
{
   return;
}

// Display the System Time
char * ATimeClass::DisplaySysTime()
{
   time(&t);
   return ctime(&t);
}

// Display the System time in GMT format
char * ATimeClass::DisplayGmtTime()
{
   time(&t);
   p = gmtime(&t);
   return asctime(p);
}

// display Day of Week, Month, Day, Year in xx format and time in hours:minutes:seconds.
char * ATimeClass::Display2DTime()
{
   time(&t);
   p = localtime(&t);
   strftime(date, sizeof(date)-1, "%a %b %d %y %H:%M:%S ", p);
   return date;
}

// display Hours Minutes Seconds
char * ATimeClass::DisplayHMSTime()
{
   time(&t);
   p = localtime(&t);
   strftime(date, sizeof(date)-1, "%H:%M:%S ", p);
   return date;
}

// display Hours Minutes
char * ATimeClass::DisplayHMTime()
{
   time(&t);
   p = localtime(&t);
   strftime(date, sizeof(date)-1, "%H:%M ", p);
   return date;
}

// display Hours
char * ATimeClass::DisplayHTime()
{
   time(&t);
   p = localtime(&t);
   strftime(date, sizeof(date)-1, "%H ", p);
   return date;
}

// display Minutes
char * ATimeClass::DisplayMTime()
{
   time(&t);
   p = localtime(&t);
   strftime(date, sizeof(date)-1, "%M ", p);
   return date;
}

// display Seconds
char * ATimeClass::DisplaySTime()
{
   time(&t);
   p = localtime(&t);
   strftime(date, sizeof(date)-1, "%S ", p);
   return date;
}

// **
// ** NOT TESTED
// ** This will display the date/time with the seconds ticking off...
// ** needs to be handled with IDCMP/PORT. <-??
// **
char * ATimeClass::TimeTicks()
{
   strftime(date, sizeof(date)-1, "%a %b %d, %Y  %H:%M:%S ", p);

   Time_Req.tr_node.io_Message.mn_ReplyPort = Timer_Port;
   Time_Req.tr_node.io_Command = TR_ADDREQUEST;
   Time_Req.tr_node.io_Flags = 0;
   Time_Req.tr_node.io_Error = 0;

   Time_Req.tr_time.tv_secs  = 0 ;
   Time_Req.tr_time.tv_micro = 250000 ;
   SendIO(&Time_Req.tr_node);

   return date;
}

// **
// ** NOT TESTED
// ** Works in conjuction with TimeTicks() above
// **
long ATimeClass::CloseTimeTicks()
{
   if(Time_Req.tr_node.io_Message.mn_ReplyPort)
   {
	if(!CheckIO(&Time_Req.tr_node)) AbortIO(&Time_Req.tr_node);
	CloseDevice((struct IORequest *)&Time_Req);
   }

   if(Timer_Port)
   {
      DeleteMsgPort(Timer_Port);
      Timer_Port = NULL;
   }

   return 0L;
}
