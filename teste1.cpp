#include <iostream>
#include <cmath>
#include <vector>

const int MAXSIZE = 30;
using namespace std;

int n, lb[MAXSIZE], cb[MAXSIZE], lt[MAXSIZE], ct[MAXSIZE], qb[4], db[2];

int possiveis=0;

int contador=0;

int aqui = 0;

vector<vector<int>> vecaux;
vector<int> order(30);

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


bool detetaDefeitos(){
    int contaPretoLinha = 0;
    int contaPretoColuna = 0;
    int contaPretoQuadrante = 0;

    /*int x = n/2;
    for(int i = 0;i<n;i++){
        if(cb[i]==n || cb[i]==0){
            if(ct[i] !=0)
                return false;
        }
        if(lb[i]==n || lb[i]==0){
            if(lt[i]!=0)
                return false;
        }
        if(lt[i] > n-1 || ct[i]>n-1)
            return false;
        if(lt[i] == n-1 || ct[i]== n-1){
            if(n%2==0){
                if(lb[i]!=x || cb[i]!=x)
                    return false;
            }
            else{
                if(lb[i]!=x+1 || cb[i]!=x+1||cb[i]!=x||lb[i]!=x)
                    return false;
            }
        }
    }*/

    for(int i = 0; i<n; i++){
        if(i<4) contaPretoQuadrante += qb[i];
        contaPretoColuna += cb[i];
        contaPretoLinha += lb[i];
    }
    if(n<4){
        for(int i = n; i<4; i++) contaPretoQuadrante+=qb[i];
    }
    if(contaPretoColuna!=contaPretoLinha || contaPretoLinha != contaPretoQuadrante || db[0]>n || db[1] > n
    || contaPretoColuna > n*n || contaPretoLinha > n*n || contaPretoQuadrante > n*n) {
        //cout << contaPretoColuna << " " << contaPretoLinha << " " << contaPretoQuadrante << endl;
        return true;
    }
    return false;
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
           // cout << conta << " " << ct[i] << endl;
           // return 0;
        }
        conta=0;
    }
    //if(conta1 > db[0]) return 0;
    //if(conta2 > db[1]) return 0;
    //if(nLinha==v) if(q1 != qb[0] || q2 != qb[1]) return 0;
    if(q1 > qb[0] || q2 > qb[1] || q3 > qb[2] || q4 > qb[3]) return 0;
    return 1;
}

int calculaTransicoesColuna(int novo, int linha, int coluna, vector<vector<int>>& vecc){
    int contaPreto = 0;
    int contaTrans = 0;
    int estadoAtual=vecc[0][coluna];

    vector<vector<int>> vec = vec;

    vec[linha-1][coluna]= novo;

    for(int i = 1; i<n; i++){
        if(vec[i][coluna]==1)contaPreto++;
        if(vec[i][coluna]!=estadoAtual){
            contaTrans++;
            estadoAtual=vec[i][coluna];
        }
    }  
    //cout << contaPreto << " " << contaTrans << " " <<cb[coluna] << " " << ct[coluna] << endl; 
    if(ct[coluna]< contaTrans)return 0;
    if(cb[coluna]< contaPreto)return 0;
    return 1;
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

int verifica(vector<vector<int>>& vec){
    int conta1 = 0;
    int conta2 = 0;
    int q1=0,q2=0,q3=0,q4=0;
    int conta = 0;
    int estadoAtual;
    int s = vec.size();
    int contaCol=0;

    for(int i = 0; i<n; i++){
        estadoAtual=vec[0][i];
        if(vec[i][i]==1) conta1++;
        if(vec[i][s-i-1]==1) conta2++;
        for(int j = 0; j<n; j++){
            if((j+1<n) && vec[j+1][i]!=estadoAtual){
                conta+=1;
                estadoAtual=vec[j+1][i];
            }
            if(vec[j][i]==1) contaCol+=1;
            if(vec[i][j]==1){
                if(i+1<=floor(s/2) && j+1 > floor(s/2)) q1++;
                if(i+1<=floor(s/2) && j +1<= floor(s/2)) q2++;
                if(i+1>floor(s/2) && j+1 <= floor(s/2)) q3++;
                if(i+1>floor(s/2) && j+1 > floor(s/2)) q4++;
            }
        }
        if(cb[i]!=contaCol) {
            return 0;
        }
        contaCol=0;
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


int verificaCol(vector<vector<int>>& vec){
    int conta1 = 0;
    int conta2 = 0;
    int q1=0,q2=0,q3=0,q4=0;
    int conta = 0;
    int estadoAtual;
    int s = vec.size();
    int contaLine=0;
    for(int i = 0; i<n; i++){
        estadoAtual=vec[i][0];
        if(vec[i][i]==1) conta1++;
        if(vec[i][s-i-1]==1) conta2++;
        for(int j = 0; j<n; j++){
            if((j+1<n) && vec[i][j+1]!=estadoAtual){
                conta+=1;
                estadoAtual=vec[i][j+1];
            }
            if(vec[i][j]==1) contaLine+=1;
            if(vec[i][j]==1){
                if(i+1<=floor(s/2) && j+1 > floor(s/2)) q1++;
                if(i+1<=floor(s/2) && j +1<= floor(s/2)) q2++;
                if(i+1>floor(s/2) && j+1 <= floor(s/2)) q3++;
                if(i+1>floor(s/2) && j+1 > floor(s/2)) q4++;
            }
        }
        if(lb[i]!=contaLine) {
            return 0;
        }
        contaLine=0;
        if(conta != lt[i]){
            //printValid(vec);
           // cout << conta << " " << lt[i] << endl;
            return 0;
        }
        conta=0;
    }
    if(conta1 != db[0]) return 0;
    if(conta2 != db[1]) return 0;
    if(q1 != qb[0] || q2 != qb[1] || q3 != qb[2] || q4 != qb[3]) return 0;
    return 1;
}




void buildMatrix(int linha,vector<int> &combination,vector<vector<int>>& vec,vector<int> &saldoColunas,int lineOrCol,int index);

//gera uma linha inteira celula a celula
void gerador(int x, int linha, int inicio, int fim, vector<int> &combination,vector<vector<int>>& vec,vector<int> &saldoColunas,int index){
    //if(!verificaUntil(vec,linha,n)==1) return;

    
    if(inicio == fim){
        buildMatrix(linha, combination, vec,saldoColunas,1,index);
        return;
    }
    int calc = calculaTransicoesLinha(inicio, combination);
    int c = lt[linha-1];
    if(calc > lt[linha-1])return;
    if (x > 0 && saldoColunas[inicio]>0) {
        combination[inicio] = 1;
        saldoColunas[inicio]--;
        gerador(x-1, linha, inicio+1, fim, combination, vec, saldoColunas,index);
        saldoColunas[inicio]++;
    }
    
    if (n-inicio > x) {
        combination[inicio] = 0;
        gerador(x, linha,  inicio+1, fim,  combination, vec, saldoColunas, index);
    }
}

void geradorColuna(int x, int linha, int inicio, int fim, vector<int> &combination,vector<vector<int>>& vec,vector<int> &saldoColunas,int index){
    //if(!verificaUntil(vec,linha,n)==1) return;

    
    if(inicio == fim){
        buildMatrix(linha, combination, vec,saldoColunas,0,index);
        return;
    }
    int calc = calculaTransicoesLinha(inicio, combination);
    int c = ct[linha-1];
    if(calc > ct[linha-1])return;
    if (x > 0 && saldoColunas[inicio]>0) {
        combination[inicio] = 1;
        saldoColunas[inicio]--;
        geradorColuna(x-1, linha, inicio+1, fim, combination, vec, saldoColunas,index);
        saldoColunas[inicio]++;
    }
    
    if (n-inicio > x) {
        combination[inicio] = 0;
        geradorColuna(x, linha,  inicio+1, fim,  combination, vec, saldoColunas, index);
    }
}



//gera uma linha inteira
void constroiLinhas(int n, vector<vector<int>>& vec,int linha,vector<int> &saldoColunas, int index){
    vector<int> combination(n,0);
    contador++;
    if(lb[linha-1] == n){
       // cout << linha << " aqui" << endl;
        //aqui++;
        //cout<<aqui<<"tudo a um"<<endl;
        vector<int> t(n,1);
        vec[linha-1]=t;
        if(index+1<n) constroiLinhas(n,vec,order[index+1],saldoColunas, index + 1);
        if(index+1==n && verifica(vec)==1){
            possiveis++;
            vecaux=vec;
        }
    }
    else if(lb[linha-1] == 0){
        //aqui++;
        //cout<<aqui<<endl;
        //cout << linha << " aqui1" << endl;
        vec[linha-1]=combination;
        if(index+1<n) constroiLinhas(n,vec,order[index+1],saldoColunas, index + 1);
        if(index+1==n && verifica(vec)==1){
            possiveis++;
            vecaux=vec;
        }
    }
    else if(lb[linha-1]==1 && lt[linha-1]%2 != 0){
       // cout << linha << " aqui2" << endl;
        vector<int> t(n,0);
        combination=t;
        combination[0]=1;
        saldoColunas[0]--;
        gerador(lb[linha-1]-1, linha, 1,n,combination, vec,saldoColunas,index);
        combination[0]=0;
        saldoColunas[0]++;
        combination[n-1]=1;
        saldoColunas[n-1]--;
        gerador(lb[linha-1]-1, linha, 0,n-1,combination, vec, saldoColunas,index);
        saldoColunas[n-1]++;
    }else if(lt[linha-1]==1){
       // cout << linha << " aqui3" << endl;
        vector<int> t(n,0);
        combination=t;
        for(int i = 0; i<lb[linha-1]; i++){ combination[i]=1;saldoColunas[i]--;}
        buildMatrix(linha, combination, vec,saldoColunas,1,index);
        for(int i = 0; i<lb[linha-1]; i++){saldoColunas[i]++;}
        combination=t;
        for(int i = combination.size()-lb[linha-1]; i<combination.size(); i++){combination[i]=1;saldoColunas[i]--;}
        buildMatrix(linha, combination, vec,saldoColunas,1,index);
        for(int i = combination.size()-lb[linha-1]; i<combination.size(); i++)saldoColunas[i]++;
    }else if(lt[linha-1]==n-1){
       // cout << linha << " aqui4" << endl; 
        vector<int> t(n,0);
        for(int i = 0; i<n; i++)if(i%2==0){t[i]=1;saldoColunas[i]--;}
        combination=t;
        buildMatrix(linha, combination, vec,saldoColunas,1,index);
        for(int i = 0; i<n; i++)if(i%2==0){t[i]=0;saldoColunas[i]++;}
        for(int i = 0; i<n; i++)if(i%2!=0){t[i]=1;saldoColunas[i]--;}
        combination=t;
        buildMatrix(linha, combination, vec,saldoColunas,1,index);
        for(int i = 0; i<n; i++)if(i%2!=0){t[i]=0;saldoColunas[i]++;}
    }
    else {
       // cout << linha << " aqui5" << endl;
        gerador(lb[linha-1], linha, 0,n,combination, vec,saldoColunas,index);
    }
}

//gera uma linha coluna
void constroiColunas(int n, vector<vector<int>>& vec,int coluna,vector<int> &saldoLinhas,int index){
    vector<int> combination(n,0);
    contador++;
    if(cb[coluna-1] == n){
        //aqui++;
        //cout<<aqui<<"tudo a um"<<endl;
        vector<int> t(n,1);
        for(int i = 0; i<n; i++)vec[i][coluna-1]=t[i];
        if(coluna<n) constroiColunas(n,vec,coluna+1,saldoLinhas,index+1);
        if(coluna==n && verificaCol(vec)==1){
            possiveis++;
            vecaux=vec;
        }
    }
    else if(cb[coluna-1] == 0){
        //aqui++;
        //cout<<aqui<<endl;
        for(int i = 0; i<n; i++)vec[i][coluna-1]=combination[i];
        if(coluna<n) constroiColunas(n,vec,coluna+1,saldoLinhas,index+1);
        if(coluna==n && verificaCol(vec)==1){
            possiveis++;
            vecaux=vec;
        }
    }
    else if(cb[coluna-1]==1 && ct[coluna-1]%2 != 0){
        vector<int> t(n,0);
        combination=t;
        combination[0]=1;
        saldoLinhas[0]--;
        geradorColuna(cb[coluna-1]-1, coluna, 1,n,combination, vec,saldoLinhas,index);
        combination[0]=0;
        saldoLinhas[0]++;
        combination[n-1]=1;
        saldoLinhas[n-1]--;
        geradorColuna(cb[coluna-1]-1, coluna, 0,n-1,combination, vec, saldoLinhas,index);
        saldoLinhas[n-1]++;
    }else if(ct[coluna-1]==1){
        vector<int> t(n,0);
        combination=t;
        for(int i = 0; i<cb[coluna-1]; i++){ combination[i]=1;saldoLinhas[i]--;}
        buildMatrix(coluna, combination, vec,saldoLinhas,0,index);
        for(int i = 0; i<cb[coluna-1]; i++){saldoLinhas[i]++;}
        combination=t;
        for(int i = combination.size()-cb[coluna-1]; i<combination.size(); i++){combination[i]=1;saldoLinhas[i]--;}
        buildMatrix(coluna, combination, vec,saldoLinhas,0,index);
        for(int i = combination.size()-cb[coluna-1]; i<combination.size(); i++)saldoLinhas[i]++;
    }else if(ct[coluna-1]==n-1){
        vector<int> t(n,0);
        for(int i = 0; i<n; i++)if(i%2==0){t[i]=1;saldoLinhas[i]--;}
        combination=t;
        buildMatrix(coluna, combination, vec,saldoLinhas,0,index);
        for(int i = 0; i<n; i++)if(i%2==0){t[i]=0;saldoLinhas[i]++;}
        for(int i = 0; i<n; i++)if(i%2!=0){t[i]=1;saldoLinhas[i]--;}
        combination=t;
        buildMatrix(coluna, combination, vec,saldoLinhas,0,index);
        for(int i = 0; i<n; i++)if(i%2!=0){t[i]=0;saldoLinhas[i]++;}
    }
    else {
        geradorColuna(cb[coluna-1], coluna, 0,n,combination, vec,saldoLinhas,index);
    }
}



/*
                    cout << linha << endl;
            for(int i = 0; i<n; i++){
                for(int j = 0; j<n; j++)
                    cout << vec[i][j] << " ";
                cout << endl;
            }
            cout << endl;*/


//acrescenta a linha gerada à matriz e ve se nao da problemas
void buildMatrix(int linha,vector<int> &combination,vector<vector<int>>& vec,vector<int> &saldoColunas, int lineOrCol,int index){
    if(lineOrCol==1 && calculaTransicoesLinha(n,combination)==lt[linha-1]){
        
        vec[linha-1]=combination;
        if(index<n-1 && verificaUntil(vec,n,n)==1){
            constroiLinhas(n,vec,order[index+1],saldoColunas,index+1);
        }
        if(index==n-1 && verifica(vec)==1){
            possiveis++;
            vecaux=vec;
        }
    }if(lineOrCol==0 && calculaTransicoesLinha(n,combination)==ct[linha-1]){
        for(int i = 0; i<n; i++)vec[i][linha-1]=combination[i];
        if(linha<n) constroiColunas(n,vec,linha+1,saldoColunas,index+1);
        if(linha==n && verificaCol(vec)==1){
            possiveis++;
            vecaux=vec;
            //printValid(vec);
        }
    }
}



int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int qrcodes;
    cin >> qrcodes;
    while(qrcodes--){
        if(!leitura() || detetaDefeitos())cout << "DEFECT: No QR Code generated!"<< endl;
        else{
            vector<int> saldo(n,0);
            vector<int> combination(n);
            vector<vector<int>> vect( n , vector<int> (n,0));
            int contaLine=0, contaCol=0;
            for(int i = 0; i<n; i++){
                contaLine+=lt[i];
                contaCol+=ct[i];
            }

            vector<int> aux(n);
            for(int i=0; i<n; i++) {
                order[i]=i+1;
                aux[i]= lt[i];
            }
            
            for(int i = 0; i < n - 1; ++i) 
            {
                int min_index = i; 
                for(int j = i + 1; j < n; ++j) 
                {
                    if(aux[j] < aux[min_index]) 
                        min_index = j;
                }
                swap(aux[i], aux[min_index]); 
                swap(order[i], order[min_index]); 
            }

            //for(int i = 0; i<n; i++) cout << order[i] << " ";
            //cout << endl;
            if(true){
                for(int i = 0; i<n; i++) saldo[i] = cb[i];
                constroiLinhas(n, vect,order[0],saldo, 0);
            }
            else{
                for(int i = 0; i<n; i++) saldo[i] = lb[i];
                constroiColunas(n, vect,order[0],saldo,0);
            }
            //cout<<aqui<<endl;
            if (possiveis == 0) cout << "DEFECT: No QR Code generated!" << endl;
            else if (possiveis > 1) cout << "INVALID: " << possiveis << " QR Codes generated!" << endl;
            else printValid(vecaux);
            possiveis=0;
            //cout << contador << endl;
            contador = 0;
        }
    }
    return 0;
}