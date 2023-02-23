
#include <iostream>
#include <cmath>
#include <vector>

const int MAXSIZE = 30;
using namespace std;

int n, lb[MAXSIZE], cb[MAXSIZE], lt[MAXSIZE], ct[MAXSIZE], qb[4], db[2];

int possiveis=0;

int contador=0;


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

    for(int i = 1; i<nLinha; i++){
        if(matrix[i]!= estadoAtual) conta+=1;
        estadoAtual=matrix[i];
    }
    //cout << conta << endl;
    return conta;
}
/*
int calculaTransicoesColuna(vector<vector<int>>& vec, int nLinha){
    int conta = 0;
    int estadoAtual;

    for(int i = 0; i<nLinha; i++){
        estadoAtual=vec[0][i];
        for(int j = 1; j<n; j++){
            if(vec[j][i]!=estadoAtual)conta+=1;
            //cout << estadoAtual <<" " <<vec[j][i] <<" " <<conta<< "| ";
            estadoAtual=vec[j][i];
        }
        //cout << endl;
        //cout << conta << " "<<ct[i] << endl;
        if(conta > ct[i]){
            return 0;
        }
        conta=0;
        
    }
    return 1;
}


int contaQuadrantes(vector<vector<int>>& vec,int nLinha){
    int s = vec.size();
    int v = floor(s/2);
    int q1=0,q2=0,q3=0,q4=0;
    for(int i = 0; i<nLinha; i++){
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
    
    if(nLinha==v) if(q1 != qb[0] || q2 != qb[1]) return 0;
    if(q1 > qb[0] || q2 > qb[1] || q3 > qb[2] || q4 > qb[3]) return 0;
    
    return 1;
}


int verificaDiagonais(vector<vector<int>>& vec, int nLinha){
    int conta1 = 0;
    int conta2 = 0;
    int k = vec.size();
    
    for(int i = 0; i<nLinha; i++){
        //cout << vec[n-i-1][i] << " ";
        if(vec[i][i]==1) conta1++;

        if(vec[i][k-i-1]==1) conta2++;
    }
    //cout << endl;
    //cout << vec.size()<<" "<< conta1 << " " << conta2<< " " << db[0] << " " << db[1] << endl << endl;
    if(conta1 > db[0]) return 0;
    if(conta2 > db[1]) return 0;
    return 1;
}

*/

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


int verificaUntil(vector<vector<int>>& vec, int nLinha, int nColuna){
    int conta1 = 0;
    int conta2 = 0;
    int q1=0,q2=0,q3=0,q4=0;
    int conta = 0;
    int estadoAtual;
    int s = vec.size();
    int v = floor(s/2);

    for(int i = 0; i<nLinha; i++){
        estadoAtual=vec[0][i];
        if(vec[i][i]==1) conta1++;
        if(vec[i][s-i-1]==1) conta2++;
        for(int j = 0; j<nColuna; j++){
            if((j+1<nLinha) && vec[j+1][i]!=estadoAtual){
                conta+=1;
                estadoAtual=vec[j+1][i];
            }
            if(vec[i][j]==1){
                if(i+1<=floor(s/2) && j+1 > floor(s/2)) q1++;
                if(i+1<=floor(s/2) && j +1<= floor(s/2)) q2++;
                if(i+1>floor(s/2) && j+1 <= floor(s/2)) q3++;
                if(i+1>floor(s/2) && j+1 > floor(s/2)) q4++;
            }
        }
        if(conta > ct[i]){
            return 0;
        }
        conta=0;
    }
    
    return 1;
}





int verifica(vector<vector<int>>& vec){
    int conta1 = 0;
    int conta2 = 0;
    int q1=0,q2=0,q3=0,q4=0;
    int contaColuna = 0;
    int estadoAtualColuna;
    int s = vec.size();
    int v = floor(s/2);

    for(int i = 0; i<n; i++){
        estadoAtualColuna=vec[0][i];
        if(vec[i][i]==1) conta1++;
        if(vec[i][s-i-1]==1) conta2++;
        for(int j = 0; j<n; j++){
            if((j+1<n) && vec[j+1][i]!=estadoAtualColuna){
                contaColuna+=1;
                estadoAtualColuna=vec[j+1][i];
            }
            if(vec[i][j]==1){
                if(i+1<=floor(s/2) && j+1 > floor(s/2)) q1++;
                if(i+1<=floor(s/2) && j +1<= floor(s/2)) q2++;
                if(i+1>floor(s/2) && j+1 <= floor(s/2)) q3++;
                if(i+1>floor(s/2) && j+1 > floor(s/2)) q4++;
            }
        }
        if(contaColuna != ct[i]){
            return 0;
        }
        contaColuna=0;
    }
    if(conta1 != db[0]) return 0;
    if(conta2 != db[1]) return 0;
    if(q1 != qb[0] || q2 != qb[1] || q3 != qb[2] || q4 != qb[3]) return 0;
    //cout << conta1 << " " << conta2 << endl;
    //cout << q1 << " " << q2 << " " << q3 << " " << q4 << endl << endl;
    return 1;
}


void generateCombinations(int n, vector<vector<int>>& vec,int linha, int coluna) {
    contador++;
    int x = linha-1;
    int y = coluna-1;

    vec[x][y] = 0;
    //cout << linha << " " << coluna << endl;
    vector<int> aux(n);
    aux = vec[x];
    if(calculaTransicoesLinha(coluna,aux)<=lt[x]){
        if(coluna==n && linha!=n) {
            if(calculaTransicoesLinha(coluna,aux)==lt[x] && verificaUntil(vec,linha, coluna)==1){
                generateCombinations(n,vec,linha+1,1);
            }
        }
        else if(linha==n && coluna == n){
            if(verifica(vec)==1){
                possiveis++;
                vecaux = vec;
            }
            
        }
        else generateCombinations(n,vec,linha,coluna+1);
    }

    vec[x][y] = 1;
       
    aux = vec[x];
    if(calculaTransicoesLinha(coluna,aux)<=lt[x]){
        if(coluna==n && linha!=n) {
            if(calculaTransicoesLinha(coluna,aux)==lt[x] && verificaUntil(vec,linha, coluna)==1){
                generateCombinations(n,vec,linha+1,1);
            }
        }
        else if(linha==n && coluna == n){
            if(verifica(vec)==1){
                possiveis++;
                vecaux = vec;
            }
            
        }
        else generateCombinations(n,vec,linha,coluna+1);
    }
    
}


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int qrcodes;
    cin >> qrcodes;
    while(qrcodes--){
        
        if(!leitura())cout << "No QR Code generated!"<< endl;
        //cout << n << endl;
        vector<vector<int>> vec( n , vector<int> (n));
        generateCombinations(n, vec,1,1);
        if (possiveis == 0) cout << "DEFECT: No QR Code generated!" << endl;
        else if (possiveis > 1) cout << "INVALID: " << possiveis << " QR Codes generated!" << endl;
        else printValid(vecaux);
        possiveis=0;
        cout << contador << endl;
        contador = 0;
    }
    return 0;
}