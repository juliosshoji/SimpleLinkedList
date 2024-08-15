#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* Next;
};

typedef struct Node Tnode;

int InsertNodeFinal(Tnode* List, int info);
int InsertNodeAny(int pos, Tnode* List, int info);
int RemoveNode(int pos, Tnode* List);
int EditNode(int pos, Tnode* List, int info);
int GetNodeInfo(int pos, Tnode* List, int* info);
void printList(Tnode* List);
void ExitProgram(Tnode* List);

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
        printf("3. Remove Node\n");
        printf("4. Change data on node\n");
        printf("5. Print Linked List\n");
        printf("6. Get node info\n\n\n");
        
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
                if(InsertNodeAny(pos, List, info) != 0){
                    printf("An error ocurred, exiting!\n");
                    return 1;
                };
                break;
            case 3:
                printf("What node to remove?\n");
                scanf("%d", &pos);
                if(RemoveNode(pos, List) != 0){
                    printf("An error ocurred, exiting!\n");
                    return 1;
                }
                break;
            case 4:
                printf("What node do you want to change?\n");
                scanf("%d",&pos);
                printf("What info do you want to put in it?\n");
                scanf("%d", &info);
                if(EditNode(pos, List, info) != 0){
                    printf("An error ocurred, exiting!\n");
                    return 1;
                }
                break;
            case 5:
                printList(List);
                break;
            case 6:
                printf("Where to look for info?\n");
                scanf("%d", &pos);
                if(GetNodeInfo(pos, List, &info) == 2){
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


int InsertNodeAny(int pos, Tnode* List, int info){
    
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
        InsertNodeAny(--pos, List->Next, info);
    }

    return 0;
};

int GetNodeInfo(int pos, Tnode* List, int* info){
    
    pos--;
    if(List->Next == NULL){
        return 2;
    }
    *info = (List->Next)->data;
    if(pos == 0){
        return 1;
    }
    
    return GetNodeInfo(pos, List->Next, info);
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

void printList(Tnode* List){

    printf("\n\n");

    if(List->Next == NULL){
        printf("List is too short!\n");
        return;
    }

    Tnode* aux;
    aux = List->Next;
    while(aux->Next != NULL){

        printf("%d\n", aux->data);
        aux = aux->Next;
        
    }

    printf("%d\n", aux->data);

    printf("\n\n");
    getchar();

    return;
};

int RemoveNode(int pos, Tnode* List){

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
}

int EditNode(int pos, Tnode* List, int info){

    Tnode* aux;
    int index = 0;
    while(pos > 0){
        if(List->Next){
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

void ExitProgram(Tnode* List){

    Tnode* aux;

    while(List->Next != NULL){
        aux = List->Next;
        free(List);
        List = aux;
    }

    free(List);

};
