#include <iostream>
using namespace std;
int main(){
    int ROWS, COL;
    cout << "Введите количество строк массива: ";
    cin >> ROWS;
    cout << "Введите количество столбоцов массива: ";
    cin >> COL;
    double *C_l =new double[ROWS*COL];
    for (int i = 0 ; i < ROWS*COL; i++) cin >> *(C_l + i);
    for (int i = 0; i < ROWS*COL; i++){
        if (i % COL == 0)
        {
            cout << '\n';
        }
        cout << *(C_l + i) << ' ';
    }
    cout << endl;
    delete[] C_l;
    return 0;
}