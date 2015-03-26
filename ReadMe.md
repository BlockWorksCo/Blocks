

BlockWorks 
----------

Blocks
------

- Queue; Multipurpose, static queue.

- EventQueue; General purpose function call queue.
- BlockedEvents;
- PredicatedEvents;
- TimedEvents;

- Debugger;

- FileStorage;
- KeyValueStore;
- LogStorage; General purpose, append-only storage of fixed-size blocks.
- PersistentStorage; Abstraction of a FLASH-type storage system, fixed-size blocks.

- I2CMaster; I2C s/w master, uses two GPIO pins.
- UARTReceiver; UART s/w transmitter, uses a GPIO pin.
- UARTTransmitter; UART s/w receiver, uses a GPIO pin.
- SPI master;
- SPI receiver;
- CAN

- Platform;
- Utilities;

- Framebuffer;
- Font;
- TextDisplay;

- MODBUS RTU;
- MODBUS ASCII;
- HART;
- NMEA;
- PPP;

- UnitTest;


Relationships
-------------


EventQueue          <---- BlockedEvents, PredicatedEvents, TimedEvents
UARTReceiver        <---- Debugger
UARTTransimtter     <---- Debugger
PersistentStorage   <---- LogStorage, KeyValueStore.




