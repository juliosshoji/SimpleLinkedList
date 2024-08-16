#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* Next;
};

typedef struct Node Tnode;

int InsertNodeFinal(Tnode* List, int info);
int InsertNodeStart(Tnode* List, int info);
int InsertNodeAny(Tnode* List, int pos, int info);
int RemoveNode(Tnode* List, int pos);
int RemoveNodeFinal(Tnode* List);
int RemoveNodeStart(Tnode* List);
int EditNode(Tnode* List, int pos, int info);
int GetNodeInfo(Tnode* List, int pos, int* info);
int printList(Tnode* List);
int ExitProgram(Tnode* List);

void drawLine();

int main(int argc, char* argv[]){

    int info = 0;
    Tnode* List = (Tnode*)malloc(sizeof(Tnode));
    if(List == NULL){
        return 1;
    }

    int pos = 0;
    int option = 0;

    while(1){

        printf("\n\n\tChosse List option\n\n");
        printf("0. Exit\n");
        printf("1. Insert new node at the End\n");
        printf("2. Insert new node in a given position\n");
        printf("3. Insert Node at the Start\n");
        printf("4. Remove Node anywhere\n");
        printf("5. Remove node at the end\n");
        printf("6. Change data on node\n");
        printf("7. Print Linked List\n");
        printf("8. Get node info\n\n\n");
        
        scanf("%d", &option);

        switch(option)
        {
            case 0:
                ExitProgram(List);
                printf("Saindo\n");
                return 0;
            case 1:
                getchar();
                printf("\nWhat integer to store on linked list?\n");
                scanf("%d", &info);
                if(InsertNodeFinal(List, info) != 0){
                    printf("An error ocurred, exiting!\n");
                    return 1;
                };
                break;
            case 2:
                printf("\nWhat integer to store on linked list?\n");    
                scanf("%d", &info);
                printf("What position?\n");
                scanf("%d", &pos);
                if(InsertNodeAny(List, pos, info) != 0){
                    printf("An error ocurred, exiting!\n");
                    return 1;
                };
                break;
            case 3:
                printf("What info to store a new node at start?\n");
                scanf("%d", &info);
                if(InsertNodeStart(List, info) != 0){
                    printf("An error ocurred, exiting!\n");
                    return 1;
                }
                break;
            case 4:
                printf("What node to remove?\n");
                scanf("%d", &pos);
                if(RemoveNode(List, pos) != 0){
                    printf("An error ocurred, exiting!\n");
                    return 1;
                }
                break;
            case 5:
                if(RemoveNodeFinal(List) != 0){
                    printf("An error ocurred exiting!\n");
                    return 1;
                }
                break;
            case 6:
                printf("What node do you want to change?\n");
                scanf("%d",&pos);
                printf("What info do you want to put in it?\n");
                scanf("%d", &info);
                if(EditNode(List, pos, info) == 1){
                    printf("Try again\n");
                }
                break;
            case 7:
                if(printList(List) != 0){
                    printf("An error ocurred!\n");
                };
                break;
            case 8:
                printf("Where to look for info?\n");
                scanf("%d", &pos);
                if(GetNodeInfo(List, pos, &info) == 2){
                    printf("List too short!\n");
                    break;
                }
                printf("Node info: %d\n", info);
                break;
            default:
                break;
        }
    }
    ExitProgram(List);
    return 0;
}


int InsertNodeAny(Tnode* List, int pos, int info){
    
    if(pos == 1){  
        Tnode* AuxN = List->Next;
        
        Tnode* NewNode = (Tnode*)malloc(sizeof(Tnode));
        if(NewNode == NULL){
            printf("Memory error!\n");
            return 1;
        }
        NewNode->Next = AuxN;
        NewNode->data = info;
        List->Next = NewNode;
        return 0;
    }else{
        if(List->Next == NULL){
            printf("List not long enough! Try usign add to Last Node\n");
            return 0;
        }
        InsertNodeAny(List->Next, --pos, info);
    }

    return 0;
};

int InsertNodeStart(Tnode* List, int info){

    Tnode* NewNode = (Tnode*)malloc(sizeof(Tnode));
    if(NewNode == NULL){
        printf("Error alocating memory!\n");
        return 1;
    }

    NewNode->Next = List->Next;
    NewNode->data = info;
    List->Next = NewNode;

    return 0;
};

int GetNodeInfo(Tnode* List, int pos, int* info){
    
    pos--;
    if(List->Next == NULL){
        return 2;
    }
    *info = (List->Next)->data;
    if(pos == 0){
        return 1;
    }
    
    return GetNodeInfo(List->Next, pos, info);
};

int InsertNodeFinal(Tnode* List, int info){

    Tnode* NewNode = (Tnode*)malloc(sizeof(Tnode));
    if(NewNode == NULL){
        printf("Memory error!\n");
        return 1;
    }

    NewNode->data = info;
    NewNode->Next = NULL;

    Tnode* aux1;
    while(List->Next != NULL)
    {
        aux1 = List->Next;
        List = aux1;
    }
    
    List->Next = NewNode;

    return 0;
};

int printList(Tnode* List){

    printf("\n\n");

    if(List->Next == NULL){
        printf("List is too short!\n");
        return 1;
    }

    int index = 1;

    Tnode* aux;
    aux = List->Next;
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

int RemoveNode(Tnode* List, int pos){

    Tnode* aux;
    int index = 0;
    while(pos > 1){
        if(List->Next == NULL){
            printf("Non existent node, try another one!\n");
            return 0;
        }
        aux = List->Next;
        List = aux;
        pos--;
    }
    aux = List->Next;
    List->Next = aux->Next;
    free(aux);

    return 0;
};

int RemoveNodeFinal(Tnode* List){

    if((List->Next)->Next == NULL){
        free(List->Next);
        List->Next = NULL;
        return 0;
    }
    return RemoveNodeFinal(List->Next);
};

int EditNode(Tnode* List, int pos, int info){

    Tnode* aux;
    int index = 0;
    while(pos > 0){
        if(List->Next == NULL){
            printf("Error finding node!\n");
            return 1;
        }
        aux = List->Next;
        List = aux;
        pos--;
    }
    List->data = info;

    return 0;
};

int ExitProgram(Tnode* List){

    Tnode* aux;

    while(List->Next != NULL){
        aux = List->Next;
        free(List);
        List = aux;
    }

    free(List);

    return 0;
};

void drawLine(){
    printf("\n");
    for(int index = 0; index < 25; index++){
        printf("*");
    }
    printf("\n");
};