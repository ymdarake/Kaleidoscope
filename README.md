# Kaleidoscope

https://llvm.org/docs/tutorial/MyFirstLanguageFrontend/index.html

## Build

```bash
$ cd build
$ cmake ..
$ make all
$ ctest
$ ./Kaleidoscope-googletest
$ ./Kaleidoscope
```

## GoogleTest setup

https://github.com/google/googletest/blob/main/googletest/README.md#standalone-cmake-project

```bash
git clone https://github.com/google/googletest.git -b release-1.12.0
cd googletest        # Main directory of the cloned repository.
mkdir build          # Create a directory to hold the build output.
cd build
cmake ..             # Generate native build scripts for GoogleTest.
make
sudo make install    # Install in /usr/local/ by default
```
