//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//



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
EndOfContent        P   0   0
BOOLEAN             P   1   1
INTEGER             P   2   2
BITSTRING           P/C 3   3
OCTETSTRING         P/C 4   4
NULL                P   5   5
OBJECTIDENTIFIER    P   6   6
ObjectDescriptor    P/C 7   7
EXTERNAL            C   8   8
REAL                P   9   9
ENUMERATED          P   10  A
EMBEDDED PDV        C   11  B
UTF8String          P/C 12  C
RELATIVE-OID        P   13  D
(reserved)          -   14  E
(reserved)          -   15  F
SEQUENCEOF          C   16  10
SETOF               C   17  11
NumericString       P/C 18  12
PrintableString     P/C 19  13
T61String           P/C 20  14
VideotexString      P/C 21  15
IA5String           P/C 22  16
UTCTime             P/C 23  17
GeneralizedTime     P/C 24  18
GraphicString       P/C 25  19
VisibleString       P/C 26  1A
GeneralString       P/C 27  1B
UniversalString     P/C 28  1C
CHARACTERSTRING     P/C 29  1D
BMPString           P/C 30  1E
LongForm            -   31  1F

} BERTag;






//
//
//
void berDecode(uint8_t* stream)
{
    BERClass    classType      = (BERClass)   ((stream[0] & 0xc0) >> 6);
    BERContent  contentType    = (BERContent) ((stream[0] & 0x20) >> 5);
    BERTag      tagType        = (BERTag)     ((stream[0] & 0x1f) >> 5);

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






void Test1()
{
    uint8_t     stream1[]   = {0x01, 0x02, 0x03, 0x04};

    berDecode( &stream1[0] );
}



