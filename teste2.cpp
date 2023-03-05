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
vector<vector<int>> vecaux2;


void pre_processa( vector<vector<int>> &vec,vector<int> &saldoColunas, vector<int> &saldoLinhas);


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
        if((lb[i]==n|| lb[i]==0) && lt[i]>0) return true;
        if((cb[i]==n|| cb[i]==0) && ct[i]>0) return true;
    }

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
            else if(vec[i][j] == -1) cout<<"~";
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




void buildMatrix(int linha,vector<int> &combination,vector<vector<int>>& vec,vector<int> &saldoColunas,vector<int> &saldoLinhas);

//gera uma linha inteira celula a celula
void gerador(int x, int linha, int inicio, int fim, vector<int> &combination,vector<vector<int>>& vec,vector<int> &saldoColunas,vector<int> &saldoLinhas){
    //if(!verificaUntil(vec,linha,n)==1) return;

    if(inicio == fim){
        buildMatrix(linha, combination, vec,saldoColunas,saldoLinhas);
        return;
    }
    if(vecaux2[linha-1][inicio]!=-1){
        //cout << vecaux2[linha-1][inicio] << " " << linha << " " << inicio+1 <<endl;
        combination[inicio]=vecaux2[linha-1][inicio];
        int k = vecaux2[linha-1][inicio];
        gerador(x-k, linha, inicio+1, fim, combination, vec, saldoColunas,saldoLinhas);
    }else{
        int calc = calculaTransicoesLinha(inicio, combination);
        int c = lt[linha-1];
        if(calc > lt[linha-1])return;
        else{
            if (x > 0 && saldoColunas[inicio]>0) {
                combination[inicio] = 1;
                saldoColunas[inicio]--;
                saldoLinhas[linha-1]--;
                gerador(x-1, linha, inicio+1, fim, combination, vec, saldoColunas,saldoLinhas);
                saldoColunas[inicio]++;
                saldoLinhas[linha-1]++;
            }
            
            if (n-inicio > x) {
                combination[inicio] = 0;
                gerador(x, linha,  inicio+1, fim,  combination, vec, saldoColunas,saldoLinhas);
            }
        }
    }
}
vector<vector<int>> vecaux3;
//gera uma linha inteira
void constroiLinhas(int n, vector<vector<int>>& vec,int linha,vector<int> &saldoColunas, vector<int> &saldoLinhas){
    vector<int> combination(n,0);
    contador++;
    //printValid(vec);
    if(saldoLinhas[linha-1]==0 && linha!=n) {
        constroiLinhas(n, vec, linha+1, saldoColunas, saldoLinhas);
    }
    else if(saldoLinhas[linha-1]==0 && linha==n){
        if(linha==n && verifica(vec)==1){
            possiveis++;
            vecaux=vec;
        }
    }
    else {
        //cout << linha << " merda" << endl;
        gerador(lb[linha-1], linha, 0,n,combination, vec,saldoColunas,saldoLinhas);
    }
}

//acrescenta a linha gerada à matriz e ve se nao da problemas
void buildMatrix(int linha,vector<int> &combination,vector<vector<int>>& vec,vector<int> &saldoColunas, vector<int> &saldoLinhas){
    if(calculaTransicoesLinha(n,combination)==lt[linha-1]){
        vec[linha-1]=combination;
        if(linha<n && verificaUntil(vec,linha,n)==1) constroiLinhas(n,vec,linha+1,saldoColunas, saldoLinhas);
        //if(linha == n) printValid(vec);
        else if(linha==n && verifica(vec)==1){
           // for(int i = 0; i<n; i++) cout<< saldoLinhas[i]<<"\t";
           // cout << endl;
            //for(int i = 0; i<n; i++) cout<< saldoColunas[i]<<"\t";  
           // cout << endl; 
            possiveis++;
            vecaux=vec;
        }
    }
}

void pre_processa( vector<vector<int>> &vec,vector<int> &saldoColunas, vector<int> &saldoLinhas,vector<int> &saldoDiag,vector<int> &saldoQuad){
    int k = n;
    int y = n;
    int s = floor(n/2);
    int s_q1= s*(s+1);
    int s_q2=s*s;
    int s_q3=s*(s+1);
    int s_q4=(s+1)*(s+1);
    vector<int> preto(n,1);

    for(int i = 0;i<n;i++){
        if(lb[i]==1 && lt[i]==1){
            for(int k = 1; k<n-1; k++) vec[i][k]=0;
        }
        if(lt[i]==2 && lb[i]==n-1) {
            if(vec[i][0]==-1){
                vec[i][0]=1;
                saldoLinhas[i]-=1;
                saldoColunas[0]--;
            }
            if(vec[i][n-1]==-1){
                vec[i][n-1]=1;
                saldoLinhas[i]-=1;
                saldoColunas[n-1]--;
            }
        }
        if(lt[i]==1 && lb[i]==n-1) {
            vec[i]=preto;
            vec[i][0]=-1;
            vec[i][n-1]=-1;
            for(int k = 1; k<n-1; k++){saldoColunas[k]--; saldoLinhas[i]--;}
        }
        if(lb[i]== n){
            vector<int> black(n,1);
            for(int y = 0;y<n;y++){
                if(vec[i][y]==-1)
                    saldoColunas[y]--;
            }
            vec[i] = black;
            saldoLinhas[i] = 0;
        }
        if(cb[i] == n)
        {   
            for(int x = 0;x<n;x++){
                    if(vec[x][i] == -1){
                        vec[x][i] = 1;
                        saldoLinhas[x]--;
                    }       
            }  
            saldoColunas[i] = 0;
        }
        if(lb[i]==0){
                k--;
                vector<int> white(n,0);
                vec[i] = white;
        }

        if(cb[i] == 0){
                y--;
                for(int z = 0;z<n;z++){
                    if(vec[z][i] ==-1 )
                        vec[z][i] = 0;
            }
        }
    } 
    //for(int i = 0; i<n; i++) cout << i+1 << " " << saldoColunas[i] << " " << k << endl;
    for(int i = 0; i<n; i++){
        if(saldoColunas[i]==k){
            for(int j = 0; j<n; j++){
                if(vec[j][i]==-1 && vec[j][i]!=1){
                    saldoLinhas[j]--;
                    vec[j][i]=1;
                }
            }
            saldoColunas[i]=0;
        }
    }

    for(int i = 0; i<n; i++){
        if(saldoLinhas[i]==y){
            for(int j = 0; j<n; j++){
                if(vec[i][j]==-1 && vec[i][j]!=1){
                    saldoColunas[j]--;
                    vec[i][j]=1;
                }
            }
            saldoLinhas[i]=0;
        }
    }


    if(s_q1 == qb[0] || s_q2 == qb[1] || s_q3 == qb[2] || s_q4 == qb[3] || db[0]==n || db[1]==n || db[0]==0 || db[1]==0 ){
        for(int i = 0; i<n; i++){
            if(db[0]==n){
                if(vec[i][i]==-1 && vec[i][i]!=1) {
                    vec[i][i]=1;
                    saldoColunas[i]--;
                    saldoLinhas[i]--;
                }
            }
            if(db[0]==0){
                if(vec[i][i]==-1) {
                    vec[i][i]=0;
                }
            }
            if(db[1]==n){
                if(vec[i][n-i-1]==-1 && vec[i][n-i-1]!=1) {
                    vec[i][n-i-1]=1;
                    saldoColunas[n-i-1]--;
                    saldoLinhas[i]--;
                }
            }
            if(db[1]==0){
                if(vec[i][n-i-1]==-1) {
                    vec[i][n-i-1]=0;
                }
            }

            for(int j = 0; j<n; j++){
                if(s_q1 == qb[0]){
                    if(i+1<=floor(n/2) && j+1 > floor(n/2)){
                        if(vec[i][j]==-1 && vec[i][j]!=1){
                            vec[i][j] = 1;
                            saldoColunas[j]--;
                            saldoLinhas[i]--;
                        }
                    }
                }
                if(0 == qb[0]){
                    if(i+1<=floor(n/2) && j+1 > floor(n/2)){
                        if(vec[i][j]==-1){
                            vec[i][j] = 0;
                        }
                    }
                }
                if(s_q2 == qb[1]){
                    if(i+1<=floor(n/2) && j +1<= floor(n/2)){
                        if(vec[i][j]==-1 && vec[i][j]!=1){
                            vec[i][j] = 1;
                            saldoColunas[j]--;
                            saldoLinhas[i]--;
                        }
                    }
                }
                if(0 == qb[1]){
                    if(i+1<=floor(n/2) && j +1<= floor(n/2)){
                        if(vec[i][j]==-1){
                            vec[i][j] = 0;
                        }
                    }
                }
                if(s_q3 == qb[2]){
                    if(i+1>floor(n/2) && j+1 <= floor(n/2)){
                        if(vec[i][j]==-1 && vec[i][j]!=1){
                            vec[i][j] = 1;
                            saldoColunas[j]--;
                            saldoLinhas[i]--;
                        }
                    }
                }
                if(0 == qb[2]){
                    if(i+1>floor(n/2) && j+1 <= floor(n/2)){
                        if(vec[i][j]==-1){
                            vec[i][j] = 0;
                        }
                    }
                }
                if(s_q4 == qb[3]){
                    if(i+1>floor(n/2) && j+1 > floor(n/2)){
                        if(vec[i][j]==-1 && vec[i][j]!=1){
                            vec[i][j] = 1;
                            saldoColunas[j]--;
                            saldoLinhas[i]--;
                        }
                    }
                }
                if(0 == qb[3]){
                    if(i+1>floor(n/2) && j+1 > floor(n/2)){
                        if(vec[i][j]==-1){
                            vec[i][j] = 0;
                        }
                    }
                }
            }
        }
    }
    for(int i = 0; i<n; i++){
        if(saldoLinhas[i]==0){
            for(int j = 0; j<n; j++){
                if(vec[i][j]==-1){
                    vec[i][j]=0;
                }
            }
        }
        if(saldoColunas[i]==0){
            for(int j = 0; j<n; j++){
                if(vec[j][i]==-1){
                    vec[j][i]=0;
                }
            }
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
            for(int i = 0; i<n; i++) saldoColunas[i] = cb[i];
            vector<int> saldoLinhas(n,0);
            for(int i = 0; i<n; i++) saldoLinhas[i] = lb[i];
            vector<int> saldoDiag(2,0);
            saldoDiag[0]=db[0];
            saldoDiag[1]=db[1];
            vector<int> saldoQuad(4,0);
            saldoQuad[0]= qb[0];
            saldoQuad[1]= qb[1];
            saldoQuad[2]= qb[2];
            saldoQuad[3]= qb[3];
            vector<vector<int>> vect( n , vector<int> (n,-1));
            pre_processa(vect,saldoColunas,saldoLinhas, saldoDiag, saldoQuad);
             //for(int i = 0; i<n; i++) cout<< saldoLinhas[i]<<"\t";
             //for(int i = 0; i<n; i++) cout<< saldoColunas[i]<<"\t";
            vecaux2=vect;
            //printValid(vect);
            //vector<int> saldoColunas(n,0);
            //for(int i = 0; i<n; i++) saldoColunas[i] = cb[i];
            vector<int> combination(n);
            int c1=0, c2=0;
            for(int i = 0; i<n; i++){if(saldoColunas[i]>0)c1++; if(saldoLinhas[i]>0)c2++;}
           // for(int i = 0; i<n; i++) cout<< saldoLinhas[i]<<"\t";
           // cout << endl;
           // for(int i = 0; i<n; i++) cout<< saldoColunas[i]<<"\t";  
           // cout << endl; 
            if(c1 == 0 && c2 == 0) printValid(vect);
            else{
                constroiLinhas(n, vect,1,saldoColunas, saldoLinhas);
                //cout<<aqui<<endl;
                if (possiveis == 0) cout << "DEFECT: No QR Code generated!" << endl;
                else if (possiveis > 1) cout << "INVALID: " << possiveis << " QR Codes generated!" << endl;
                else printValid(vecaux);
                possiveis=0;
                //cout << contador << endl;
                contador = 0;
            }
        }
    }
    return 0;
}