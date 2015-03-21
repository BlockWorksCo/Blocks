//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//




#include "Debugger.h"


//
//
//
typedef enum
{
    Identify,
    MemoryRead,
    MemoryWrite,
    Restart,
    Continue,
    RegistersRead,
    RegistersWrite,

} DebuggerCommand;



//
//
//
DebuggerCommand GetCommand()
{
    return Continue;
}



//
// Only return on a "Continue" command.
//
void debugger()
{
    bool        continueFlag    = false;

    //
    //
    //
    while( continueFlag == false )
    {
        DebuggerCommand     command     = GetCommand();

        switch(command)
        {
            case MemoryRead:
                break;

            case MemoryWrite:
                break;

            case Restart:
                break;

            case Continue:
                continueFlag    = true;
                break;

            case RegistersRead:
                break;

            case RegistersWrite:
                break;

            default:
                break;
        }
    }
}





