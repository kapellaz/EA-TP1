#include <iostream>
#include <vector>

using namespace std;



void printMatrix(vector<int>& matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        cout << matrix[i] << " ";
    }
    cout << endl;
}

void generateCombinations(int x, int n, vector<int>& combination, int i) {

    if (i == n) {
        for (int i = 0; i < combination.size(); i++) {
                cout << combination[i] << " ";
            }
            cout << endl;
    }
        // Caso o elemento i seja 1, adiciona-o na matriz e decrementa o valor de x
    if (x > 0) {
        combination[i] = 1;
        generateCombinations(x-1, n, combination, i+1);
    }
    
    // Caso o elemento i seja 0, adiciona-o na matriz e não decrementa o valor de x
    if (n-i > x) {
        combination[i] = 0;
        generateCombinations(x, n, combination, i+1);
    }
}

int main() {
    int n = 5; // número de casas
    int x = 3; // número de casas com 1
    vector<int> combination(n);
    generateCombinations(x, n, combination, 0);
    return 0;
}
