/*Girleanu Andrei Alexandru-313CC*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//definim structurile pentru lista
//nodeList reprezinta structura pentru nodurile listei
typedef struct nodeList {
    char *data;
    struct nodeList *prev;
    struct nodeList *next;
} nodeList;

//TList reprezinta structura care contine pointerul catre
//primul element al listei(head) si catre nodul curent(curr)
typedef struct TList {
    nodeList *head;
    nodeList *curr;
} TList;

//functia care initializeaza lista
void initializare(TList **list) {
    (*list)=malloc(sizeof(TList));
    (*list)->head=NULL;
    (*list)->curr=NULL;
}

//functia care creeaza nodul santinela
void creareSantinela(TList *list) {
    nodeList *nou=malloc(sizeof(nodeList));
    
    list->head=nou;
    list->curr=nou;
    nou->prev=NULL;
    nou->next=NULL;
}

//aceasta functie creeaza un nod nou pe care il adauga la finalul listei
//de asemenea, plaseaza deja degetul pe acesta
//il modifica pe list->curr pentru a pointa catre noul nod
//observam ca retinem in fiecare nod care este curent
//cele doua bari ce indica acest lucru si le modificam pe parcurs
void creareNod(TList *list) {
    nodeList *current;
    current=list->head;
    
    //parcurgem lista pana la final deoarece adaugam nodul la sfarsit
    while (current->next!=NULL) {
        current=current->next;
    }

    nodeList *nou=malloc(sizeof(nodeList));
    nou->data=malloc(5*sizeof(char));
    
    //adaugam in nod caracterul # insotit de cele 2 bari
    strcpy(nou->data, "|#|");
    
    nou->prev=current;
    nou->next=NULL;
    current->next=nou;

    //actualizam list->curr
    list->curr=nou;
}

//aceasta functie realizeaza operatia de MOVE_LEFT
void Move_Left(TList *list, int*ok) {
    nodeList *nod;
    nod=list->curr;
    
    //ok este variabila ce ne indica daca s-a realizat operatia
    (*ok)=0;
    
    //verificam daca se poate executa operatia
    if (nod->prev->prev!=NULL) {
        //modificam pozitia degetului de pe nodul curent, stergand barele
        nod->data[0]=nod->data[1];
        nod->data[1]='\0';

        //adaugam barile pe noua pozitie din lista
        nod=nod->prev;
        nod->data[1]=nod->data[0];
        nod->data[0]='|';
        nod->data[2]='|';
        nod->data[3]='\0';

        //actualizam list->curr
        list->curr=nod;
        (*ok)=1;
    }
}

//aceasta functie realizeaza operatia de MOVE_RIGHT
void Move_Right(TList *list) {
    nodeList *nod;
    nod=list->curr;

    //modificam pozitia degetului de pe nodul curent, stergand barile
    nod->data[0]=nod->data[1];
    nod->data[1]='\0';

    //verificam daca este necesara crearea unui nod nou
    if (nod->next==NULL) {
        creareNod(list);
    }
    else {
        //adaugam barile pe noua pozitie din lista
        nod=nod->next;
        nod->data[1]=nod->data[0];
        nod->data[0]='|';
        nod->data[2]='|';
        nod->data[3]='\0';
        
        //actualizam list->curr
        list->curr=nod;
    }
}

//aceasta functie realizeaza operatia de MOVE_LEFT_CHAR <C>
void Move_Left_char(TList *list, char c,int *ok) {
    nodeList *nod;
    nod=list->curr;
    
    //ok este variabila ce ne indica daca s-a realizat operatia
    (*ok)=0;

    //stergem barile de pe nodul curent, insa le vom adauga inapoi
    //daca operatia nu s-a realizat
    nod->data[0]=nod->data[1];
    nod->data[1]='\0';
    
    //cautam caracterul c
    while (nod->prev->prev!=NULL) {
        if (nod->data[0]==c) {
            //actualizam list->curr
            list->curr=nod;

            //adaugam barile pe noul nod curent
            nod->data[0]='|';
            nod->data[1]=c;
            nod->data[2]='|';
            nod->data[3]='\0';
            
            (*ok)=1;   
            break;
        }
        nod=nod->prev;
    }

    if (nod->data[0]==c) {
        //actualizam list->curr
        list->curr=nod;

        //adaugam barile pe noul nod curent
        nod->data[0]='|';
        nod->data[1]=c;
        nod->data[2]='|';
        nod->data[3]='\0';
        
        (*ok)=1;
    }

    //daca ok=0, inseamna ca nu s-a putut realiza modificarea
    //si adaugam inapoi barile, fara a il actualiza pe list->curr
    if ((*ok)==0) {
        nod=list->curr;
        nod->data[1]=nod->data[0];
        nod->data[0]='|';
        nod->data[2]='|';
        nod->data[3]='\0';
    }
    //daca ok este 0, inseamna ca trebuie sa afisam ERROR in main
}

//aceasta functie realizeaza operatia de MOVE_RIGHT_CHAR <C>
void Move_Right_char(TList *list, char c) {
    nodeList *nod;
    nod=list->curr;
    
    //ok ne ajuta sa ne dam seama daca trebuie sa cream un nod nou
    int ok=0;
    
    //modificam pozitia degetului de pe nodul curent, stergand barile
    nod->data[0]=nod->data[1];
    nod->data[1]='\0';
    
    //cautam caracterul c
    while (nod->next!=NULL) {
        if (nod->data[0]==c){
            //actualizam list->curr
            list->curr=nod;

            //adaugam barile pe noul nod curent
            nod->data[0]='|';
            nod->data[1]=c;
            nod->data[2]='|';
            nod->data[3]='\0';
            
            ok=1;
            break;
        }
        nod=nod->next;
    }

    if (nod->data[0]==c&&ok==0) {
        //actualizam list->curr
        list->curr=nod;
        
        //adaugam barile pe noul nod curent
        nod->data[0]='|';
        nod->data[1]=c;
        nod->data[2]='|';
        nod->data[3]='\0';
        
        ok=1;
    }

    //daca nu s-a gasit caracterul in lista, cream un nod nou
    if (ok==0) {
        creareNod(list);
    }
}

//aceasta functie realizeaza operatia de WRITE
void Write(TList *list, char c) {
    nodeList *nod;
    nod=list->curr;
    nod->data[0]='|';
    nod->data[1]=c;
    nod->data[2]='|';
    nod->data[3]='\0';
}

//aceasta functie realizeaza operatia de INSERT_LEFT <C>
void Insert_Left(TList *list, char c, int *ok) {
    nodeList *nod;
    nod=list->curr;
    
    //verificam daca se poate realiza operatia
    if (nod->prev->prev==NULL) {
        //daca nu, ok=0 si vom afisa in main ERROR
        (*ok)=0;
    }
    else {
        nodeList *nou=malloc(sizeof(nodeList));
        nou->data=malloc(5*sizeof(char));
        
        //mutam barile de pe nodul curent
        nod->data[0]=nod->data[1];
        nod->data[1]='\0';

        //cream un nod nou
        nod->prev->next=nou;
        nou->next=nod;
        nou->prev=nod->prev;
        nod->prev=nou;

        //adaugam barile pe noul nod curent
        nou->data[0]='|';
        nou->data[1]=c;
        nou->data[2]='|';
        nou->data[3]='\0';
        
        //actualizam list->curr
        list->curr=nou;
        (*ok)=1;
    }
}

//aceasta functie realizeaza operatia de INSERT_RIGHT <C>
void Insert_Right(TList *list, char c) {
    nodeList *nod;
    nod=list->curr;

    //stergem barile de pe nodul curent
    nod->data[0]=nod->data[1];
    nod->data[1]='\0';

    if (nod->next!=NULL) {
        nodeList *nou=malloc(sizeof(nodeList));
        nou->data=malloc(5*sizeof(char));
        
        //cream un nod nou
        nou->next=nod->next;
        nou->prev=nod;
        nod->next->prev=nou;
        nod->next=nou;
        
        //adaugam barile pe noul nod curent
        nou->data[0]='|';
        nou->data[1]=c;
        nou->data[2]='|';
        nou->data[3]='\0';
        
        //actualizam list->curr
        list->curr=nou;
    }
    else {
        creareNod(list);
        nod->next->data[1]=c;
    }
}

//aceasta functie elibereaza nodurile listei
void freeList(TList **list) {
    nodeList *nod, *curr;
    curr=(*list)->head;

    nod=curr;
    curr=nod->next;

    //eliberam separat santinela
    //deoarece nu alocam memorie pentrul campul data in aceasta
    free(nod);
    
    while (curr!=NULL) {
        nod=curr;
        curr=curr->next;
        
        free(nod->data);
        free(nod);
    }

    free(curr);
}

//definim structurile necesare cozii
//nodeCoada reprezinta nodurile cozii
typedef struct nodeCoada {
    char *data;
    struct nodeCoada *next;
} nodeCoada;

//TCoada contine pointerii catre inceputul cozii si catre sfarsitul sau 
typedef struct TCoada {
    nodeCoada *first;
    nodeCoada *last;
} TCoada;

//aceasta functie initializeaza coada
void initializareCoada(TCoada **coada) {
    (*coada)=malloc(sizeof(TCoada));
    (*coada)->first=NULL;
    (*coada)->last=NULL;
}

//aceasta functie adauga elemente la finalul cozii
void adaugaElemCoada(TCoada *coada, char *s) {
    nodeCoada *nou=malloc(sizeof(nodeCoada));
    nou->data=malloc(20*sizeof(char));

    //verificam daca coada este goala pentru a actualiza coada->first
    if (coada->first==NULL) {
        coada->first=nou;
        coada->last=nou;
        nou->next=NULL;
        
        strcpy(nou->data, s);
    }
    else {   
        coada->last->next=nou;
        coada->last=nou;
        nou->next=NULL;
        
        strcpy(nou->data, s);
    }
}

//aceasta functie extrage elemente de la inceputul cozii,
//tocmai pentru a putea fi extrase in ordinea adaugarii
void extrageElemCoada(TCoada *coada, char *info) {
    nodeCoada *nod;
    nod=coada->first;
    
    //extragem in info informatia
    strcpy(info, nod->data);
    
    coada->first=nod->next;

    //eliberam nodul din care a fost extrasa informatia
    free(nod->data);
    free(nod);
}

//aceasta functie elibereaza coada
void freeCoada(TCoada **coada) {
    nodeCoada *nod, *curr;
    curr=(*coada)->first;
    
    while (curr!=NULL) {
        nod=curr;
        curr=curr->next;
        
        free(nod->data);
        free(nod);
    }

    free(curr);
}

//structurile necesare stivei
//nodeStiva reprezinta structura pentru nodurile stivei
typedef struct nodeStiva {
    nodeList *poz;
    struct nodeStiva *next;
} nodeStiva;

//TStiva reprezinta structura care contine pointerul
//catre primul nod al stivei
typedef struct TStiva {
    nodeStiva *first;
} TStiva;

//functia care initializeaza stiva
void initializareStiva(TStiva **stiva) {
    (*stiva)=malloc(sizeof(TStiva));
    (*stiva)->first=NULL;
}

//aceasta functie adauga elemente la inceputul stivei
void adaugaElemStiva(TStiva *stiva, TList *list) {
    nodeStiva *nou=malloc(sizeof(nodeStiva));
    
    //verificam daca stiva este goala
    //in nou->poz este salvata adresa solicitata
    if (stiva->first==NULL) {
        stiva->first=nou;
        nou->next=NULL;
        nou->poz=list->curr;
    }
    else {
        nou->next=stiva->first;
        stiva->first=nou;
        nou->poz=list->curr;
    }
}

//aceasta functie extrage primul nod al listei, tocmai
//pentru a putea fi extrase in ordinea inversa adaugarii
nodeStiva* extrageElemStiva(TStiva *stiva) {
    nodeStiva *nod;
    nod=stiva->first;
    stiva->first=nod->next;
    return nod;
}

//aceasta functie elibereaza stiva
void freeStiva(TStiva **stiva) {
    nodeStiva *nod; 
    nodeStiva *curr;
    curr=(*stiva)->first;

    while (curr!=NULL) {
        nod=curr;
        curr=curr->next;
        
        free(nod);
    }

    free(curr);
    (*stiva)->first=NULL;
}

int main(){
    
    //deschidem fisierele de citire si afisare
    FILE *f=fopen("tema1.in", "r");
    FILE *fc=fopen("tema1.out", "w");

    //declaram si intializam lista
    TList *list;
    initializare(&list);
    
    //declaram si initializam coada
    TCoada *coada;
    initializareCoada(&coada);
    
    //declaram si initializam stivele pentru UNDO si REDO
    TStiva *UNDO, *REDO;
    initializareStiva(&UNDO);
    initializareStiva(&REDO);
    
    //cream nodul santinela si primul nod ce contine informatii
    creareSantinela(list);
    creareNod(list);

    //citim numarul de comenzi
    int n,i;
    fscanf(f, "%d\n", &n);
    
    //declaram si alocam o structura de tip TList ce ne va ajuta
    //sa salvam adresa catre nodul curent inainte de a verifica
    //daca operatia se poate realiza
    TList *adresa=malloc(sizeof(TList));

    //declaram si alocam dinamic stringul in care se citesc comenzile
    char *command;
    command=malloc(20*sizeof(char));

    //ok este o variabila ce ne indica daca operatiile de MOVE_LEFT,
    //MOVE_LEFT_CHAR <C> si INSERT_LEFT <C> s-au putut realiza
    int ok;

    for (i=0;i<n;i++) {
        //citim fiecare comanda
        fgets(command, 20, f);
        
        //plasam caracterul NULL la finalul fiecarei comenzi pentru a
        //modifica plasarea caracterului \n de catre functia fgets
        command[strlen(command)-1]='\0';
        
        //verificam daca comanda citita trebuie adaugata in coada
        //comenzile care trebuie adaugate sunt de tip MOVE_LEFT/RIGHT,
        //INSERT_LEFT/RIGHT si WRITE, deci vom verifica daca stringul
        //citit in command incepe cu una dintre literele M,I sau W
        if ((command[0]=='M')||(command[0]=='I')||(command[0]=='W')) {
            adaugaElemCoada(coada, command);
        }

        //daca in command se afla SHOW, afisam lista
        if (strcmp(command, "SHOW")==0) {
            nodeList *current;
            
            //il initializam pe current cu list->head->next deoarece
            //in list->head se afla santinela
            current=list->head->next;

            while (current!=NULL) {
                fprintf(fc, "%s", current->data);
                current=current->next;
            }

            fprintf(fc, "\n");
        }

        //daca in command se afla SHOW_CURRENT,
        //afisam caracterul curent
        if (strcmp(command, "SHOW_CURRENT")==0) {
            fprintf(fc, "%c\n", list->curr->data[1]);        
        }

        //daca in coomand se afla EXECUTE, 
        //atunci extragem din coada
        if (strcmp(command, "EXECUTE")==0) {
            //declaram si alocam memorie pentru exec,
            //stringul in care este extrasa comanda
            //din coada
            char *exec;
            exec=malloc(20*sizeof(char));
            
            extrageElemCoada(coada, exec);
            
            //daca in exec se afloa MOVE_LEFT
            if (strcmp(exec, "MOVE_LEFT")==0) {
                //salvam adresa curenta inainte de
                //executarea comenzii
                adresa->curr=list->curr;

                //executam comanda
                Move_Left(list, &ok);
                
                //verificam daca s-a realizat comanda
                //pentru a adauga adresa in stiva
                if (ok==1) {
                    adaugaElemStiva(UNDO, adresa);
                }
            }

            //daca in exec se afla MOVE_RIGHT
            if (strcmp(exec, "MOVE_RIGHT")==0) {
                //adaugam adresa in stiva
                adaugaElemStiva(UNDO, list);

                //executam comanda
                Move_Right(list);
            }

            //verificam daca in exec se afla MOVE_LEFT_CHAR <C>,
            //uitandu-ne la caracterul de pe pozitia 10 care
            //este C, spre deosebire de MOVE_RIGHT_CHAR <C> care
            //are caracterul C pe pozitia 11
            //de asemenea, nicio alta comanda nu are C pe pozitia 10
            if (strlen(exec)>=10&&exec[10]=='C') {
                //caracterul care trebuie cautat se afla pe
                //pozitia 15 in exec
                Move_Left_char(list, exec[15], &ok);
                
                //verificam daca s-a realizat operatia
                if (ok==0) {
                    fprintf(fc, "ERROR\n");
                }

                //eliberam cele 2 stive
                freeStiva(&UNDO);
                freeStiva(&REDO);
            }

            //verificam daca in exec se afla MOVE_RIGHT_CHAR <C>,
            //uitandu-ne la caracterul de pe pozitia 11 care
            //este C, spre deosebire de MOVE_LEFT_CHAR <C> care
            //are caracterul C pe pozitia 10
            //de asemenea, nicio alta comanda nu are C pe pozitia 11
            if (strlen(exec)>=11&&exec[11]=='C') {
                //caracterul care trebuie cautat se afla
                //pe pozitia 16 in exec
                Move_Right_char(list, exec[16]);
                
                //eliberam cele 2 stive
                freeStiva(&UNDO);
                freeStiva(&REDO);
            }

            //daca in exec se afla INSERT_LEFT <C>,
            //verificam uitandu-ne la pozitia 7 din exec
            //deoarece nicio alta comanda nu are L pe
            //pozitia 7
            if (strlen(exec)>=7&&exec[7]=='L') {
                //caracterul care trebuie inserat se afla
                //pe pozitia 12 in exec
                Insert_Left(list, exec[12], &ok);
                
                //verificam daca s-a realizat operatia
                if (ok==0) {
                    fprintf(fc, "ERROR\n");
                }

                //eliberam cele 2 stive
                freeStiva(&UNDO);
                freeStiva(&REDO);
            }

            //daca in exec se afla INSERT_RIGHT <C>,
            //verificam uitandu-ne la pozitiile 0 si 7 din exec
            //deoarece nicio alta comanda nu are simultan I pe
            //pozitia 0 si R pe pozitia 7
            if (strlen(exec)>=7&&exec[0]=='I'&&exec[7]=='R') {
                //caracterul care trebuie inserat se afla
                //pe pozitia 13 in exec
                Insert_Right(list, exec[13]);

                //eliberam cele 2 stive
                freeStiva(&UNDO);
                freeStiva(&REDO);
            }

            //daca in exec se afla WRITE <C>
            if (exec[0]=='W') {
                Write(list, exec[6]);

                //eliberam cele 2 stive
                freeStiva(&UNDO);
                freeStiva(&REDO);
            }

            //eliberam memoria alocata lui exec
            free(exec);
        }

        //daca in command se afla UNDO
        if (strcmp(command, "UNDO")==0) {
            //in extrage extragem nodul din stiva
            nodeStiva *extrage;
            nodeList *curr;
            
            //extragem elementul din stiva UNDO
            extrage=extrageElemStiva(UNDO);

            //adaugam pozitia curenta in stiva REDO
            adaugaElemStiva(REDO, list);
            
            //stergem barile de pe nodul curent
            curr=list->curr;
            curr->data[0]=curr->data[1];
            curr->data[1]='\0';
            
            //adaugam barile pe noul nod curent
            curr=extrage->poz;
            curr->data[1]=curr->data[0];
            curr->data[0]='|';
            curr->data[2]='|';
            curr->data[3]='\0';
            
            //actualizam pozitia degetului in list->>curr
            list->curr=curr;
            
            //eliberam memoria alocata pentru nodul extras
            //din stiva
            free(extrage);
        }

        //daca in command se afla REDO
        if (strcmp(command, "REDO")==0) {
            //in extrage extragem nodul din stiva
            nodeStiva *extrage;
            nodeList *curr;
            
            //extragem elementul din stiva REDO
            extrage=extrageElemStiva(REDO);

            //adaugam pozitia curenta in stiva UNDO
            adaugaElemStiva(UNDO, list);
            
            //stergem barile de pe nodul curent
            curr=list->curr;
            curr->data[0]=curr->data[1];
            curr->data[1]='\0';
            
            //adaugam barile pe noul nod curent
            curr=extrage->poz;
            curr->data[1]=curr->data[0];
            curr->data[0]='|';
            curr->data[2]='|';
            curr->data[3]='\0';
            
            //actualizam pozitia degetului in list->>curr
            list->curr=curr;
            
            //eliberam memoria alocata pentru nodul extras
            //din stiva
            free(extrage);
        }    
    }

    //eliberam memoria pentru adresa, command, lista,
    //coada si cele 2 stive
    free(adresa);
    free(command);
    freeList(&list);
    free(list);
    freeCoada(&coada);
    free(coada);
    freeStiva(&UNDO);
    free(UNDO);
    freeStiva(&REDO);
    free(REDO);

    //inchidem fisierele de intrare si iesire
    fclose(f);
    fclose(fc);

    return 0;
}
