//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//


#include <stddef.h>


#define DECLARE_KEY_VALUE_STORAGE( type, name )     type name##Storage
#define DECLARE_KEY( name )                         name = offsetof( KeyValueData, name##Storage )
#define SET_KEY_VALUE( key, value )                 keyValueData.key##Storage = value;KeyValueStoreWritten(key)
#define GET_KEY_VALUE( key )                        keyValueData.key##Storage 

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

