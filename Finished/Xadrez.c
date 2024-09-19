#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRETAS "\x1b[30m"
#define BRANCAS "\x1b[37m"
#define CLARO "\e[0;104m"
#define ESCURO "\e[44m"
#define R "\e[0m"
#define LINHAS 8
#define COLUNAS 8
#define CARACTERES 4
#define PECAS 50

//Disciplina: Programação Estruturada e Modular
//Prof. Carlos Veríssimo

//Objetivo do Programa: Tabuleiro de xadrez 100% funcional
//Data - 03/09/2024
//Autor: Luis Fellipe Franco Arakaki

char tabuleiro[LINHAS][COLUNAS][CARACTERES] = { 
    {"PT1", "PC1", "PB1", "PD1", "PR1", "PB2", "PC2", "PT2"},
    {"PP1", "PP2", "PP3", "PP4", "PP5", "PP6", "PP7", "PP8"},
    {"   ", "   ", "   ", "   ", "   ", "   ", "   ", "   "},
    {"   ", "   ", "   ", "   ", "   ", "   ", "   ", "   "},
    {"   ", "   ", "   ", "   ", "   ", "   ", "   ", "   "},
    {"   ", "   ", "   ", "   ", "   ", "   ", "   ", "   "},
    {"BP1", "BP2", "BP3", "BP4", "BP5", "BP6", "BP7", "BP8"},
    {"BT1", "BC1", "BB1", "BD1", "BR1", "BB2", "BC2", "BT2"},
};
char bordas[18][16] = {
    R " |", R "8|", R "|8", R "7|", R "|𝘓", R "6|", R "|9", R "5|", R "|S", 
    R "4|", R "|߈", R "3|", R "|Ɛ", R "2|", R "|↊", R "1|", R "|⇂", R "|"
};
char* fundoClaro = CLARO;
char* fundoEscuro = ESCURO;
char* pecaBranca = BRANCAS;
char* pecaPreta = PRETAS;
int i, j, contadorEnPassant, contadorXeque, contadorBlock, contadorPecaBlock, contadorMate, linhaXeque, colunaXeque;
int contadorRoqueCurtoBranco = 1, contadorRoqueLongoBranco = 1;
int contadorRoqueCurtoPreto = 1, contadorRoqueLongoPreto = 1;
char pecaXeque[CARACTERES], pecasBlock[PECAS][CARACTERES];

void Exibir();
void Mover(char peca[CARACTERES], char destino[CARACTERES]);
void Roque(char peca[CARACTERES], char destino[CARACTERES], char torre[CARACTERES], char vazio[CARACTERES]);
void EnPassant(char peca[CARACTERES], char destino[CARACTERES]);
void JogadaBranca();
void JogadaPreta();
void JogadaBrancaXeque();
void JogadaPretaXeque();
void MoverTorre(int linhaPeca, int colunaPeca, char peca[CARACTERES]);
void MoverCavalo(int linhaPeca, int colunaPeca, char peca[CARACTERES]);
void MoverBispo(int linhaPeca, int colunaPeca, char peca[CARACTERES]);
void MoverDama(int linhaPeca, int colunaPeca, char peca[CARACTERES]);
void MoverRei(int linhaPeca, int colunaPeca, char peca[CARACTERES]);
void MoverPeao(int linhaPeca, int colunaPeca, char peca[CARACTERES]);
void MoverTorreXeque(int linhaPeca, int colunaPeca, char peca[CARACTERES]);
void MoverCavaloXeque(int linhaPeca, int colunaPeca, char peca[CARACTERES]);
void MoverBispoXeque(int linhaPeca, int colunaPeca, char peca[CARACTERES]);
void MoverDamaXeque(int linhaPeca, int colunaPeca, char peca[CARACTERES]);
void MoverPeaoXeque(int linhaPeca, int colunaPeca, char peca[CARACTERES]);
void ChecarPossivelRei(int linhaPeca, int colunaPeca, char peca[CARACTERES]);
void ChecarPossivelDama(int linhaPeca, int colunaPeca, char peca[CARACTERES]);
void ChecarPossivelTorre(int linhaPeca, int colunaPeca, char peca[CARACTERES]);
void ChecarPossivelCavalo(int linhaPeca, int colunaPeca, char peca[CARACTERES]);
void ChecarPossivelBispo(int linhaPeca, int colunaPeca, char peca[CARACTERES]);
void ChecarPossivelPeao(int linhaPeca, int colunaPeca, char peca[CARACTERES]);
void ChecarPossivelReiXeque(int linhaPeca, int colunaPeca, char peca[CARACTERES]);
void ChecarPossivelXeque(char peca[CARACTERES]);
void ChecarXequeBranco();
void ChecarXequePreto();
void ChecarXeque(char rei[CARACTERES], int linhaRei, int colunaRei);
void ChecarBlock(char rei[CARACTERES], int linhaRei, int colunaRei);
void ChecarMate1(char rei[CARACTERES], int linhaPeca, int colunaPeca);
void ChecarMate2(int linhaRei, int colunaRei);
void LimparBlock();
void Promocao(char peca[CARACTERES], char destino[CARACTERES]);


int main() {
    
    Exibir();
    
    while(contadorMate==0)
    {
        JogadaBranca();
        ChecarXequeBranco();
        if(contadorMate>0)
        {
            return (0);
        }
        JogadaPreta();
        ChecarXequePreto();
    }
    
    return (0);
}

void Exibir(){
    
    char linha[100], index[100], indexINV[100], espacoBranco[16], espacoPreto[16];
    int cont, borda;
    
    i=0;
    j=0;
    
    strcpy(linha, R "  --------------------------------------------------------");
    strcpy(index, R "     a      b      c      d      e      f      g      h");
    strcpy(indexINV, R "     ɐ      q      ɔ      p      ǝ      ɟ      ɓ      ɥ");
    strcpy(espacoBranco, CLARO "       ");
    strcpy(espacoPreto, ESCURO "       ");
  
    printf("\n%s",indexINV);
    printf("\n%s",linha);
    for(i=0;i<LINHAS;i=i+2)
    {
        printf("\n%s",bordas[0]);
        for(cont=0;cont<4;cont++)
        {
            printf("%s%s",espacoBranco, espacoPreto);
        }
        cont=0;
        printf("%s\n%s",bordas[17], bordas[borda+1]);
        for(j=0;j<COLUNAS;j++)
        {
            if(tabuleiro[i][j][0] == 'P')
            {
                if(j%2==0)
                {
                    printf("%s%s  %s  ",fundoClaro, pecaPreta, tabuleiro[i][j]);
                }
                else
                {
                    printf("%s%s  %s  ",fundoEscuro, pecaPreta, tabuleiro[i][j]);
                }
            }
            else
            {
                if(j%2==0)
                {
                    printf("%s%s  %s  ",fundoClaro, pecaBranca, tabuleiro[i][j]);
                }
                else
                {
                    printf("%s%s  %s  ",fundoEscuro, pecaBranca, tabuleiro[i][j]);
                }
            }
        }
        j=0;
        printf("%s\n%s",bordas[borda+2], bordas[0]);
        for(cont=0;cont<4;cont++)
        {
            printf("%s%s",espacoBranco, espacoPreto);
        }
        cont=0;
        printf("%s\n%s",bordas[17], bordas[0]);
        for(cont=0;cont<4;cont++)
        {
            printf("%s%s",espacoPreto, espacoBranco);
        }
        cont=0;
        printf("%s\n%s",bordas[17], bordas[borda+3]);
        for(j=0;j<COLUNAS;j++)
        {
            if(tabuleiro[i+1][j][0] == 'P')
            {
                if(j%2==0)
                {
                    printf("%s%s  %s  ",fundoEscuro, pecaPreta, tabuleiro[i+1][j]);
                }
                else
                {
                    printf("%s%s  %s  ",fundoClaro, pecaPreta, tabuleiro[i+1][j]);
                }
            }
            else
            {
                if(j%2==0)
                {
                    printf("%s%s  %s  ",fundoEscuro, pecaBranca, tabuleiro[i+1][j]);
                }
                else
                {
                    printf("%s%s  %s  ",fundoClaro, pecaBranca, tabuleiro[i+1][j]);
                }
            }
        }
        j=0;
        printf("%s\n%s",bordas[borda+4], bordas[0]);
        for(cont=0;cont<4;cont++)
        {
            printf("%s%s",espacoPreto, espacoBranco);
        }
        cont=0;
        printf("%s",bordas[17]);
        borda = borda+4;
    }
    printf("\n%s", linha);
    printf("\n%s\n\n",index);
    
    i=0;
    j=0;
    cont=0;
    borda=0;
}

void Mover(char peca[CARACTERES], char destino[CARACTERES]){
    
    int comp;
    
    i=0;
    j=0;
    
    for(i=0;i<LINHAS;i++)
    {
        for(j=0;j<COLUNAS;j++)
        {
            comp = strcmp(tabuleiro[i][j], "...");
            if(comp == 0)
            {
                strcpy(tabuleiro[i][j], "   ");
            }
        }
    }
    strcpy(destino, peca);
    strcpy(peca, "...");
    Exibir();
    
}

void Roque(char peca[CARACTERES], char destino[CARACTERES], char torre[CARACTERES], char vazio[CARACTERES]){
    
    int comp;
    
    i=0;
    j=0;
    
    for(i=0;i<LINHAS;i++)
    {
        for(j=0;j<COLUNAS;j++)
        {
            comp = strcmp(tabuleiro[i][j], "...");
            if(comp == 0)
            {
                strcpy(tabuleiro[i][j], "   ");
            }
        }
    }
    strcpy(destino, peca);
    strcpy(peca, "...");
    strcpy(vazio, torre);
    strcpy(torre, "   ");
    Exibir();
    
}

void JogadaBranca(){
    
    char peca[CARACTERES];
    int comp, linhaPeca, colunaPeca;
    linhaPeca = -1;
    colunaPeca = -1;
    
    printf("JOGADA BRANCAS\n");
    
    invalido:
    printf("Qual peça deseja mover?\n");
    printf("Digite como está representada no tabuleiro (Ex: Torre1 = 'BT1')\n");
    scanf("%s",peca);
    if(peca[0] != 'B')
    {
        printf("A peça movida deve ser branca\n\n");
        goto invalido;
    }
    for(i=0;i<LINHAS;i++)
    {
        for(j=0;j<COLUNAS;j++)
        {
            comp = strcmp(peca, tabuleiro[i][j]);
            if(comp == 0)
            {
                linhaPeca = i;
                colunaPeca = j;
                goto valido;
            }
        }
    }
    printf("Peça inválida, por favor digite como aparece no tabuleiro\n\n");
    goto invalido;
    
    valido:
    i=0;
    j=0;
    
    if(peca[1] == 'T')
    {
        ChecarPossivelTorre(linhaPeca, colunaPeca, peca);
        MoverTorre(linhaPeca, colunaPeca, peca);
    }
    if(peca[1] == 'C')
    {
        ChecarPossivelCavalo(linhaPeca, colunaPeca, peca);
        MoverCavalo(linhaPeca, colunaPeca, peca);
    }
    if(peca[1] == 'B')
    {
        ChecarPossivelBispo(linhaPeca, colunaPeca, peca);
        MoverBispo(linhaPeca, colunaPeca, peca);
    }
    if(peca[1] == 'D')
    {
        ChecarPossivelDama(linhaPeca, colunaPeca, peca);
        MoverDama(linhaPeca, colunaPeca, peca);
    }
    if(peca[1] == 'R')
    {
        ChecarPossivelRei(linhaPeca, colunaPeca, peca);
        MoverRei(linhaPeca, colunaPeca, peca);
    }
    if(peca[1] == 'P')
    {
        ChecarPossivelPeao(linhaPeca, colunaPeca, peca);
        MoverPeao(linhaPeca, colunaPeca, peca);
    }
}

void JogadaBrancaXeque(){
    
    char peca[CARACTERES];
    int comp, linhaPeca, colunaPeca;
    linhaPeca = -1;
    colunaPeca = -1;
    
    printf("JOGADA BRANCAS\n");
    printf("Voce está em xeque\n");
    
    invalido:
    printf("Qual peça deseja mover?\n");
    printf("Digite como está representada no tabuleiro (Ex: Torre1 = 'BT1')\n");
    scanf("%s",peca);
    if(peca[0] != 'B')
    {
        printf("A peça movida deve ser branca\n\n");
        goto invalido;
    }
    for(i=0;i<LINHAS;i++)
    {
        for(j=0;j<COLUNAS;j++)
        {
            comp = strcmp(peca, tabuleiro[i][j]);
            if(comp == 0)
            {
                linhaPeca = i;
                colunaPeca = j;
                goto valido;
            }
        }
    }
    printf("Peça inválida, por favor digite como aparece no tabuleiro\n\n");
    goto invalido;
    
    valido:
    i=0;
    j=0;
    
    if(peca[1] == 'T')
    {
        ChecarPossivelXeque(peca);
        MoverTorreXeque(linhaPeca, colunaPeca, peca);
    }
    if(peca[1] == 'C')
    {
        ChecarPossivelXeque(peca);
        MoverCavaloXeque(linhaPeca, colunaPeca, peca);
    }
    if(peca[1] == 'B')
    {
        ChecarPossivelXeque(peca);
        MoverBispoXeque(linhaPeca, colunaPeca, peca);
    }
    if(peca[1] == 'D')
    {
        ChecarPossivelXeque(peca);
        MoverDamaXeque(linhaPeca, colunaPeca, peca);
    }
    if(peca[1] == 'R')
    {
        ChecarPossivelReiXeque(linhaPeca, colunaPeca, peca);
        MoverRei(linhaPeca, colunaPeca, peca);
    }
    if(peca[1] == 'P')
    {
        ChecarPossivelXeque(peca);
        MoverPeaoXeque(linhaPeca, colunaPeca, peca);
    }
}

void JogadaPreta(){
    
    char peca[CARACTERES];
    int comp, linhaPeca, colunaPeca;
    linhaPeca = -1;
    colunaPeca = -1;
    
    printf("JOGADA PRETAS\n");
    
    invalido:
    printf("Qual peça deseja mover?\n");
    printf("Digite como está representada no tabuleiro (Ex: Torre1 = 'PT1')\n");
    scanf("%s",peca);
    if(peca[0] != 'P')
    {
        printf("A peça movida deve ser preta\n\n");
        goto invalido;
    }
    for(i=0;i<LINHAS;i++)
    {
        for(j=0;j<COLUNAS;j++)
        {
            comp = strcmp(peca, tabuleiro[i][j]);
            if(comp == 0)
            {
                linhaPeca = i;
                colunaPeca = j;
                goto valido;
            }
        }
    }
    printf("Peça inválida, por favor digite como aparece no tabuleiro\n\n");
    goto invalido;
    
    valido:
    i=0;
    j=0;
    
    if(peca[1] == 'T')
    {
        ChecarPossivelTorre(linhaPeca, colunaPeca, peca);
        MoverTorre(linhaPeca, colunaPeca, peca);
    }
    if(peca[1] == 'C')
    {
        ChecarPossivelCavalo(linhaPeca, colunaPeca, peca);
        MoverCavalo(linhaPeca, colunaPeca, peca);
    }
    if(peca[1] == 'B')
    {
        ChecarPossivelBispo(linhaPeca, colunaPeca, peca);
        MoverBispo(linhaPeca, colunaPeca, peca);
    }
    if(peca[1] == 'D')
    {
        ChecarPossivelDama(linhaPeca, colunaPeca, peca);
        MoverDama(linhaPeca, colunaPeca, peca);
    }
    if(peca[1] == 'R')
    {
        ChecarPossivelRei(linhaPeca, colunaPeca, peca);
        MoverRei(linhaPeca, colunaPeca, peca);
    }
    if(peca[1] == 'P')
    {
        ChecarPossivelPeao(linhaPeca, colunaPeca, peca);
        MoverPeao(linhaPeca, colunaPeca, peca);
    }
}

void JogadaPretaXeque(){
    
    char peca[CARACTERES];
    int comp, linhaPeca, colunaPeca;
    linhaPeca = -1;
    colunaPeca = -1;
    
    printf("JOGADA PRETAS\n");
    printf("Voce está em xeque\n");
    
    invalido:
    printf("Qual peça deseja mover?\n");
    printf("Digite como está representada no tabuleiro (Ex: Torre1 = 'PT1')\n");
    scanf("%s",peca);
    if(peca[0] != 'P')
    {
        printf("A peça movida deve ser preta\n\n");
        goto invalido;
    }
    for(i=0;i<LINHAS;i++)
    {
        for(j=0;j<COLUNAS;j++)
        {
            comp = strcmp(peca, tabuleiro[i][j]);
            if(comp == 0)
            {
                linhaPeca = i;
                colunaPeca = j;
                goto valido;
            }
        }
    }
    printf("Peça inválida, por favor digite como aparece no tabuleiro\n\n");
    goto invalido;
    
    valido:
    i=0;
    j=0;
    
    if(peca[1] == 'T')
    {
        ChecarPossivelXeque(peca);
        MoverTorreXeque(linhaPeca, colunaPeca, peca);
    }
    if(peca[1] == 'C')
    {
        ChecarPossivelXeque(peca);
        MoverCavaloXeque(linhaPeca, colunaPeca, peca);
    }
    if(peca[1] == 'B')
    {
        ChecarPossivelXeque(peca);
        MoverBispoXeque(linhaPeca, colunaPeca, peca);
    }
    if(peca[1] == 'D')
    {
        ChecarPossivelXeque(peca);
        MoverDamaXeque(linhaPeca, colunaPeca, peca);
    }
    if(peca[1] == 'R')
    {
        ChecarPossivelReiXeque(linhaPeca, colunaPeca, peca);
        MoverRei(linhaPeca, colunaPeca, peca);
    }
    if(peca[1] == 'P')
    {
        ChecarPossivelXeque(peca);
        MoverPeaoXeque(linhaPeca, colunaPeca, peca);
    }
}

void MoverTorre(int linhaPeca, int colunaPeca, char peca[CARACTERES]){
    
    int linhaDestino, colunaDestino;
    
    invalido:
    i = linhaPeca;
    j = colunaPeca;
    
    printf("Para qual linha deseja movê-la?\n");
    scanf("%i",&linhaDestino);
    printf("Para qual coluna deseja movê-la?\n");
    scanf("%i",&colunaDestino);
        
    colunaDestino = colunaDestino-1;
    linhaDestino = linhaDestino + 2*(4-linhaDestino);
    
    if(linhaDestino > 7 || linhaDestino < 0 || colunaDestino > 7 || colunaDestino < 0)
    {
        printf("Jogada inválida\n\n");
        goto invalido;
    }
    if(linhaDestino != linhaPeca && colunaDestino != colunaPeca)
    {
        printf("Jogada inválida\n\n");
        goto invalido;
    }
    if(linhaDestino == linhaPeca && colunaDestino == colunaPeca)
    {
        printf("Jogada inválida\n\n");
        goto invalido;
    }
    if(linhaDestino > linhaPeca)
    {
        i++;
        for(i=i;i<=linhaDestino;i++)
        {
            if(tabuleiro[i][j][0] == peca[0])
            {
                printf("Jogada inválida\n\n");
                goto invalido;
            }
        }
    }
    if(linhaDestino < linhaPeca)
    {
        i--;
        for(i=i;i>=linhaDestino;i--)
        {
            if(tabuleiro[i][j][0] == peca[0])
            {
                printf("Jogada inválida\n\n");
                goto invalido;
            }
        }
    }
    if(colunaDestino > colunaPeca)
    {
        j++;
        for(j=j;j<=colunaDestino;j++)
        {
            if(tabuleiro[i][j][0] == peca[0])
            {
                printf("Jogada inválida\n\n");
                goto invalido;
            }
        }
    }
    if(colunaDestino < colunaPeca)
    {
        j--;
        for(j=j;j>=colunaDestino;j--)
        {
            if(tabuleiro[i][j][0] == peca[0])
            {
                printf("Jogada inválida\n\n");
                goto invalido;
            }
        }
    }
    if(peca[0] == 'P' && peca[2] == '1')
    {
        contadorRoqueLongoPreto--;
    }
    if(peca[0] == 'B' && peca[2] == '1')
    {
        contadorRoqueLongoBranco--;
    }
    if(peca[0] == 'P' && peca[2] == '2')
    {
        contadorRoqueCurtoPreto--;
    }
    if(peca[0] == 'B' && peca[2] == '2')
    {
        contadorRoqueCurtoBranco--;
    }
    
    i=0;
    j=0;
    contadorEnPassant = 0;
    
    Mover(tabuleiro[linhaPeca][colunaPeca], tabuleiro[linhaDestino][colunaDestino]);
}

void MoverCavalo(int linhaPeca, int colunaPeca, char peca[CARACTERES]){
    
    int linhaDestino, colunaDestino;
    
    invalido:
    printf("Para qual linha deseja movê-la?\n");
    scanf("%i",&linhaDestino);
    printf("Para qual coluna deseja movê-la?\n");
    scanf("%i",&colunaDestino);
    
    colunaDestino = colunaDestino-1;
    linhaDestino = linhaDestino + 2*(4-linhaDestino);
    
    if(linhaDestino > 7 || linhaDestino < 0 || colunaDestino > 7 || colunaDestino < 0)
    {
        printf("Jogada inválida\n\n");
        goto invalido;
    }
    if(tabuleiro[linhaDestino][colunaDestino][0] == peca[0])
    {
        printf("Jogada inválida\n\n");
        goto invalido;
    }
    if(linhaDestino > linhaPeca+2 || colunaDestino > colunaPeca+2)
    {
        printf("Jogada inválida\n\n");
        goto invalido;
    }
    if(linhaDestino == linhaPeca || colunaDestino == colunaPeca)
    {
        printf("Jogada inválida\n\n");
        goto invalido;
    }
    if(abs(linhaDestino-linhaPeca) == abs(colunaDestino-colunaPeca))
    {
        printf("Jogada inválida\n\n");
        goto invalido;
    }
    
    contadorEnPassant = 0;

    Mover(tabuleiro[linhaPeca][colunaPeca], tabuleiro[linhaDestino][colunaDestino]);
}

void MoverBispo(int linhaPeca, int colunaPeca, char peca[CARACTERES]){
    
    int linhaDestino, colunaDestino;
    
    invalido:
    i = linhaPeca;
    j = colunaPeca;
    
    printf("Para qual linha deseja movê-la?\n");
    scanf("%i",&linhaDestino);
    printf("Para qual coluna deseja movê-la?\n");
    scanf("%i",&colunaDestino);
    
    colunaDestino = colunaDestino-1;
    linhaDestino = linhaDestino + 2*(4-linhaDestino);
    
    if(linhaDestino > 7 || linhaDestino < 0 || colunaDestino > 7 || colunaDestino < 0)
    {
        printf("Jogada inválida\n\n");
        goto invalido;
    }
    if(linhaDestino == linhaPeca || colunaDestino == colunaPeca)
    {
        printf("Jogada inválida\n\n");
        goto invalido;
    }
    if(abs(linhaDestino-linhaPeca) != abs(colunaDestino-colunaPeca))
    {
        printf("Jogada inválida\n\n");
        goto invalido;
    }
    if(linhaDestino > linhaPeca && colunaDestino > colunaPeca)
    {
        i++;
        j++;
        for(i=i;i<=linhaDestino;i++)
        {
            if(tabuleiro[i][j][0] == peca[0])
            {
                printf("Jogada inválida\n\n");
                goto invalido;
            }
            j++;
        }
    }
    if(linhaDestino < linhaPeca && colunaDestino > colunaPeca)
    {
        i--;
        j++;
        for(i=i;i>=linhaDestino;i--)
        {
            if(tabuleiro[i][j][0] == peca[0])
            {
                printf("Jogada inválida\n\n");
                goto invalido;
            }
            j++;
        }
    }
    if(linhaDestino > linhaPeca && colunaDestino < colunaPeca)
    {
        i++;
        j--;
        for(i=i;i<=linhaDestino;i++)
        {
            if(tabuleiro[i][j][0] == peca[0])
            {
                printf("Jogada inválida\n\n");
                goto invalido;
            }
            j--;
        }
    }
    if(linhaDestino < linhaPeca && colunaDestino < colunaPeca)
    {
        i--;
        j--;
        for(i=i;i>=linhaDestino;i--)
        {
            if(tabuleiro[i][j][0] == peca[0])
            {
                printf("Jogada inválida\n\n");
                goto invalido;
            }
            j--;
        }
    }
    
    i=0;
    j=0;
    contadorEnPassant = 0;
    
    Mover(tabuleiro[linhaPeca][colunaPeca], tabuleiro[linhaDestino][colunaDestino]);
}

void MoverDama(int linhaPeca, int colunaPeca, char peca[CARACTERES]){
    
    int linhaDestino, colunaDestino;
    
    invalido:
    i = linhaPeca;
    j = colunaPeca;
    
    printf("Para qual linha deseja movê-la?\n");
    scanf("%i",&linhaDestino);
    printf("Para qual coluna deseja movê-la?\n");
    scanf("%i",&colunaDestino);
    
    colunaDestino = colunaDestino-1;
    linhaDestino = linhaDestino + 2*(4-linhaDestino);
    
    if(linhaDestino > 7 || linhaDestino < 0 || colunaDestino > 7 || colunaDestino < 0)
    {
        printf("Jogada inválida\n\n");
        goto invalido;
    }
    if(linhaDestino == linhaPeca && colunaDestino == colunaPeca)
    {
        printf("Jogada inválida\n\n");
        goto invalido;
    }
    if(linhaDestino != linhaPeca && colunaDestino != colunaPeca)
    {
        if(abs(linhaDestino-linhaPeca) != abs(colunaDestino-colunaPeca))
        {
            printf("Jogada inválida\n\n");
            goto invalido;
        }
        if(linhaDestino > linhaPeca && colunaDestino > colunaPeca)
        {
            i++;
            j++;
            for(i=i;i<=linhaDestino;i++)
            {
                if(tabuleiro[i][j][0] == peca[0])
                {
                    printf("Jogada inválida\n\n");
                    goto invalido;
                }
                j++;
            }
        }
        if(linhaDestino < linhaPeca && colunaDestino > colunaPeca)
        {
            i--;
            j++;
            for(i=i;i>=linhaDestino;i--)
            {
                if(tabuleiro[i][j][0] == peca[0])
                {
                    printf("Jogada inválida\n\n");
                    goto invalido;
                }
                j++;
            }
        }
        if(linhaDestino > linhaPeca && colunaDestino < colunaPeca)
        {
            i++;
            j--;
            for(i=i;i<=linhaDestino;i++)
            {
                if(tabuleiro[i][j][0] == peca[0])
                {
                    printf("Jogada inválida\n\n");
                    goto invalido;
                }
                j--;
            }
        }
        if(linhaDestino < linhaPeca && colunaDestino < colunaPeca)
        {
            i--;
            j--;
            for(i=i;i>=linhaDestino;i--)
            {
                if(tabuleiro[i][j][0] == peca[0])
                {
                    printf("Jogada inválida\n\n");
                    goto invalido;
                }
                j--;
            }
        }
    }
    if(linhaDestino > linhaPeca)
    {
        i++;
        for(i=i;i<=linhaDestino;i++)
        {
            if(tabuleiro[i][j][0] == peca[0])
            {
                printf("Jogada inválida\n\n");
                goto invalido;
            }
        }
    }
    if(linhaDestino < linhaPeca)
    {
        i--;
        for(i=i;i>=linhaDestino;i--)
        {
            if(tabuleiro[i][j][0] == peca[0])
            {
                printf("Jogada inválida\n\n");
                goto invalido;
            }
        }
    }
    if(colunaDestino > colunaPeca)
    {
        j++;
        for(j=j;j<=colunaDestino;j++)
        {
            if(tabuleiro[i][j][0] == peca[0])
            {
                printf("Jogada inválida\n\n");
                goto invalido;
            }
        }
    }
    if(colunaDestino < colunaPeca)
    {
        j--;
        for(j=j;j>=colunaDestino;j--)
        {
            if(tabuleiro[i][j][0] == peca[0])
            {
                printf("Jogada inválida\n\n");
                goto invalido;
            }
        }
    }
    
    i=0;
    j=0;
    contadorEnPassant = 0;
    
    Mover(tabuleiro[linhaPeca][colunaPeca], tabuleiro[linhaDestino][colunaDestino]);
}

void MoverRei(int linhaPeca, int colunaPeca, char peca[CARACTERES]){
    
    int linhaDestino, colunaDestino;
    
    invalido:
    printf("Para qual linha deseja movê-la?\n");
    scanf("%i",&linhaDestino);
    printf("Para qual coluna deseja movê-la?\n");
    scanf("%i",&colunaDestino);
    
    colunaDestino = colunaDestino-1;
    linhaDestino = linhaDestino + 2*(4-linhaDestino);
    
    if(tabuleiro[linhaDestino][colunaDestino][0] == peca[0])
    {
        printf("Jogada inválida\n\n");
        goto invalido;
    }
    if(linhaDestino > 7 || linhaDestino < 0 || colunaDestino > 7 || colunaDestino < 0)
    {
        printf("Jogada inválida\n\n");
        goto invalido;
    }
    if(linhaDestino == linhaPeca && colunaDestino == colunaPeca)
    {
        printf("Jogada inválida\n\n");
        goto invalido;
    }
    if(linhaDestino > linhaPeca+1 || linhaDestino < linhaPeca-1)
    {
        printf("Jogada inválida\n\n");
        goto invalido;
    }
    
    i = linhaDestino;
    j = colunaDestino+1;
    
    for(j=j;j<COLUNAS;j++)
    {
        if(tabuleiro[i][j][0] == peca[0])
        {
            break;
        }
        if(tabuleiro[i][j][0] != peca[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
        {
            if(tabuleiro[i][j][1] != 'T' && tabuleiro[i][j][1] != 'D')
            {
                break;
            }
            else
            {
                printf("Jogada inválida\n\n");
                goto invalido;
            }
        }
    }
    
    j = colunaDestino-1;
    
    for(j=j;j>=0;j--)
    {
        if(tabuleiro[i][j][0] == peca[0])
        {
            break;
        }
        if(tabuleiro[i][j][0] != peca[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
        {
            if(tabuleiro[i][j][1] != 'T' && tabuleiro[i][j][1] != 'D')
            {
                break;
            }
            else
            {
                printf("Jogada inválida\n\n");
                goto invalido;
            }
        }
    }
    
    j = colunaDestino;
    i = linhaDestino+1;
    
    for(i=i;i<LINHAS;i++)
    {
        if(tabuleiro[i][j][0] == peca[0])
        {
            break;
        }
        if(tabuleiro[i][j][0] != peca[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
        {
            if(tabuleiro[i][j][1] != 'T' && tabuleiro[i][j][1] != 'D')
            {
                break;
            }
            else
            {
                printf("Jogada inválida\n\n");
                goto invalido;
            }
        }
    }
    
    i = linhaDestino-1;
    
    for(i=i;i>=0;i--)
    {
        if(tabuleiro[i][j][0] == peca[0])
        {
            break;
        }
        if(tabuleiro[i][j][0] != peca[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
        {
            if(tabuleiro[i][j][1] != 'T' && tabuleiro[i][j][1] != 'D')
            {
                break;
            }
            else
            {
                printf("Jogada inválida\n\n");
                goto invalido;
            }
        }
    }
    
    i = linhaDestino+1;
    j = colunaDestino+1;
    
    for(i=i;i<LINHAS;i++)
    {
        if(tabuleiro[i][j][0] == peca[0])
        {
            break;
        }
        if(tabuleiro[i][j][0] != peca[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
        {
            if(tabuleiro[i][j][1] != 'B' && tabuleiro[i][j][1] != 'D')
            {
                break;
            }
            else
            {
                printf("Jogada inválida\n\n");
                goto invalido;
            }
        }
        j++;
    }
    
    i = linhaDestino+1;
    j = colunaDestino-1;
    
    for(i=i;i<LINHAS;i++)
    {
        if(tabuleiro[i][j][0] == peca[0])
        {
            break;
        }
        if(tabuleiro[i][j][0] != peca[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
        {
            if(tabuleiro[i][j][1] != 'B' && tabuleiro[i][j][1] != 'D')
            {
                break;
            }
            else
            {
                printf("Jogada inválida\n\n");
                goto invalido;
            }
        }
        j--;
    }
    
    i = linhaDestino-1;
    j = colunaDestino+1;
    
    for(i=i;i>=0;i--)
    {
        if(tabuleiro[i][j][0] == peca[0])
        {
            break;
        }
        if(tabuleiro[i][j][0] != peca[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
        {
            if(tabuleiro[i][j][1] != 'B' && tabuleiro[i][j][1] != 'D')
            {
                break;
            }
            else
            {
                printf("Jogada inválida\n\n");
                goto invalido;
            }
        }
        j++;
    }
    
    i = linhaDestino-1;
    j = colunaDestino-1;
    
    for(i=i;i>=0;i--)
    {
        if(tabuleiro[i][j][0] == peca[0])
        {
            break;
        }
        if(tabuleiro[i][j][0] != peca[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
        {
            if(tabuleiro[i][j][1] != 'B' && tabuleiro[i][j][1] != 'D')
            {
                break;
            }
            else
            {
                printf("Jogada inválida\n\n");
                goto invalido;
            }
        }
        j--;
    }
    
    i = linhaDestino+2;
    j = colunaDestino+1;
    
    if(tabuleiro[i][j][0] != peca[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
    {
        if(tabuleiro[i][j][1] == 'C')
        {
            printf("Jogada inválida\n\n");
            goto invalido;
        }
    }
    
    i = linhaDestino+2;
    j = colunaDestino-1;
    
    if(tabuleiro[i][j][0] != peca[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
    {
        if(tabuleiro[i][j][1] == 'C')
        {
            printf("Jogada inválida\n\n");
            goto invalido;
        }
    }
    
    i = linhaDestino-2;
    j = colunaDestino+1;
    
    if(tabuleiro[i][j][0] != peca[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
    {
        if(tabuleiro[i][j][1] == 'C')
        {
            printf("Jogada inválida\n\n");
            goto invalido;
        }
    }
    
    i = linhaDestino-2;
    j = colunaDestino-1;
    
    if(tabuleiro[i][j][0] != peca[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
    {
        if(tabuleiro[i][j][1] == 'C')
        {
            printf("Jogada inválida\n\n");
            goto invalido;
        }
    }
    
    i = linhaDestino+1;
    j = colunaDestino+2;
    
    if(tabuleiro[i][j][0] != peca[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
    {
        if(tabuleiro[i][j][1] == 'C')
        {
            printf("Jogada inválida\n\n");
            goto invalido;
        }
    }
    
    i = linhaDestino-1;
    j = colunaDestino+2;
    
    if(tabuleiro[i][j][0] != peca[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
    {
        if(tabuleiro[i][j][1] == 'C')
        {
            printf("Jogada inválida\n\n");
            goto invalido;
        }
    }
    
    i = linhaDestino+1;
    j = colunaDestino-2;
    
    if(tabuleiro[i][j][0] != peca[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
    {
        if(tabuleiro[i][j][1] == 'C')
        {
            printf("Jogada inválida\n\n");
            goto invalido;
        }
    }
    
    i = linhaDestino-1;
    j = colunaDestino-2;
    
    if(tabuleiro[i][j][0] != peca[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
    {
        if(tabuleiro[i][j][1] == 'C')
        {
            printf("Jogada inválida\n\n");
            goto invalido;
        }
    }
    
    i = linhaDestino-1;
    j = colunaDestino;
    
    if(tabuleiro[i][j][0] != peca[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
    {
        if(tabuleiro[i][j][1] == 'P' || tabuleiro[i][j][1] == 'R')
        {
            printf("Jogada inválida\n\n");
            goto invalido;
        }
    }
    
    i = linhaDestino-1;
    j = colunaDestino-1;
    
    if(tabuleiro[i][j][0] != peca[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
    {
        if(tabuleiro[i][j][1] == 'P' || tabuleiro[i][j][1] == 'R')
        {
            printf("Jogada inválida\n\n");
            goto invalido;
        }
    }
    
    i = linhaDestino-1;
    j = colunaDestino+1;
    
    if(tabuleiro[i][j][0] != peca[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
    {
        if(tabuleiro[i][j][1] == 'P' || tabuleiro[i][j][1] == 'R')
        {
            printf("Jogada inválida\n\n");
            goto invalido;
        }
    }
    
    i = linhaDestino+1;
    j = colunaDestino;
    
    if(tabuleiro[i][j][0] != peca[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
    {
        if(tabuleiro[i][j][1] == 'P' || tabuleiro[i][j][1] == 'R')
        {
            printf("Jogada inválida\n\n");
            goto invalido;
        }
    }
    
    i = linhaDestino+1;
    j = colunaDestino-1;
    
    if(tabuleiro[i][j][0] != peca[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
    {
        if(tabuleiro[i][j][1] == 'P' || tabuleiro[i][j][1] == 'R')
        {
            printf("Jogada inválida\n\n");
            goto invalido;
        }
    }
    
    i = linhaDestino+1;
    j = colunaDestino+1;
    
    if(tabuleiro[i][j][0] != peca[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
    {
        if(tabuleiro[i][j][1] == 'P' || tabuleiro[i][j][1] == 'R')
        {
            printf("Jogada inválida\n\n");
            goto invalido;
        }
    }
    
    i = linhaDestino;
    j = colunaDestino+1;
    
    if(tabuleiro[i][j][0] != peca[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
    {
        if(tabuleiro[i][j][1] == 'P' || tabuleiro[i][j][1] == 'R')
        {
            printf("Jogada inválida\n\n");
            goto invalido;
        }
    }
    
    i = linhaDestino;
    j = colunaDestino-1;
    
    if(tabuleiro[i][j][0] != peca[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
    {
        if(tabuleiro[i][j][1] == 'P' || tabuleiro[i][j][1] == 'R')
        {
            printf("Jogada inválida\n\n");
            goto invalido;
        }
    }
    
    if(colunaDestino == colunaPeca-2 && linhaDestino == linhaPeca)
    {
        if(peca[0] == 'P')
        {
            if(contadorRoqueLongoPreto == 1)
            {
                if(tabuleiro[linhaDestino][colunaDestino+1][0] != ' ' && tabuleiro[linhaDestino][colunaDestino+1][0] != '.')
                {
                    printf("Jogada inválida\n\n");
                    goto invalido;
                }
                if(tabuleiro[linhaDestino][colunaDestino-1][0] != ' ' && tabuleiro[linhaDestino][colunaDestino-1][0] != '.')
                {
                    printf("Jogada inválida\n\n");
                    goto invalido;
                }
                ChecarXeque(peca, linhaDestino, colunaDestino+1);
                if(contadorXeque>0)
                {
                    printf("Jogada inválida\n\n");
                    goto invalido;
                }
                contadorRoqueCurtoPreto=0;
                contadorRoqueLongoPreto=0;
                Roque(tabuleiro[linhaPeca][colunaPeca], tabuleiro[linhaDestino][colunaDestino], tabuleiro[linhaDestino][colunaDestino-2], tabuleiro[linhaDestino][colunaDestino+1]);
                return;
            }
        }
        if(peca[0] == 'B')
        {
            if(contadorRoqueLongoBranco == 1)
            {
                if(tabuleiro[linhaDestino][colunaDestino+1][0] != ' ' && tabuleiro[linhaDestino][colunaDestino+1][0] != '.')
                {
                    printf("Jogada inválida\n\n");
                    goto invalido;
                }
                if(tabuleiro[linhaDestino][colunaDestino-1][0] != ' ' && tabuleiro[linhaDestino][colunaDestino-1][0] != '.')
                {
                    printf("Jogada inválida\n\n");
                    goto invalido;
                }
                ChecarXeque(peca, linhaDestino, colunaDestino+1);
                if(contadorXeque>0)
                {
                    printf("Jogada inválida\n\n");
                    goto invalido;
                }
                contadorRoqueCurtoBranco=0;
                contadorRoqueLongoBranco=0;
                Roque(tabuleiro[linhaPeca][colunaPeca], tabuleiro[linhaDestino][colunaDestino], tabuleiro[linhaDestino][colunaDestino-2], tabuleiro[linhaDestino][colunaDestino+1]);
                return;
            }
        }
    }
    if(colunaDestino == colunaPeca+2 && linhaDestino == linhaPeca)
    {
        if(peca[0] == 'P')
        {
            if(contadorRoqueCurtoPreto == 1)
            {
                if(tabuleiro[linhaDestino][colunaDestino-1][0] != ' ' && tabuleiro[linhaDestino][colunaDestino-1][0] != '.')
                {
                    printf("Jogada inválida\n\n");
                    goto invalido;
                }
                ChecarXeque(peca, linhaDestino, colunaDestino-1);
                if(contadorXeque>0)
                {
                    printf("Jogada inválida\n\n");
                    goto invalido;
                }
                contadorRoqueCurtoPreto=0;
                contadorRoqueLongoPreto=0;
                Roque(tabuleiro[linhaPeca][colunaPeca], tabuleiro[linhaDestino][colunaDestino], tabuleiro[linhaDestino][colunaDestino+1], tabuleiro[linhaDestino][colunaDestino-1]);
                return;
            }
        }
        if(peca[0] == 'B')
        {
            if(contadorRoqueCurtoBranco == 1)
            {
                if(tabuleiro[linhaDestino][colunaDestino-1][0] != ' ' && tabuleiro[linhaDestino][colunaDestino-1][0] != '.')
                {
                    printf("Jogada inválida\n\n");
                    goto invalido;
                }
                ChecarXeque(peca, linhaDestino, colunaDestino-1);
                if(contadorXeque>0)
                {
                    printf("Jogada inválida\n\n");
                    goto invalido;
                }
                contadorRoqueCurtoBranco=0;
                contadorRoqueLongoBranco=0;
                Roque(tabuleiro[linhaPeca][colunaPeca], tabuleiro[linhaDestino][colunaDestino], tabuleiro[linhaDestino][colunaDestino+1], tabuleiro[linhaDestino][colunaDestino-1]);
                return;
            }
        }
    }
    
    i=0;
    j=0;
    contadorEnPassant = 0;
    
    LimparBlock();
    Mover(tabuleiro[linhaPeca][colunaPeca], tabuleiro[linhaDestino][colunaDestino]);
}

void MoverPeao(int linhaPeca, int colunaPeca, char peca[CARACTERES]){
    
    int linhaDestino, colunaDestino;
    i = linhaPeca;
    j = colunaPeca;
    
    invalido:
    printf("Para qual linha deseja movê-la?\n");
    scanf("%i",&linhaDestino);
    printf("Para qual coluna deseja movê-la?\n");
    scanf("%i",&colunaDestino);
    
    colunaDestino = colunaDestino-1;
    linhaDestino = linhaDestino + 2*(4-linhaDestino);
    
    if(linhaDestino > 7 || linhaDestino < 0 || colunaDestino > 7 || colunaDestino < 0)
    {
        printf("Jogada inválida\n\n");
        goto invalido;
    }
    if(linhaDestino == linhaPeca && colunaDestino == colunaPeca)
    {
        printf("Jogada inválida\n\n");
        goto invalido;
    }
    if(colunaDestino > colunaPeca+1 || linhaDestino > linhaPeca+2)
    {
        printf("Jogada inválida\n\n");
        goto invalido;
    }
    if(peca[0] == 'B')
    {
        if(colunaDestino == colunaPeca+1 || colunaDestino == colunaPeca-1)
        {
            if(linhaDestino < linhaPeca-1)
            {
                printf("Jogada inválida\n\n");
                goto invalido;
            }
            if(tabuleiro[linhaDestino][colunaDestino][0] == 'B' || tabuleiro[linhaDestino][colunaDestino][0] == '.')
            {
                printf("Jogada inválida\n\n");
                goto invalido;
            }
            if(tabuleiro[linhaDestino][colunaDestino][0] == ' ' && tabuleiro[linhaDestino+1][colunaDestino][0] == 'P')
            {
                if(contadorEnPassant != 1)
                {
                    printf("Jogada inválida\n\n");
                    goto invalido;
                }
                EnPassant(tabuleiro[linhaPeca][colunaPeca], tabuleiro[linhaDestino][colunaDestino]);
                return;
            }
            else
            {
                printf("Jogada inválida\n\n");
                goto invalido;
            }
        }
        else
        {
            if(tabuleiro[linhaDestino][colunaDestino][0] != ' ' && tabuleiro[linhaDestino][colunaDestino][0] != '.')
            {
                printf("Jogada inválida\n\n");
                goto invalido;
            }
        }
        if(linhaPeca != 6)
        {
            if(colunaDestino > colunaPeca+1 || colunaDestino < colunaPeca-1 || linhaDestino < linhaPeca-1)
            {
                printf("Jogada inválida\n\n");
                goto invalido;
            }
        }
        if(colunaDestino > colunaPeca+1 || colunaDestino < colunaPeca-1 || linhaDestino < linhaPeca-2)
        {
            printf("Jogada inválida\n\n");
            goto invalido;
        }
        if(linhaDestino == linhaPeca-2)
        {
            contadorEnPassant = 1;
        }
        else
        {
            contadorEnPassant = 0;
        }
        if(linhaDestino == 0)
        {
            Promocao(tabuleiro[linhaPeca][colunaPeca], tabuleiro[linhaDestino][colunaDestino]);
            return;
        }
    }
    if(peca[0] == 'P')
    {
        if(colunaDestino == colunaPeca+1 || colunaDestino == colunaPeca-1)
        {
            if(linhaDestino > linhaPeca+1)
            {
                printf("Jogada inválida\n\n");
                goto invalido;
            }
            if(tabuleiro[linhaDestino][colunaDestino][0] == 'P' || tabuleiro[linhaDestino][colunaDestino][0] == '.')
            {
                printf("Jogada inválida\n\n");
                goto invalido;
            }
            if(tabuleiro[linhaDestino][colunaDestino][0] == ' ' && tabuleiro[linhaDestino-1][colunaDestino][0] == 'B')
            {
                if(contadorEnPassant != 1)
                {
                    printf("Jogada inválida\n\n");
                    goto invalido;
                }
                EnPassant(tabuleiro[linhaPeca][colunaPeca], tabuleiro[linhaDestino][colunaDestino]);
                return;
            }
            else
            {
                printf("Jogada inválida\n\n");
                goto invalido;
            }
        }
        else
        {
            if(tabuleiro[linhaDestino][colunaDestino][0] != ' ' && tabuleiro[linhaDestino][colunaDestino][0] != '.')
            {
                printf("Jogada inválida\n\n");
                goto invalido;
            }
        }
        if(linhaPeca != 1)
        {
            if(colunaDestino > colunaPeca+1 || colunaDestino < colunaPeca-1 || linhaDestino > linhaPeca+1)
            {
                printf("Jogada inválida\n\n");
                goto invalido;
            }
        }
        if(colunaDestino > colunaPeca+1 || colunaDestino < colunaPeca-1 || linhaDestino > linhaPeca+2)
        {
            printf("Jogada inválida\n\n");
            goto invalido;
        }
        if(linhaDestino == linhaPeca+2)
        {
            contadorEnPassant = 1;
        }
        else
        {
            contadorEnPassant = 0;
        }
        if(linhaDestino == 7)
        {
            Promocao(tabuleiro[linhaPeca][colunaPeca], tabuleiro[linhaDestino][colunaDestino]);
            return;
        }
    }
    
    i=0;
    j=0;
    
    Mover(tabuleiro[linhaPeca][colunaPeca], tabuleiro[linhaDestino][colunaDestino]);
}

void ChecarPossivelTorre(int linhaPeca, int colunaPeca, char peca[CARACTERES]){
    
    int cont;
    cont = 0;
    
    if(tabuleiro[linhaPeca+1][colunaPeca][0] == peca[0] || linhaPeca+1 > 7)
    {
        cont++;
    }
    if(tabuleiro[linhaPeca-1][colunaPeca][0] == peca[0] || linhaPeca-1 < 0)
    {
        cont++;
    }
    if(tabuleiro[linhaPeca][colunaPeca+1][0] == peca[0] || colunaPeca+1 > 7)
    {
        cont++;
    }
    if(tabuleiro[linhaPeca][colunaPeca-1][0] == peca[0] || colunaPeca-1 < 0)
    {
        cont++;
    }
    if(cont == 4)
    {
        if(peca[0] == 'B')
        {
            printf("Não existem movimentos válidos para essa peça\n\n");
            JogadaBranca();
        }
        if(peca[0] == 'P')
        {
            printf("Não existem movimentos válidos para essa peça\n\n");
            JogadaPreta();
        }
    }
}

void ChecarPossivelCavalo(int linhaPeca, int colunaPeca, char peca[CARACTERES]){
    
    int cont;
    cont = 0;
    
    if(tabuleiro[linhaPeca+2][colunaPeca+1][0] == peca[0] || linhaPeca+2 > 7 || colunaPeca+1 > 7)
    {
        cont++;
    }
    if(tabuleiro[linhaPeca+2][colunaPeca-1][0] == peca[0] || linhaPeca+2 > 7 || colunaPeca-1 < 0)
    {
        cont++;
    }
    if(tabuleiro[linhaPeca-2][colunaPeca+1][0] == peca[0] || linhaPeca-2 < 0 || colunaPeca+1 > 7)
    {
        cont++;
    }
    if(tabuleiro[linhaPeca-2][colunaPeca-1][0] == peca[0] || linhaPeca-2 < 0 || colunaPeca-1 < 0)
    {
        cont++;
    }
    if(tabuleiro[linhaPeca+1][colunaPeca+2][0] == peca[0] || linhaPeca+1 > 7 || colunaPeca+2 > 7)
    {
        cont++;
    }
    if(tabuleiro[linhaPeca+1][colunaPeca-2][0] == peca[0] || linhaPeca+1 > 7 || colunaPeca-2 < 0)
    {
        cont++;
    }
    if(tabuleiro[linhaPeca-1][colunaPeca+2][0] == peca[0] || linhaPeca-1 < 0 || colunaPeca+2 > 7)
    {
        cont++;
    }
    if(tabuleiro[linhaPeca-1][colunaPeca-2][0] == peca[0] || linhaPeca-1 < 0 || colunaPeca-2 < 0)
    {
        cont++;
    }
    if(cont == 8)
    {
        if(peca[0] == 'B')
        {
            printf("Não existem movimentos válidos para essa peça\n\n");
            JogadaBranca();
        }
        if(peca[0] == 'P')
        {
            printf("Não existem movimentos válidos para essa peça\n\n");
            JogadaPreta();
        }
    }
}

void ChecarPossivelBispo(int linhaPeca, int colunaPeca, char peca[CARACTERES]){
    
    int cont;
    cont = 0;
    
    if(tabuleiro[linhaPeca+1][colunaPeca+1][0] == peca[0] || linhaPeca+1 > 7 || colunaPeca+1 > 7)
    {
        cont++;
    }
    if(tabuleiro[linhaPeca-1][colunaPeca+1][0] == peca[0] || linhaPeca-1 < 0 || colunaPeca+1 > 7)
    {
        cont++;
    }
    if(tabuleiro[linhaPeca-1][colunaPeca-1][0] == peca[0] || linhaPeca-1 < 0 || colunaPeca-1 < 0)
    {
        cont++;
    }
    if(tabuleiro[linhaPeca+1][colunaPeca-1][0] == peca[0] || linhaPeca+1 > 7 || colunaPeca-1 < 0)
    {
        cont++;
    }
    if(cont == 4)
    {
        if(peca[0] == 'B')
        {
            printf("Não existem movimentos válidos para essa peça\n\n");
            JogadaBranca();
        }
        if(peca[0] == 'P')
        {
            printf("Não existem movimentos válidos para essa peça\n\n");
            JogadaPreta();
        }
    }
}

void ChecarPossivelDama(int linhaPeca, int colunaPeca, char peca[CARACTERES]){
    
    int cont;
    cont = 0;
    
    if(tabuleiro[linhaPeca+1][colunaPeca+1][0] == peca[0] || linhaPeca+1 > 7 || colunaPeca+1 > 7)
    {
        cont++;
    }
    if(tabuleiro[linhaPeca-1][colunaPeca+1][0] == peca[0] || linhaPeca-1 < 0 || colunaPeca+1 > 7)
    {
        cont++;
    }
    if(tabuleiro[linhaPeca-1][colunaPeca-1][0] == peca[0] || linhaPeca-1 < 0 || colunaPeca-1 < 0)
    {
        cont++;
    }
    if(tabuleiro[linhaPeca+1][colunaPeca-1][0] == peca[0] || linhaPeca+1 > 7 || colunaPeca-1 < 0)
    {
        cont++;
    }
    if(tabuleiro[linhaPeca+1][colunaPeca][0] == peca[0] || linhaPeca+1 > 7)
    {
        cont++;
    }
    if(tabuleiro[linhaPeca-1][colunaPeca][0] == peca[0] || linhaPeca-1 < 0)
    {
        cont++;
    }
    if(tabuleiro[linhaPeca][colunaPeca+1][0] == peca[0] || colunaPeca+1 > 7)
    {
        cont++;
    }
    if(tabuleiro[linhaPeca][colunaPeca-1][0] == peca[0] || colunaPeca-1 < 0)
    {
        cont++;
    }
    if(cont > 8)
    {
        if(peca[0] == 'B')
        {
            printf("Não existem movimentos válidos para essa peça\n\n");
            JogadaBranca();
        }
        if(peca[0] == 'P')
        {
            printf("Não existem movimentos válidos para essa peça\n\n");
            JogadaPreta();
        }
    }
}

void ChecarPossivelRei(int linhaPeca, int colunaPeca, char peca[CARACTERES]){
    
    int cont;
    cont = 0;
    
    if(tabuleiro[linhaPeca+1][colunaPeca+1][0] == peca[0] || linhaPeca+1 > 7 || colunaPeca+1 > 7)
    {
        cont++;
    }
    if(tabuleiro[linhaPeca-1][colunaPeca+1][0] == peca[0] || linhaPeca-1 < 0 || colunaPeca+1 > 7)
    {
        cont++;
    }
    if(tabuleiro[linhaPeca-1][colunaPeca-1][0] == peca[0] || linhaPeca-1 < 0 || colunaPeca-1 < 0)
    {
        cont++;
    }
    if(tabuleiro[linhaPeca+1][colunaPeca-1][0] == peca[0] || linhaPeca+1 > 7 || colunaPeca-1 < 0)
    {
        cont++;
    }
    if(tabuleiro[linhaPeca+1][colunaPeca][0] == peca[0] || linhaPeca+1 > 7)
    {
        cont++;
    }
    if(tabuleiro[linhaPeca-1][colunaPeca][0] == peca[0] || linhaPeca-1 < 0)
    {
        cont++;
    }
    if(tabuleiro[linhaPeca][colunaPeca+1][0] == peca[0] || colunaPeca+1 > 7)
    {
        cont++;
    }
    if(tabuleiro[linhaPeca][colunaPeca-1][0] == peca[0] || colunaPeca-1 < 0)
    {
        cont++;
    }
    ChecarXeque(peca, linhaPeca+1, colunaPeca+1);
    if(contadorXeque>0)
    {
        cont++;
    }
    ChecarXeque(peca, linhaPeca-1, colunaPeca+1);
    if(contadorXeque>0)
    {
        cont++;
    }
    ChecarXeque(peca, linhaPeca-1, colunaPeca-1);
    if(contadorXeque>0)
    {
        cont++;
    }
    ChecarXeque(peca, linhaPeca+1, colunaPeca-1);
    if(contadorXeque>0)
    {
        cont++;
    }
    ChecarXeque(peca, linhaPeca+1, colunaPeca);
    if(contadorXeque>0)
    {
        cont++;
    }
    ChecarXeque(peca, linhaPeca-1, colunaPeca);
    if(contadorXeque>0)
    {
        cont++;
    }
    ChecarXeque(peca, linhaPeca, colunaPeca+1);
    if(contadorXeque>0)
    {
        cont++;
    }
    ChecarXeque(peca, linhaPeca, colunaPeca-1);
    if(contadorXeque>0)
    {
        cont++;
    }
    if(cont >= 8)
    {
        if(peca[0] == 'B')
        {
            printf("Não existem movimentos válidos para essa peça\n\n");
            JogadaBranca();
        }
        if(peca[0] == 'P')
        {
            printf("Não existem movimentos válidos para essa peça\n\n");
            JogadaPreta();
        }
    }
}

void ChecarPossivelReiXeque(int linhaPeca, int colunaPeca, char peca[CARACTERES]){
    
    int cont;
    cont = 0;
    
    if(tabuleiro[linhaPeca+1][colunaPeca+1][0] == peca[0] || linhaPeca+1 > 7 || colunaPeca+1 > 7)
    {
        cont++;
    }
    if(tabuleiro[linhaPeca-1][colunaPeca+1][0] == peca[0] || linhaPeca-1 < 0 || colunaPeca+1 > 7)
    {
        cont++;
    }
    if(tabuleiro[linhaPeca-1][colunaPeca-1][0] == peca[0] || linhaPeca-1 < 0 || colunaPeca-1 < 0)
    {
        cont++;
    }
    if(tabuleiro[linhaPeca+1][colunaPeca-1][0] == peca[0] || linhaPeca+1 > 7 || colunaPeca-1 < 0)
    {
        cont++;
    }
    if(tabuleiro[linhaPeca+1][colunaPeca][0] == peca[0] || linhaPeca+1 > 7)
    {
        cont++;
    }
    if(tabuleiro[linhaPeca-1][colunaPeca][0] == peca[0] || linhaPeca-1 < 0)
    {
        cont++;
    }
    if(tabuleiro[linhaPeca][colunaPeca+1][0] == peca[0] || colunaPeca+1 > 7)
    {
        cont++;
    }
    if(tabuleiro[linhaPeca][colunaPeca-1][0] == peca[0] || colunaPeca-1 < 0)
    {
        cont++;
    }
    ChecarXeque(peca, linhaPeca+1, colunaPeca+1);
    if(contadorXeque>0)
    {
        cont++;
    }
    ChecarXeque(peca, linhaPeca-1, colunaPeca+1);
    if(contadorXeque>0)
    {
        cont++;
    }
    ChecarXeque(peca, linhaPeca-1, colunaPeca-1);
    if(contadorXeque>0)
    {
        cont++;
    }
    ChecarXeque(peca, linhaPeca+1, colunaPeca-1);
    if(contadorXeque>0)
    {
        cont++;
    }
    ChecarXeque(peca, linhaPeca+1, colunaPeca);
    if(contadorXeque>0)
    {
        cont++;
    }
    ChecarXeque(peca, linhaPeca-1, colunaPeca);
    if(contadorXeque>0)
    {
        cont++;
    }
    ChecarXeque(peca, linhaPeca, colunaPeca+1);
    if(contadorXeque>0)
    {
        cont++;
    }
    ChecarXeque(peca, linhaPeca, colunaPeca-1);
    if(contadorXeque>0)
    {
        cont++;
    }
    if(cont >= 8)
    {
        if(peca[0] == 'B')
        {
            printf("Não existem movimentos válidos para essa peça\n\n");
            JogadaBrancaXeque();
        }
        if(peca[0] == 'P')
        {
            printf("Não existem movimentos válidos para essa peça\n\n");
            JogadaPretaXeque();
        }
    }
}

void ChecarPossivelPeao(int linhaPeca, int colunaPeca, char peca[CARACTERES]){

    if(peca[0] == 'B')
    {
        if(tabuleiro[linhaPeca-1][colunaPeca][0] != ' ' && tabuleiro[linhaPeca-1][colunaPeca][0] != '.')
        {
            if(tabuleiro[linhaPeca-1][colunaPeca+1][0] == peca[0] || tabuleiro[linhaPeca-1][colunaPeca+1][0] == '.' || linhaPeca-1 < 0 || colunaPeca+1 > 7)
            {
                if(tabuleiro[linhaPeca-1][colunaPeca-1][0] == peca[0] || tabuleiro[linhaPeca-1][colunaPeca-1][0] == '.' || colunaPeca-1 < 0)
                {
                    printf("Não existem movimentos válidos para essa peça\n\n");
                    JogadaBranca();
                }
                else
                {
                    if(tabuleiro[linhaPeca-1][colunaPeca-1][0] == ' ')
                    {
                        if(contadorEnPassant != 1)
                        {
                            printf("Não existem movimentos válidos para essa peça\n\n");
                            JogadaBranca();
                        }
                    }
                }
            }
            else
            {
                if(tabuleiro[linhaPeca-1][colunaPeca+1][0] == ' ')
                {
                    if(contadorEnPassant != 1)
                    {
                        if(tabuleiro[linhaPeca-1][colunaPeca-1][0] == peca[0] || tabuleiro[linhaPeca-1][colunaPeca-1][0] == '.' || colunaPeca-1 < 0)
                        {
                            printf("Não existem movimentos válidos para essa peça\n\n");
                            JogadaBranca();
                        }
                        else
                        {
                            if(tabuleiro[linhaPeca-1][colunaPeca-1][0] == ' ')
                            {
                                if(contadorEnPassant != 1)
                                {
                                    printf("Não existem movimentos válidos para essa peça\n\n");
                                    JogadaBranca();
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if(peca[0] == 'P')
    {
        if(tabuleiro[linhaPeca+1][colunaPeca][0] != ' ' && tabuleiro[linhaPeca+1][colunaPeca][0] != '.')
        {
            if(tabuleiro[linhaPeca+1][colunaPeca+1][0] == peca[0] || tabuleiro[linhaPeca+1][colunaPeca+1][0] == '.' || linhaPeca+1 > 7 || colunaPeca+1 > 7)
            {
                if(tabuleiro[linhaPeca+1][colunaPeca-1][0] == peca[0] || tabuleiro[linhaPeca+1][colunaPeca-1][0] == '.' || linhaPeca+1 > 7 || colunaPeca-1 < 0)
                {
                    printf("Não existem movimentos válidos para essa peça\n\n");
                    JogadaPreta();
                }
                else
                {
                    if(tabuleiro[linhaPeca+1][colunaPeca-1][0] == ' ')
                    {
                        if(contadorEnPassant != 1)
                        {
                            printf("Não existem movimentos válidos para essa peça\n\n");
                            JogadaBranca();
                        }
                    }
                }
            }
            else
            {
                if(tabuleiro[linhaPeca+1][colunaPeca+1][0] == ' ')
                {
                    if(contadorEnPassant != 1)
                    {
                        if(tabuleiro[linhaPeca+1][colunaPeca-1][0] == peca[0] || tabuleiro[linhaPeca+1][colunaPeca-1][0] == '.' || colunaPeca-1 < 0)
                        {
                            printf("Não existem movimentos válidos para essa peça\n\n");
                            JogadaBranca();
                        }
                        else
                        {
                            if(tabuleiro[linhaPeca+1][colunaPeca-1][0] == ' ')
                            {
                                if(contadorEnPassant != 1)
                                {
                                    printf("Não existem movimentos válidos para essa peça\n\n");
                                    JogadaBranca();
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void ChecarXequeBranco(){
    
    int comp, linhaRei, colunaRei;
    char rei[CARACTERES];
    
    i=0;
    j=0;
    
    strcpy(rei, "PR1");
    
    for(i=0;i<LINHAS;i++)
    {
        for(j=0;j<COLUNAS;j++)
        {
            comp = strcmp(tabuleiro[i][j], rei);
            if(comp == 0)
            {
                linhaRei = i;
                colunaRei = j;
            }
        }
    }
    
    ChecarXeque(rei, linhaRei, colunaRei);
    
    if(contadorXeque>1)
    {
        ChecarMate1(rei, linhaRei, colunaRei);
    }
    if(contadorXeque == 1)
    {
        ChecarMate2(linhaRei, colunaRei);
    }
}

void ChecarXequePreto(){
    
    int comp, linhaRei, colunaRei;
    char rei[CARACTERES];
    
    i=0;
    j=0;
    
    strcpy(rei, "BR1");
    
    for(i=0;i<LINHAS;i++)
    {
        for(j=0;j<COLUNAS;j++)
        {
            comp = strcmp(tabuleiro[i][j], rei);
            if(comp == 0)
            {
                linhaRei = i;
                colunaRei = j;
            }
        }
    }
    
    ChecarXeque(rei, linhaRei, colunaRei);
    
    if(contadorXeque>1)
    {
        ChecarMate1(rei, linhaRei, colunaRei);
    }
    if(contadorXeque == 1)
    {
        ChecarMate2(linhaRei, colunaRei);
    }
}

void ChecarXeque(char rei[CARACTERES], int linhaRei, int colunaRei){
    
    contadorXeque=0;
    i = linhaRei;
    j = colunaRei+1;
    
    for(j=j;j<COLUNAS;j++)
    {
        if(tabuleiro[i][j][0] == rei[0])
        {
            break;
        }
        if(tabuleiro[i][j][0] != rei[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
        {
            if(tabuleiro[i][j][1] != 'T' && tabuleiro[i][j][1] != 'D')
            {
                break;
            }
            else
            {
                linhaXeque = i;
                colunaXeque = j;
                strcpy(pecaXeque, tabuleiro[i][j]);
                contadorXeque++;
                
                break;
            }
        }
    }
    
    i = linhaRei;
    j = colunaRei-1;
    
    for(j=j;j>=0;j--)
    {
        if(tabuleiro[i][j][0] == rei[0])
        {
            break;
        }
        if(tabuleiro[i][j][0] != rei[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
        {
            if(tabuleiro[i][j][1] != 'T' && tabuleiro[i][j][1] != 'D')
            {
                break;
            }
            else
            {
                linhaXeque = i;
                colunaXeque = j;
                strcpy(pecaXeque, tabuleiro[i][j]);
                contadorXeque++;
                
                break;
            }
        }
    }
    
    j = colunaRei;
    i = linhaRei+1;
    
    for(i=i;i<LINHAS;i++)
    {
        if(tabuleiro[i][j][0] == rei[0])
        {
            break;
        }
        if(tabuleiro[i][j][0] != rei[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
        {
            if(tabuleiro[i][j][1] != 'T' && tabuleiro[i][j][1] != 'D')
            {
                break;
            }
            else
            {
                linhaXeque = i;
                colunaXeque = j;
                strcpy(pecaXeque, tabuleiro[i][j]);
                contadorXeque++;
                
                break;
            }
        }
    }
    
    i = linhaRei-1;
    
    for(i=i;i>=0;i--)
    {
        if(tabuleiro[i][j][0] == rei[0])
        {
            break;
        }
        if(tabuleiro[i][j][0] != rei[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
        {
            if(tabuleiro[i][j][1] != 'T' && tabuleiro[i][j][1] != 'D')
            {
                break;
            }
            else
            {
                linhaXeque = i;
                colunaXeque = j;
                strcpy(pecaXeque, tabuleiro[i][j]);
                contadorXeque++;
                
                break;
            }
        }
    }
    
    i = linhaRei+1;
    j = colunaRei+1;
    
    for(i=i;i<LINHAS;i++)
    {
        if(tabuleiro[i][j][0] == rei[0])
        {
            break;
        }
        if(tabuleiro[i][j][0] != rei[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
        {
            if(tabuleiro[i][j][1] != 'B' && tabuleiro[i][j][1] != 'D')
            {
                break;
            }
            else
            {
                linhaXeque = i;
                colunaXeque = j;
                strcpy(pecaXeque, tabuleiro[i][j]);
                contadorXeque++;
                
                break;
            }
        }
        j++;
    }
    
    i = linhaRei+1;
    j = colunaRei-1;
    
    for(i=i;i<LINHAS;i++)
    {
        if(tabuleiro[i][j][0] == rei[0])
        {
            break;
        }
        if(tabuleiro[i][j][0] != rei[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
        {
            if(tabuleiro[i][j][1] != 'B' && tabuleiro[i][j][1] != 'D')
            {
                break;
            }
            else
            {
                linhaXeque = i;
                colunaXeque = j;
                strcpy(pecaXeque, tabuleiro[i][j]);
                contadorXeque++;
                
                break;
            }
        }
        j--;
    }
    
    i = linhaRei-1;
    j = colunaRei+1;
    
    for(i=i;i>=0;i--)
    {
        if(tabuleiro[i][j][0] == rei[0])
        {
            break;
        }
        if(tabuleiro[i][j][0] != rei[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
        {
            if(tabuleiro[i][j][1] != 'B' && tabuleiro[i][j][1] != 'D')
            {
                break;
            }
            else
            {
                linhaXeque = i;
                colunaXeque = j;
                strcpy(pecaXeque, tabuleiro[i][j]);
                contadorXeque++;
                
                break;
            }
        }
        j++;
    }
    
    i = linhaRei-1;
    j = colunaRei-1;
    
    for(i=i;i>=0;i--)
    {
        if(tabuleiro[i][j][0] == rei[0])
        {
            break;
        }
        if(tabuleiro[i][j][0] != rei[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
        {
            if(tabuleiro[i][j][1] != 'B' && tabuleiro[i][j][1] != 'D')
            {
                break;
            }
            else
            {
                linhaXeque = i;
                colunaXeque = j;
                strcpy(pecaXeque, tabuleiro[i][j]);
                contadorXeque++;
                
                break;
            }
        }
        j--;
    }
    
    i = linhaRei+2;
    j = colunaRei+1;
    
    if(tabuleiro[i][j][0] != rei[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
    {
        if(tabuleiro[i][j][1] == 'C')
        {
            linhaXeque = i;
            colunaXeque = j;
            strcpy(pecaXeque, tabuleiro[i][j]);
            contadorXeque++;
        }
    }
    
    i = linhaRei+2;
    j = colunaRei-1;
    
    if(tabuleiro[i][j][0] != rei[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
    {
        if(tabuleiro[i][j][1] == 'C')
        {
            linhaXeque = i;
            colunaXeque = j;
            strcpy(pecaXeque, tabuleiro[i][j]);
            contadorXeque++;
        }
    }
    
    i = linhaRei-2;
    j = colunaRei+1;
    
    if(tabuleiro[i][j][0] != rei[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
    {
        if(tabuleiro[i][j][1] == 'C')
        {
            linhaXeque = i;
            colunaXeque = j;
            strcpy(pecaXeque, tabuleiro[i][j]);
            contadorXeque++;
        }
    }
    
    i = linhaRei-2;
    j = colunaRei-1;
    
    if(tabuleiro[i][j][0] != rei[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
    {
        if(tabuleiro[i][j][1] == 'C')
        {
            linhaXeque = i;
            colunaXeque = j;
            strcpy(pecaXeque, tabuleiro[i][j]);
            contadorXeque++;
        }
    }
    
    i = linhaRei+1;
    j = colunaRei+2;
    
    if(tabuleiro[i][j][0] != rei[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
    {
        if(tabuleiro[i][j][1] == 'C')
        {
            linhaXeque = i;
            colunaXeque = j;
            strcpy(pecaXeque, tabuleiro[i][j]);
            contadorXeque++;
        }
    }
    
    i = linhaRei-1;
    j = colunaRei+2;
    
    if(tabuleiro[i][j][0] != rei[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
    {
        if(tabuleiro[i][j][1] == 'C')
        {
            linhaXeque = i;
            colunaXeque = j;
            strcpy(pecaXeque, tabuleiro[i][j]);
            contadorXeque++;
        }
    }
    
    i = linhaRei+1;
    j = colunaRei-2;
    
    if(tabuleiro[i][j][0] != rei[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
    {
        if(tabuleiro[i][j][1] == 'C')
        {
            linhaXeque = i;
            colunaXeque = j;
            strcpy(pecaXeque, tabuleiro[i][j]);
            contadorXeque++;
        }
    }
    
    i = linhaRei-1;
    j = colunaRei-2;
    
    if(tabuleiro[i][j][0] != rei[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
    {
        if(tabuleiro[i][j][1] == 'C')
        {
            linhaXeque = i;
            colunaXeque = j;
            strcpy(pecaXeque, tabuleiro[i][j]);
            contadorXeque++;
        }
    }
    
    i = linhaRei-1;
    j = colunaRei;
    
    if(tabuleiro[i][j][0] != rei[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
    {
        if(tabuleiro[i][j][1] == 'R')
        {
            linhaXeque = i;
            colunaXeque = j;
            strcpy(pecaXeque, tabuleiro[i][j]);
            contadorXeque++;
        }
    }
    
    i = linhaRei-1;
    j = colunaRei-1;
    
    if(tabuleiro[i][j][0] != rei[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
    {
        if(tabuleiro[i][j][1] == 'R')
        {
            linhaXeque = i;
            colunaXeque = j;
            strcpy(pecaXeque, tabuleiro[i][j]);
            contadorXeque++;
        }
    }
    
    i = linhaRei-1;
    j = colunaRei+1;
    
    if(tabuleiro[i][j][0] != rei[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
    {
        if(tabuleiro[i][j][1] == 'R')
        {
            linhaXeque = i;
            colunaXeque = j;
            strcpy(pecaXeque, tabuleiro[i][j]);
            contadorXeque++;
        }
    }
    
    i = linhaRei+1;
    j = colunaRei;
    
    if(tabuleiro[i][j][0] != rei[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
    {
        if(tabuleiro[i][j][1] == 'R')
        {
            linhaXeque = i;
            colunaXeque = j;
            strcpy(pecaXeque, tabuleiro[i][j]);
            contadorXeque++;
        }
    }
    
    i = linhaRei+1;
    j = colunaRei-1;
    
    if(tabuleiro[i][j][0] != rei[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
    {
        if(tabuleiro[i][j][1] == 'R')
        {
            linhaXeque = i;
            colunaXeque = j;
            strcpy(pecaXeque, tabuleiro[i][j]);
            contadorXeque++;
        }
    }
    
    i = linhaRei+1;
    j = colunaRei+1;
    
    if(tabuleiro[i][j][0] != rei[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
    {
        if(tabuleiro[i][j][1] == 'R')
        {
            linhaXeque = i;
            colunaXeque = j;
            strcpy(pecaXeque, tabuleiro[i][j]);
            contadorXeque++;
        }
    }
    
    i = linhaRei;
    j = colunaRei+1;
    
    if(tabuleiro[i][j][0] != rei[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
    {
        if(tabuleiro[i][j][1] == 'R')
        {
            linhaXeque = i;
            colunaXeque = j;
            strcpy(pecaXeque, tabuleiro[i][j]);
            contadorXeque++;
        }
    }
    
    i = linhaRei;
    j = colunaRei-1;
    
    if(tabuleiro[i][j][0] != rei[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
    {
        if(tabuleiro[i][j][1] == 'R')
        {
            linhaXeque = i;
            colunaXeque = j;
            strcpy(pecaXeque, tabuleiro[i][j]);
            contadorXeque++;
        }
    }
    if(rei[0] == 'P')
    {
        i = linhaRei+1;
        j = colunaRei+1;
        
        if(tabuleiro[i][j][1] == 'P' && tabuleiro[i][j][0] != rei[0])
        {
            linhaXeque = i;
            colunaXeque = j;
            strcpy(pecaXeque, tabuleiro[i][j]);
            contadorXeque++;
        }
        
        j = colunaRei-1;
        
        if(tabuleiro[i][j][1] == 'P' && tabuleiro[i][j][0] != rei[0])
        {
            linhaXeque = i;
            colunaXeque = j;
            strcpy(pecaXeque, tabuleiro[i][j]);
            contadorXeque++;
        }
    }
    if(rei[0] == 'B')
    {
        i = linhaRei-1;
        j = colunaRei+1;
        
        if(tabuleiro[i][j][1] == 'P' && tabuleiro[i][j][0] != rei[0])
        {
            linhaXeque = i;
            colunaXeque = j;
            strcpy(pecaXeque, tabuleiro[i][j]);
            contadorXeque++;
        }
        
        j = colunaRei-1;
        
        if(tabuleiro[i][j][1] == 'P' && tabuleiro[i][j][0] != rei[0])
        {
            linhaXeque = i;
            colunaXeque = j;
            strcpy(pecaXeque, tabuleiro[i][j]);
            contadorXeque++;
        }
    }
}

void ChecarBlock(char rei[CARACTERES], int linhaRei, int colunaRei){
    
    if(rei[0] == 'B')
    {
        i = linhaXeque-1;
        j = colunaXeque+1;
        
        if(tabuleiro[i][j][0] == 'P')
        {
            if(tabuleiro[i][j][1] == 'P')
            {
                strcpy(pecasBlock[contadorBlock], tabuleiro[i][j]);
                contadorBlock++;
            }
        }
        j = colunaXeque-1;
        
        if(tabuleiro[i][j][0] == 'P')
        {
            if(tabuleiro[i][j][1] == 'P')
            {
                strcpy(pecasBlock[contadorBlock], tabuleiro[i][j]);
                contadorBlock++;
            }
        }
    }
    
    if(rei[0] == 'P')
    {
        i = linhaXeque+1;
        j = colunaXeque+1;
        
        if(tabuleiro[i][j][0] == 'B')
        {
            if(tabuleiro[i][j][1] == 'P')
            {
                strcpy(pecasBlock[contadorBlock], tabuleiro[i][j]);
                contadorBlock++;
            }
        }
        j = colunaXeque-1;
        
        if(tabuleiro[i][j][0] == 'B')
        {
            if(tabuleiro[i][j][1] == 'P')
            {
                strcpy(pecasBlock[contadorBlock], tabuleiro[i][j]);
                contadorBlock++;
            }
        }
    }
    
    i = linhaRei;
    j = colunaRei+1;
    
    for(j=j;j<COLUNAS;j++)
    {
        if(tabuleiro[i][j][0] == rei[0])
        {
            break;
        }
        if(tabuleiro[i][j][0] != rei[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
        {
            if(tabuleiro[i][j][1] != 'T' && tabuleiro[i][j][1] != 'D')
            {
                break;
            }
            else
            {
                strcpy(pecasBlock[contadorBlock], tabuleiro[i][j]);
                contadorBlock++;
                
                break;
            }
        }
    }
    
    i = linhaRei;
    j = colunaRei-1;
    
    for(j=j;j>=0;j--)
    {
        if(tabuleiro[i][j][0] == rei[0])
        {
            break;
        }
        if(tabuleiro[i][j][0] != rei[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
        {
            if(tabuleiro[i][j][1] != 'T' && tabuleiro[i][j][1] != 'D')
            {
                break;
            }
            else
            {
                strcpy(pecasBlock[contadorBlock], tabuleiro[i][j]);
                contadorBlock++;
                
                break;
            }
        }
    }
    
    j = colunaRei;
    i = linhaRei+1;
    
    for(i=i;i<LINHAS;i++)
    {
        if(tabuleiro[i][j][0] == rei[0])
        {
            break;
        }
        if(tabuleiro[i][j][0] != rei[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
        {
            if(tabuleiro[i][j][1] != 'T' && tabuleiro[i][j][1] != 'D')
            {
                break;
            }
            else
            {
                strcpy(pecasBlock[contadorBlock], tabuleiro[i][j]);
                contadorBlock++;
                
                break;
            }
        }
    }
    
    i = linhaRei-1;
    
    for(i=i;i>=0;i--)
    {
        if(tabuleiro[i][j][0] == rei[0])
        {
            break;
        }
        if(tabuleiro[i][j][0] != rei[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
        {
            if(tabuleiro[i][j][1] != 'T' && tabuleiro[i][j][1] != 'D')
            {
                break;
            }
            else
            {
                strcpy(pecasBlock[contadorBlock], tabuleiro[i][j]);
                contadorBlock++;
                
                break;
            }
        }
    }
    
    i = linhaRei+1;
    j = colunaRei+1;
    
    for(i=i;i<LINHAS;i++)
    {
        if(tabuleiro[i][j][0] == rei[0])
        {
            break;
        }
        if(tabuleiro[i][j][0] != rei[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
        {
            if(tabuleiro[i][j][1] != 'B' && tabuleiro[i][j][1] != 'D')
            {
                break;
            }
            else
            {
                strcpy(pecasBlock[contadorBlock], tabuleiro[i][j]);
                contadorBlock++;
                
                break;
            }
        }
        j++;
    }
    
    i = linhaRei+1;
    j = colunaRei-1;
    
    for(i=i;i<LINHAS;i++)
    {
        if(tabuleiro[i][j][0] == rei[0])
        {
            break;
        }
        if(tabuleiro[i][j][0] != rei[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
        {
            if(tabuleiro[i][j][1] != 'B' && tabuleiro[i][j][1] != 'D')
            {
                break;
            }
            else
            {
                strcpy(pecasBlock[contadorBlock], tabuleiro[i][j]);
                contadorBlock++;
                
                break;
            }
        }
        j--;
    }
    
    i = linhaRei-1;
    j = colunaRei+1;
    
    for(i=i;i>=0;i--)
    {
        if(tabuleiro[i][j][0] == rei[0])
        {
            break;
        }
        if(tabuleiro[i][j][0] != rei[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
        {
            if(tabuleiro[i][j][1] != 'B' && tabuleiro[i][j][1] != 'D')
            {
                break;
            }
            else
            {
                strcpy(pecasBlock[contadorBlock], tabuleiro[i][j]);
                contadorBlock++;
                
                break;
            }
        }
        j++;
    }
    
    i = linhaRei-1;
    j = colunaRei-1;
    
    for(i=i;i>=0;i--)
    {
        if(tabuleiro[i][j][0] == rei[0])
        {
            break;
        }
        if(tabuleiro[i][j][0] != rei[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
        {
            if(tabuleiro[i][j][1] != 'B' && tabuleiro[i][j][1] != 'D')
            {
                break;
            }
            else
            {
                strcpy(pecasBlock[contadorBlock], tabuleiro[i][j]);
                contadorBlock++;
                
                break;
            }
        }
        j--;
    }
    
    i = linhaRei+2;
    j = colunaRei+1;
    
    if(tabuleiro[i][j][0] != rei[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
    {
        if(tabuleiro[i][j][1] == 'C')
        {
            strcpy(pecasBlock[contadorBlock], tabuleiro[i][j]);
            contadorBlock++;
        }
    }
    
    i = linhaRei+2;
    j = colunaRei-1;
    
    if(tabuleiro[i][j][0] != rei[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
    {
        if(tabuleiro[i][j][1] == 'C')
        {
            strcpy(pecasBlock[contadorBlock], tabuleiro[i][j]);
            contadorBlock++;
        }
    }
    
    i = linhaRei-2;
    j = colunaRei+1;
    
    if(tabuleiro[i][j][0] != rei[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
    {
        if(tabuleiro[i][j][1] == 'C')
        {
            strcpy(pecasBlock[contadorBlock], tabuleiro[i][j]);
            contadorBlock++;
        }
    }
    
    i = linhaRei-2;
    j = colunaRei-1;
    
    if(tabuleiro[i][j][0] != rei[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
    {
        if(tabuleiro[i][j][1] == 'C')
        {
            strcpy(pecasBlock[contadorBlock], tabuleiro[i][j]);
            contadorBlock++;
        }
    }
    
    i = linhaRei+1;
    j = colunaRei+2;
    
    if(tabuleiro[i][j][0] != rei[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
    {
        if(tabuleiro[i][j][1] == 'C')
        {
            strcpy(pecasBlock[contadorBlock], tabuleiro[i][j]);
            contadorBlock++;
        }
    }
    
    i = linhaRei-1;
    j = colunaRei+2;
    
    if(tabuleiro[i][j][0] != rei[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
    {
        if(tabuleiro[i][j][1] == 'C')
        {
            strcpy(pecasBlock[contadorBlock], tabuleiro[i][j]);
            contadorBlock++;
        }
    }
    
    i = linhaRei+1;
    j = colunaRei-2;
    
    if(tabuleiro[i][j][0] != rei[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
    {
        if(tabuleiro[i][j][1] == 'C')
        {
            strcpy(pecasBlock[contadorBlock], tabuleiro[i][j]);
            contadorBlock++;
        }
    }
    
    i = linhaRei-1;
    j = colunaRei-2;
    
    if(tabuleiro[i][j][0] != rei[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
    {
        if(tabuleiro[i][j][1] == 'C')
        {
            strcpy(pecasBlock[contadorBlock], tabuleiro[i][j]);
            contadorBlock++;
        }
    }
    
    if(rei[0] == 'B' && rei[1] != 'C')
    {
        i = linhaRei-1;
        j = colunaRei;
        if(tabuleiro[linhaRei][colunaRei][0] == ' ' || tabuleiro[linhaRei][colunaRei][0] == '.')
        {
            if(tabuleiro[i][j][0] != rei[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
            {
                if(tabuleiro[i][j][1] == 'P')
                {
                    strcpy(pecasBlock[contadorBlock], tabuleiro[i][j]);
                    contadorBlock++;
                }
            }
            if(linhaRei == 3)
            {
                i = linhaRei-2;
                if(tabuleiro[i][j][0] != rei[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
                {
                    if(tabuleiro[i][j][1] == 'P')
                    {
                        strcpy(pecasBlock[contadorBlock], tabuleiro[i][j]);
                        contadorBlock++;
                    }
                }
            }
        }
    }
    if(rei[0] == 'P')
    {
        i = linhaRei+1;
        j = colunaRei;
        if(tabuleiro[linhaRei][colunaRei][0] == ' ' || tabuleiro[linhaRei][colunaRei][0] == '.')
        {
            if(tabuleiro[i][j][0] != rei[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
            {
                if(tabuleiro[i][j][1] == 'P')
                {
                    strcpy(pecasBlock[contadorBlock], tabuleiro[i][j]);
                    contadorBlock++;
                }
            }
            if(linhaRei == 4)
            {
                i = linhaRei+2;
                if(tabuleiro[i][j][0] != rei[0] && tabuleiro[i][j][0] != ' ' && tabuleiro[i][j][0] != '.')
                {
                    if(tabuleiro[i][j][1] == 'P')
                    {
                        strcpy(pecasBlock[contadorBlock], tabuleiro[i][j]);
                        contadorBlock++;
                    }
                }
            }
        }
    }
    
    i = linhaRei;
    j = colunaRei;
}

void ChecarMate1(char peca[CARACTERES], int linhaPeca, int colunaPeca){
    
    int cont;
    cont = 0;
    
    if(tabuleiro[linhaPeca+1][colunaPeca+1][0] == peca[0] || linhaPeca+1 > 7 || colunaPeca+1 > 7)
    {
        cont++;
    }
    if(tabuleiro[linhaPeca-1][colunaPeca+1][0] == peca[0] || linhaPeca-1 < 0 || colunaPeca+1 > 7)
    {
        cont++;
    }
    if(tabuleiro[linhaPeca-1][colunaPeca-1][0] == peca[0] || linhaPeca-1 < 0 || colunaPeca-1 < 0)
    {
        cont++;
    }
    if(tabuleiro[linhaPeca+1][colunaPeca-1][0] == peca[0] || linhaPeca+1 > 7 || colunaPeca-1 < 0)
    {
        cont++;
    }
    if(tabuleiro[linhaPeca+1][colunaPeca][0] == peca[0] || linhaPeca+1 > 7)
    {
        cont++;
    }
    if(tabuleiro[linhaPeca-1][colunaPeca][0] == peca[0] || linhaPeca-1 < 0)
    {
        cont++;
    }
    if(tabuleiro[linhaPeca][colunaPeca+1][0] == peca[0] || colunaPeca+1 > 7)
    {
        cont++;
    }
    if(tabuleiro[linhaPeca][colunaPeca-1][0] == peca[0] || colunaPeca-1 < 0)
    {
        cont++;
    }
    ChecarXeque(peca, linhaPeca+1, colunaPeca+1);
    if(contadorXeque>0)
    {
        cont++;
    }
    ChecarXeque(peca, linhaPeca-1, colunaPeca+1);
    if(contadorXeque>0)
    {
        cont++;
    }
    ChecarXeque(peca, linhaPeca-1, colunaPeca-1);
    if(contadorXeque>0)
    {
        cont++;
    }
    ChecarXeque(peca, linhaPeca+1, colunaPeca-1);
    if(contadorXeque>0)
    {
        cont++;
    }
    ChecarXeque(peca, linhaPeca+1, colunaPeca);
    if(contadorXeque>0)
    {
        cont++;
    }
    ChecarXeque(peca, linhaPeca-1, colunaPeca);
    if(contadorXeque>0)
    {
        cont++;
    }
    ChecarXeque(peca, linhaPeca, colunaPeca+1);
    if(contadorXeque>0)
    {
        cont++;
    }
    ChecarXeque(peca, linhaPeca, colunaPeca-1);
    if(contadorXeque>0)
    {
        cont++;
    }
    if(cont >= 8)
    {
        printf("Xeque-Mate");
        contadorMate++;
    }
    else
    {
        if(peca[0] == 'B')
        {
            JogadaBrancaXeque();
        }
        if(peca[0] == 'P')
        {
            JogadaPretaXeque();
        }
    }
}

void ChecarMate2(int linhaRei, int colunaRei){
    
    char rei[CARACTERES], peca[CARACTERES];
    
    strcpy(peca, pecaXeque);
    
    if(peca[0] == 'P')
    {
        strcpy(rei, "BR1");   
    }
    if(peca[0] == 'B')
    {
        strcpy(rei, "PR1");   
    }
    
    i = linhaXeque;
    j = colunaXeque;
    
    if(linhaXeque > linhaRei  && colunaXeque == colunaRei)
    {
        for(i=i;i>linhaRei;i--)
        {
            ChecarBlock(peca, i, j);
        }
        if(contadorBlock>0)
        {
            if(pecasBlock[0][0] == 'B')
            {
                JogadaBrancaXeque();
            }
            if(pecasBlock[0][0] == 'P')
            {
                JogadaPretaXeque();
            }
        }
    }
    if(linhaXeque < linhaRei  && colunaXeque == colunaRei)
    {
        for(i=i;i<linhaRei;i++)
        {
            ChecarBlock(peca, i, j);
        }
        if(contadorBlock>0)
        {
            if(pecasBlock[0][0] == 'B')
            {
                JogadaBrancaXeque();
            }
            if(pecasBlock[0][0] == 'P')
            {
                JogadaPretaXeque();
            }
        }
    }
    if(linhaXeque == linhaRei  && colunaXeque > colunaRei)
    {
        for(j=j;j>colunaRei;j--)
        {
            ChecarBlock(peca, i, j);
        }
        if(contadorBlock>0)
        {
            if(pecasBlock[0][0] == 'B')
            {
                JogadaBrancaXeque();
            }
            if(pecasBlock[0][0] == 'P')
            {
                JogadaPretaXeque();
            }
        }
    }
    if(linhaXeque == linhaRei  && colunaXeque < colunaRei)
    {
        for(j=j;j<colunaRei;j++)
        {
            ChecarBlock(peca, i, j);
        }
        if(contadorBlock>0)
        {
            if(pecasBlock[0][0] == 'B')
            {
                JogadaBrancaXeque();
            }
            if(pecasBlock[0][0] == 'P')
            {
                JogadaPretaXeque();
            }
        }
    }
    if(abs(linhaXeque-linhaRei) == abs(colunaXeque-colunaRei))
    {
        if(linhaXeque > linhaRei && colunaXeque > colunaRei)
        {
            for(i=i;i>linhaRei;i--)
            {
                ChecarBlock(peca, i, j);
                j--;
            }
            if(contadorBlock>0)
            {
                if(pecasBlock[0][0] == 'B')
                {
                    JogadaBrancaXeque();
                }
                if(pecasBlock[0][0] == 'P')
                {
                    JogadaPretaXeque();
                }
            }
        }
        if(linhaXeque > linhaRei && colunaXeque < colunaRei)
        {
            for(i=i;i>linhaRei;i--)
            {
                ChecarBlock(peca, i, j);
                j++;
            }
            if(contadorBlock>0)
            {
                if(pecasBlock[0][0] == 'B')
                {
                    JogadaBrancaXeque();
                }
                if(pecasBlock[0][0] == 'P')
                {
                    JogadaPretaXeque();
                }
            }
        }
        if(linhaXeque < linhaRei && colunaXeque > colunaRei)
        {
            for(i=i;i<linhaRei;i++)
            {
                ChecarBlock(peca, i, j);
                j--;
            }
            if(contadorBlock>0)
            {
                if(pecasBlock[0][0] == 'B')
                {
                    JogadaBrancaXeque();
                }
                if(pecasBlock[0][0] == 'P')
                {
                    JogadaPretaXeque();
                }
            }
        }
        if(linhaXeque < linhaRei && colunaXeque < colunaRei)
        {
            for(i=i;i<linhaRei;i++)
            {
                ChecarBlock(peca, i, j);
                j++;
            }
            if(contadorBlock>0)
            {
                if(pecasBlock[0][0] == 'B')
                {
                    JogadaBrancaXeque();
                }
                if(pecasBlock[0][0] == 'P')
                {
                    JogadaPretaXeque();
                }
            }
        }
    }
    if(linhaXeque == linhaRei+2 && colunaXeque == colunaRei+1)
    {
        ChecarBlock(peca, i, j);
        if(contadorBlock>0)
        {
            if(pecasBlock[0][0] == 'B')
            {
                JogadaBrancaXeque();
            }
            if(pecasBlock[0][0] == 'P')
            {
                JogadaPretaXeque();
            }
        }
    }
    if(linhaXeque == linhaRei+2 && colunaXeque == colunaRei-1)
    {
        ChecarBlock(peca, i, j);
        if(contadorBlock>0)
        {
            if(pecasBlock[0][0] == 'B')
            {
                JogadaBrancaXeque();
            }
            if(pecasBlock[0][0] == 'P')
            {
                JogadaPretaXeque();
            }
        }
    }
    if(linhaXeque == linhaRei-2 && colunaXeque == colunaRei+1)
    {
        ChecarBlock(peca, i, j);
        if(contadorBlock>0)
        {
            if(pecasBlock[0][0] == 'B')
            {
                JogadaBrancaXeque();
            }
            if(pecasBlock[0][0] == 'P')
            {
                JogadaPretaXeque();
            }
        }
    }
    if(linhaXeque == linhaRei-2 && colunaXeque == colunaRei-1)
    {
        ChecarBlock(peca, i, j);
        if(contadorBlock>0)
        {
            if(pecasBlock[0][0] == 'B')
            {
                JogadaBrancaXeque();
            }
            if(pecasBlock[0][0] == 'P')
            {
                JogadaPretaXeque();
            }
        }
    }
    if(linhaXeque == linhaRei+1 && colunaXeque == colunaRei+2)
    {
        ChecarBlock(peca, i, j);
        if(contadorBlock>0)
        {
            if(pecasBlock[0][0] == 'B')
            {
                JogadaBrancaXeque();
            }
            if(pecasBlock[0][0] == 'P')
            {
                JogadaPretaXeque();
            }
        }
    }
    if(linhaXeque == linhaRei+1 && colunaXeque == colunaRei-2)
    {
        ChecarBlock(peca, i, j);
        if(contadorBlock>0)
        {
            if(pecasBlock[0][0] == 'B')
            {
                JogadaBrancaXeque();
            }
            if(pecasBlock[0][0] == 'P')
            {
                JogadaPretaXeque();
            }
        }
    }
    if(linhaXeque == linhaRei-1 && colunaXeque == colunaRei+2)
    {
        ChecarBlock(peca, i, j);
        if(contadorBlock>0)
        {
            if(pecasBlock[0][0] == 'B')
            {
                JogadaBrancaXeque();
            }
            if(pecasBlock[0][0] == 'P')
            {
                JogadaPretaXeque();
            }
        }
    }
    if(linhaXeque == linhaRei-1 && colunaXeque == colunaRei-2)
    {
        ChecarBlock(peca, i, j);
        if(contadorBlock>0)
        {
            if(pecasBlock[0][0] == 'B')
            {
                JogadaBrancaXeque();
            }
            if(pecasBlock[0][0] == 'P')
            {
                JogadaPretaXeque();
            }
        }
    }
    ChecarMate1(rei, linhaRei, colunaRei);
}

void ChecarPossivelXeque(char peca[CARACTERES]){
    
    int comp;
    comp=1;
    
    i=0;
    
    for(i=0;i<PECAS;i++)
    {
        comp = strcmp(pecasBlock[i], peca);
        if(comp == 0)
        {
            return;
        }
    }
    printf("Não existem movimentos validos para essa peça\n\n");
    if(peca[0] == 'P')
    {
        JogadaPretaXeque();
    }
    if(peca[0] == 'B')
    {
        JogadaBrancaXeque();
    }
}

void MoverTorreXeque(int linhaPeca, int colunaPeca, char peca[CARACTERES]){
    
    char rei[CARACTERES];
    int linhaDestino, colunaDestino, linhaRei, colunaRei, comp;
    
    i=0;
    j=0;
    
    if(peca[0] == 'P')
    {
        strcpy(rei, "PR1");
    }
    if(peca[0] == 'B')
    {
        strcpy(rei, "BR1");
    }
    for(i=0;i<LINHAS;i++)
    {
        for(j=0;j<COLUNAS;j++)
        {
            comp = strcmp(rei, tabuleiro[i][j]);
            if(comp == 0)
            {
                linhaRei = i;
                colunaRei = j;
                goto invalido;
            }
        }
    }

    invalido:
    i = linhaPeca;
    j = colunaPeca;
    
    printf("Para qual linha deseja movê-la?\n");
    scanf("%i",&linhaDestino);
    printf("Para qual coluna deseja movê-la?\n");
    scanf("%i",&colunaDestino);
    
    colunaDestino = colunaDestino-1;
    linhaDestino = linhaDestino + 2*(4-linhaDestino);
    
    if(colunaXeque == colunaRei)
    {
        if(colunaDestino != colunaXeque)
        {
            printf("Jogada inválida\n\n");
            goto invalido;
        }
    }
    if(linhaXeque == linhaRei)
    {
        if(linhaDestino != linhaXeque)
        {
            printf("Jogada inválida\n\n");
            goto invalido;
        }
    }
    if(abs(linhaXeque-linhaRei) != abs(colunaXeque-colunaRei))
    {
        if(linhaDestino != linhaXeque && colunaDestino != colunaXeque)
        {
            printf("Jogada inválida\n\n");
            goto invalido;
        }
    }
    if(abs(linhaXeque-linhaRei) == abs(colunaXeque-colunaRei))
    {
        if(abs(linhaXeque-linhaDestino) == abs(colunaXeque-colunaDestino))
        {
            printf("Jogada inválida\n\n");
            goto invalido;
        }
    }
    if(linhaDestino > 7 || linhaDestino < 0 || colunaDestino > 7 || colunaDestino < 0)
    {
        printf("Jogada inválida\n\n");
        goto invalido;
    }
    if(linhaDestino != linhaPeca && colunaDestino != colunaPeca)
    {
        printf("Jogada inválida\n\n");
        goto invalido;
    }
    if(linhaDestino == linhaPeca && colunaDestino == colunaPeca)
    {
        printf("Jogada inválida\n\n");
        goto invalido;
    }
    if(linhaDestino > linhaPeca)
    {
        i++;
        for(i=i;i<=linhaDestino;i++)
        {
            if(tabuleiro[i][j][0] == peca[0])
            {
                printf("Jogada inválida\n\n");
                goto invalido;
            }
        }
    }
    if(linhaDestino < linhaPeca)
    {
        i--;
        for(i=i;i>=linhaDestino;i--)
        {
            if(tabuleiro[i][j][0] == peca[0])
            {
                printf("Jogada inválida\n\n");
                goto invalido;
            }
        }
    }
    if(colunaDestino > colunaPeca)
    {
        j++;
        for(j=j;j<=colunaDestino;j++)
        {
            if(tabuleiro[i][j][0] == peca[0])
            {
                printf("Jogada inválida\n\n");
                goto invalido;
            }
        }
    }
    if(colunaDestino < colunaPeca)
    {
        j--;
        for(j=j;j>=colunaDestino;j--)
        {
            if(tabuleiro[i][j][0] == peca[0])
            {
                printf("Jogada inválida\n\n");
                goto invalido;
            }
        }
    }
    if(peca[0] == 'P' && peca[2] == '1')
    {
        contadorRoqueLongoPreto--;
    }
    if(peca[0] == 'B' && peca[2] == '1')
    {
        contadorRoqueLongoBranco--;
    }
    if(peca[0] == 'P' && peca[2] == '2')
    {
        contadorRoqueCurtoPreto--;
    }
    if(peca[0] == 'B' && peca[2] == '2')
    {
        contadorRoqueCurtoBranco--;
    }
    
    i=0;
    j=0;
    contadorEnPassant = 0;
    
    LimparBlock();
    Mover(tabuleiro[linhaPeca][colunaPeca], tabuleiro[linhaDestino][colunaDestino]);
}

void MoverCavaloXeque(int linhaPeca, int colunaPeca, char peca[CARACTERES]){
    
    char rei[CARACTERES];
    int linhaDestino, colunaDestino, linhaRei, colunaRei, comp;
    
    i=0;
    j=0;
    
    if(peca[0] == 'P')
    {
        strcpy(rei, "PR1");
    }
    if(peca[0] == 'B')
    {
        strcpy(rei, "BR1");
    }
    for(i=0;i<LINHAS;i++)
    {
        for(j=0;j<COLUNAS;j++)
        {
            comp = strcmp(rei, tabuleiro[i][j]);
            if(comp == 0)
            {
                linhaRei = i;
                colunaRei = j;
                goto invalido;
            }
        }
    }

    invalido:
    i = linhaPeca;
    j = colunaPeca;
    
    printf("Para qual linha deseja movê-la?\n");
    scanf("%i",&linhaDestino);
    printf("Para qual coluna deseja movê-la?\n");
    scanf("%i",&colunaDestino);
    
    colunaDestino = colunaDestino-1;
    linhaDestino = linhaDestino + 2*(4-linhaDestino);
    
    if(colunaXeque == colunaRei)
    {
        if(colunaDestino != colunaXeque)
        {
            printf("Jogada inválida\n\n");
            goto invalido;
        }
    }
    if(linhaXeque == linhaRei)
    {
        if(linhaDestino != linhaXeque)
        {
            printf("Jogada inválida\n\n");
            goto invalido;
        }
    }
    if(abs(linhaXeque-linhaRei) != abs(colunaXeque-colunaRei))
    {
        if(linhaDestino != linhaXeque && colunaDestino != colunaXeque)
        {
            printf("Jogada inválida\n\n");
            goto invalido;
        }
    }
    if(abs(linhaXeque-linhaRei) == abs(colunaXeque-colunaRei))
    {
        if(abs(linhaXeque-linhaDestino) == abs(colunaXeque-colunaDestino))
        {
            printf("Jogada inválida\n\n");
            goto invalido;
        }
    }
    if(linhaDestino > 7 || linhaDestino < 0 || colunaDestino > 7 || colunaDestino < 0)
    {
        printf("Jogada inválida\n\n");
        goto invalido;
    }
    if(tabuleiro[linhaDestino][colunaDestino][0] == peca[0])
    {
        printf("Jogada inválida\n\n");
        goto invalido;
    }
    if(linhaDestino > linhaPeca+2 || colunaDestino > colunaPeca+2)
    {
        printf("Jogada inválida\n\n");
        goto invalido;
    }
    if(linhaDestino == linhaPeca || colunaDestino == colunaPeca)
    {
        printf("Jogada inválida\n\n");
        goto invalido;
    }
    if(abs(linhaDestino-linhaPeca) == abs(colunaDestino-colunaPeca))
    {
        printf("Jogada inválida\n\n");
        goto invalido;
    }
    
    contadorEnPassant = 0;

    LimparBlock();
    Mover(tabuleiro[linhaPeca][colunaPeca], tabuleiro[linhaDestino][colunaDestino]);
}

void MoverBispoXeque(int linhaPeca, int colunaPeca, char peca[CARACTERES]){
    
    char rei[CARACTERES];
    int linhaDestino, colunaDestino, linhaRei, colunaRei, comp;
    
    i=0;
    j=0;
    
    if(peca[0] == 'P')
    {
        strcpy(rei, "PR1");
    }
    if(peca[0] == 'B')
    {
        strcpy(rei, "BR1");
    }
    for(i=0;i<LINHAS;i++)
    {
        for(j=0;j<COLUNAS;j++)
        {
            comp = strcmp(rei, tabuleiro[i][j]);
            if(comp == 0)
            {
                linhaRei = i;
                colunaRei = j;
                goto invalido;
            }
        }
    }

    invalido:
    i = linhaPeca;
    j = colunaPeca;
    
    printf("Para qual linha deseja movê-la?\n");
    scanf("%i",&linhaDestino);
    printf("Para qual coluna deseja movê-la?\n");
    scanf("%i",&colunaDestino);
    
    colunaDestino = colunaDestino-1;
    linhaDestino = linhaDestino + 2*(4-linhaDestino);
    
    if(colunaXeque == colunaRei)
    {
        if(colunaDestino != colunaXeque)
        {
            printf("Jogada inválida\n\n");
            goto invalido;
        }
    }
    if(linhaXeque == linhaRei)
    {
        if(linhaDestino != linhaXeque)
        {
            printf("Jogada inválida\n\n");
            goto invalido;
        }
    }
    if(abs(linhaXeque-linhaRei) != abs(colunaXeque-colunaRei))
    {
        if(linhaDestino != linhaXeque && colunaDestino != colunaXeque)
        {
            printf("Jogada inválida\n\n");
            goto invalido;
        }
    }
    if(abs(linhaXeque-linhaRei) == abs(colunaXeque-colunaRei))
    {
        if(abs(linhaXeque-linhaDestino) == abs(colunaXeque-colunaDestino))
        {
            printf("Jogada inválida\n\n");
            goto invalido;
        }
    }
    if(linhaDestino > 7 || linhaDestino < 0 || colunaDestino > 7 || colunaDestino < 0)
    {
        printf("Jogada inválida\n\n");
        goto invalido;
    }
    if(linhaDestino == linhaPeca || colunaDestino == colunaPeca)
    {
        printf("Jogada inválida\n\n");
        goto invalido;
    }
    if(abs(linhaDestino-linhaPeca) != abs(colunaDestino-colunaPeca))
    {
        printf("Jogada inválida\n\n");
        goto invalido;
    }
    if(linhaDestino > linhaPeca && colunaDestino > colunaPeca)
    {
        i++;
        j++;
        for(i=i;i<=linhaDestino;i++)
        {
            if(tabuleiro[i][j][0] == peca[0])
            {
                printf("Jogada inválida\n\n");
                goto invalido;
            }
            j++;
        }
    }
    if(linhaDestino < linhaPeca && colunaDestino > colunaPeca)
    {
        i--;
        j++;
        for(i=i;i>=linhaDestino;i--)
        {
            if(tabuleiro[i][j][0] == peca[0])
            {
                printf("Jogada inválida\n\n");
                goto invalido;
            }
            j++;
        }
    }
    if(linhaDestino > linhaPeca && colunaDestino < colunaPeca)
    {
        i++;
        j--;
        for(i=i;i<=linhaDestino;i++)
        {
            if(tabuleiro[i][j][0] == peca[0])
            {
                printf("Jogada inválida\n\n");
                goto invalido;
            }
            j--;
        }
    }
    if(linhaDestino < linhaPeca && colunaDestino < colunaPeca)
    {
        i--;
        j--;
        for(i=i;i>=linhaDestino;i--)
        {
            if(tabuleiro[i][j][0] == peca[0])
            {
                printf("Jogada inválida\n\n");
                goto invalido;
            }
            j--;
        }
    }
    
    i=0;
    j=0;
    contadorEnPassant = 0;
    
    LimparBlock();
    Mover(tabuleiro[linhaPeca][colunaPeca], tabuleiro[linhaDestino][colunaDestino]);
}

void MoverDamaXeque(int linhaPeca, int colunaPeca, char peca[CARACTERES]){
    
    char rei[CARACTERES];
    int linhaDestino, colunaDestino, linhaRei, colunaRei, comp;
    
    i=0;
    j=0;
    
    if(peca[0] == 'P')
    {
        strcpy(rei, "PR1");
    }
    if(peca[0] == 'B')
    {
        strcpy(rei, "BR1");
    }
    for(i=0;i<LINHAS;i++)
    {
        for(j=0;j<COLUNAS;j++)
        {
            comp = strcmp(rei, tabuleiro[i][j]);
            if(comp == 0)
            {
                linhaRei = i;
                colunaRei = j;
                goto invalido;
            }
        }
    }

    invalido:
    i = linhaPeca;
    j = colunaPeca;
    
    printf("Para qual linha deseja movê-la?\n");
    scanf("%i",&linhaDestino);
    printf("Para qual coluna deseja movê-la?\n");
    scanf("%i",&colunaDestino);
    
    colunaDestino = colunaDestino-1;
    linhaDestino = linhaDestino + 2*(4-linhaDestino);
    
    if(colunaXeque == colunaRei)
    {
        if(colunaDestino != colunaXeque)
        {
            printf("Jogada inválida\n\n");
            goto invalido;
        }
    }
    if(linhaXeque == linhaRei)
    {
        if(linhaDestino != linhaXeque)
        {
            printf("Jogada inválida\n\n");
            goto invalido;
        }
    }
    if(abs(linhaXeque-linhaRei) != abs(colunaXeque-colunaRei))
    {
        if(linhaDestino != linhaXeque && colunaDestino != colunaXeque)
        {
            printf("Jogada inválida\n\n");
            goto invalido;
        }
    }
    if(abs(linhaXeque-linhaRei) == abs(colunaXeque-colunaRei))
    {
        if(abs(linhaXeque-linhaDestino) == abs(colunaXeque-colunaDestino))
        {
            printf("Jogada inválida\n\n");
            goto invalido;
        }
    }
    if(linhaDestino > 7 || linhaDestino < 0 || colunaDestino > 7 || colunaDestino < 0)
    {
        printf("Jogada inválida\n\n");
        goto invalido;
    }
    if(linhaDestino == linhaPeca && colunaDestino == colunaPeca)
    {
        printf("Jogada inválida\n\n");
        goto invalido;
    }
    if(linhaDestino != linhaPeca && colunaDestino != colunaPeca)
    {
        if(abs(linhaDestino-linhaPeca) != abs(colunaDestino-colunaPeca))
        {
            printf("Jogada inválida\n\n");
            goto invalido;
        }
        if(linhaDestino > linhaPeca && colunaDestino > colunaPeca)
        {
            i++;
            j++;
            for(i=i;i<=linhaDestino;i++)
            {
                if(tabuleiro[i][j][0] == peca[0])
                {
                    printf("Jogada inválida\n\n");
                    goto invalido;
                }
                j++;
            }
        }
        if(linhaDestino < linhaPeca && colunaDestino > colunaPeca)
        {
            i--;
            j++;
            for(i=i;i>=linhaDestino;i--)
            {
                if(tabuleiro[i][j][0] == peca[0])
                {
                    printf("Jogada inválida\n\n");
                    goto invalido;
                }
                j++;
            }
        }
        if(linhaDestino > linhaPeca && colunaDestino < colunaPeca)
        {
            i++;
            j--;
            for(i=i;i<=linhaDestino;i++)
            {
                if(tabuleiro[i][j][0] == peca[0])
                {
                    printf("Jogada inválida\n\n");
                    goto invalido;
                }
                j--;
            }
        }
        if(linhaDestino < linhaPeca && colunaDestino < colunaPeca)
        {
            i--;
            j--;
            for(i=i;i>=linhaDestino;i--)
            {
                if(tabuleiro[i][j][0] == peca[0])
                {
                    printf("Jogada inválida\n\n");
                    goto invalido;
                }
                j--;
            }
        }
    }
    if(linhaDestino > linhaPeca)
    {
        i++;
        for(i=i;i<=linhaDestino;i++)
        {
            if(tabuleiro[i][j][0] == peca[0])
            {
                printf("Jogada inválida\n\n");
                goto invalido;
            }
        }
    }
    if(linhaDestino < linhaPeca)
    {
        i--;
        for(i=i;i>=linhaDestino;i--)
        {
            if(tabuleiro[i][j][0] == peca[0])
            {
                printf("Jogada inválida\n\n");
                goto invalido;
            }
        }
    }
    if(colunaDestino > colunaPeca)
    {
        j++;
        for(j=j;j<=colunaDestino;j++)
        {
            if(tabuleiro[i][j][0] == peca[0])
            {
                printf("Jogada inválida\n\n");
                goto invalido;
            }
        }
    }
    if(colunaDestino < colunaPeca)
    {
        j--;
        for(j=j;j>=colunaDestino;j--)
        {
            if(tabuleiro[i][j][0] == peca[0])
            {
                printf("Jogada inválida\n\n");
                goto invalido;
            }
        }
    }
    
    i=0;
    j=0;
    contadorEnPassant = 0;
    
    LimparBlock();
    Mover(tabuleiro[linhaPeca][colunaPeca], tabuleiro[linhaDestino][colunaDestino]);
}

void MoverPeaoXeque(int linhaPeca, int colunaPeca, char peca[CARACTERES]){
    
    char rei[CARACTERES];
    int linhaDestino, colunaDestino, linhaRei, colunaRei, comp;
    
    i=0;
    j=0;
    
    if(peca[0] == 'P')
    {
        strcpy(rei, "PR1");
    }
    if(peca[0] == 'B')
    {
        strcpy(rei, "BR1");
    }
    for(i=0;i<LINHAS;i++)
    {
        for(j=0;j<COLUNAS;j++)
        {
            comp = strcmp(rei, tabuleiro[i][j]);
            if(comp == 0)
            {
                linhaRei = i;
                colunaRei = j;
                goto invalido;
            }
        }
    }

    invalido:
    i = linhaPeca;
    j = colunaPeca;
    
    printf("Para qual linha deseja movê-la?\n");
    scanf("%i",&linhaDestino);
    printf("Para qual coluna deseja movê-la?\n");
    scanf("%i",&colunaDestino);
    
    colunaDestino = colunaDestino-1;
    linhaDestino = linhaDestino + 2*(4-linhaDestino);
    
    if(colunaXeque == colunaRei)
    {
        if(colunaDestino != colunaXeque)
        {
            printf("Jogada inválida\n\n");
            goto invalido;
        }
    }
    if(linhaXeque == linhaRei)
    {
        if(linhaDestino != linhaXeque)
        {
            printf("Jogada inválida\n\n");
            goto invalido;
        }
    }
    if(abs(linhaXeque-linhaRei) != abs(colunaXeque-colunaRei))
    {
        if(linhaDestino != linhaXeque && colunaDestino != colunaXeque)
        {
            printf("Jogada inválida\n\n");
            goto invalido;
        }
    }
    if(abs(linhaXeque-linhaRei) == abs(colunaXeque-colunaRei))
    {
        if(abs(linhaXeque-linhaDestino) == abs(colunaXeque-colunaDestino))
        {
            printf("Jogada inválida\n\n");
            goto invalido;
        }
    }
    if(linhaDestino > 7 || linhaDestino < 0 || colunaDestino > 7 || colunaDestino < 0)
    {
        printf("Jogada inválida\n\n");
        goto invalido;
    }
    if(linhaDestino == linhaPeca && colunaDestino == colunaPeca)
    {
        printf("Jogada inválida\n\n");
        goto invalido;
    }
    if(colunaDestino > colunaPeca+1 || linhaDestino > linhaPeca+2)
    {
        printf("Jogada inválida\n\n");
        goto invalido;
    }
    if(peca[0] == 'B')
    {
        if(linhaPeca != 6)
        {
            if(colunaDestino > colunaPeca+1 || colunaDestino < colunaPeca-1 || linhaDestino < linhaPeca-1)
            {
                printf("Jogada inválida\n\n");
                goto invalido;
            }
        }
        if(colunaDestino > colunaPeca+1 || colunaDestino < colunaPeca-1 || linhaDestino < linhaPeca-2)
        {
            printf("Jogada inválida\n\n");
            goto invalido;
        }
        if(linhaDestino == 0)
        {
            Promocao(tabuleiro[linhaPeca][colunaPeca], tabuleiro[linhaDestino][colunaDestino]);
            return;
        }
    }
    if(peca[0] == 'P')
    {
        if(linhaPeca != 1)
        {
            if(colunaDestino > colunaPeca+1 || colunaDestino < colunaPeca-1 || linhaDestino > linhaPeca+1)
            {
                printf("Jogada inválida\n\n");
                goto invalido;
            }
        }
        if(colunaDestino > colunaPeca+1 || colunaDestino < colunaPeca-1 || linhaDestino > linhaPeca+2)
        {
            printf("Jogada inválida\n\n");
            goto invalido;
        }
        if(linhaDestino == 7)
        {
            Promocao(tabuleiro[linhaPeca][colunaPeca], tabuleiro[linhaDestino][colunaDestino]);
            return;
        }
    }
    
    i=0;
    j=0;
    contadorEnPassant = 0;
    
    LimparBlock();
    Mover(tabuleiro[linhaPeca][colunaPeca], tabuleiro[linhaDestino][colunaDestino]);
}

void LimparBlock(){
    
    for(contadorBlock=contadorBlock;contadorBlock>=0;contadorBlock--)
    {
        strcpy(pecasBlock[contadorBlock], "   ");
    }
    contadorBlock=0;
}

void Promocao(char peca[CARACTERES], char destino[CARACTERES]){
    
    int comp, contC, contB, contD, contT;
    char promovido[2], novaPeca[CARACTERES], numero;
    
    contC = 0;
    contT = 0;
    contB = 0;
    contD = 0;
    i=0;
    j=0;
    
    for(i=0;i<LINHAS;i++)
    {
        for(j=0;j<COLUNAS;j++)
        {
            comp = strcmp(tabuleiro[i][j], "...");
            if(comp == 0)
            {
                strcpy(tabuleiro[i][j], "   ");
            }
        }
    }
    
    invalido:
    printf("Para qual peça deseja promover?\n");
    printf("(C=Cavalo/T=Torre/D=Dama/B=Bispo)\n");
    scanf("%s",promovido);
    if(promovido[0] != 'C' && promovido[0] != 'B' && promovido[0] != 'D' && promovido[0] != 'T')
    {
        printf("Promoçao invalida");
        printf("A promoçao deve ser para uma das 4 peças citadas\n");
        goto invalido;
    }
    else
    {
        if(promovido[0] == 'C')
        {
            contC++;
            numero = (char)contC;
            novaPeca[0] = peca[0];
            novaPeca[1] = promovido[0];
            switch(contC)
            {
                case 1:
                novaPeca[2] = '3';
                break;
                case 2:
                novaPeca[2] = '4';
                break;
                case 3:
                novaPeca[2] = '5';
                break;
                case 4:
                novaPeca[2] = '6';
                break;
                case 5:
                novaPeca[2] = '7';
                break;
                case 6:
                novaPeca[2] = '8';
                break;
                case 7:
                novaPeca[2] = '9';
                break;
                case 8:
                novaPeca[2] = '0';
                break;
            }
        }
        if(promovido[0] == 'T')
        {
            contT++;
            numero = (char)contT;
            novaPeca[0] = peca[0];
            novaPeca[1] = promovido[0];
            switch(contT)
            {
                case 1:
                novaPeca[2] = '3';
                break;
                case 2:
                novaPeca[2] = '4';
                break;
                case 3:
                novaPeca[2] = '5';
                break;
                case 4:
                novaPeca[2] = '6';
                break;
                case 5:
                novaPeca[2] = '7';
                break;
                case 6:
                novaPeca[2] = '8';
                break;
                case 7:
                novaPeca[2] = '9';
                break;
                case 8:
                novaPeca[2] = '0';
                break;
            }
        }
        if(promovido[0] == 'B')
        {
            contB++;
            novaPeca[0] = peca[0];
            novaPeca[1] = promovido[0];
            switch(contB)
            {
                case 1:
                novaPeca[2] = '3';
                break;
                case 2:
                novaPeca[2] = '4';
                break;
                case 3:
                novaPeca[2] = '5';
                break;
                case 4:
                novaPeca[2] = '6';
                break;
                case 5:
                novaPeca[2] = '7';
                break;
                case 6:
                novaPeca[2] = '8';
                break;
                case 7:
                novaPeca[2] = '9';
                break;
                case 8:
                novaPeca[2] = '0';
                break;
            }
        }
        if(promovido[0] == 'D')
        {
            contD++;
            novaPeca[0] = peca[0];
            novaPeca[1] = promovido[0];
            switch(contD)
            {
                case 1:
                novaPeca[2] = '2';
                break;
                case 2:
                novaPeca[2] = '3';
                break;
                case 3:
                novaPeca[2] = '4';
                break;
                case 4:
                novaPeca[2] = '5';
                break;
                case 5:
                novaPeca[2] = '6';
                break;
                case 6:
                novaPeca[2] = '7';
                break;
                case 7:
                novaPeca[2] = '8';
                break;
                case 8:
                novaPeca[2] = '9';
                break;
            }
        }
    }
    strcpy(destino, novaPeca);
    strcpy(peca, "...");
    Exibir();
}

void EnPassant(char peca[CARACTERES], char destino[CARACTERES]){
    
    int comp;
    
    i=0;
    j=0;
    
    for(i=0;i<LINHAS;i++)
    {
        for(j=0;j<COLUNAS;j++)
        {
            comp = strcmp(tabuleiro[i][j], "...");
            if(comp == 0)
            {
                strcpy(tabuleiro[i][j], "   ");
            }
        }
    }
    strcpy(destino, peca);
    strcpy(peca, "...");
    Exibir();
}