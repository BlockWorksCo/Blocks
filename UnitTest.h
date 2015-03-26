//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//



#ifndef __UNITTEST_H__
#define __UNITTEST_H__


#include "Platform.h"

#define MAX_TESTS           (16)


//
//
//
typedef void (*TestFunction)();


//
//
//
void AddTest( char* name, TestFunction fn );
void RunTests( char* suiteName );

void AssertEqual( bool test, char* message );


#endif


