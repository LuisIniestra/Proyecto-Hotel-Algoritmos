#ifndef SORTS_H_
#define SORTS_H_

#include <vector>

template <class T>
class Sorts {

private:

    void swap(std::vector<T>&, int, int);

public:

    std::vector<T> selectionSort(const std::vector<T>&);
};


template <class T>
void Sorts<T>::swap(std::vector<T> &v, int i, int j) {

    T aux = v[i];

    v[i] = v[j];
    v[j] = aux;
}


template <class T>
std::vector<T> Sorts<T>::selectionSort(const std::vector<T> &source) {

    std::vector<T> v(source);

    int pos;

    for (int i = v.size() - 1; i > 0; i--) {

        pos = 0;

        for (int j = 1; j <= i; j++) {

            if (v[j] > v[pos]) {

                pos = j;
            }
        }

        if (pos != i) {

            swap(v, i, pos);
        }
    }

    return v;
}


#endif /* SORTS_H_ */
