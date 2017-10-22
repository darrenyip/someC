## Description :bowtie:
**_fileArchiver_** is a super simply program that combines a number of files together into one archive file. All the functionalities of this program implemented with just C programming built in file read and file write.

## Example :star:

##### This program can provide these features:
- Given a list of files and the desired archive name, create the archive while leaving the original files intact.
- Given a list of files, the desired archive name, and a desired archive size, create a series of
archives of up to the given size while leaving the original files intact.

- Given an archive file, create the individual files contained in that archive, while leaving the
archive intact.

- Given an archive file, list statistical information about the file.

- Given an archive file and a list of individual files, verify that the archive contains those files.


## How to use it :eyes:

**To archive files:**
```
archiver -a archivename file1 file2 ... fileN
```
---
- This command line will create an archive with the specified
name from the specified files. The original files should remain unchanged. The number of files can vary.

**To unpack an archived file:**
```
archiver -u archivename
```
---
- Unpack the specified archive and generate each file contained within. The original archive should remain unchanged.

**To show the detail of an archived file:**
```
archiver -l archivename
```
---
- Print out the total size of the archive, the number of files in the archive, and each filename along with the corresponding file size.

**To check if specified files are included in the archived file:**
```
archiver -v archivename file1 file2 ... fileN
```
---
- determine whether or not the specified archive is damaged. There are three possibilities:
  - The archive correctly contains all N files.
  - The archive is missing some data. The program will tell you number of missing bytes.
  - The archive has N files, and is the correct size to contain the specified files, but some of the data is incorrect. You will see the message "Archive is corrupted".
  
