void pos_pre_processa( vector<vector<int>> &vec,vector<int> &saldoColunas, vector<int> &saldoLinhas,vector<int> &saldoDiag,vector<int> &saldoQuad){
    int conta = 0;
    for(int i = 0; i<n; i++){
        //caso o saldo de celulas pretas da linha seja 0. Preenche as restantes celulas a branco
        if(saldoLinhas[i]==0){
            for(int j = 0; j<n; j++){
                if(vec[i][j]==-1){
                    vec[i][j]=0;
                }
            }
        }
        //caso o saldo de celulas pretas da coluna seja 0. Preenche as restantes celulas a branco
        if(saldoColunas[i]==0){
            for(int j = 0; j<n; j++){
                if(vec[j][i]==-1){
                    vec[j][i]=0;
                }
            }
        }
    }
     //coloca a preto se o saldo das colunas for igual ao numero de linhas por preencher (para casos com linhas todas a branco)
    for(int i = 0; i<n; i++){
        if(saldoColunas[i]==k){
            for(int j = 0; j<n; j++){
                if(vec[j][i]==-1 && vec[j][i]!=1){
                    saldoLinhas[j]--;
                    vec[j][i]=1;
                }
                if(i == j && vec[j][i]!=1){
                    saldoDiag[0]-=1;
                }
                if(i == n-i-1 && vec[j][i]!=1){
                    saldoDiag[1]-=1;
                }
            }
            saldoColunas[i]=0;
        }
    }
   //coloca a preto se o saldo das linhas for igual ao numero de colunas por preencher 
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
    if(conta > 0){
        pos_pre_processa(vec,saldoColunas,saldoLinhas,saldoDiag,saldoQuad)
    }   
}