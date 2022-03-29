# Week 10 File Systems

## Disk Topology
- blocks are not byte addressable (read/written block at a time)
- even modern SSDs keep this organization
- How to store data on a disk in a meaningful form?

## File Systems
- a filesystem is essentially an index that allows us to have the abstraction of files and directories

## What is a file?
- File is data (array of bytes) with some properties:
  - contents, size, owner, last read time, permission bits, etc

- File can have a type, which can be ecnoded either in the name or the contents
  - Windows encode type in name
    - `.exe` `.bat` `.txt`
  - Unix encodes type in contents
    - magic numbers, initial characters, etc

## Unix file operations
- `unlink()` is delete


> File itself does not know its name or path. File can be multiply linked in multiple directories with multiple names. Directory knows the name.

> Given a unix-style filesystem with a 512 byte block size where inodes contain 12 direct blocks, 1 single indirect block, and 1 double indirect block, what is the maximum file size

- use the first two quizes as part of the studying
  - in essence - no questions will be the exact same
- cumulative final exam