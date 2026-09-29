#include <iostream>

using namespace std;

int main()
{
  int seg = 20000;
  int hora, min, dia;
  dia = seg / 86400;
  seg = seg % 86400 ;
  hora = seg / 3600;
  seg = seg % 3600;
  min = seg / 60;
  seg = seg % 60;
cout << "\nDias = \n" << dia << endl;
cout << "\n Hora = \n" << hora << endl;
cout << "\n Minuto= \n" << min << endl;
cout << "\n SEgundo = \n" << seg << endl;
return 0; 
}
