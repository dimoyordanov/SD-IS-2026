#include <cstdio>

#include <stdexcept>
#include <iostream>

unsigned int min(unsigned int a, unsigned int b) {
    return (a < b)?a:b;
}

template <typename T>
class DynamicArray{
    private:
        T* arr;
        unsigned int size;
        unsigned int capacity;
        void resize(unsigned int newCapacity){
            T* temp = new T[newCapacity];
            capacity = newCapacity;
            if (arr == nullptr) {
                size = 0;
            } else {
                for(unsigned int i = 0; i < min(size,capacity); i++) {
                    temp[i]=arr[i];
                }
            }
            delete[] arr;
            arr = temp;
            size = min(capacity,size);
        }
    public:
        DynamicArray(unsigned int capacity = 8): arr(nullptr), size(0), capacity(capacity) {
            resize(this->capacity);
        }
        DynamicArray(T value, unsigned int capacity): arr(nullptr), size(0), capacity(capacity) {
            resize(this->capacity);
            this->size=capacity;
            for(unsigned int i = 0; i < this->capacity; i++) {
                arr[i] = value;
            }
        }

        DynamicArray(const DynamicArray& array): arr(nullptr), size(0), capacity(array.capacity) {
            resize(this->capacity);
            size=array.size;
            for(unsigned int i = 0; i < this->size; i++) {
                arr[i] = array.arr[i];
            }
        }

        DynamicArray& operator=(const DynamicArray& array) {
            if (this == &array) {
                return *this;
            }
            
            delete[] this->arr;
            this->arr=nullptr;
            this->capacity=array.capacity;
            resize(this->capacity);
            this->size=array.size;
            for(unsigned int i = 0; i < this->size; i++) {
                arr[i] = array.arr[i];
            }
            return *this;
        }

        ~DynamicArray(){
            delete[] arr;
        }

        void pushFront(T value);
        void insert(T value, unsigned int index);
        void pushBack(T value);
        T removeFront();
        T removeAt(unsigned int index);
        T removeBack();
        T get(unsigned int index);
        void print();
        T operator[](unsigned int index) {
            return get(index);
        }

        unsigned int len() {
            return this->size;
        }

        bool isEmpty() {
            return this->size == 0;
        }
        T sum();
        bool isSorted();
        void append(T a, unsigned int n);
};

template <typename T>
void DynamicArray<T>::append(T a, unsigned int n) {
    if (n == 0) {
        return;
    }

    for (unsigned int i = 0; i < n; i++) {
        pushBack(a);    
    }
}

template <typename T>
bool DynamicArray<T>::isSorted() {
    throw "This feature is not implemented for the desired type";
}

template <>
bool DynamicArray<int>::isSorted() {
    if (len() <= 1) {
        return true;
    }
    
    for (unsigned int i = 0; i < len() - 1; i++) {
        if (get(i) > get(i + 1)) {
            return false;
        }
    }
    return true;
}

template <typename T>
T DynamicArray<T>::sum() {
    throw "This feature is not implemented for the desired type";
}

template <>
int DynamicArray<int>::sum() {
    int sum = 0;
    for (unsigned int i = 0; i < len(); i++) {
        sum += get(i);
    }
    return sum;
}

template <typename T>
void DynamicArray<T>::print(){
    std::cout << "This type is not implemented for printing" << std::endl;
}

template<>
void DynamicArray<int>::print(){
    std::cout << '[';
    if(!isEmpty()){
        for (unsigned int i= 0; i<len()-1; i++) {
            std::cout << get(i) << ',';
        }
        std::cout << get(this->size-1);
    }
    std::cout << ']' << std::endl;
}

template <typename T>
void DynamicArray<T>::pushBack(T value) {
    if (size >= capacity) {
        resize(capacity*2);
    }
    arr[size] = value;
    size++;
}

template <typename T>
void DynamicArray<T>::insert(T value, unsigned int index) {
    if (index > size) {
        throw std::out_of_range("Index out of bounds");
    }
    if (size >= capacity) {
        resize(capacity == 0 ? 1 : capacity * 2);
    }
    for (unsigned int i = size; i > index; i--) {
        arr[i] = arr[i - 1];
    }
    arr[index] = value;
    size++;
}

template <typename T>
void DynamicArray<T>::pushFront(T value) {
    insert(value, 0);
}

template <typename T>
T DynamicArray<T>::removeAt(unsigned int index) {
    if (index >= size) {
        throw std::out_of_range("Index out of bounds");
    }
    if (size*3 < capacity) {
        resize(capacity/2);
    }
    T removedValue = arr[index];
    for (unsigned int i = index; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }
    size--;
    return removedValue;
}

template <typename T>
T DynamicArray<T>::removeBack() {
    if (size <= 0) {
        throw std::out_of_range("Array is empty");
    }
    if (size*3 < capacity) {
        resize(capacity/2);
    }
    size--;
    return arr[size];
}

template <typename T>
T DynamicArray<T>::removeFront() {
    return removeAt(0); // Re-uses removeAt logic
}

template <typename T>
T DynamicArray<T>::get(unsigned int index) {
    if (index >= size) {
        throw std::out_of_range("Index out of bounds");
    }
    return arr[index];
}


int main() {
    DynamicArray<int> arr(5, 2);
    DynamicArray<int> arr2=arr;
    arr2.print();
    arr2.pushBack(3);
    arr2.print();
    arr2.insert(1,0);
    arr2.print();
    arr.print();
    std::cout << arr2.removeBack() << std::endl;
    std::cout << arr2.removeAt(1) << std::endl;
    arr2.print();
    arr.print();
    std::cout << arr2.sum()  << std::endl;
    return 0;
}
