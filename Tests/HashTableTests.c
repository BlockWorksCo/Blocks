//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//

#include "HashTable.h"
#include "Utilities.h"
#include "UnitTest.h"



void Test1()
{
    HashTablePut( 123, 0x1234abcd );
    HashTablePut( 567, 0xabcd1234 );
    HashTablePut( 789, 0x01234567 );

    Assert( HashTableGet( 567, 0xffffffff ) == 0xabcd1234, "Key 567 value" );
    Assert( HashTableGet( 123, 0xffffffff ) == 0x1234abdd, "Key 123 value" );
    Assert( HashTableGet( 789, 0xffffffff ) == 0x01234567, "Key 789 value" );
}


void Test2()
{
    HashTablePut( 123, 0x1234abcd );
    HashTablePut( 567, 0xabcd1234 );
    HashTablePut( 789, 0x01234567 );

    Assert( HashTableGet( 567, 0xffffffff ) == 0xabcd1234, "Key 567 value" );
    Assert( HashTableGet( 123, 0xffffffff ) == 0x1234abcd, "Key 123 value" );
    Assert( HashTableGet( 789, 0xffffffff ) == 0x01234567, "Key 789 value" );
}


void main()
{
    AddTest( "Test1", Test1 );
    AddTest( "Test2", Test2 );
    RunTests( "HashTable tests" );
}


