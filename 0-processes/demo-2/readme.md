## demo - 20 - memory allocation

build the program
```
gcc -Wall ./program.c -o program
```


whenever it asks you check memory run (on a separate session): `ps aux | grep -E '(USER|program)'`

while the program is running run `cat /proc/<pid>/maps` to explore the memory map for this process. this has a lot more details https://gist.github.com/CMCDragonkai/10ab53654b2aa6ce55c11cfc5b2432a4

the key finding:
each row is a memory with the following:
start-end-offsets {permission} {file map offset if applicable} {device if file mapped} {inode if file mapped} {path}


vdso = virtual dynamic shared object (kernel)
vsyscall = unprivileged syscall (that does not require raising irq) such as gettimeofday();
vvar = variables declared by kernel visible in userspace.


note: while we allocate memory in unaligned bytes. memory works in pages. os page size can be identified by `getconf PAGESIZE`
