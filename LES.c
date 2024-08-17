#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* Next;
};


//First data is always initialized with 0
typedef struct Node Tnode;

int storeListOnDisk(Tnode** List);
int readListFromDisk(Tnode** List);

int InitializeList(Tnode** List);
int ReInitializeList(Tnode** List);
int InsertNodeFinal(Tnode** List, int info);
int InsertNodeStart(Tnode** List, int info);
int InsertNodeAny(Tnode** List, int pos, int info);
int RemoveNode(Tnode** List, int pos);
int RemoveNodeFinal(Tnode** List);
int RemoveNodeStart(Tnode** List);
int EditNode(Tnode** List, int pos, int info);
int GetNodeInfo(Tnode** List, int pos, int* info);
int printList(Tnode** List);
int ExitProgram(Tnode** List);
int sizeList(Tnode** List);


void drawLine();

int main(int argc, char* argv[]){

    int info = 0;
    int pos = 0;
    int option = 0;

    Tnode* List;
    
    while(1){

        printf("\n\n\tChosse List option\n\n");
        printf("0. Exit\n");
        printf("1. Initialize List\n");
        printf("2. Reinitialize List\n");
        printf("3. Insert new node at the End\n");
        printf("4. Insert new node in a given position\n");
        printf("5. Insert Node at the Start\n");
        printf("6. Remove Node anywhere\n");
        printf("7. Remove node at the end\n");
        printf("8. Change data on node\n");
        printf("9. Print Linked List\n");
        printf("10. Get node info\n");
        printf("11. Print size of the list\n\n");
        
        scanf("%d", &option);

        switch(option)
        {
            case 0:
                ExitProgram(&List);
                printf("Saindo\n");
                return 0;
            case 1:
                if(InitializeList(&List) != 0){
                    printf("Error initializing List!\n");
                    return 1;
                };
                printf("\nList initialized!\n");
            case 2:
                if(ReInitializeList(&List) != 0){
                    printf("An error ocurred trying to reinitialize the list!\n");
                }
                break;
            case 3:
                getchar();
                printf("\nWhat integer to store on linked list?\n");
                scanf("%d", &info);
                if(InsertNodeFinal(&List, info) != 0){
                    printf("An error ocurred, exiting!\n");
                    return 1;
                };
                break;
            case 4:
                printf("\nWhat integer to store on linked list?\n");    
                scanf("%d", &info);
                printf("What position?\n");
                scanf("%d", &pos);
                if(InsertNodeAny(&List, pos, info) != 0){
                    printf("An error ocurred, exiting!\n");
                    return 1;
                };
                break;
            case 5:
                printf("What info to store a new node at start?\n");
                scanf("%d", &info);
                if(InsertNodeStart(&List, info) != 0){
                    printf("An error ocurred, exiting!\n");
                    return 1;
                }
                break;
            case 6:
                printf("What node to remove?\n");
                scanf("%d", &pos);
                if(RemoveNode(&List, pos) != 0){
                    printf("An error ocurred, exiting!\n");
                    return 1;
                }
                break;
            case 7:
                if(RemoveNodeFinal(&List) != 0){
                    printf("An error ocurred exiting!\n");
                    return 1;
                }
                break;
            case 8:
                printf("What node do you want to change?\n");
                scanf("%d",&pos);
                printf("What info do you want to put in it?\n");
                scanf("%d", &info);
                if(EditNode(&List, pos, info) == 1){
                    printf("\nTry again\n");
                }
                break;
            case 9:
                if(printList(&List) != 0){
                    printf("An error ocurred!\n");
                };
                break;
            case 10:
                printf("Where to look for info?\n");
                scanf("%d", &pos);
                if(GetNodeInfo(&List, pos, &info) != 0){
                    printf("List too short!\n");
                    break;
                }
                printf("Node info: %d\n", info);
                break;
            case 11:
                printf("\nThe size of the list is: %d node(s)\n", sizeList(&List));
                break;
            default:
                printf("Try a valid response!\n");
                break;
        }
    }
    ExitProgram(&List);
    return 0;
}

int InitializeList(Tnode** List){

    *List = (Tnode*)malloc(sizeof(Tnode));
    if(*List == NULL){
        printf("Error alocating memory!\n");
        return 1;
    }

    Tnode* aux = *List;
    aux->data = 0;
    aux->Next = NULL;

    return 0;
};

int ReInitializeList(Tnode** List){

    Tnode *aux, *percorre;
    percorre = *List;

    while(percorre->Next != NULL){

        aux = percorre->Next;
        free(percorre);
        percorre = aux;

    }

    free(percorre);

    if(InitializeList(List) != 0){
        return 1;
    };

    return 0;
};

int InsertNodeAny(Tnode** List, int pos, int info){
    Tnode* AuxN = *List;
    if(pos == 2){  
    
        Tnode* NewNode = (Tnode*)malloc(sizeof(Tnode));
        if(NewNode == NULL){
            printf("Memory error!\n");
            return 1;
        }
        NewNode->Next = AuxN->Next;
        NewNode->data = info;
        AuxN->Next = NewNode;
        return 0;
    }else{
        if(AuxN->Next == NULL){
            printf("List not long enough! Try usign add to Last Node\n");
            return 0;
        }
        InsertNodeAny(&AuxN->Next, --pos, info);
    }

    return 0;
};

int InsertNodeStart(Tnode** List, int info){

    Tnode* aux = *List;

    Tnode* NewNode = (Tnode*)malloc(sizeof(Tnode));
    if(NewNode == NULL){
        printf("Error alocating memory!\n");
        return 1;
    }
    NewNode->Next = aux;
    NewNode->data = info;
    *List = NewNode;

    return 0;
};

int GetNodeInfo(Tnode** List, int pos, int* info){
    
    Tnode* aux = *List;

    pos--;

    if(pos == -1){
        return 0;
    }
    
    *info = aux->data;
    
    if(aux->Next == NULL){
        return 2;
    }

    return GetNodeInfo(&aux->Next, pos, info);
};

int InsertNodeFinal(Tnode** List, int info){

    Tnode* percorre = *List;

    Tnode* NewNode = (Tnode*)malloc(sizeof(Tnode));
    if(NewNode == NULL){
        printf("Memory error!\n");
        return 1;
    }

    NewNode->data = info;
    NewNode->Next = NULL;

    Tnode* aux1;
    while(percorre->Next != NULL)
    {
        aux1 = percorre->Next;
        percorre = aux1;
    }
    
    percorre->Next = NewNode;

    return 0;
};

int printList(Tnode** List){

    Tnode* percorre = *List;

    printf("\n\n");

    if(percorre->Next == NULL){
        printf("List is too short!\n");
        return 1;
    }

    int index = 1;

    Tnode* aux;
    aux = percorre;
    while(aux->Next != NULL){

        printf("%d) %d\n", index, aux->data);
        aux = aux->Next;
        index++;
    }

    printf("%d) %d\n",index, aux->data);

    printf("\n\n");
    getchar();

    return 0;
};

int RemoveNode(Tnode** List, int pos){

    Tnode *percorre = *List;
    Tnode* aux;
    while(pos > 2){
        if(percorre->Next == NULL){
            printf("Non existent node, try another one!\n");
            return 0;
        }
        percorre = percorre->Next;
        pos--;
    }
    aux = (percorre->Next)->Next;
    free(percorre->Next);
    percorre->Next = aux;

    return 0;
};

int RemoveNodeFinal(Tnode** List){

    Tnode* aux = *List;

    if((aux->Next)->Next == NULL){
        free(aux->Next);
        aux->Next = NULL;
        return 0;
    }
    return RemoveNodeFinal(&aux->Next);
};

int EditNode(Tnode** List, int pos, int info){

    Tnode* aux = *List;
    
    while(pos > 1){
        if(aux->Next == NULL){
            printf("Error finding node!\n");
            return 1;
        }
        aux = aux->Next;
        pos--;
    }
    aux->data = info;

    return 0;
};

int ExitProgram(Tnode** List){

    Tnode* percorre = *List;
    Tnode* aux;
    while(percorre->Next != NULL){
        aux = percorre->Next;
        free(percorre);
        percorre = aux;
    }

    free(percorre);

    return 0;
};

void drawLine(){
    printf("\n");
    for(int index = 0; index < 25; index++){
        printf("*");
    }
    printf("\n");
};

int sizeList(Tnode** List){

    Tnode* aux = *List;
    int count = 1;
    while (aux->Next != NULL)
    {
        aux = aux->Next;
        count++;
    }

    return count;

};

int storeListOnDisk(Tnode** List){

    FILE* listOnDisk =
};

int readListFromDisk(Tnode** List){};

