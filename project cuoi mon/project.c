#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct Employee{
    char empId[20];
    char name[50];
    char position[15];
    double baseSalary;
    int workDay;
};

struct TimeSheet{
    char logId[20];
    char empId[20];
    char date[20];
    char status[10];
};

// khoi tao mang
struct Employee employee[100];
int empCount = 0;

void Menu() {
    printf("\n  --------------------MENU-----------------\n"); 
    printf("  | 1. Them nhan vien moi                 |\n");
    printf("  | 2. Cap nhat ho so                     |\n");
    printf("  | 3. Sa thai nhan vien                  |\n");
    printf("  | 4. Hien thi danh sach nhan vien       |\n");
    printf("  | 5. Tra cuu nhan vien                  |\n");
    printf("  | 6. Sap xep danh sach                  |\n");
    printf("  | 7. Cham ngay cong                     |\n");
    printf("  | 8. Xem bang cong                      |\n");
    printf("  | 9. Thoat                              |\n");
    printf("  -----------------------------------------\n");
}

// ham kiem tra id 
int isValidId(char *id) {
    int len = strlen(id);
    if (len == 0) return 0;
    for (int i = 0; i < len; i++) {
        if (id[i] == ' ') return 0;
    }
    if (id[0] < '0' || id[0] > '9')
        return 0;

    return 1;
}

// ham kiem tra string trong
int isEmpty(char *str) {
    if (strlen(str) == 0) return 1;
    for (int i = 0; str[i]; i++) {
        if (!isspace(str[i])) return 0;
    }
    return 1;
}

int findEmployeeIndex(char id[]){
    for(int i = 0; i < empCount; i++){
        if(strcmp(employee[i].empId, id) == 0)
            return i;
    }
    return -1;
}

void addEmployee(){
    struct Employee add;
    add.workDay = 0;

    do {
        printf("Nhap ma nhan vien: ");
        fgets(add.empId, sizeof(add.empId), stdin);
        add.empId[strcspn(add.empId, "\n")] = 0;

        if (isEmpty(add.empId)) {
            printf("empID khong duoc de trong!\n");
        }
        else if (!isValidId(add.empId)) {
            printf("empID khong hop le!\n");
        }
        else if (findEmployeeIndex(add.empId) != -1) {
            printf("empID da ton tai!\n");
        }
        else 
            break;

    } while (1);

    do {
        printf("Nhap ten nhan vien: ");
        fgets(add.name, sizeof(add.name), stdin);
        add.name[strcspn(add.name, "\n")] = 0;

        if (isEmpty(add.name)) {
            printf("Ten khong duoc de trong!\n");
        } else break;
    } while (1);

    do {
        printf("Nhap chuc vu: ");
        fgets(add.position, sizeof(add.position), stdin);
        add.position[strcspn(add.position, "\n")] = 0;

        if (isEmpty(add.position)) {
            printf("Chuc vu khong duoc de trong!\n");
        } else break;
    } while (1);

    do {
        printf("Nhap luong co ban: ");
        if (scanf("%lf", &add.baseSalary) == 1 && add.baseSalary > 0) {
            while (getchar() != '\n'); 
            break;
        }
        printf("Luong phai la so > 0!\n");
        while (getchar() != '\n'); 
    } while (1);
	do {
        printf("Nhap so ngay cong: ");
        if (scanf("%d", &add.workDay) == 1 && add.workDay > 0) {
            while (getchar() != '\n'); 
            break;
        }
        printf("So ngay cong phai > 0!\n");
        while (getchar() != '\n'); 
    } while (1);
    employee[empCount++] = add;

    printf("Them nhan vien thanh cong!\n");
}


void updateEmployee() {
    char id[20];
    int pos;
    while(1) {
        printf("Nhap empID can cap nhat: ");
        fgets(id, sizeof(id), stdin);
        id[strcspn(id, "\n")] = 0;

        if (isEmpty(id)) { printf("empID khong duoc de trong!\n"); continue; }
        if (!isValidId(id)) { printf("empID khong hop le!\n"); continue; }

        pos = findEmployeeIndex(id);
        if (pos == -1) { printf("Khong tim thay nhan vien!\n"); continue; }
        break;
    }

    printf("\n--- Cap nhat ho so nhan vien ---\n");

    while(1) {
        printf("Nhap chuc vu moi: ");
        fgets(employee[pos].position, sizeof(employee[pos].position), stdin);
        employee[pos].position[strcspn(employee[pos].position, "\n")] = 0;
        if (isEmpty(employee[pos].position)) printf("Chuc vu khong duoc de trong!\n");
        else break;
    }

    while(1) {
        printf("Nhap luong moi: ");
        if (scanf("%lf", &employee[pos].baseSalary) == 1 && employee[pos].baseSalary > 0) {
            while (getchar() != '\n');
            break;
        }
        printf("Luong phai la so > 0!\n");
        while (getchar() != '\n');
    }

    printf("Cap nhat thanh cong!\n");
}

void deleteEmployee() {
    char id[20];
    int pos;

    while (1) {
        printf("Nhap empID muon sa thai: ");
        fgets(id, sizeof(id), stdin);
        id[strcspn(id, "\n")] = 0;

        if (isEmpty(id)) { printf("empID khong duoc de trong!\n"); continue; }
        if (!isValidId(id)) { printf("empID khong hop le!\n"); continue; }

        pos = findEmployeeIndex(id);
        if (pos == -1) { printf("Khong tim thay nhan vien!\n"); continue; }
        break;
    }

    for (int i = pos; i < empCount - 1; i++) {
        employee[i] = employee[i + 1];
    }

    empCount--;
    printf("Da sa thai nhan vien!\n");
}

void showEmployeePage() {
    if (empCount == 0) {
        printf("Danh sach nhan vien hien dang trong!\n");
        return;
    }

    int pageSize = 10;
    int totalPage = (empCount + pageSize - 1) / pageSize;
    int page;

    while (1) {
        printf("\nCo tong cong %d trang. Nhap trang muon xem (1-%d): ",
               totalPage, totalPage);

        if (scanf("%d", &page) == 1 && page >= 1 && page <= totalPage) {
            while (getchar() != '\n');
            break;
        }

        printf("Trang khong hop le! Vui long nhap tu 1 den %d.\n", totalPage);
        while (getchar() != '\n');
    }

    int start = (page - 1) * pageSize;
    int end = start + pageSize;
    if (end > empCount) end = empCount;

    printf("\n----------DANH SACH NHAN VIEN - TRANG %d/%d----------\n", page, totalPage);
    printf("%-5s %-15s %-25s %-15s %-10s %-10s\n",
           "STT", "MaNV", "Ten", "Chuc Vu", "Luong", "NgayCong");

    for (int i = start; i < end; i++) {
        printf("%-5d %-15s %-25s %-15s %-10.2lf %-10d\n",
               i + 1,
               employee[i].empId,
               employee[i].name,
               employee[i].position,
               employee[i].baseSalary,
               employee[i].workDay
        );
    }
}


void searchEmployee() {
    char searchName[50];

    printf("Nhap ten can tim: ");
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = 0;

    if (isEmpty(searchName)) {
        printf("Khong duoc de trong!\n");
        return;
    }

    int found = 0;
    for (int i = 0; i < empCount; i++) {
        if (strcmp(employee[i].name, searchName) == 0) {

            printf("\nTim thay nhan vien!\n");
            printf("ID: %s | Ten: %s | Chuc vu: %s | Luong: %.2lf | Ngay cong: %d\n",
                   employee[i].empId, employee[i].name, employee[i].position,
                   employee[i].baseSalary, employee[i].workDay);

            found = 1;
        }
    }

    if (!found) printf("Khong tim thay nhan vien!\n");
}
void searchEmployeesName(){
    if(empCount == 0){
    	printf("Danh sach nhan vien trong !\n");
    	return;
	}	
	char name[50];
	getchar();
	printf("Nhap ten nhan vien can tim:");
	fgets(name,sizeof(name),stdin);
	name[strcspn(name, "\n")] =0 ;

	int found =0;
	for(int i=0; i< empCount ;i++){
		if(strcmp(employee[i].name, name) != 0){
			printf("ID :%s | Ten:%s | Chuc Vu :%s | Luong: %.2lf | Ngay cong: %d\n",
			        employee[i].empId,
		            employee[i].name,
		            employee[i].position,
		            employee[i].baseSalary,
		            employee[i].workDay);
		        found = 1;
		}
	}
	if(found =0){
		printf("Khong tim thay ten nhan vien!\n");
	}
}
void arrangeEmployee() {
    if (empCount < 2) {
        printf("Khong du nhan vien de sap xep!\n");
        return;
    }

    int choice;
    printf("1. Tang dan (Luong)\n2. Giam dan (Luong)\nChon: ");
    scanf("%d", &choice);
    getchar();

    if (choice != 1 && choice != 2) {
        printf("Lua chon khong hop le!\n");
        return;
    }

    for (int i = 0; i < empCount - 1; i++) {
        for (int j = i + 1; j < empCount; j++) {

            int condition = 0;

            if (choice == 1 && employee[i].baseSalary > employee[j].baseSalary)
                condition = 1;
            if (choice == 2 && employee[i].baseSalary < employee[j].baseSalary)
                condition = 1;

            if (condition) {
                struct Employee temp = employee[i];
                employee[i] = employee[j];
                employee[j] = temp;
            }
        }
    }

    printf("Da sap xep thanh cong!\n");
}

int main (){
    int choice;
    do {
        Menu();

        printf("Nhap lua chon: ");
        scanf("%d", &choice);
        while(getchar()!='\n');
        switch(choice){
            case 1: 
			addEmployee(); 
			break;
			
            case 2: 
			updateEmployee(); 
			break;
			
            case 3: 
			deleteEmployee(); 
			break;
			
            case 4: 
			showEmployeePage(); 
			break;
			
            case 5: 
			searchEmployee(); 
			break;
		
            case 9: 
			printf("Thoat chuong trinh...\n"); 
			break;
            default: 
			printf("Lua chon khong hop le!\n");
        }

    } while(choice != 9);

    return 0;
}

