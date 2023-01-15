# headerlibs

Personal collection of C header-only libraries.

- chkpath.h
  - `char *which(char *command)` - returns the full path of command
  - `bool iscmdavail(char *command)` - returns whether command available
- fileops.h
  - `cat(char *file1, char *file2, ...)` - concates files and prints on
    stdout (fils are considered text)
  - `cp(char *source, char *dest)` - copies SOURCE to DEST
  - `mv(char *source, char *dest)` - moves SOURCE to DEST
