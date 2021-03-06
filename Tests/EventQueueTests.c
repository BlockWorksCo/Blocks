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
#include "KeyValueStore.h"
#include "Platform.h"
#include "Utilities.h"


uint32_t    seconds     = 0;

void HelloWorld()
{
    DPRINTF("Hello World.\n");
}

void OneShot()
{
    DPRINTF("One shot.\n");
}



bool trigger    = false;

void PullTheTrigger()
{
    trigger     = true;
    DPRINTF("pulled the trigger...\n");
}

void Bang()
{
    DPRINTF("Bang!\n");
}



void Tock()
{
    DPRINTF("Tock.\n");
}

void Tick()
{
    static uint32_t    i = 0;
    DPRINTF("Tick(%d).\n",i);
    i++;

    CallAfter_ms( Tock, 250 );
    seconds++;
}



bool TenSecondsHavePassed()
{
    if( seconds > 10 )
    {
        return true;
    }
    else
    {
        return false;
    }
}

void BigTick()
{
    DPRINTF("*** big tick ***\n");
}

int main()
{
    Call( HelloWorld );
    CallAfter_ms( OneShot, 1000 );
    CallEvery_ms( Tick, 500 );

    CallAfter_ms( PullTheTrigger, 5000 );
    CallWhenUnblocked( Bang, &trigger );

    CallWhenPredicateIsTrue( BigTick, TenSecondsHavePassed );

    SET_KEY_VALUE( Value1, 123 );
    uint32_t temp = GET_KEY_VALUE( Value1 );

    while(true)
    {
        CheckTimedEventHandlers();
        CheckBlockedEventHandlers();
        CheckPredicatedEventHandlers();
        DispatchHandlers();
    }
}
