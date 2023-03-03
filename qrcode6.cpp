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




void buildMatrix(int linha,vector<int> &combination,vector<vector<int>>& vec,vector<int> &saldoColunas,vector<int> &marcado);

//gera uma linha inteira celula a celula
void gerador(int x, int linha, int inicio, int fim, vector<int> &combination,vector<vector<int>>& vec,vector<int> &saldoColunas,vector<int> &marcado){
    //if(!verificaUntil(vec,linha,n)==1) return;


    if(x > 0 && x+inicio==fim){
        for(int i = inicio; i<combination.size(); i++){
            combination[i]=1;
        } 
        inicio=fim;
    }
    
    if(inicio == fim){
        buildMatrix(linha, combination, vec,saldoColunas,marcado);
        return;
    }
    int calc = calculaTransicoesLinha(inicio, combination);
    int c = lt[linha-1];
    if(calc > lt[linha-1])return;
    if (x > 0 && saldoColunas[inicio]>0) {
        combination[inicio] = 1;
        saldoColunas[inicio]--;
        gerador(x-1, linha, inicio+1, fim, combination, vec, saldoColunas,marcado);
        saldoColunas[inicio]++;
    }
    
    if (n-inicio > x) {
        combination[inicio] = 0;
        gerador(x, linha,  inicio+1, fim,  combination, vec, saldoColunas,marcado);
    }
}

//gera uma linha inteira
void constroiLinhas(int n, vector<vector<int>>& vec,int linha,vector<int> &saldoColunas,vector<int> &marcado){
    vector<int> combination(n,0);
    contador++;
   
   if(marcado[linha-1] != 1){
    if(lb[linha-1] == n){
        vector<int> t(n,1);
        combination=t;
        marcado[linha-1]=1;
        buildMatrix(linha, combination, vec,saldoColunas,marcado);
    }
    else if(lb[linha-1] == 0){
        vector<int> t(n,0);
        combination=t;
        marcado[linha-1]=1;
        buildMatrix(linha, combination, vec,saldoColunas,marcado);
    }
    else if(lb[linha-1]==1 && lt[linha-1]%2 != 0){
        vector<int> t(n,0);
        combination=t;
        combination[0]=1;
        saldoColunas[0]--;
        gerador(lb[linha-1]-1, linha, 1,n,combination, vec,saldoColunas,marcado);
        combination[0]=0;
        saldoColunas[0]++;
        combination[n-1]=1;
        saldoColunas[n-1]--;
        gerador(lb[linha-1]-1, linha, 0,n-1,combination, vec, saldoColunas,marcado);
        saldoColunas[n-1]++;
    }else if(lt[linha-1]==1){
        vector<int> t(n,0);
        combination=t;
        for(int i = 0; i<lb[linha-1]; i++) combination[i]=1;
        buildMatrix(linha, combination, vec,saldoColunas,marcado);
        combination=t;
        for(int i = combination.size()-lb[linha-1]; i<combination.size(); i++) combination[i]=1;
        buildMatrix(linha, combination, vec,saldoColunas,marcado);
    }
    else {
        gerador(lb[linha-1], linha, 0,n,combination, vec,saldoColunas,marcado);
    }
   }
   else{
         if(linha==n && verifica(vec)==1){
            possiveis++;
            vecaux=vec;
        }
        if(linha<n){
            constroiLinhas(n,vec,linha+1,saldoColunas,marcado);
        }
   }
}

//acrescenta a linha gerada à matriz e ve se nao da problemas
void buildMatrix(int linha,vector<int> &combination,vector<vector<int>>& vec,vector<int> &saldoColunas,vector<int> &marcado){
    if(calculaTransicoesLinha(n,combination)==lt[linha-1]){
        vec[linha-1]=combination;
        if(linha<n && verificaUntil(vec,linha,n)==1) constroiLinhas(n,vec,linha+1,saldoColunas,marcado);
        if(linha==n && verifica(vec)==1){
            possiveis++;
            vecaux=vec;
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
            vector<int> saldoColunas(n,0);
            vector<int> marcado(n,-1);
            for(int i = 0; i<n; i++) saldoColunas[i] = cb[i];
            vector<int> combination(n);
            vector<vector<int>> vect( n , vector<int> (n,-1));
            constroiLinhas(n, vect,1,saldoColunas,marcado);
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