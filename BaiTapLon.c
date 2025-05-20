//Ten: Nguyen Huy Khang
//MSSV: 6551071043
//Lop: CNTT-K65
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

//Cau truc sinh vien
typedef struct sinhVien{
    char mssv[10];
    char hoTen[50];
    float diemTB;
    int namHoc;
}sinhVien;

//Cau truc node
typedef struct Node{
    char thaoTac[100];
    struct Node* next;
}Node;

//Khai bao cac ham
void themSinhVien(sinhVien** danhSach,int* n);
void hienThi(sinhVien* danhSach,int n);
void sapXepDiem(sinhVien* danhSach,int n);
void timKiem(sinhVien* danhSach,int n);
void xoaSinhVien(sinhVien** danhSach,int *n);
void ghiRaFile(sinhVien* danhSach,int n);
void docTuFile(sinhVien** danhSach,int* n);
void themThaoTac(Node** head,const char* thaoTac);
void hienThiLichSu(Node*head);
void freeDanhSach(sinhVien* danhSach);
void freeLichSu(Node* head);

int main(){
    sinhVien* danhSach = NULL;
    int n=0;
    Node* lichSu = NULL;
    int choice;
    do {
        printf("\n=== QUAN LY SINH VIEN ===\n");
        printf("1. Them sinh vien\n");
        printf("2. Hien thi danh sach\n");
        printf("3. Sap xep theo diem TB\n");
        printf("4. Tim kiem theo MSSV\n");
        printf("5. Xoa sinh vien\n");
        printf("6. Ghi vao file\n");
        printf("7. Doc tu file\n");
        printf("8. Hien thi lich su thao tac\n");
        printf("0. Thoat\n");
        printf("Chon chuc nang: ");
        scanf("%d", &choice);
        getchar();

        switch(choice){
            case 1:
                themSinhVien(&danhSach,&n);
                themThaoTac(&lichSu,"Them sinh vien");
                break;
            case 2:
                hienThi(danhSach,n);
                themThaoTac(&lichSu,"Hien thi danh sach");
                break;
            case 3:
                sapXepDiem(danhSach, n);
                printf("Da sap xep theo diem TB\n");
                themThaoTac(&lichSu,"Sap xep theo diem TB");
                break;
            case 4:
                timKiem(danhSach,n);
                themThaoTac(&lichSu,"Tim kiem theo MSSV");
                break;
            case 5:
                xoaSinhVien(&danhSach,&n);
                themThaoTac(&lichSu,"Xoa sinh vien");
                break;
            case 6:
                ghiRaFile(danhSach,n);
                themThaoTac(&lichSu,"Ghi danh sach vao file");
                break;
            case 7:
                docTuFile(&danhSach,&n);
                themThaoTac(&lichSu,"Doc danh sach tu file");
                break;
            case 8:
                hienThiLichSu(lichSu);
                break;
            case 0:
                printf("Thoat chuong trinh\n");
                break;
            default:
                printf("Lua chon khong hop le\n");
        }   
    }  while(choice != 0); 
    freeDanhSach(danhSach);
    freeLichSu(lichSu);
    
    return 0;
}

//Ham them sinh vien
void themSinhVien(sinhVien** danhSach,int* n){
    *danhSach = (sinhVien*)realloc(*danhSach, (*n + 1)* sizeof(sinhVien));
    if(*danhSach == NULL){
        printf("Khong the cap phat bo nho\n");
        return;
    }
    
    sinhVien sv;
    printf("Nhap MSSV: ");
    fgets(sv.mssv,sizeof(sv.mssv),stdin);
    sv.mssv[strcspn(sv.mssv,"\n")] = '\0';

    printf("Nhap ho ten: ");
    fgets(sv.hoTen,sizeof(sv.hoTen),stdin);
    sv.hoTen[strcspn(sv.hoTen,"\n")] = '\0';

    printf("Nhap diem TB: ");
    scanf("%f",&sv.diemTB);
    getchar();

    printf("NHap nam hoc: ");
    scanf("%d",&sv.namHoc);
    getchar();

    (*danhSach)[*n] = sv;
    (*n)++;

    printf("Da them sinh vien thanh cong\n");
}

//Ham hien thi danh sach sinh vien
void hienThi(sinhVien* danhSach,int n){
    if(n==0){
        printf("Danh sach rong\n");
        return;
    }

    for(int i=0;i<n;i++){
        printf("\nMSSV: %s\nHo va ten: %s\nDiem TB: %.2f\nNam hoc: %d\n",danhSach[i].mssv,danhSach[i].hoTen,danhSach[i].diemTB,danhSach[i].namHoc);
    }
}

//Ham sap xep sinh vien theo diem trung binh
void sapXepDiem(sinhVien* danhSach,int n){
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            if(danhSach[i].diemTB < danhSach[j].diemTB){
                sinhVien tmp = danhSach[i];
                danhSach[i]= danhSach[j];
                danhSach[j] = tmp;
            }
        }
    }
}

//Ham tim kiem sinh vien theo ten
void timKiem(sinhVien* danhSach,int n){
    char ma[10];
    printf("Nhap MSSV can tim: ");
    fgets(ma,sizeof(ma),stdin);
    ma[strcspn(ma,"\n")] = '\0';

    int found = 0;
    for(int i=0;i<n;i++){
        if(strcmp(danhSach[i].mssv,ma)==0){
            printf("MSSV: %s\nHo va ten: %s\nDiem TB: %f\nNam hoc: %d\n",danhSach[i].mssv,danhSach[i].hoTen,danhSach[i].diemTB,danhSach[i].namHoc);
            found = 1;
            break;
        }
    }
    if(!found){
        printf("Khong tim thay sinh vien co ma %s\n",ma);
    }
}

//Ham xoa sinh vien theo ma sinh vien
void xoaSinhVien(sinhVien** danhSach,int *n){
    if(*n==0){
        printf("Danh sach rong\n");
        return;
    }
    
    char ma[10];
    printf("Nhap MSSV can xoa: ");
    fgets(ma,sizeof(ma),stdin);
    ma[strcspn(ma,"\n")] = '\0';

    int pos = -1;
    for(int i=0;i<*n;i++){
        if(strcmp((*danhSach)[i].mssv,ma)==0){
            pos = i;
            break;
        }
    }
    if(pos==-1){
        printf("Khong tim thay sinh vien co ma: %s\n",ma);
        return;
    }

    for(int i=pos;i<*n-1;i++){
        (*danhSach)[i] = (*danhSach)[i+1];
    }

    if(*n > 1){
        *danhSach = (sinhVien*)realloc(*danhSach, (*n - 1) *sizeof(sinhVien));
    } else {
        free(*danhSach);
        *danhSach = NULL;
    }

    (*n)--;
    printf("Da xoa sinh vien co ma: %s\n",ma);
}

//Ghi danh sach ra file
void ghiRaFile(sinhVien* danhSach,int n){
    FILE* f = fopen("sinhvien.txt","w");
    if(f==NULL){
        printf("Khong the mo file de ghi\n");
        return;
    }

    for(int i=0;i<n;i++){
        fprintf(f,"%s|%s|%.1f|%d\n",danhSach[i].mssv,danhSach[i].hoTen,danhSach[i].diemTB,danhSach[i].namHoc);    
    }

    fclose(f);
    printf("Da ghi danh sach vao file sinhvien.txt\n");
}

//Doc danh sach tu file
void docTuFile(sinhVien** danhSach,int* n){
    FILE* f = fopen("sinhvien.txt","r");
    if(f == NULL){
        printf("Khong the mo file de doc\n");
        return;
    }

    int count = 0;
    char buffer[100];
    while(fgets(buffer,sizeof(buffer),f) != NULL){
        count++;
    }

    rewind(f);
    *danhSach = (sinhVien*)malloc(count * sizeof(sinhVien));
    if(*danhSach == NULL){
        printf("Khong the cap phat bo nho!\n");
        fclose(f);
        return;
    }

    *n = 0;
    while(fgets(buffer,sizeof(buffer),f) != NULL && *n < count){
        sinhVien sv;
        char* token =strtok(buffer,"|");
        if(token) strcpy(sv.mssv,token);

        token = strtok(NULL,"|");
        if(token) strcpy(sv.hoTen,token);

        token = strtok(NULL,"|");
        if(token) sv.diemTB = atof(token);

        token = strtok(NULL,"\n");
        if(token) sv.namHoc = atoi(token);

        (*danhSach)[*n] = sv;
        (*n)++;
    }
    fclose(f);
    printf("Da doc %d sinh vien tu file\n",*n);
}

//Ham them thao tac vao danh sach lien ket
void themThaoTac(Node** head,const char* thaoTac){
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(newNode == NULL){
        printf("Khong the cap phat bo nho\n");
        return;
    }

    strcpy(newNode->thaoTac,thaoTac);
    newNode->next = NULL;

    if(*head == NULL){
        *head = newNode;
    }else{
        Node* tmp = *head;
        while(tmp->next != NULL){
            tmp = tmp->next;
        }
        tmp->next = newNode;
    }
}

//Ham hien thi lich su
void hienThiLichSu(Node*head){
    if(head == NULL){
        printf("Chua co thao tac duoc ghi nhan\n");
        return;
    }

    printf("=====LICH SU THAO TAC=====\n");
    int stt = 1;
    Node* tmp = head;
    while(tmp != NULL){
        printf("%d. %s\n",stt,tmp->thaoTac);
        tmp = tmp->next;
        stt++;
    }
}

//Ham giai phong bo nho cho danh sach sinh vien
void freeDanhSach(sinhVien* danhSach){
    if(danhSach != NULL){
        free(danhSach);
    }
}

//Ham giai phong bo nho cho ham hien thi lich su
void freeLichSu(Node* head){
    Node* tmp;
    while(head != NULL){
        tmp = head;
        head = head->next;
        free(tmp);
    }
}
