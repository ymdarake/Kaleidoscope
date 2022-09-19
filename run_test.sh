#!/bin/sh

pushd build
cmake ..
make all
./Kaleidoscope-googletest

pushd CMakeFiles/Kaleidoscope-googletest.dir
lcov -d . -c -o coverage.info

lcov -r coverage.info */googletest/* test/* */c++/* -o coverageFiltered.info

popd
popd

# make html report
genhtml -o lcov_html --num-spaces 4 -s --legend build/CMakeFiles/Kaleidoscope-googletest.dir/coverageFiltered.info
