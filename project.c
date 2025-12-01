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

// ham kiem tra khoang trong
int isEmpty(char *str) {
    if (strlen(str) == 0) return 1;
    for (int i = 0; str[i]; i++) {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' &&str[i] != '\r' && str[i] != '\v' && str[i] != '\f') 
        	return 0;
    }
    return 1;
}
// tim kiem id
int findEmployeeIndex(char id[]){
    for(int i = 0; i < empCount; i++){
        if(strcmp(employee[i].empId, id) == 0)
            return i;
    }
    return -1;
}
// case 1
void addEmployee() {
    struct Employee add;
    add.workDay = 0;

    // Nhap empId
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
        else break;

    } while (1);

    // Nhap ten
    do {
        printf("Nhap ten nhan vien: ");
        fgets(add.name, sizeof(add.name), stdin);
        add.name[strcspn(add.name, "\n")] = 0;

        if (isEmpty(add.name)) {
            printf("Ten khong duoc de trong!\n");
        } else break;

    } while (1);

    // Nhap chuc vu
    do {
        printf("Nhap chuc vu: ");
        fgets(add.position, sizeof(add.position), stdin);
        add.position[strcspn(add.position, "\n")] = 0;

        if (isEmpty(add.position)) {
            printf("Chuc vu khong duoc de trong!\n");
        } else break;

    } while (1);

    // Nhap luong
    char salaryStr[50];
    double salary;
    while (1) {
        printf("Nhap luong co ban: ");
        fgets(salaryStr, sizeof(salaryStr), stdin);
        salaryStr[strcspn(salaryStr, "\n")] = 0;

        if (isEmpty(salaryStr)) {
            printf("Luong khong duoc de trong!\n");
            continue;
        }

        // Chuyen chuoi sang so
        int valid = 1;
        salary = 0;
        for (int i = 0; i < strlen(salaryStr); i++) {
            if (salaryStr[i] < '0' || salaryStr[i] > '9') {
                valid = 0;
                break;
            }
            salary = salary * 10 + (salaryStr[i] - '0');
        }

        if (!valid || salary <= 0) {
            printf("Luong phai la so > 0! Vui long nhap lai.\n");
            continue;
        }

        add.baseSalary = salary;
        break;
    }

    // Nhap so ngay cong
    char input[50];
    int workDay;
    while (1) {
        printf("Nhap so ngay cong: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (isEmpty(input)) {
            printf("Khong duoc de trong!\n");
            continue;
        }

        int valid = 1;
        workDay = 0;

        for (int i = 0; i < strlen(input); i++) {
            if (input[i] < '0' || input[i] > '9') {
                valid = 0;
                break;
            }
            workDay = workDay * 10 + (input[i] - '0');
        }

        if (valid && workDay > 0) {
            add.workDay = workDay;
            break;
        } else {
            printf("So ngay cong phai la so nguyen > 0!\n");
        }
    }
    employee[empCount++] = add;
    printf("Them nhan vien thanh cong!\n");
    printf("So ngay cong da nhap: %d\n", add.workDay);
}

// case 2
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
//case 3 sa thai
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
	char choice[5];
    printf("Ban co chac chan muon xoa nhan vien %s? (Y/N): ", id);

    fgets(choice, sizeof(choice), stdin);
    choice[strcspn(choice, "\n")] = '\0';

    if (choice[0] != 'Y' && choice[0] != 'y') {
        printf("Da huy thao tac xoa!\n");
        return;
    }
    for (int i = pos; i < empCount - 1; i++) {
        employee[i] = employee[i + 1];
    }
	
    empCount--;
    printf("Da sa thai nhan vien!\n");
}
//case 4 in danh sach
void showEmployeePage() {
    if (empCount == 0) {
        printf("Danh sach nhan vien hien dang trong!\n");
        return;
    }

    int pageSize = 10;
    int totalPage = (empCount + pageSize - 1) / pageSize;
    int page;
    char input[20];
    int valid;

    while (1) {
        printf("\nCo tong cong %d trang. Nhap trang muon xem (1-%d): ", totalPage, totalPage);
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (isEmpty(input)) {
            printf("Khong duoc de trong!\n");
            continue;
        }

        valid = 1;
        page = 0;

        for (int i = 0; i < strlen(input); i++) {
            if (input[i] < '0' || input[i] > '9') {  
                valid = 0;
                break;
            }
            page = page * 10 + (input[i] - '0');
        }

        if (valid && page >= 1 && page <= totalPage) {
            break;
        } else {
            printf("Trang khong hop le! Vui long nhap tu 1 den %d.\n", totalPage);
        }
    }

    int start = (page - 1) * pageSize;
    int end = (start + pageSize > empCount) ? empCount : start + pageSize;

    printf("\n============================DANH SACH NHAN VIEN (TRANG %d/%d)==============================\n",
               page, totalPage);

    printf("%-5s | %-10s | %-20s | %-15s | %-12s | %s\n",
           "STT", "EMP ID", "TEN", "CHUC VU", "LUONG CO BAN", "NGAY CONG");
    printf("-----------------------------------------------------------------------------------------\n");

    for (int i = start; i < end; i++) {
        printf("%-5d | %-10s | %-20s | %-15s | %-12.2lf | %d\n",
               i + 1,
               employee[i].empId,
               employee[i].name,
               employee[i].position,
               employee[i].baseSalary,
               employee[i].workDay);
    }

    printf("-----------------------------------------------------------------------------------------\n");
}

//case 5 tim kiem
void searchEmployee() {
    if (empCount == 0) {
        printf("Danh sach nhan vien dang trong!\n");
        return;
    }

    char searchName[50];
    while (1) {
        printf("Nhap ten can tim: ");
        fgets(searchName, sizeof(searchName), stdin);
        searchName[strcspn(searchName, "\n")] = 0;

        if (isEmpty(searchName)) {
            printf("Ten khong duoc de trong!\n");
            continue;
        }

        int found = 0;
        int searchLen = strlen(searchName);

        for (int i = 0; i < empCount; i++) {
            int empLen = strlen(employee[i].name);

            for (int j = 0; j <= empLen - searchLen; j++) {
                int match = 1;
                for (int k = 0; k < searchLen; k++) {
                    char c1 = employee[i].name[j + k];
                    char c2 = searchName[k];

                    if ('A' <= c1 && c1 <= 'Z') c1 += 'a' - 'A';
                    if ('A' <= c2 && c2 <= 'Z') c2 += 'a' - 'A';

                    if (c1 != c2) {
                        match = 0;
                        break;
                    }
                }
                if (match) {
                    printf("\nTim thay nhan vien!\n");
                    printf("ID: %s | Ten: %s | Chuc vu: %s | Luong: %.2lf | Ngay cong: %d\n",
                           employee[i].empId, employee[i].name, employee[i].position,
                           employee[i].baseSalary, employee[i].workDay);
                    found = 1;
                    break; 
                }
            }
        }

        if (found)
            break;
        else
            printf("Khong tim thay nhan vien! Vui long nhap lai.\n");
    }
}


//case 6 sap xep
void arrangeEmployee() {
    if (empCount < 1) {
        printf("Danh sach nhan vien dang trong!\n");
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
struct TimeSheet timesheet[1000];
int timeCount = 0;
             
//case 7
void timekeeping() {
    if (empCount == 0) {
        printf("Danh sach nhan vien dang trong!\n");
        return;
    }

    char id[20], date[20];
    int pos;

    // Nhap ma nhan vien
    while (1) {
        printf("Nhap ma nhan vien: ");
        fgets(id, sizeof(id), stdin);
        id[strcspn(id, "\n")] = 0;

        if (isEmpty(id)) {
            printf("Ma nhan vien khong duoc de trong!\n");
            continue;
        }

        pos = findEmployeeIndex(id);
        if (pos == -1) {
            printf("Khong tim thay nhan vien %s! Vui long nhap lai.\n", id);
            continue;
        }
        break;
    }

    while (1) {
        printf("Nhap ngay cham cong (dd/mm/yyyy): ");
        fgets(date, sizeof(date), stdin);
        date[strcspn(date, "\n")] = 0;

        if (isEmpty(date)) {
            printf("Ngay khong duoc de trong!\n");
            continue;
        }

        int day, month, year;

        if (sscanf(date, "%d/%d/%d", &day, &month, &year) != 3) {
            printf("Dinh dang ngay khong hop le! Vui long nhap lai.\n");
            continue;
        }

        if (month < 1 || month > 12) {
            printf("Thang phai tu 1 den 12! Vui long nhap lai.\n");
            continue;
        }

        // Kiem tra ngay theo thang va nam (nam nhuan)
        int maxDay;
        switch (month) {
            case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                maxDay = 31; break;
            case 4: case 6: case 9: case 11:
                maxDay = 30; break;
            case 2:
                maxDay = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? 29 : 28;
                break;
        }

        if (day < 1 || day > maxDay) {
            printf("Ngay khong hop le! Thang %d chi co %d ngay. Vui long nhap lai.\n", month, maxDay);
            continue;
        }

        int duplicated = 0;
        for (int i = 0; i < timeCount; i++) {
            if (strcmp(timesheet[i].empId, id) == 0 &&
                strcmp(timesheet[i].date, date) == 0) {
                printf("Ngay nay da cham cong roi! Vui long nhap ngay khac.\n");
                duplicated = 1;
                break;
            }
        }

        if (!duplicated) break;
    }

    sprintf(timesheet[timeCount].logId, "LOG%03d", timeCount + 1);
    strcpy(timesheet[timeCount].empId, id);
    strcpy(timesheet[timeCount].date, date);
    strcpy(timesheet[timeCount].status, "Di lam");

    timeCount++;
    employee[pos].workDay++;

    printf("Cham cong thanh cong!\n");
}

//case 8 hien thi danh sach cham cong
void viewTimeSheet() {
    if (empCount == 0) {
        printf("Danh sach nhan vien trong!\n");
        return;
    }

    char id[20];
    int pos;

    while (1) {
        printf("Nhap ma nhan vien can xem bang cong: ");
        fgets(id, sizeof(id), stdin);
        id[strcspn(id, "\n")] = 0;

        if (isEmpty(id)) {
            printf("Ma nhan vien khong duoc de trong!\n");
            continue;
        }

        pos = findEmployeeIndex(id);
        if (pos == -1) {
            printf("Khong tim thay nhan vien %s\n", id);
            continue;
        }
        break;
    }

    printf("\n--- BANG CONG CUA %s (%s) ---\n",
           employee[pos].empId,
           employee[pos].name);

    int found = 0;

    for (int i = 0; i < timeCount; i++) {
        if (strcmp(timesheet[i].empId, id) == 0) {
            printf("%s | %s | %s\n",
                   timesheet[i].logId,
                   timesheet[i].date,
                   timesheet[i].status);
            found = 1;
        }
    }

    if (!found)
        printf("Nhan vien chua co cham cong.\n");
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
			case 6:
				arrangeEmployee();
				break;
			case 7:
				timekeeping();
				break;
			case 8:
				viewTimeSheet();	
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

