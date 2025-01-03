#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    char id[15];
    char name[50];
    char email[50];
    char phone[15];
    int gender; // 0: Male, 1: Female
    int day, month, year;
    char username[50];
    long long balance;
    char status[10];
}User;

User users[100];
int userCount = 0;

void mainMenu();
void loginAdmin();
void adminMenu();
void addUser();
void displayAllUsers();
void searchUser();
void searchUserById();
int isUnique(char id[], char email[], char phone[]);
int isUserInfoValid(char id[], char name[], char phone[]);
int isUserInfoNotEmpty(char id[], char name[], char email[], char phone[]);
void toggleUserStatus();
void sortUsersByName();

int main() {
    mainMenu();
    return 0;
}

void mainMenu() {
    int choice;
    while(1) {
        printf("\n*** User Management System ***\n");
        printf("          CHOOSE YOUR ROLE\n");
        printf("      ========================\n");
        printf("      [1] Admin\n");
        printf("      [2] User\n");
        printf("      [0] Exit the Program\n");
        printf("      ========================\n");
        printf("      Enter Your Choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                loginAdmin();
                break;
            case 2:
                printf("\nChua Them Chuc Nang\n");
                break;
            case 0:
            	printf("\n");
            	printf("    ========= Thank You =========\n");
            	printf("    ========= See You Soon ======\n");
                return;
            default:
                printf("Lua Chon Khong Hop Le\n");
        }
    }
}

void loginAdmin() {
    char email[50], password[50];
    printf("\n*** User Management System ***\n");
    printf("               LOGIN\n");
    printf("      ========================\n");
    printf("      Email: ");
    scanf("%s", email);
    printf("      Password: ");
    scanf("%s", password);
    if(strcmp(email, "adminAccount@gmail.com") == 0 && strcmp(password, "admin123") == 0) {
        adminMenu();
    } else {
        printf("Email hoac mat khau khong hop le\n");
    }
}

void adminMenu() {
    int choice;
    while(1) {
        printf("\n*** Admin Menu ***\n");
        printf("  ========================\n");
        printf("  [1] Add A New User\n");
        printf("  [2] Show ALL Users\n");
        printf("  [3] Search Users\n");
        printf("  [4] Search Users By Id\n");
        printf("  [5] Lock/Open User\n");
        printf("  [6] Sort Users By Name\n");
        printf("  [0] Exit\n");
        printf("  ========================\n");
        printf("  Enter Your Choice: ");
        scanf("%d", &choice);
        system("cls");

        switch(choice) {
            case 1:
                addUser();
                break;
            case 2:
                displayAllUsers();
                break;
            case 3:
                searchUser();
                break;
            case 4:
                searchUserById();
                break;
            case 5:    
                toggleUserStatus();
				break;
			case 6:
                sortUsersByName();  // G?i hàm s?p x?p khi ngu?i dùng ch?n
                break;	
            case 0:
                return;
            default:
                printf("Lua Chon Khong Hop Le\n");
        }
    }
}

void addUser() {
    if (userCount >= 100) {
        printf("Danh Sach Da Day\n");
        return;
    }
    User newUser;
    fflush(stdin);
    printf("\n*** Add New User ***\n");
    printf("Enter user ID (over 3 characters) : ");
    fgets(newUser.id, sizeof(newUser.id), stdin);
    newUser.id[strcspn(newUser.id, "\n")] = 0;
    fflush(stdin);
    printf("Enter user name: ");
    fgets(newUser.name, sizeof(newUser.name), stdin);
    newUser.name[strcspn(newUser.name, "\n")] = 0;
    fflush(stdin);
    printf("Enter user email: ");
    fgets(newUser.email, sizeof(newUser.email), stdin);
    newUser.email[strcspn(newUser.email, "\n")] = 0;
    fflush(stdin);
    printf("Enter user phone: ");
    fgets(newUser.phone, sizeof(newUser.phone), stdin);
    newUser.phone[strcspn(newUser.phone, "\n")] = 0;
    fflush(stdin);
    printf("Status (Open/Lock): ");
    fgets(newUser.status, sizeof(newUser.status), stdin);
    newUser.status[strcspn(newUser.status, "\n")] = 0;

    if (!isUserInfoNotEmpty(newUser.id, newUser.name, newUser.email, newUser.phone)) {
        return;
    }

    if (isUserInfoValid(newUser.id, newUser.name, newUser.phone) && isUnique(newUser.id, newUser.email, newUser.phone)) {
        users[userCount++] = newUser;
        FILE *file = fopen("user.txt", "a");
        if (file == NULL) {
            printf("Loi: Khong the mo file de ghi\n");
            return;
        }
        fprintf(file, "%s,%s,%s,%s,%s\n", newUser.id, newUser.name, newUser.email, newUser.phone, newUser.status);
        fclose(file);
        printf("Them Thanh Cong\n");
    } else {
        printf("Loi: ID hoac Email Hoac Phone Bi Trung. Nguoi Dung Khong Duoc Them Vao\n");
    }

    printf("\nPress any key to return to Admin Menu... ");
    getchar(); 
}

void displayAllUsers() {
    userCount = 0;
    FILE *file = fopen("user.txt", "r");
    if (file == NULL) {
        printf("Khong The Mo File user.txt\n");
        return;
    }

    while (fscanf(file, "%[^,],%[^,],%[^,],%[^,],%s\n",
                  users[userCount].id,
                  users[userCount].name,
                  users[userCount].email,
                  users[userCount].phone,
                  users[userCount].status) == 5) {
        userCount++;
        if (userCount >= 100) {
            printf("Danh Sach Da Day\n");
            break;
        }
    }
    fclose(file);

    if (userCount == 0) {
        printf("Khong Co Nguoi Dung\n");
        return;
    }

    printf("\n==================================================================================\n");
    printf("| %-10s | %-20s | %-20s | %-10s | %-5s |\n", "ID", "Name", "Email", "Phone", "Status");
    printf("----------------------------------------------------------------------------------\n");

    for (int i = 0; i < userCount; i++) {
        printf("| %-10s | %-20s | %-20s | %-10s | %-5s |\n",
               users[i].id, users[i].name, users[i].email, users[i].phone, users[i].status);
    }
    printf("---------------------------------------------------------------------------------\n");

    printf("\nPress any key to return to Admin Menu... ");
    getchar(); 
}

void searchUser() {
    char searchName[50];
    printf("Nhap Ten De Tim Kiem: ");
    while (getchar() != '\n');
    scanf(" %[^\n]", searchName);

    int found = 0;
    printf("\n----------------------------------------------------------------------------------\n");
    printf("| %-10s | %-20s | %-20s | %-10s | %-5s |\n", "ID", "Name", "Email", "Phone", "Status");
    printf("----------------------------------------------------------------------------------\n");

    for (int i = 0; i < userCount; i++) {
        if (strstr(users[i].name, searchName) != NULL) {
            found = 1;
            printf("| %-10s | %-20s | %-20s | %-10s | %-5s |\n",
                   users[i].id, users[i].name, users[i].email, users[i].phone, users[i].status);
        }
    }
    printf("---------------------------------------------------------------------------------\n");

    if (!found) {
        printf("Khong Tim Thay Nguoi Dung '%s'\n", searchName);
    }

    printf("\nPress any key to return to Admin Menu...");
    getchar(); 
}

void searchUserById() {
    char searchId[50];
    printf("Nhap ID De Tim Kiem: ");
    while (getchar() != '\n');
    scanf(" %[^\n]", searchId);

    int found = 0;
    printf("\n----------------------------------------------------------------------------------\n");
    printf("| %-10s | %-20s | %-20s | %-10s | %-5s |\n", "ID", "Name", "Email", "Phone", "Status");
    printf("----------------------------------------------------------------------------------\n");

    for (int i = 0; i < userCount; i++) {
        if (strstr(users[i].id, searchId) != NULL) {
            found = 1;
            printf("| %-10s | %-20s | %-20s | %-10s | %-5s |\n",
                   users[i].id, users[i].name, users[i].email, users[i].phone, users[i].status);
        }
    }
    printf("---------------------------------------------------------------------------------\n");

    if (!found) {
        printf("Khong Tim Thay Nguoi Dung ID %s\n", searchId);
    }

    printf("\nPress any key to return to Admin Menu...");
    getchar(); 
}

int isUnique(char id[], char email[], char phone[]) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].id, id) == 0 || strcmp(users[i].email, email) == 0 || strcmp(users[i].phone, phone) == 0) {
            return 0;
        }
    }
    return 1;
}

int isUserInfoValid(char id[], char name[], char phone[]) {
    if (strlen(id) < 3 || 
        strlen(name) <= 3 ||
        strlen(phone) != 10) {
        printf("Thong tin khong hop le. ID nguoi dung phai dai 3 ky tu tro len, Ten phai nhieu hon 3 ky tu, So dien thoai phai dai 10 ky tu.\n");
        return 0;
    }
    return 1;
}

int isUserInfoNotEmpty(char id[], char name[], char email[], char phone[]) {
    if (strlen(id) == 0 || strlen(name) == 0 || strlen(email) == 0 || strlen(phone) == 0) {
        printf("Thong tin nguoi dung khong duoc de trong. Vui long nhap lai.\n");
        return 0;
    }
    return 1;
}

void toggleUserStatus() {
    char userId[15];
    printf("Nhap ID Nguoi Dung De Lock/Unlock: ");
    scanf("%s", userId);
    int userFound = 0;

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].id, userId) == 0) {
            userFound = 1;
            // Toggle the user's status
            if (strcmp(users[i].status, "Open") == 0) {
                strcpy(users[i].status, "Lock");
                printf("User %s Hien Da Bi Khoa\n", users[i].name);
            } else {
                strcpy(users[i].status, "Open");
                printf("User %s Hien Da Duoc Mo Khoa\n", users[i].name);
            }

            FILE *file = fopen("user.txt", "w");
            if (file == NULL) {
                printf("Loi: Khong the mo file de ghi\n");
                return;
            }

            for (int j = 0; j < userCount; j++) {
                fprintf(file, "%s,%s,%s,%s,%s\n",
                        users[j].id, users[j].name, users[j].email, users[j].phone, users[j].status);
            }

            fclose(file);
            return;
        }
    }

    if (!userFound) {
        printf("Khong Tim Thay ID Nguoi Dung\n");
    }
}

void sortUsersByName() {
    int choice;
    printf("\n*** Sort Users by Name ***\n");
    printf("1. Sort A to Z (Ascending)\n");
    printf("2. Sort Z to A (Descending)\n");
    printf("Choose your option: ");
    scanf("%d", &choice);

    if (choice == 1) {
        // A -> Z
        for (int i = 0; i < userCount - 1; i++) {
            for (int j = i + 1; j < userCount; j++) {
                if (strcmp(users[i].name, users[j].name) > 0) {
                    // Hoán d?i các user[i] và user[j]
                    User temp = users[i];
                    users[i] = users[j];
                    users[j] = temp;
                }
            }
        }
        printf("Danh Sach Nguoi Dung Da Duoc Sap Xep Tu A Den Z\n");
    } else if (choice == 2) {
        // Z -> A
        for (int i = 0; i < userCount - 1; i++) {
            for (int j = i + 1; j < userCount; j++) {
                if (strcmp(users[i].name, users[j].name) < 0) {
                    // Hoán d?i các user[i] và user[j]
                    User temp = users[i];
                    users[i] = users[j];
                    users[j] = temp;
                }
            }
        }
        printf("Danh Sach Nguoi Dung Da Duoc Sap Xep Tu Z Den A\n");
    } else {
        printf("Lua Chon Khong Hop Le\n");
        return;
    }

    // Luu du lieu vao file
    FILE *file = fopen("user.txt", "w");  
    if (file == NULL) {
        printf("Loi: Khong the mo file de ghi\n");
        return;
    }

    // Ghi lai danh sach nguoi dung vao file
    for (int i = 0; i < userCount; i++) {
        fprintf(file, "%s,%s,%s,%s,%s\n",
                users[i].id, users[i].name, users[i].email, users[i].phone, users[i].status);
    }

    fclose(file);

    // Hien thi lai danh sach nguoi dung da sap xep
    displayAllUsers();
}

