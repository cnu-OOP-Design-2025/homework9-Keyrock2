#include <iostream>
#include <string>
#include <list>
using namespace std;

template <typename T>
class MyVector
{
private:
    T *data; // 데이터 타입이 int에서 T로 변경됨
    size_t capacity;
    size_t length;

    void resize()
    {
        cout << "Resize: " << capacity << " -> " << capacity * 2 << endl;
        size_t newCapacity = capacity * 2;
        T *newData = new T[newCapacity]; // int 대신 T 타입 배열 할당

        for (size_t i = 0; i < length; ++i)
        {
            newData[i] = data[i];
        }

        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    MyVector() : capacity(2), length(0)
    {
        data = new T[capacity]; // int 대신 T 타입 할당
    }

    ~MyVector()
    {
        if (data != nullptr)
        {
            delete[] data;
        }
    }

    void push_back(const T &value)
    { // 매개변수 타입이 T로 변경됨
        if (length == capacity)
        {
            resize();
        }
        data[length++] = value;
    }

    T pop_back()
    { // 반환 타입이 T로 변경됨
        if (length == 0)
            throw out_of_range("Vector is empty");
        return data[--length];
    }

    T &operator[](const int index)
    { // 반환 타입이 T&로 변경됨
        return data[index];
    }

    size_t size() const
    {
        return length;
    }

    // 심화 학습: 범위 기반 for 문을 위한 begin, end 구현
    T *begin() { return data; }
    T *end() { return data + length; }
};

template <typename T>
void testVector(const string &name, std::list<T> values)
{

    cout << "------------------" << endl;
    MyVector<T> vec;
    for (auto &v : values)
        vec.push_back(v);

    cout << name << ": ";

    // 심화 학습: 범위 기반 for문 적용
    // 원래 코드: for (size_t i = 0; i < vec.size(); ++i) cout << vec[i] << " ";
    for (auto &e : vec)
    {
        cout << e << " ";
    }

    cout << endl;
    while (vec.size())
        cout << "Pop: " << vec.pop_back() << "\n";
}

int main()
{
    testVector<int>("IntVec", {1, 2, 3, 4, 5, 6});
    testVector<double>("DoubleVec", {1.1, 2.2, 3.3, 4.4, 5.5});
    testVector<char>("CharVec", {'A', 'B', 'C', 'D', 'E', 'F'});
    testVector<string>("StringVec", {"Hello", "World", "C++", "Template", "Vector"});
    return 0;
}