#include <stdio.h> // UPDATE CPU VA RAM - DS LIEN KET DON
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
int current_computer = 0;

typedef struct Node{
    char CPU[3];
    char RAM[3];
    struct Node* next;
}Node;
Node* first, *last;

Node* makeNode(char* cpu, char* ram){
    Node* tmp = (Node*)malloc(sizeof(Node));
    strcpy(tmp->CPU, cpu);
    strcpy(tmp->RAM, ram);
    tmp->next = NULL; 
    return tmp;
}

void Init(){
    first = NULL; last = NULL;
}

int listEmpty(){
    return first == NULL && last == NULL;
}


void insertLast(char* cpu, char* ram){
    Node* tmp = makeNode(cpu, ram);
    if(listEmpty()){
        first = tmp; last = tmp;
    }else{
        last->next = tmp; last = tmp;
    }
}

void printList(){
    int i = 1;
    for(Node* p = first; p != NULL; p = p->next){
         printf("%d %s %s\n",i, p->CPU, p->RAM);
        i++;
    }
}

void load(char* filename){
    FILE* f = fopen(filename,"r");
    if(f == NULL) printf("File khong ton tai\n");
    int count;
    char cpu[3], ram[3];
    fscanf(f, "%d", &count);
    if((current_computer + count) <= 20){
        for(int i = 0; i < count; i++){
            fscanf(f,"%s %s", cpu, ram);
            insertLast(cpu, ram);
        }
        printf("So may vua them moi: %d\n", count);
        current_computer += count;
    }
    else{
        if(current_computer == 20){
            printf("Danh sach da day, khong them duoc\n");
        }
        else{
            for(int i = 0; i < 20 - current_computer; i++){
                fscanf(f,"%s %s", cpu, ram);
                insertLast(cpu, ram);
            }
            printf("So may vua them moi: %d\n", 20 - current_computer);
            current_computer = 20; 
        }
    }
    printf("So may hien tai la: %d\n", current_computer);
    fclose(f);
}

void processLoad(){
    char filename[256];
    printf("Hay nhap ten file: ");
    scanf("%s", filename);
    load(filename);
}

void finalize(){
    Node* p = first;
    while(p != NULL){
        Node* np = p->next;
        free(p);
        p = np;
    }
}

void updateCPU(){
    printf("Nhap ID cua may can update CPU: ");
    int id;
    scanf("%d", &id);
    while (id < 1 || id > current_computer){
        printf("Ban vui long nhap lai ID (1 <= ID <= %d): ", current_computer);
        scanf("%d", &id);
    }
    char new_cpu[3];
    Node *tmp = first;
    for(int i = 1; i < id; i++){
        tmp = tmp->next;
    }
    while(id <= current_computer){
        printf("Ban nhay nhap ten CPU moi cho may co ID = %d: ", id);
        scanf("%s", new_cpu);
        while((strcmp(new_cpu,"I3") != 0) && (strcmp(new_cpu,"I5") != 0) && (strcmp(new_cpu,"I7") != 0) && (strcmp(new_cpu,"i3") != 0) && (strcmp(new_cpu,"i5") != 0) && (strcmp(new_cpu,"i7") != 0) && (strcmp(new_cpu,"STOP") != 0)){
            printf("Loi! Ban hay nhap lai ten CPU moi: ");
            scanf("%s", new_cpu);
        }
        if(strcmp(new_cpu, "STOP") == 0){
            break;
        }
        else{
            strcpy(tmp->CPU, new_cpu);
            tmp = tmp->next;
            id++;
        }
    }
}

void updateRAM(){
    printf("Nhap ID cua may can update RAM: ");
    int id;
    scanf("%d", &id);
    while (id < 1 || id > current_computer){
        printf("Ban vui long nhap lai ID (1 <= ID <= %d): ", current_computer);
        scanf("%d", &id);
    }
    char new_ram[3];
    Node *tmp = first;
    for(int i = 1; i < id; i++){
        tmp = tmp->next;
    }
    while(id <= current_computer){
        printf("Ban nhay nhap RAM moi cho may co ID = %d: ", id);
        scanf("%s", new_ram);
        while((strcmp(new_ram, "1")) && (strcmp(new_ram, "2")) && (strcmp(new_ram, "4")) && (strcmp(new_ram, "8")) && (strcmp(new_ram, "16")) && (strcmp(new_ram, "32")) && (strcmp(new_ram, "STOP"))){
            printf("Loi! Ban hay nhap lai RAM moi: ");
            scanf("%s", new_ram);
        }
        if(strcmp(new_ram, "STOP") == 0){
            break;
        }
        else{
            strcpy(tmp->RAM, new_ram);
            tmp = tmp->next;
            id++;
        }
    }
}

void Find(){
    printf("Nhap CPU hoac RAM ban muon tim: ");
    char s[3];
    scanf("%s", s);
    if((strcmp(s,"I3") != 0) && (strcmp(s,"I5") != 0) && (strcmp(s,"I7") != 0) && (strcmp(s,"i3") != 0) && (strcmp(s,"i5") != 0) && (strcmp(s,"i7") != 0) && (strcmp(s, "1")) && (strcmp(s, "2")) && (strcmp(s, "4")) && (strcmp(s, "8")) && (strcmp(s, "16")) && (strcmp(s, "32"))){
        printf("Gia tri tim kiem khong hop le\n");
        return;
    }
    else{
        if((strcmp(s,"I3") == 0) || (strcmp(s,"I5") == 0) || (strcmp(s,"I7") == 0) || (strcmp(s,"i3") == 0) || (strcmp(s,"i5") == 0) || (strcmp(s,"i7") == 0)){
            for(Node *tmp = first; tmp != NULL; tmp = tmp->next){
                char p[3];
                strcpy(p, tmp->CPU);
                if(strcmp(strlwr(s), strlwr(p)) == 0){
                    printf("%s %s\n", tmp->CPU, tmp->RAM);
                }
            }
        }
        else{
            for(Node *tmp = first; tmp != NULL; tmp = tmp->next){
                if(strcmp(s, tmp->RAM) == 0){
                    printf("%s %s\n", tmp->CPU, tmp->RAM);
                }
            }
        }
    }
}   

void Menu(){
    printf("\n====Program for management computers====\n");
    printf("|0) Print                               |\n");
    printf("|1) Load Data Files                     |\n");
    printf("|2) Update CPU infor                    |\n");
    printf("|3) Update RAM infor                    |\n");
    printf("|4) Search                              |\n");
    printf("|5) Quit                                |\n");
    printf("-----------------------------------------\n");
    printf("Moi ban chon chuc nang: ");
}

int main(){
    Init();
    while(1){
        Menu();
        int k;
        scanf("%d", &k);
        while (k < 1 || k > 5){
            printf("Ban hay chon lai chuc nang(1->5): ");
            scanf("%d", &k);
        }
        switch (k)
        {
        case 0:
            printList();
            break;
        case 1:
            processLoad();
            break;
        case 2:
            updateCPU();
            printList();
            break;
        case 3:
            updateRAM();
            printList();
            break;
        case 4:
            Find();
            break;
        case 5:
            finalize();
            return 0;
        default:
            break;
        }
    }
    return 0;
}
