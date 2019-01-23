
fish shell command

set DYLD_LIBRARY_PATH
```
set -x -U DYLD_LIBRARY_PATH /Users/kazumatakata/local/lib
```
compile with debug option
```
eval g++ (pkg-config --cflags --libs opencv) -g -std=c++11  Helloworld.cpp  -o yourFileProgram  
```
