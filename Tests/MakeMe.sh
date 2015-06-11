

gcc -std=c99 -o EventQueueTests -I../ EventQueueTests.c ../BlockedEvents.c ../PredicatedEvents.c ../TimedEvents.c ../EventQueue.c ../Utilities.c ../KeyValueStore.c ../PersistentStorage.c ../FileStorage.c

#gcc -std=c99 -o ResourceSharingTests -I../ ResourceSharingTests.c ../BlockedEvents.c ../PredicatedEvents.c ../TimedEvents.c ../EventQueue.c ../Utilities.c ../KeyValueStore.c ../PersistentStorage.c ../FileStorage.c

#gcc -std=c99 -o I2CTests -I../ I2CTests.c ../BlockedEvents.c ../PredicatedEvents.c ../TimedEvents.c ../EventQueue.c ../Utilities.c ../I2CMaster.c

#gcc -std=c99 -o UARTTests -I../ UARTTests.c ../BlockedEvents.c ../PredicatedEvents.c ../TimedEvents.c ../EventQueue.c ../Utilities.c ../UARTTransmitter.c ../UARTReceiver.c

#gcc -std=c99 -o HashTableTests -I../ HashTableTests.c  ../UnitTest.c ../Utilities.c ../HashTable.c

