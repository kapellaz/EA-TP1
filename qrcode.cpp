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
    if(conta1 > db[0]) return 0;
    if(conta2 > db[1]) return 0;
    if(nLinha==v) if(q1 != qb[0] || q2 != qb[1]) return 0;
    if(q1 > qb[0] || q2 > qb[1] || q3 > qb[2] || q4 > qb[3]) return 0;
    return 1;
}


int verificaUntil2(vector<vector<int>>& vec, int nLinha, int nColuna){
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
    if(conta1 > db[0]) return 0;
    if(conta2 > db[1]) return 0;
    if(q1 > qb[0] || q2 > qb[1] || q3 > qb[2] || q4 > qb[3]){
        return 0;
    }
    return 1;
}



int verifica(vector<vector<int>>& vec){
    int conta1 = 0;
    int conta2 = 0;
    int q1=0,q2=0,q3=0,q4=0;
    int conta = 0;
    int estadoAtual;
    int s = vec.size();

    for(int i = 0; i<n; i++){
        estadoAtual=vec[0][i];
        if(vec[i][i]==1) conta1++;
        if(vec[i][s-i-1]==1) conta2++;
        for(int j = 0; j<n; j++){
            if((j+1<n) && vec[j+1][i]!=estadoAtual){
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
        if(conta != ct[i]){
            return 0;
        }
        conta=0;
    }
    if(conta1 != db[0]) return 0;
    if(conta2 != db[1]) return 0;
    if(q1 != qb[0] || q2 != qb[1] || q3 != qb[2] || q4 != qb[3]) return 0;
    return 1;
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



int generateCombinations(vector<int>& combination, vector<vector<int>>& vec, int nLinha) {
    if(calculaTransicoesLinha(n,combination)==lt[nLinha-1]){
        vec[nLinha-1]=combination;
        if(nLinha<n){
            //if(verificaUntil(vec, nLinha,n)==1){
             //   return 1;
           // }
        }
        if(nLinha==n && verifica(vec)==1){
                possiveis++;
                vecaux=vec;
                printValid(vec);
                return 2;
        }
        //if(nLinha==n && calculaTransicoesColuna(vec)==1 && contaQuadrantes(vec)==1
        //&& verificaDiagonais(vec)==1){
    }
    return -1;
}
int conta1=0;

vector<int> combinationold;
void geraLinhas(int x, int n, vector<int>& combination, vector<vector<int>>& vec,int i,int control, int nLinha){
    contador++;
    if(control==0){
        if(x == 0){
            vector<int> t(n,0);
            combination=t;
            i=n; 
        }else control=1;
        if(x == n){
            vector<int> t(n,1);
            combination=t;
            i=n;
        }else control=1;
    }if(control==1){
        if (i<n && x > 0) {
            conta1++;
            combination[i] = 1;
            geraLinhas(x-1, n, combination, vec,i+1,1,nLinha);
        }
        if (i<n && n-i > x) {
            combination[i] = 0;
            geraLinhas(x, n, combination,vec,i+1,1, nLinha);
        }
    }
    for(int i = 0; i<combination.size(); i++){
        cout << combination[i] << " ";
    }
    cout << endl;  
    if(calculaTransicoesLinha(n,combination)==lt[nLinha-1]){ 
        vec[nLinha-1]= combination;
        vector<int> combination1(n);
        if(nLinha<n){
            if(verificaUntil(vec, nLinha,n)==1){
                cout << "bom "<< nLinha << endl; 
                geraLinhas(lb[nLinha], n, combination1, vec,0, 0, nLinha+1);
            }
        }   
    }
    return;          
}




int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int qrcodes;
    cin >> qrcodes;
    while(qrcodes--){
        
        if(!leitura())cout << "No QR Code generated!"<< endl;
        vector<int> combination(n);
        vector<vector<int>> vec(n);
        //generateCombinations(lb[0],n,combination,vec,0,1);
        geraLinhas(lb[0], n, combination,vec, 0,0,1);
        if (possiveis == 0) cout << "DEFECT: No QR Code generated!" << endl;
        else if (possiveis > 1) cout << "INVALID: " << possiveis << " QR Codes generated!" << endl;
        else printValid(vecaux);
        possiveis=0;
        cout << contador << endl;
        contador = 0;
    }
    return 0;
}