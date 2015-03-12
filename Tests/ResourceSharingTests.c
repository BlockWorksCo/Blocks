
// ResourceSharingTest.c --------------------------------------------------------------------------------


typedef struct
{
    uint8_t*    dataIn;
    uint8_t*    dataOut;
    uint8_t     cs;
    uint8_t     numberOfBytesToTransfer;
    Handler     completionHandler;

} TransferRequest;

DECLARE_QUEUE( TransferRequestQueue, TransferRequest, 16);

TransferRequest     currentRequest;
TransferRequest     nullRequest = 
{
    .dataIn                  = 0, 
    .dataOut                 = 0, 
    .numberOfBytesToTransfer = 0, 
    .completionHandler       = 0
};

void TransferFinished();

void PollRequestQueue()
{
    currentRequest  = TransferRequestQueueGet( nullRequest );
    if( currentRequest.numberOfBytesToTransfer != 0 )
    {
        //
        // Simulate a real transfer, will be called via ISR in reality.
        //
        CallAfter_ms( TransferFinished, 100 );        
    }    
}

void TransferFinished()
{
    printf("<TransferFinished>\n");
    Call( currentRequest.completionHandler );

    PollRequestQueue();
}

void PerformTransfer( uint8_t* dataIn, uint8_t* dataOut, uint8_t numberOfBytesToTransfer, Handler completionHandler )
{
    TransferRequest     request     = 
    {
        .dataIn                  = dataIn, 
        .dataOut                 = dataOut, 
        .numberOfBytesToTransfer = numberOfBytesToTransfer, 
        .completionHandler       = completionHandler
    };

    TransferRequestQueuePut( request );

    PollRequestQueue();
}
























void TransferComplete()
{
    printf("TransferComplete\n");
}

void Tock()
{
    printf("Tock.\n");

    static uint8_t  in[8];
    static uint8_t  out[8];

    PerformTransfer( &in[0], &out[0], 8, TransferComplete );
}

void Tick()
{
    static uint32_t    i = 0;
    printf("Tick(%d).\n",i);
    i++;

    CallAfter_ms( Tock, 250 );
    seconds++;
}
