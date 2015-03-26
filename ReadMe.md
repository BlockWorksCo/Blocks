

BlockWorks 
----------
Blocks is a set of small, finey crafted, composable blocks for embedded systems. It is intended that these blocks be
picked and modified as appropriate.
Broadly, the areas that are covered are:
- Abstractions and softwae implementations of bus drivers and commnications devices, i.e. I2C, SPI, UART, CAN.
- Common storage structures; Logging, KeyValueStore.
- State Machine and event dispatch mechanism; EventQueue, *Events.
- Test running and reporting mechanism.

Blocks
------

- Queue; Multipurpose, static queue.
- Hash Table.

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
- GPIB;

- UnitTest;


Relationships
-------------


EventQueue          <---- BlockedEvents, PredicatedEvents, TimedEvents
UARTReceiver        <---- Debugger
UARTTransimtter     <---- Debugger
PersistentStorage   <---- LogStorage, KeyValueStore.




