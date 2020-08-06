#include <vector>
#define DEFAULT_MEMSIZE 1000

template<typename T>
class MemoryStrip{
public:
    MemoryStrip(size_t memsize=DEFAULT_MEMSIZE);
    T getValue();
    void setValue(T val);
    void incValue();
    void decValue();
    void incPointer();
    void decPointer();
private:
    T *strip;
    size_t strip_size;
    size_t location;
};

template<typename T>
MemoryStrip<T>::MemoryStrip(size_t memsize){
    strip = new T[memsize];
    location = memsize/2;
    strip_size = memsize;
}

template<typename T>
T MemoryStrip<T>::getValue(){
    return strip[location];
}

template<typename T>
void MemoryStrip<T>::setValue(T val){
    strip[location] = val;
}

template<typename T>
void MemoryStrip<T>::incValue(){
    strip[location]++;
}

template<typename T>
void MemoryStrip<T>::decValue(){
    strip[location]--;
}

template<typename T>
void MemoryStrip<T>::incPointer(){
    location = (location+1) % strip_size;
}

template<typename T>
void MemoryStrip<T>::decPointer(){
    location = (location-1) % strip_size;
}

