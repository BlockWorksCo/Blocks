//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//

#include "HashTable.h"
#include "Utilities.h"



void main()
{
    HashTablePut( 123, "Hello World" );
    HashTablePut( 567, "Goodbye Mars" );
    HashTablePut( 789, "Is that Jupiter?" );

    DPRINTF("%s\n", (char*)HashTableGet( 567, "!!" ) );
    DPRINTF("%s\n", (char*)HashTableGet( 123, "!!" ) );
    DPRINTF("%s\n", (char*)HashTableGet( 789, "!!" ) );
}


