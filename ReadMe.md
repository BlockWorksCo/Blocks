

BlockWorks 
----------

Blocks
------

- EventQueue;
- BlockedEvents;
- Debugger;
- FileStorage;
- I2CMaster;
- KeyValueStore;
- LogStorage;
- PersistentStorage;
- PredicatedEvents;
- TimedEvents;
- UARTReceiver;
- UARTTransmitter;
- Utilities;



Relationships
-------------


EventQueue          <---- BlockedEvents, PredicatedEvents, TimedEvents
UARTReceiver        <---- Debugger
UARTTransimtter     <---- Debugger
PersistentStorage   <---- LogStorage, KeyValueStore.




