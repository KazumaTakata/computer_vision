fish shell command

install opencv

```
git clone https://github.com/opencv/opencv.git
mkdir debug
cd debug
cmake -D CMAKE_BUILD_TYPE=DEBUG -D OPENCV_GENERATE_PKGCONFIG=YES  -D CMAKE_INSTALL_PREFIX=/Users/kazumatakata/local ..
make -j8
sudo make install
```

set PKG_CONFIG_PATH

```
export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig
```

set DYLD_LIBRARY_PATH

```
set -x -U DYLD_LIBRARY_PATH /Users/kazumatakata/local/lib
```

compile with debug option

```
eval g++ (pkg-config --cflags --libs opencv4) -g -std=c++11  Helloworld.cpp  -o yourFileProgram
```

in order to debug in vscode set env field of launch.json like this

```
"environment": [
        {
          "name": "DYLD_LIBRARY_PATH",
          "value": "/Users/kazumatakata/local/lib"
        }
      ]
```
