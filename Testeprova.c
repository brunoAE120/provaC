#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
typedef struct carro{
    int reg_carro;
    char status;
    char tipo;
    }carro;
    
typedef struct cliente{
    char CPF[13];
    char nome[80];
    int num_reg;
    int dias;
    }cliente;
    
void aloca_carro(carro **pcar,int qcar); 
void aloca_cliente (cliente **pcli,int qcli); 
void cadastra_carro(carro *pcar,int qcar); 
void cadastra_cliente(cliente *pcli, carro *pcar); 
void devolucao(cliente *pcli,int qcli, carro *pcar,int qcar); 
int busca_carro(carro *pcar,char tipo_car); 
int busca_CPF(cliente *pcli,int qcli, char *aux); 
void mostra_carro(carro *pcar,int qcar);

main()
{
carro *car=NULL;
cliente *cli=NULL;
int op, cont=0,pos;

aloca_carro(&car,15); 
cadastra_carro(car, 15);

    do{
        system("cls");
        printf("[1] Locacao\n[2] Devolucao\n[3] Fim\nOpcao: ");
        scanf("%i",&op);
        fflush(stdin);
        switch(op)
            {
            case 1: mostra_carro(car, 15); 
            aloca_cliente(&cli,cont+1); //20
            cadastra_cliente(cli+cont,car); //16
            cont++;
            break;
            
            case 2: 
			devolucao(cli, cont,car,15); //44
            break;
            }
    }while(op!=3);
    
}

void aloca_carro(carro **pcar, int qcar)
{
    if((*pcar=(carro*)realloc(*pcar,qcar*sizeof(carro)))== NULL) //26
    exit;
}

void aloca_cliente(cliente **pcli, int qcli)
{
    if((*pcli=(cliente*)realloc(*pcli,qcli*sizeof(cliente))) == NULL) //41
    exit;
}

void cadastra_carro(carro *pcar, int qcar)
{
    int i;
    for(i=0;i<qcar;i++,pcar++)
    {
    (pcar->reg_carro=i+1); //40
    pcar->status='L';
    if(i<5)
        pcar->tipo='P';
    else if(i<10)
        pcar->tipo='M';
    else
        pcar->tipo='G';
    }
}//cadastra_carro

void cadastra_cliente (cliente *pcli,carro *pcar)
    {
    char tipcar;
    int numcar;
    printf("\nTipo de carro [PM-G]: ");
    scanf("%c",&tipcar);
    fflush(stdin);
    tipcar=toupper(tipcar);
    numcar=busca_carro(pcar,tipcar); //6
    
    if(numcar==-1)
        printf("\nNao ha carros disponiveis desse tipo\n\n\n");
    else
    {
    pcli->num_reg=numcar; //8
    printf("\nCPF: ");
    gets(pcli->CPF);
    fflush(stdin);
    printf("\nNome: ");
    gets(pcli->nome);
    fflush(stdin);
    printf("\nQtos dias: ");
    scanf("%i", &(pcli->dias)); //53
    fflush(stdin);
    printf("\nCadastro feito com sucesso\nCarro: %i\n\n\n",pcli->num_reg);
    }
system("pause");
}//cadastro_cliente

void devolucao(cliente *pcli,int qcli, carro *pcar, int qcar)
{
    char aux_cpf[13],tip;
    int pos,reg,tempo;
    printf("\nCPF a ser encerrado: ");
    gets(aux_cpf);
    fflush(stdin);
    pos=busca_CPF(pcli,qcli,aux_cpf);
    if(pos==-1)
        printf("\nCPF invalido\n");
    else
    {
        reg=(pcli+pos)->num_reg; //54
        (pcar+reg-1)->status='L'; //23
        tip=(pcar+reg-1)->tipo; //45
        tempo=(pcli+pos)->dias; //51
        
        printf("Tipo de carro: %c", tip); 
        switch(tip) 
        {
            case 'P': printf("\nValor a pagar: %.2f\n\n",tempo*150.00); 
                break;
            case 'M': printf("\nValor a pagar: %.2f\n\n", tempo*200.00);
                break; 
            case 'G': printf("\nValor a pagar: %.2f\n\n",tempo*300.00); 
                break;
        }//switch
    }//else
system("pause");
}//devolucao


int busca_carro(carro *pcar,char tipo_car)
{
    int i;
    for(i=0;i<15;i++)
    if((pcar+i)->tipo==tipo_car && (pcar+i)->status=='L') //31 e 12
    {
        (pcar+i)->status='A'; //28
        return((pcar+i)->reg_carro); //60
    }
return -1;
}

int busca_CPF(cliente *pcli,int qcli, char *aux)
{
    int i,reg;
    for(i=0;i<qcli;i++,pcli++)
    if(strcmp(pcli->CPF,aux)==0) //34
    {
        printf("\nNome: %s\nCarro: %i\nDias: %i", pcli->nome,pcli->num_reg,pcli->dias);
        return(i);
    }
return -1;
}//busca_CPF


void mostra_carro(carro *pcar,int qcar)
{
    int i;
    for(i=0;i<qcar;i++,pcar++)
        printf("\nRegistro Carro: %i\nTipo: %c\nStatus: %c\n\n",pcar->reg_carro,pcar->tipo,pcar->status);
        printf("\n\n\n");
}//mostra_carro


