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




void AssertEqual( bool test, char* message )
{
    DPRINTF("\t\t<Assertion name=\"%s\">\r\n", message );
    DPRINTF("\t\t\t<Result>\r\n");
    if( test == false )
    {
        DPRINTF("\t\t\t\tFAIL\r\n");
    }
    else
    {
        DPRINTF("\t\t\t\tPASS\r\n");
    }
    DPRINTF("\t\t\t</Result>\r\n");
    DPRINTF("\t\t</Assertion>\r\n");
}


//
//
//
void RunTests( char* suiteName )
{
    DPRINTF("<TestSuite Name=\"%s\">\r\n", suiteName );
    for(uint8_t i=0; i<NUMBER_OF_ELEMENTS(testTable); i++)
    {
        if(testTable[i].fn != 0)
        {
            DPRINTF("\t<Test Name=\"%s\" >\n", testTable[i].name );
            testTable[i].fn();
            DPRINTF("\t</TestSuite>\r\n");
        }
    }
    DPRINTF("</TestSuite>\r\n");
}



