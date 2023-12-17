# Log Manager

Log manager is logger management module for process log messages and sink

## Important notes

the Log manager module use filesystem header which has been added to c++ standard
library as of C++17. However, not all compilers support this updates, especially
if you are using Mac OS's default c++ compiler.

Hence, we highly recommend you to use clang++ compiler that will fully support filesystem
header. 

If you are Mac OS user and if you are using `ar` installed from homebrew, there are known issues
with `clang++` compiler and binutils's `ar` (https://stackoverflow.com/questions/77444892/xcode-15-0-1-macos-sonoma-clang-archive-or-linking-issue).

modify your `$PATH` variable to use `/usr/bin/ar` instead will solve the issue.
