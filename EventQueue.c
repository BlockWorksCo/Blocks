//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//




#include "Platform.h"
#include "Utilities.h"
#include "Queue.h"
#include "EventQueue.h"

DECLARE_QUEUE( HandlerQueue, Handler, 16);


void Call( Handler handler )
{
    HandlerQueuePut( handler );
}


void DispatchHandlers()
{
    Handler     handler;

    do
    {
        handler = HandlerQueueGet( 0 );
        if( handler != 0 )
        {
            handler();
        }

    } while( handler != 0 );
}



