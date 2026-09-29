#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    float d, h, r, a, v=0;
    float pi = 3.1415129;
    d = 6;
    h = 12;
    r = d/2;
    cout <<"Valor do raio:"<< r << endl;
    a = pi * pow(r,2);
    cout <<"Valor da area :"<< a << endl;
    v = a * h ;
    cout<<"Volume do copo: "<< v << endl;
    return 0;
}
