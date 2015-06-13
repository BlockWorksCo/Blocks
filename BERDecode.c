//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//

#include "Platform.h"
#include "Utilities.h"


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
typedef struct _BERDecodeContext
{
    uint8_t*    stream;

    void        (*handlePrimitive)( struct _BERDecodeContext*, BERClass, BERContent, BERTag, uint8_t*, uint32_t);

    void*       userContext;

} BERDecodeContext;



//
//
//
void berDecode( BERDecodeContext* context )
{
    BERClass    classType               = (BERClass)   ((context->stream[0] & 0xc0) >> 6);
    BERContent  contentType             = (BERContent) ((context->stream[0] & 0x20) >> 5);
    BERTag      tagType                 = (BERTag)     ((context->stream[0] & 0x1f) >> 5);
    uint8_t     lengthByte              = context->stream[1];
    uint32_t    numberOfBytesInContent  = 0;
    uint8_t*    content                 = 0;

    if( (lengthByte&0x80) == 0)
    {
        //
        // Short form.
        //
        numberOfBytesInContent  = lengthByte;
        content                 = &context->stream[2];
    }
    else
    {
        //
        // Long form.
        //
        uint8_t     numberOfBytesInLengthField  = lengthByte & 0x7f;
        switch(numberOfBytesInLengthField)
        {
            case 0:
                PANIC();    // Indefinite form not supported.
                break;

            case 1:
                numberOfBytesInContent  = ((uint32_t)context->stream[2]);
                content                 = &context->stream[3];
                break;

            case 2:
                numberOfBytesInContent  = ((uint32_t)context->stream[2])<<8 | ((uint32_t)context->stream[3]);
                content                 = &context->stream[4];
                break;

            case 3:
                numberOfBytesInContent  = ((uint32_t)context->stream[2])<<16 | ((uint32_t)context->stream[3])<<8 | ((uint32_t)context->stream[4]);
                content                 = &context->stream[5];
                break;

            case 4:
                numberOfBytesInContent  = ((uint32_t)context->stream[2])<<24 | ((uint32_t)context->stream[3])<<16 | ((uint32_t)context->stream[4])<<8 | ((uint32_t)context->stream[5]);
                content                 = &context->stream[6];
                break;

            default:
                PANIC();
                break;
        }
    }

    //
    //
    //
    context->handlePrimitive( context, classType, contentType, tagType, content, numberOfBytesInContent );
}
















#include <stdio.h>


//
//
//
void handlePrimitive( struct _BERDecodeContext* context, BERClass classType, BERContent contentType, BERTag tagType, uint8_t* content, uint32_t numberOfBytesInContent )
{
    printf("classType=%02x contentType=%02x tagType=%02x",classType, contentType, tagType );
    for(uint32_t i=0; i<numberOfBytesInContent; i++)
    {
        printf("(%02x) ", content[i] );
    }
    printf("\n");

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
    FILE*       inFile          = fopen("Tests/Example1.ber","rb");
    uint8_t     stream1[128]    = {0};
    fread( &stream1[0], 1,sizeof(stream1), inFile );

    //uint8_t             stream1[]   = {0x01, 0x02, 0x03, 0x04};
    BERDecodeContext    context     = 
    {
        .stream             = &stream1[0],
        .handlePrimitive    = handlePrimitive,
        .userContext        = 0,
    };

    berDecode( &context );
}



