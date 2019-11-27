cedictToSqlite
---------


## About cedictToSqlite:
Converts a cedict dictionary file to a sqlite3 database file. Only works on linux. Windows utf-8 problems have not been solved.



## Getting started
### Git:

Use git to clone the repository. Then init and update submodule "SQLiteCpp".

```Shell
git clone https://github.com/camccar/cedictToSqliteLinux.git
cd cedictToSqliteLinux
git submodule init
git submodule update
```

### CMake and build:

Use build.bat or ./build.sh script, or cmake commande line (example for Linux): 

```Shell
mkdir -p build
cd build

# Generate a Makefile for GCC (or Clang, depanding on CC/CXX envvar)
cmake ..

# Build (ie 'make')
cmake --build .
```


### Run

Launch build/cedictToSqlite from the command line

