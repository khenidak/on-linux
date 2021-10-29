# demo - 00 - exploring processes

## explore processes with ps command

```
sudo ps -auxww
```

### notice:
- pid (second column) is process id
- Process STAT field


## demo - 01 - explore process tree

```
sudo ps -aux --forest
```


### notice:

how process start each process has a parent


## demo - 02 - use proc fs

> don't worry about proc fs details, we are covering this next session (File Systems)


```
sudo ls -lah /proc/$$ # $$ is current process id (where do you think it points to?)
```

### notice
- the cwd,root and exe are sylinks


## demo - 03 - scriptable proc fs

```
./crawl-ps-tree.sh
```


as an additional exercise check out the content of an elf file. this https://linux-audit.com/elf-binaries-on-linux-understanding-and-analysis/ has a lot more details

## demo - 03 - limits
check limits of your system
```
ulimit -aH # all hard limits
ulimit -aS # all soft limit
```

to check limits applied on your shell process
```
cat /proc/$$/limits
```

## demo - 04 -- caps

run
```
## or for pid
cat /proc/$$/status | grep Cap

## decode
cat /proc/$$/status | grep Cap | xargs -I {} echo {} | awk '{print $2}'| xargs -I {} capsh --decode={}

## you can also do
capsh --print
```

> `inherited` v `permitted` v `effective` v `bound` v `ambient` is discussed in a different session

