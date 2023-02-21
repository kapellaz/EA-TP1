#include <iostream>
#include <cmath>
#include <vector>

const int MAXSIZE = 30;
using namespace std;

int n, lb[MAXSIZE], cb[MAXSIZE], lt[MAXSIZE], ct[MAXSIZE], qb[4], db[2];

int matrix[MAXSIZE][MAXSIZE];

int possiveis=0;

vector<vector<int>> vecaux;

bool leitura(){
        int i = 0;
        cin >> n;
        if(n<2 || n>MAXSIZE) i++;
        for(int i = 0; i< n; i++){
            cin >> lb[i];
            if(lb[i]<0 || lb[i]>n) i++;
        }
        for(int i = 0; i< n; i++){
            cin >> cb[i];
            if(cb[i]<0 || cb[i]>n) i++;
        }
        for(int i = 0; i< n; i++){
            cin >> lt[i];
            if(lt[i]<0 || lt[i]>n-1) i++;
        }
        for(int i = 0; i< n; i++){
            cin >> ct[i];
            if(ct[i]<0 || ct[i]>n-1) i++;
        }

        int a = floor((n/2+1)^2);
        cin >> qb[0] >> qb[1] >> qb[2] >> qb[3] >> db[0] >> db[1];
        
        for(int i = 0; i<4; i++){
            if(qb[i]<0 || qb[i] > a) i++;
            if(i<2 && (db[i] <0 || db[i]>n)) i++;
        }
    if(i>0) return false;
    return true;
}


int calculaTransicoesLinha(int nLinha,vector<int>& matrix){
    int conta = 0;
    int estadoAtual=matrix[0];

    for(int i = 1; i<n; i++){
        if(matrix[i]!= estadoAtual) conta+=1;
        estadoAtual=matrix[i];
    }
    //cout << conta << endl;
    return conta;
}

int calculaTransicoesColuna(vector<vector<int>>& vec){
    int conta = 0;
    int estadoAtual;

    for(int i = 0; i<n; i++){
        estadoAtual=vec[0][i];
        for(int j = 1; j<n; j++){
            if(vec[j][i]!=estadoAtual)conta+=1;
            //cout << estadoAtual <<" " <<vec[j][i] <<" " <<conta<< "| ";
            estadoAtual=vec[j][i];
        }
        //cout << endl;
        //cout << conta << " "<<ct[i] << endl;
        if(conta != ct[i]){
            return 0;
        }
        conta=0;
        
    }
    return 1;
}


int contaQuadrantes(vector<vector<int>>& vec){
    int s = vec.size();
    int q1=0,q2=0,q3=0,q4=0;
    for(int i = 0; i<s; i++){
        for(int j = 0; j<s; j++){
            if(vec[i][j]==1){
                if(i+1<=floor(s/2) && j+1 > floor(s/2)) q1++;
                if(i+1<=floor(s/2) && j +1<= floor(s/2)) q2++;
                if(i+1>floor(s/2) && j+1 <= floor(s/2)) q3++;
                if(i+1>floor(s/2) && j+1 > floor(s/2)) q4++;
            }
        }
    }
    //cout << floor(s/2)<< " "<< q1 << " " << q2 << " " << q3 << " " << q4 << endl << endl;
    if(q1 != qb[0] || q2 != qb[1] || q3 != qb[2] || q4 != qb[3]) return 0;
    return 1;
}

int verificaDiagonais(vector<vector<int>>& vec){
    int conta1 = 0;
    int conta2 = 0;
    int k = vec.size();
    for(int i = 0; i<k; i++){
        //cout << vec[n-i-1][i] << " ";
        if(vec[i][i]==1) conta1++;
        if(vec[k-i-1][i]==1) conta2++;
    }
    //cout << endl;
    //cout << vec.size()<<" "<< conta1 << " " << conta2<< " " << db[0] << " " << db[1] << endl << endl;
    if(conta1 != db[0]) return 0;
    return 1;
}


void generateCombinations(int x, int n, vector<int>& combination, vector<vector<int>>& vec,int i, int nLinha) {
    if (i == n) {
        if(calculaTransicoesLinha(nLinha,combination)==lt[nLinha-1]){
            vec[nLinha-1]=combination;
            //cout << endl;
            vector<int> combination1(n);
            if(nLinha<n)generateCombinations(lb[nLinha],n,combination1,vec,0,nLinha+1);
            if(nLinha==n && calculaTransicoesColuna(vec)==1 
            && contaQuadrantes(vec)==1 && verificaDiagonais(vec)==1){
                possiveis++;
                vecaux=vec;
                return;
            }
        }
    }
        // Caso o elemento i seja 1, adiciona-o na matriz e decrementa o valor de x
    if (x > 0) {
        combination[i] = 1;
        generateCombinations(x-1, n, combination,vec, i+1,nLinha);
    }
    
    // Caso o elemento i seja 0, adiciona-o na matriz e não decrementa o valor de x
    if (n-i > x) {
        combination[i] = 0;
        generateCombinations(x, n, combination,vec, i+1,nLinha);
    }
    return;
}

void printValid(vector<vector<int>>& vec){
    cout << "VALID: 1 QR Code generated!" << endl;
    cout << "+";
    for(int i = 0; i<vec.size(); i++) cout << "-";
    cout << "+" << endl;
    for(int i = 0; i<vec.size();i++){
        cout << "|";
        for(int j = 0; j<vec.size();j++){
            if(vec[i][j]==1) cout << "#";
            else cout << " ";
        }
        cout << "|" << endl;
    }
    cout << "+";
    for(int i = 0; i<vec.size(); i++) cout << "-";
    cout << "+" << endl;
}

int main(){
    int qrcodes;
    cin >> qrcodes;
    while(qrcodes--){
        
        if(!leitura())cout << "No QR Code generated!"<< endl;
        vector<int> combination(n);
        vector<vector<int>> vec(n);
        generateCombinations(lb[0],n,combination,vec,0,1);
        if (possiveis == 0) cout << "DEFECT: No QR Code generated!" << endl;
        else if (possiveis > 1) cout << "INVALID: " << possiveis << " QR Codes generated!" << endl;
        else printValid(vecaux);
        possiveis=0;
    }
    return 0;
}