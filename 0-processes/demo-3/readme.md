## demo - 31 - memory maps

the reader/writer are basic producer consumer using a mapped memory as a communication medium

build and run the writer

```
gcc -Wall writer.c -o writer -lrt # need to link to rt posix extention
./writer
```

writer created a named shared memory object that consists of two unsigned longs. one is used
for locking (with compare and swap call) the other is used as simple counter.

build and run the reader

```
gcc -Wall reader.c -o reader -lrt
./reader
```

reader tries to open an existing shared memory object map it to its own memory and read the counter with lock.

> in theory we don't need the lock since it is an x64 and we are well under the boundaries of torn read/write. *but* it is always a good idea to have a lock around shared objects.



## demo - 32 - shared memory as storage

1. stop both reader and writer.
2. init the counter from the shared memory instead of `0`.
3. build and run the writer
4. stop the writer
5. run it again

shared memory objects life cycle is detached from the process that created it. This include the data that sets in this memory.

