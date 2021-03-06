//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//


#include "KeyValueStore.h"
#include "FileStorage.h"

KeyValueData keyValueData;

void KeyValueStoreBackedUp()
{
}

void KeyValueStoreErased()
{
    WriteFileBlock( 1, 0, (uint8_t*)&keyValueData, sizeof(keyValueData), KeyValueStoreBackedUp );
}

void KeyValueStoreWritten( uint32_t key )
{
    //
    // Write to persistent storage.
    // alteratively, can just write the individual value...
    //
    EraseFileBlock( 1, 0, KeyValueStoreErased );
}

bool KeyValueValidate( Key key, void* _value )
{
    bool    returnValue     = false;

    switch( key )
    {
        case Value1:
            uint32_t*   value   = (uint32_t*)_value;
            if( (*value >= 0) && (*value < 10) )
            {
                returnValue     = true;
            }

        default:
            PANIC();
            break;
    }

    return returnValue;
}