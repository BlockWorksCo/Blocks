

gcc -std=c99 -o EventQueueTests -I../ EventQueueTests.c ../BlockedEvents.c ../PredicatedEvents.c ../TimedEvents.c ../EventQueue.c ../Utilities.c ../KeyValueStore.c ../PersistentStorage.c ../FileStorage.c



gcc -std=c99 -o ResourceSharingTests -I../ ResourceSharingTests.c ../BlockedEvents.c ../PredicatedEvents.c ../TimedEvents.c ../EventQueue.c ../Utilities.c ../KeyValueStore.c ../PersistentStorage.c ../FileStorage.c


