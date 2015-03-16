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



int8_t  data[] = {0,1,2};

void WriteComplete()
{
    DPRINTF("Write Complete.\n");
}


int main()
{
    CallEvery_ms( Tick, 500 );

    Write( &data[0], NUMBER_OF_ELEMENTS(data), WriteComplete );
    CallEvery_ms( i2cISR, 1 );

    while(true)
    {
        CheckTimedEventHandlers();
        CheckBlockedEventHandlers();
        CheckPredicatedEventHandlers();
        DispatchHandlers();
    }
}


