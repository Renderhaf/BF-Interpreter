#include <string>
#include <fstream>
#include <sstream>
#include "tokens.h"

class FileStreamer{
public:
    FileStreamer(std::string filename);
    char getCurrentChar();
    char getCharAt(int pos);
    void advance();
    bool isFinished();
    void jump(int pos);
    int find_matching_close(); //Search ] forward
    int find_matching_open(); //Search [ backwards
private:
    int _pos;
    std::ifstream file_stream;
    std::string file_contents;
};

FileStreamer::FileStreamer(std::string filename){
    file_stream = std::ifstream(filename);
    std::stringstream buffer;
    buffer << file_stream.rdbuf();
    file_contents = buffer.str();
    _pos = 0;
}

char FileStreamer::getCurrentChar(){
    return file_contents[_pos];
}

char FileStreamer::getCharAt(int pos){
    return file_contents[pos];
}

void FileStreamer::advance(){
    _pos++;
}

bool FileStreamer::isFinished(){
    return _pos > file_contents.length();
}

void FileStreamer::jump(int pos){
    _pos = pos;
}

int FileStreamer::find_matching_close(){
    int pos = _pos;
    int unclosed_brackets = 0;

    while (pos < file_contents.length()){
        if (getCharAt(pos) == CLOSE_LOOP){
            if (unclosed_brackets == 1)
                return pos;
            unclosed_brackets--;
        } else if (getCharAt(pos) == OPEN_LOOP){
            unclosed_brackets++;
        }
        pos++;
    }
    return -1;
}

int FileStreamer::find_matching_open(){
    int pos = _pos;
    int unclosed_brackets = 0;

    while (pos >= 0){
        if (getCharAt(pos) == OPEN_LOOP){
            if (unclosed_brackets == 1)
                return pos;
            unclosed_brackets--;
        } else if (getCharAt(pos) == CLOSE_LOOP){
            unclosed_brackets++;
        }
        pos--;
    }
    return -1;
}
