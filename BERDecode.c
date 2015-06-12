//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//

#include "Platform.h"

//
//
//
typedef enum
{
    Universal           = 0x0,
    Application         = 0x1,
    ContextSpecific     = 0x2,
    Private             = 0x3,

} BERClass;

//
//
//
typedef enum
{
    Primitive           = 0x0,
    Constructed         = 0x1,

} BERContent;


//
//
//
typedef enum
{
    EndOfContent        = 0,
    BOOLEAN             = 1,
    INTEGER             = 2,
    BITSTRING           = 3,
    OCTETSTRING         = 4,
    NULLTag             = 5,
    OBJECTIDENTIFIER    = 6,
    ObjectDescriptor    = 7,
    EXTERNAL            = 8,
    REAL                = 9,
    ENUMERATED          = 10,
    EMBEDDEDPDV         = 11,
    UTF8String          = 12,
    RELATIVEOID         = 13,
    SEQUENCEOF          = 16,
    SETOF               = 17,
    NumericString       = 18,
    PrintableString     = 19,
    T61String           = 20,
    VideotexString      = 21,
    IA5String           = 22,
    UTCTime             = 23,
    GeneralizedTime     = 24,
    GraphicString       = 25,
    VisibleString       = 26,
    GeneralString       = 27,
    UniversalString     = 28,
    CHARACTERSTRING     = 29,
    BMPString           = 30,
    LongForm            = 31,

} BERTag;



//
//
//
typedef struct
{
    uint8_t*    stream;

} BERDecodeContext;



//
//
//
void berDecode( BERDecodeContext* context )
{
    BERClass    classType      = (BERClass)   ((context->stream[0] & 0xc0) >> 6);
    BERContent  contentType    = (BERContent) ((context->stream[0] & 0x20) >> 5);
    BERTag      tagType        = (BERTag)     ((context->stream[0] & 0x1f) >> 5);

    switch( classType )
    {
        case Universal:
            break;
            
        case Application:
            break;
            
        case ContextSpecific:
            break;
            
        case Private:
            break;
            
        default:
            break;
    }

    switch( contentType )
    {
        case Primitive:
            break;
            
        case Constructed:
            break;
            
        default:
            break;
    }

}






void main()
{
    uint8_t             stream1[]   = {0x01, 0x02, 0x03, 0x04};
    BERDecodeContext    context     = {.stream=&stream1[0]};

    berDecode( &context );
}



