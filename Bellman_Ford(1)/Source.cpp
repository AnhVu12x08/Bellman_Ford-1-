#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <iostream>
#define _CRT_SECURE_NO_WARNINGS

struct Canh {
    int nguon, dich, trongSo;
};
struct DoThi {
    int V, E;
    struct Canh* canh;//mảng cạnh
};
struct DoThi* taoDoThi(int V, int E) {//tạo đồ thị với V đỉnh và E cạnh
    struct DoThi* dothi = new DoThi;//cấp phát động cho đồ thị
    dothi->V = V;//gán số lượng đỉnh và cạnh cho V và E
    dothi->E = E;
    dothi->canh = new Canh[E]; //cấp phát động cho mảng cạnh
    return dothi;
}

void InKetQua(int khoangCach[], int n) {
    printf("\n\t\t\tDinh\t\tKhoang cach\n");
    for (int i = 0; i < n; i++) {
        printf("\t\t\t%d\t\t\t%d\n", i, khoangCach[i]);
    }
}
int CoChuTrinhCanhAm(struct DoThi* dothi, int khoangCach[]) {
    for (int i = 0; i < dothi->E; i++) {
        int u = dothi->canh[i].nguon;
        int v = dothi->canh[i].dich;
        int trongSo = dothi->canh[i].trongSo;
        if (khoangCach[u] + trongSo < khoangCach[v]) {
            return 1;
        }
    }
    return 0;
}
void BellmanFord(struct DoThi* dothi, int nguon) {
    int V = dothi->V; //gán số lượng đỉnh và cạnh cho V và E (đã có số lượng đỉnh và cạnh)
    int E = dothi->E;
    int* KhoangCach = new int[V]; //mảng lưu khoảng cách ngắn nhất từ đỉnh nguồn đến các đỉnh còn lại
    for (int i = 0; i < V; i++) //khởi tạo khoảng cách ngắn nhất của tất cả các đỉnh là vô cực, ngoại trừ đỉnh nguồn là 0.
        KhoangCach[i] = INT_MAX;
    KhoangCach[nguon] = 0;
    for (int i = 1; i <= V - 1; i++) { //lặp lại V - 1 lần
        for (int j = 0; j < E; j++) { //duyệt qua tất cả các cạnh của đồ thị
            int u = dothi->canh[j].nguon; //lấy đỉnh nguồn và đỉnh đích của cạnh
            int v = dothi->canh[j].dich;
            int trongSo = dothi->canh[j].trongSo;
            if (KhoangCach[u] + trongSo < KhoangCach[v]) //nếu khoảng cách ngắn nhất từ đỉnh nguồn đến đỉnh u là KhoangCach[u], và trọng số của cạnh (u, v) là trongSo, 
                KhoangCach[v] = KhoangCach[u] + trongSo; //thì cập nhật khoảng cách ngắn nhất từ đỉnh nguồn đến đỉnh v thành KhoangCach[v] = KhoangCach[u] + trongSo).
        }
    }
    if (CoChuTrinhCanhAm(dothi, KhoangCach)) {
        printf("\t\t\tDo thi nay Co Chu Trinh Canh Am\n");
        delete[] KhoangCach;
        return;
    }
    InKetQua(KhoangCach, V);
    delete[] KhoangCach;
}
void NhapDoThi() {
    int V, E, S;
    printf("\n\t\t\tNhap thong tin cho do thi\n");    
    printf("\t\t\tNhap so Dinh: ");
    scanf_s("%d", &V);
    printf("\t\t\tNhap so Canh: ");
    scanf_s("%d", &E);
    printf("\t\t\tDinh Nguon: ");
    scanf_s("%d", &S);
    struct DoThi* dothi = taoDoThi(V, E);
    for (int i = 0; i < E; i++) {
        printf("\t\t\tNhap vao Nguon cua canh %d: ", i + 1);
        scanf_s("%d", &dothi->canh[i].nguon);
        printf("\t\t\tNhap vao Dich cua canh %d: ", i + 1);
        scanf_s("%d",&dothi->canh[i].dich);
        printf("\t\t\tNhap vao Trong So cua canh %d: ", i + 1);
        scanf_s("%d",&dothi->canh[i].trongSo);
        fflush(stdin);
    }
    BellmanFord(dothi, S);
    delete[] dothi->canh;
    delete dothi;
}
struct DoThi* DocFile() {
    FILE* f;
    if (fopen_s(&f, "input.txt", "r") != 0) {
        printf("\n\t\t\tMo tep khong thanh cong.\n");
        return NULL;
    }
    else {
    }
    int V, E, S;
    fscanf_s(f, "%d %d %d", &V, &E, &S);
    struct DoThi* dothi = taoDoThi(V, E);
    for (int i = 0; i < E; i++) {
        fscanf_s(f, "%d %d %d", &dothi->canh[i].nguon, &dothi->canh[i].dich, &dothi->canh[i].trongSo);
    }
    fclose(f);
    return dothi;
}
void XuatFile() {
    struct DoThi* dothi = DocFile();
    for (int i = 0; i < dothi->E; i++) {
        printf("\t\t\t%d %d %d\n", dothi->canh[i].nguon, dothi->canh[i].dich, dothi->canh[i].trongSo);
    }
}
void XuatKQTuFile() {
    struct DoThi* dothi = DocFile();
    int S = dothi->canh[0].nguon;
    if (dothi == NULL) {
        return;
    }
    BellmanFord(dothi, S);
    delete[] dothi->canh;
    delete dothi;
}
void XoaManHinh() {
    system("cls");
}

void Menu() {
    printf("\n\t\t\t****************************************************\n");
    printf("\t\t\t**                                               **\n");
    printf("\t\t\t**               Welcome to the Menu             **\n");
    printf("\t\t\t**                                               **\n");
    printf("\t\t\t****************************************************\n");
    printf("\t\t\t1. Nhap do thi de tim duong di ngan nhat den cac dinh con lai\n");
    printf("\t\t\t2. Xuat noi dung trong File\n");
    printf("\t\t\t3. Doc du lieu tu File va xuat ket qua\n");
    printf("\t\t\t4. Xoa man hinh\n");
    printf("\t\t\t5. Thoat\n");
}

int main() {
    int chon;
    do {
        Menu();
        printf("\t\t\tNhap lua chon: ");
        scanf_s("%d", &chon);
        switch (chon) {
        case 1:
            NhapDoThi();
            break;
        case 2:
            printf("\n\t\t\tNoi dung trong File la:\n");
            XuatFile();
            break;
        case 3:
            printf("\n\t\t\tKet qua tu File la:");
            XuatKQTuFile();
            break;
        case 4:
            XoaManHinh();
            break;
        case 5:
            exit(0);
        default:
            printf("Nhap sai, nhap lai!\n");
            break;
        }
    } while (chon != 5);
    return 0;
}

