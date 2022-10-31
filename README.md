This project was created by Dru Guiao.

How to run main program (classic):
1. cd path/to/toy-robot
2. Compile all cpp files: 
    - > g++ -o bin/toy-robot *.cpp
3. Run toy-robot program (Command-line input): 
    - > ./bin/toy-robot
    - > Note: Program will end if no input is given
4. Run toy-robot program (File-based input):
    - > ./bin/toy-robot -i <filename>
    - > Note: filename should not have any spaces

How to run tests:
Note: proceed to step 3 if googletest was already cloned
1. cd path/to/toy-robot
2. git clone https://github.com/google/googletest.git 
3. build the project: cmake --build build/ --config Debug --target all -j10
4. cd build/
5. run tests: ctest -j10 -C Debug -T test --output-on-failure
