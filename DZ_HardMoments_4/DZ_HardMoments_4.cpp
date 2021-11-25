
#include <vector>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <numeric>

using namespace std;

/*Task 1
Имеется отсортированный массив целых чисел.
Необходимо разработать функцию insert_sorted, которая принимает вектор и новое число
и вставляет новое число в определенную позицию в векторе, чтобы упорядоченность контейнера сохранялась.
Реализуйте шаблонную функцию insert_sorted, которая сможет аналогично работать с любым контейнером, содержащим любой тип значения. */

template<typename T, typename N>
void insert_sorted(T& v, const N  n)
{
    const auto insert_pos(lower_bound(begin(v), end(v), n));
    v.insert(insert_pos, n);
}

template<typename T>
void inform(const T& v)
{
    for (const auto e : v) cout << e << ' ';
}

/*Task 2
Сгенерируйте вектор a, состоящий из 100 вещественный чисел, представляющий собой значения аналогового сигнала.
На основе этого массива чисел создайте другой вектор целых чисел b, представляющий цифровой сигнал, в котором будут откинуты дробные части чисел. 
Выведите получившиеся массивы чисел. Посчитайте ошибку, которой обладает цифровой сигнал по сравнению с аналоговым */

const size_t size_one = 5;
const size_t size_two = 10;

int getRandomNumber(int min, int max)
{
    const static auto seed = chrono::system_clock::now().time_since_epoch().count();
    static mt19937_64 generator(seed);
    uniform_int_distribution<int> dis(min, max);
    return dis(generator);
}

void VectorGenerateEror() 
{
    vector<float> vector_one(size_two);
    generate(vector_one.begin(), vector_one.end(), []() { return float(getRandomNumber(1, 100)) + (float(getRandomNumber(1, 100)) / 100); });

    cout << "Вектор вещественный чисел:"<< endl;
    for (auto n : vector_one)
    {
        cout  << n << '\t';
    }

    cout << endl;

    vector<int> vector_two;
    vector_two.reserve(size_two);
    transform(vector_one.begin(), vector_one.end(), back_inserter(vector_two), [](float f) {return int(f); });

    cout << "\nВектор целых чисел:"<<endl;
    for (auto n : vector_two) 
    {
        cout << n << '\t';
    }

    cout << endl;
    cout << "\nОшибка, которой обладает цифровой сигнал по сравнению с аналоговым: ";
    cout << inner_product(vector_two.begin(), vector_two.end(), vector_one.begin(), 0.f, plus<>(), [](float a, float d)   {  return (a - d) * (a - d); });
    cout << endl;
}

int main()
{
    //Task 1

    setlocale(LC_ALL, "rus");
    {
        cout << "Задание 1 \n\n";

        vector<int> v{ 1, 2, 3, 4, 5, 7, 8 , 9, 10 };
        cout << "Пример типа int!" << endl;
        cout << "Изначальный массив: ";
        inform(v);
        cout << "\nФункция insert_sorted сработала: ";
        assert(true == is_sorted(begin(v), end(v)));
        insert_sorted(v, 6);
        inform(v);
        cout << "\n\n";

        vector<float> m{ 1.3, 2.5, 3.2, 4.4, 5.1, 7.1, 8.4 , 9.5, 10.3 };
        cout << "Пример типа float!" << endl;
        cout << "Изначальный массив: ";
        inform(m);
        cout << "\nФункция insert_sorted сработала: ";
        assert(true == is_sorted(begin(m), end(m)));
        insert_sorted(m, 6.4);
        inform(m);
        cout << "\n\n";

        vector<string>g{ "a b c","d e f g","i j k" };
        cout << "Пример типа string!" << endl;
        cout << "Изначальный массив: ";
        inform(g);
        cout << "\nФункция insert_sorted сработала: ";
        assert(true == is_sorted(begin(g), end(g)));
        insert_sorted(g, "h");
        inform(g);
        cout << "\n\n";
    }

    // Task 2
    {
        cout << "Задание 2\n\n";

        VectorGenerateEror();
    }

    return 0;

};


