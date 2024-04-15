
#include <iostream>
#include "Matrix (version 2).cpp"
using namespace std;

int main() {
    const double constanta = 3;
    matrix a(3, 2);
    matrix b(2, 3);
    matrix c(3, 3);
    matrix d(3, 3);
    matrix examp;
    cin >> a >> b >> c >> d;

//    оператор присваивания
    examp = a;
    cout << "examp = a: " << endl << examp << endl;

//    составные операторы присваивания
    examp = c;
    examp += d;
    cout << "c += d: " << endl << examp << endl;

    examp = c;
    examp -= d;
    cout << "c -= d: " << endl << examp << endl;

    examp = a;
    examp *= b;
    cout << "a *= b: " << endl << examp << endl;

    examp = a;
    examp *= constanta;
    cout << "a *= constanta: " << endl << examp << endl;

//    умножение на константу слева;
    examp = 3 * a;
    cout << "3 * a" << endl << examp << endl;

//    умножение на константу справа;
    examp = a * 3;
    cout << "a * 3" << endl << examp << endl;

//    деление на константу
    examp = a / 3;
    cout << "a / 3" << endl << examp << endl;

//    сложение матриц
    examp = c + d;
    cout << "c + d" << endl << examp << endl;

//    вычитание матриц
    examp = c - d;
    cout << "c - d" << endl << examp << endl;

//    умножение матриц
    examp = a * b;
    cout << "a * b" << endl << examp << endl;

//    сравнение матриц на равенство и неравенство
    cout << "c == d" << endl << (c == d) << endl;
    cout << "c != c" << endl << (c != c) << endl;
}
