//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//



#include "EventQueue.h"
#include "BlockedEvents.h"
#include "PredicatedEvents.h"
#include "TimedEvents.h"
#include "I2CMaster.h"
#include "Queue.h"
#include "Platform.h"
#include "Utilities.h"










void Tick()
{
    static uint32_t    i = 0;
    DPRINTF("Tick(%d).\n",i);
    i++;
}




void ReadStopComplete()
{
    DPRINTF("Read Complete.\n");    
}

bool byteReceived(uint8_t value)
{
    DPRINTF("<---- %02x\n",value);
    return true;
}

void ReadComplete()
{
    Stop( ReadStopComplete );    
}

void StartRead()
{
    DPRINTF("StartRead.\n");    
    Read( byteReceived, 3, ReadComplete );
}

int8_t  data[] = {0xff,0xa5,0x81};

void StopComplete()
{
    DPRINTF("Write Complete.\n");    
    CallAfter_ms(StartRead, 500);
}

void WriteComplete()
{
    Stop( StopComplete );
}


int main()
{
    CallEvery_ms( Tick, 1000 );

    Write( &data[0], NUMBER_OF_ELEMENTS(data), WriteComplete );
    CallEvery_ms( I2CDisplay, 1 );
    CallEvery_ms( i2cISR, 4 );

    while(true)
    {
        CheckTimedEventHandlers();
        CheckBlockedEventHandlers();
        CheckPredicatedEventHandlers();
        DispatchHandlers();
    }
}


