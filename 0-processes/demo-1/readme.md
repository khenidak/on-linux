## demo - 10 -  syscalls

explore the ultra basic hello-world

```
cd ./0-processes/demo-1/hello-world
cat ./hello-world.c
```

how many syscall do you think this program will do?

build it

```
gcc program.c -o ./program
```

you can test where the program spent its time using

```
time ./program
```

because the program spent very little time in kernel space you get 0.0s in system. That *does not* mean the program didn't spent time in kernel space. try running

```
strace ./program
```

the output contains all the syscalls executed by this running process



## demo - 11 - setuid

build and run the program

```
cd 0-processes/demo-1/setuid/
gcc ./program.c -o program
```

get the user by its id

```
id -nu 1000
```


Now change the owner of the file
```
sudo chown root ./program
```

then set the sticky bit (allows a program to run with the user who created the binary)

```
sudo chmod u+s ./program
```

rerun the program



