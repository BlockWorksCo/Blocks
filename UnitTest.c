//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//



#include "UnitTest.h"
#include "Platform.h"
#include "Utilities.h"


//
//
//
typedef struct
{
    TestFunction    fn;
    char*           name;

} TestTableEntry;

TestTableEntry  testTable[MAX_TESTS]    = {0};



//
//
//
void AddTest( char* name, TestFunction fn )
{
    for(uint8_t i=0; i<NUMBER_OF_ELEMENTS(testTable); i++)
    {
        if(testTable[i].fn == 0)
        {
            testTable[i].fn     = fn;
            testTable[i].name   = name;
            return;
        }
    }

    PANIC();
}




void Assert( bool test, char* message )
{
    if( test == false )
    {
        DPRINTF("\t\t<failure name=\"%s\" classname=\"main\" time=\"1\">\r\n", message );
            DPRINTF("\t\t\t<system-out></system-out>\r\n");
            DPRINTF("\t\t\t<system-err></system-err>\r\n");
        DPRINTF("\t\t</failure>\r\n");
    }
}


//
//
//
void RunTests( char* suiteName )
{
    uint8_t     testCount   = 3;

    DPRINTF("<testsuite tests=\"%d\" name=\"%s\">\r\n", testCount, suiteName );
    for(uint8_t i=0; i<NUMBER_OF_ELEMENTS(testTable); i++)
    {
        if(testTable[i].fn != 0)
        {
            DPRINTF("\t<testcase name=\"%s\" >\n", testTable[i].name );
            testTable[i].fn();
            DPRINTF("\t</testcase>\r\n");
        }
    }
    DPRINTF("</testsuite>\r\n");
}



