
#include <iostream>
#include <stdexcept>
using namespace std;
class twoStacks {
public:
    twoStacks() {
        sizeOne = 0;
        sizeTwo = 0;
        array_sz = 10;
        length = 5;
        stacks[array_sz] = {0};

    };
    void pop_first();
    void pop_second();
    void push_first(int& newVal);
    void push_second(int& newVal);
    int size_first();
    int size_second();

private:
    void doubleArray();
    unsigned int array_sz;
    int length;
    int sizeOne;
    int sizeTwo;
    int stacks[];

};


int twoStacks::size_first() {
    return sizeOne;
}

int twoStacks::size_second() {
    return sizeTwo;
}


void twoStacks::pop_first() {
    if (sizeOne == 0) {
        throw std::out_of_range("Stack 1 is empty\n");
    }
    for (unsigned i = 0; i < (sizeOne - 1); i++) {
        stacks[i] = stacks[i + 1];
    }
    sizeOne -= 1;
}

void twoStacks::pop_second() {
    if (sizeTwo == 0) {
        throw std::out_of_range("Stack 2 is empty\n");
    }
    for (unsigned i = sizeTwo; i < (array_sz - 1); i++) {
        stacks[i] = stacks[i + 1];
    }
    sizeTwo -= 1;
}

void twoStacks::push_first(int& newVal) {
    if ((sizeOne + 1) > length) {
        doubleArray();
    }
    for (int i = length - 1; i > -1; i--) {
        if (i == 0) {
            stacks[i] = newVal;
        }
        else {
            stacks[i] = stacks[i - 1];
        }
    }
    sizeOne++;

}

void twoStacks::push_second(int& newVal) {
    if ((sizeTwo + 1) > length) {
        doubleArray();
    }

    for (int i = (length * 2) - 1; i > (length - 1); i--) {
        if (i == length) {
            stacks[i] = newVal;
        }
        stacks[i] = stacks[i - 1];
    }
    sizeTwo++;
}

void twoStacks::doubleArray() {
    array_sz = array_sz * 2;
    int temp[array_sz];
    for (unsigned i = 0; i < array_sz; i++) {
        if (i < length) {
            temp[i] = stacks[i];
        }
        else if (i < (length * 2) && (i > (length))) {
            temp[i] = 0;
        }
        else if (i < (length * 3) && (i > length * 2)) {
            temp[i] = stacks[i];
        }
        else if (i < (length * 4) && i > (length * 3)) {
            temp[i] = 0;
        }
    }

    length = length * 2;
    stacks[array_sz] = {0};
    for (unsigned i = 0; i < array_sz; i++) {
        stacks[i] = temp[i];
    }

}