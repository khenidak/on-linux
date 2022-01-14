# build server

The example is a simple epoll loop that reads from n sockets. You can extend it for write too.

```
gcc main.c -o server
```

# run server

```
./server 5505
```

run test clients by running multiple concurrent

```
 echo $(date) | nc localhost 5505
```

