
# TextEditor in C++ 
The textEditor is a text content management class that performs basic functionalities usually found in a string. Functionalities are listed below:
* insert a string to a specific position
* append a string to the end
* erase string in certain length from a specific position
* erase certain length from trail of the string
* undo the previous step
* redo the previous step
* load from txt file
* save to a txt file

## File directories

| File No. | File | Description |
|------|--------|-------------|
| Folder Name | **textEditor** | **Source code of text management class** |
| 1 | *a.txt* | File containing text |
| 2 | *editClass.cpp* | Source code file of editClass |
| 3 | *editClass.hpp* | Header file of editClass |
| 4 | *main.cpp* | Main function runs a brief demo of all interfaces |
| 5 | *Makefile* | Makefile of the textEditor |
| 6 | *opObj.cpp* | Source code of the opObj class |
| 7 | *opObj.hpp* | Header file of the opObj class |

| File No. | File | Description |
|------|--------|-------------|
| Folder Name | **textEditor_test** | **Source code of unit test class by GTest framework** |
| 1 | *a.txt* | File containing text |
| 2 | *CMakeList.txt* | CMakeLists File to generate Makefile |
| 3 | *editClass_test_f.cpp* | Unit test class |


## How to run
```
## Run the main program
cd textEditor
make
./run
cd ..

## Run the unit test file
cd textEditor_test
cmake CMakeLists.txt
make
./runTest
``` 

## How to install GTest
``` 
sudo apt-get install libgtest-dev
sudo apt-get install cmake # install cmake
cd /usr/src/gtest
sudo cmake CMakeLists.txt
sudo make
sudo cp *.a/usr/lib #copy or symlink libgtest.a and libgtest_main.a to /usr/lib
```

