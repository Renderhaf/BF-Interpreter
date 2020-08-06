#include "memorystrip.cpp"
#include "file_handler.cpp"
#include "tokens.h"
#include <iostream>

using namespace std;
typedef unsigned char memtype;

int main(int argc, char* argv[]){
    // Make sure a target file is given
    if (argc < 2){
        cout << "USAGE: " << "filename" << " bf-filename [flags]" << endl;
        return -1; 
    }

    FileStreamer program = FileStreamer(argv[1]);
    MemoryStrip<memtype> memory = MemoryStrip<memtype>();

    while (true){
        char instruction = program.getCurrentChar();

        switch (instruction){
        case INC_VAL:
            memory.incValue();
            break;
        case DEC_VAL:
            memory.decValue();
            break;
        case INC_PTR:
            memory.incPointer();
            break;
        case DEC_PTR:
            memory.decPointer();
            break;
        case PRINT_VAL:
            cout << (char) memory.getValue();
            cout.flush();
            break;
        case GET_VAL:
            memory.setValue((memtype) cin.get());
            break;
        case OPEN_LOOP:
            if (!memory.getValue())
                program.jump(program.find_matching_close());
            break;
        case CLOSE_LOOP:
            if (memory.getValue() != 0)
                program.jump(program.find_matching_open());
            break;
        default:
            break;
        }

        program.advance();
        if (program.isFinished()){
            break;
        }
    }

}