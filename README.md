This project was created by Dru Guiao.

How to run main program:
1. cd path/to/toy-robot
2. Compile all cpp files: 
    > g++ -o bin/toy-robot *.cpp
3. Run toy-robot program (Command-line input): 
    > ./bin/toy-robot
4. Run toy-robot program (File-based input):
    > ./bin/toy-robot -i <filename>
    > Note: filename should not have any spaces

How to run tests (vs-code):
1. Download and install google test: https://github.com/google/googletest
2. Make sure CMAKE and CMAKE tools are installed: Installation guide:
    > https://code.visualstudio.com/docs/cpp/cmake-linux#:~:text=Install%20the%20C%2FC%2B%2B%20extension,a%20debugger%2C%20and%20build%20tools.
3. Make sure CMakeLists.txt files are properly configured.
4. To run tests:
    > CTRL + SHIFT + P: Cmake: Run Tests
