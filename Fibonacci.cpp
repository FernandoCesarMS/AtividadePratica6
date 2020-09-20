#include <iostream>

using namespace std;

template <typename T>
T fibonacci(T n)
{
    if (n == 1 || n == 2)
        return 1;

    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main()
{
    // testando para inteiro
    int Inteiro = 0;
    Inteiro = fibonacci(8);
    cout << "Fibonacci para inteiro: " << Inteiro << endl;
    
    // testando para float
    float Real = 0.0;
    Real = fibonacci(8);
    cout << "Fibonacci para float: " <<  Real << endl;
    
    // testando para long
    long Long = 0.0;
    Long = fibonacci(8.0);
    cout << "Fibonacci para Long: " << Long << endl;
    return 0;
}