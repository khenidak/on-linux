# demo - 00 - a tour around blkdev


to list all blk devices use

```
lsblk
```

this command lists all the blkdev (and their partitions) available on the system. Note:
1. devices don't need to be mounted/formatted, these are the devices that are *plugged* in the system
2. notice the major:minor (and also where minor is assigned for partitions - same major)


pick one of the block devices and do 

```
cat /sys/block/<device>/queue/scheduler
```

this will tell you 1) all the schedulers in the system and which one is assigned to this block device. Note that scheduler works on all partitions (you can not select scheduler per partition).


files that identifies write back throttling are wbt_lat_usec and wb_window_usec. Other files that identify sector, max, min etc are there in .../queue this https://www.kernel.org/doc/html/latest/block/queue-sysfs.html covers them in good details

# demo - 01 - file attributes

> it is unlikely that your file system has xattr. Unless you have enabled and correctly configured
selinux. for reference to use shell to get xattrs use

```
getfattr -d -m
```

to get standard attributes (which are available for any file on any file system)

```
stat <file>
```

notice the inode number, the file type the blocks. The device is hex and decimal encoded major:minor

try the following 

```
stat /dev/<one of the devices>
```

can you tell the difference?

let us test this with symlinks and hard links

```
cd /tmp
echo "Hello, World!" >> ./hello
stat ./hello # take a note of the inode #
# symlink
ln -s ./hello h_s
stat h_s # notice how they carry different inode #?
# hardlink
ln  ./hello h_h
stat h_h # notice how it uses the same inode # as the original file 
```

# demo - 02 - file systems

One of the way to learn about inode stats for file system is 
```
df -i /dev/<blkdev>
```

you can also get superblock by

```
dumpe2fs -h /dev/<blkdev>
# if you want to learn where they -super blocks - are saved
sudo dumpe2fs /dev/sda | grep -i superblock
```

dropping dentry and inode cache can be done via

```
echo 2 > /proc/sys/vm/drop_caches
```

running `slabtop` will get you all the information about how big inode/dentry caches are


understanding your i/o utilization/latency
run
```
iostat -x -p <dev>
```

The output is explained here: https://manpages.debian.org/testing/sysstat/iostat.1.en.html -- FYI: the tool parses /sys/block/<dev>/stat
