## Description :bowtie:
**_mylogger_** is a program that merge several log files in order of timestamp.
This might be useful when people wants to reconstruct a single chronological order of events that occurred across several processes on a server (or in a distributed system, on several machines). The merged log file is particularly useful to understand if one event in one program caused another event in another program.

## Example :star:

##### Let the following be the contents of `server.log` and `client.log` respectively:

```
#SERVER
DEBUG,2011-10-21 14:32:00,server starting
DEBUG,2011-10-21 14:32:01,server started
WARN,2011-10-21 14:32:10,client connected
DEBUG,2011-10-21 14:32:15,received string
INFO,2011-10-21 14:32:18,sent result
ERROR,2011-10-21 14:32:19,error sending
DEBUG,2011-10-21 14:32:22,client disconnected
```

```
#CLIENT
WARN,2011-10-21 14:32:09,session started
INFO,2011-10-21 14:32:14,calling server
ERROR,2011-10-21 14:32:20,error while calling
DEBUG,2011-10-21 14:32:21,disconnecting

```

##### The expected output when running `mylogger` in the directory containing these two logs should be:

```
DEBUG,2011-10-21 14:32:00,server starting
DEBUG,2011-10-21 14:32:01,server started
WARN,2011-10-21 14:32:09,session started
WARN,2011-10-21 14:32:10,client connected
INFO,2011-10-21 14:32:14,calling server
DEBUG,2011-10-21 14:32:15,received string
INFO,2011-10-21 14:32:18,sent result
ERROR,2011-10-21 14:32:19,error sending
ERROR,2011-10-21 14:32:20,error while calling
DEBUG,2011-10-21 14:32:21,disconnecting
DEBUG,2011-10-21 14:32:22,client disconnected
```

Note that the lines containing **#SERVER** and **#CLIENT** are discarded.

## Detail of implementation :eyes:

**To use:**
```
mylogger [logfilesCollectionPath]
```
---
- The **optional** command line argument **_logfilesCollectionPath_** is the path to a directory containing a collection of log files that **mylogger** program can operate on.
- If no argument is given, **mylogger** program will operate on the current working directory.
- The output of the program will be named **combinedlogs.log**
- If **combinedlogs.log** already exists in the **_logfilesCollectionPath_** directory, the program will **overwrite** the contents of that file.

:ok_hand:
---
>In order to operate on several log files:

- The program first concatenate all the log files into a single file, and then read the result of this concatenation.
- Assume that the format of all log files to be provided to the program is the same (i.e., each log starts with a line `#<name of program>`,  Each entry will follows the format `<level>,<date>,<message>`, and the timestamp format is `YYYY-MM-DD HH:MM:SS`).
- The program used linkedList data structure.
