//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//




#include "I2CMaster.h"
#include "Platform.h"
#include "Utilities.h"
#include "EventQueue.h"




bool            sda                                 = false;
bool            sdaDriven                           = false;
bool            scl                                 = false;


void SET_SDA()
{
    sda = true;
}

void CLEAR_SDA()
{
    sda = false;
}

void DRIVE_SDA()
{
    sdaDriven = true;
}

void FLOAT_SDA()
{
    sdaDriven = false;
}

bool GET_SDA()
{
    return sda;
}

void SET_SCL()
{
    scl = true;
}

void CLEAR_SCL()
{
    scl = false;
}













void WriteEngine();
void ReadEngine();
void StopEngine();



typedef enum
{
    Transmitting,
    Receiving,
    Stopping,
    Idle,

} I2CMasterState;


#define    maxBytesToTransmit 64

I2CMasterState  masterState                         = Idle;
uint32_t        nextEdgeTime                        = 0;
bool            nextValue                           = 0;
uint8_t         dataToTransmit[maxBytesToTransmit]  = {0};
uint8_t         acksForBytes[maxBytesToTransmit]    = {0};
uint8_t         numberOfBytesToTranfer              = 0;
uint8_t         state                               = 0;
bool            transferFinished                    = true;
Handler         completionEvent                     = 0;
uint8_t*        bytes                               = 0;




//
//
//
void Write(uint8_t* _bytes, uint8_t _numberOfBytes, Handler _completionCallback )
{
    completionEvent     = _completionCallback;
    masterState         = Transmitting;
    state               = 0;

    numberOfBytesToTranfer  = _numberOfBytes;
    bytes                   = _bytes;
}

//
//
//
void Read( void (*_byteReceivedCallback)() , Handler _completionCallback )
{
    completionEvent     = _completionCallback;        
    masterState         = Receiving;
    state               = 0;

    numberOfBytesToTranfer  = 0;
}

//
//
//
void Stop( Handler _completionCallback )
{
    completionEvent     = _completionCallback;        
    masterState         = Stopping;
    state               = 0;
}















//
// Called at regular intervals to transmit an I2C bus protocol.
//
void WriteEngine()
{
    const uint8_t   numberOfStartStates     = 3;
    const uint8_t   numberOfStopStates      = 3;
    const uint8_t   numberOfBitsPerByte     = 8+1;                      // data+ACK.
    const uint8_t   numberOfStatesPerByte   = numberOfBitsPerByte*2;    // lo clock & hi clock.


    if(state == 0)
    {
        //
        // Start condition.
        //
        DRIVE_SDA();
        SET_SDA();
        SET_SCL();
    }
    else if(state == 1)
    {
        //
        // Start condition.
        //
        CLEAR_SDA();
    }
    else if(state == 2)
    {
        //
        // Start condition.
        //
        SET_SCL();
    }
    else if( state < (numberOfBytesToTranfer*numberOfStatesPerByte)+numberOfStartStates )
    {
        uint8_t             byteIndex   = (state-3)/(2*9);
        uint8_t             byte        = dataToTransmit[ byteIndex ];
        volatile uint8_t    bitInByte   = (state - ((byteIndex*numberOfStatesPerByte) + numberOfStartStates)) / 2;

        //
        // Set the data/clock lines as appropriate.
        //
        if( (state%2) != 0)
        {
            CLEAR_SCL();        // bring clock down before setting new data.

            if(bitInByte == 8)
            {
                FLOAT_SDA();
            }
            else
            {
                volatile uint8_t bitValue = byte&(0x80>>bitInByte);
                if( bitValue != 0 )
                {
                    SET_SDA();
                }
                else
                {
                    CLEAR_SDA();
                }

            }
        }
        else
        {
            SET_SCL();

            if(bitInByte == 8)
            {
                acksForBytes[byteIndex] = GET_SDA();         // detect ACK.                                
            }
        }
    }
    else
    {
        Call( completionEvent );
        masterState     = Idle;
    }

    state++;
}

//
// Called at regular intervals to transmit an I2C bus protocol.
//
void ReadEngine()
{
    const uint8_t   numberOfStartStates     = 3;
    const uint8_t   numberOfStopStates      = 3;
    const uint8_t   numberOfBitsPerByte     = 8+1;                      // data+ACK.
    const uint8_t   numberOfStatesPerByte   = numberOfBitsPerByte*2;    // lo clock & hi clock.

    if(state == 0)
    {
        //
        // Start condition.
        //
        DRIVE_SDA();
        SET_SDA();
        SET_SCL();
    }
    else if(state == 1)
    {
        //
        // Start condition.
        //
        SET_SDA( false );
    }
    else if(state == 2)
    {
        //
        // Start condition.
        //
        CLEAR_SCL();
        FLOAT_SDA();
    }
    else if( state < (numberOfBytesToTranfer*numberOfStatesPerByte)+numberOfStartStates )
    {
        uint8_t         byteIndex   = (state-3)/(2*9);
        static uint8_t  byte        = 0;
        uint8_t         bitInByte   = (state - ((byteIndex*numberOfStatesPerByte) + numberOfStartStates)) / 2;

        //
        // Reset the byte.
        //
        if(byteIndex == 0)
        {
            byte = 0;
        }

        //
        // Set the data/clock lines as appropriate.
        //
        if( (state%2) != 0)
        {
            CLEAR_SCL();        // bring clock down before setting new data.

            if(bitInByte == 8)
            {
                CLEAR_SDA();   // ack.
            }
        }
        else
        {
            SET_SCL();

            // TODO: Wait a bit to settle....

            bool bit = GET_SDA();
            if(bit == true)
            {
                bit     |= (1<<bitInByte);
            }
        }
    }
    else
    {
        Call( completionEvent );
        masterState     = Idle;
    }

    state++;
}


//
// Called at regular intervals to transmit an I2C bus protocol.
//
void StopEngine()
{
    const uint8_t   numberOfStartStates     = 3;
    const uint8_t   numberOfStopStates      = 3;
    const uint8_t   numberOfBitsPerByte     = 8+1;                      // data+ACK.
    const uint8_t   numberOfStatesPerByte   = numberOfBitsPerByte*2;    // lo clock & hi clock.

    if( state == 0 )
    {
        //
        // Stop condition 0
        //
        DRIVE_SDA();
        CLEAR_SCL();
        CLEAR_SDA();
    }
    else if( state == 1 )
    {
        //
        // Stop condition 1
        //
        SET_SCL();
    }
    else if( state == 2 )
    {
        //
        // Stop condition 2
        //
        SET_SDA();
    }
    else
    {
        //
        // No more.
        //
        SET_SDA();
        SET_SCL();
        transferFinished = true;

        Call( completionEvent );
        masterState     = Idle;
    }

    state++;
}















//
//
//
void ISR()
{
    switch( masterState )
    {
        case Transmitting:
            WriteEngine();
            break;

        case Receiving:
            ReadEngine();
            break;

        case Stopping:
            StopEngine();
            break;

        case Idle:
            break;

        default:
            PANIC();
            break;
    }
}

