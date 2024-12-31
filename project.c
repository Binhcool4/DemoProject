#include <stdio.h>
#include <string.h>

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
int userCount=0;
void mainMenu();
void loginAdmin();
void adminMenu();
void addUser();
void displayAllUsers();
void searchUser();
void searchUserById();
//void arrangeUser();
//void toggleUserStatus();
int isUnique(char id[], char email[], char phone[]);
int main(){
    mainMenu();
    return 0;
}
void mainMenu(){
    int choice;
    while(1){
        printf("\n*** User Management System ***\n");
        printf("          CHOOSE YOUR ROLE\n");
        printf("      ========================\n");
        printf("      [1] Admin\n");
        printf("      [2] User\n");
        printf("      [0] Exit the Program\n");
        printf("      ========================\n");
        printf("      Enter Your Choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                loginAdmin();
                break;
            case 2:
                printf("\nChua Them Chuc Nang\n");
                break;
            case 0:
                printf("Goodbye\n");
                return;
            default:
                printf("Lua Chon Khong Hop Le\n");
        }
    }
}
void loginAdmin(){
    char email[50], password[50];
    printf("\n*** User Management System ***\n");
    printf("               LOGIN\n");
    printf("      ========================\n");
    printf("      Email: ");
    scanf("%s", email);
    printf("      Password: ");
    scanf("%s", password);
    if(strcmp(email, "adminAccount@gmail.com")==0 && strcmp(password, "admin123")==0){
        adminMenu();
    }else{
        printf("Email hoac mat khau khong hop le\n");
    }
}
void adminMenu(){
    int choice;
    while(1){
        printf("\n*** User Management System ***\n");
        printf("\n  Menu\n");
        printf("  ========================\n");
        printf("  [1] Add A New User\n");
        printf("  [2] Show ALL Users\n");
        printf("  [3] Search Users\n");
//      printf("[4] Lock/Unlock A User\n");
        printf("  [5] Search Users By Id\n");
        printf("  [0] Exit\n");
        printf("  ========================\n");
        printf("  Enter Your Choice: ");
        scanf("%d", &choice);
        switch (choice){
            case 1:
                addUser();
                break;
            case 2:
                displayAllUsers();
                break;
            case 3:
                searchUser();
                break;
//            case 4:
//                toggleUserStatus();
//                break;
            case 5:
            	searchUserById();
            	break;
            case 0:
                return;
            default:
                printf("Lua Chon Khong Hop Le\n");
        }
    }
}
void addUser(){
    if (userCount>=100){
        printf("Danh Sach Da Day\n");
        return;
    }
    User newUser;
	fflush(stdin);
    printf("Enter user ID (over 3 characters) : ");
    fgets(newUser.id, sizeof(newUser.id), stdin);
    newUser.id[strcspn(newUser.id, "\n")]=0;
    fflush(stdin);
    printf("Enter user name: ");
    fgets(newUser.name, sizeof(newUser.name), stdin);
    newUser.name[strcspn(newUser.name, "\n")]=0;
    fflush(stdin);
    printf("Enter user email: ");
    fgets(newUser.email, sizeof(newUser.email), stdin);
    newUser.email[strcspn(newUser.email, "\n")]=0;
    fflush(stdin);
    printf("Enter user phone: ");
    fgets(newUser.phone, sizeof(newUser.phone), stdin);
    newUser.phone[strcspn(newUser.phone, "\n")]=0;
    fflush(stdin);
    printf("Status (Open/Lock): ");
    fgets(newUser.status, sizeof(newUser.status), stdin);
    newUser.status[strcspn(newUser.status, "\n")]=0;

    if (!isUserInfoNotEmpty(newUser.id, newUser.name, newUser.email, newUser.phone)){
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
}
void displayAllUsers(){
	userCount=0;
    FILE *file = fopen("user.txt","r");
    if(file==NULL){
        printf("Khong The Mo File user.txt\n");
        return;
    }
    while(fscanf(file, "%[^,],%[^,],%[^,],%[^,],%s\n",
                  users[userCount].id,
                  users[userCount].name,
                  users[userCount].email,
                  users[userCount].phone,
                  users[userCount].status) == 5){
        userCount++;
        if(userCount>=100){
            printf("Danh Sach Da Day\n");
            break;
        }
    }
    fclose(file);
    if(userCount==0){
        printf("Khong Co Nguoi Dung\n");
        return;
    }
    printf("\n==================================================================================\n");
    printf("| %-10s | %-20s | %-20s | %-10s | %-5s |\n", "ID", "Name", "Email", "Phone", "Status");
    printf("----------------------------------------------------------------------------------\n");
    for(int i=0; i<userCount; i++){
        printf("| %-10s | %-20s | %-20s | %-10s | %-5s |\n",
               users[i].id, users[i].name, users[i].email, users[i].phone, users[i].status);
    }
    printf("---------------------------------------------------------------------------------\n");
}
void searchUser(){
    char searchName[50];
    printf("Nhap Ten De Tim Kiem: ");
    while(getchar()!='\n');
    scanf(" %[^\n]", searchName);
    int found=0;
    printf("\n----------------------------------------------------------------------------------\n");
    printf("| %-10s | %-20s | %-20s | %-10s | %-5s |\n", "ID", "Name", "Email", "Phone", "Status");
    printf("----------------------------------------------------------------------------------\n");
    for(int i=0; i<userCount; i++){
        if(strstr(users[i].name, searchName)!=NULL){
            found=1;
            printf("| %-10s | %-20s | %-20s | %-10s | %-5s |\n",
                   users[i].id, users[i].name, users[i].email, users[i].phone, users[i].status);
        }
    }
    printf("---------------------------------------------------------------------------------\n");
    if(!found){
        printf("Khong Tim Thay Nguoi Dung '%s'\n", searchName);
    }
}

void searchUserById(){
    char searchId[50];
    printf("Nhap ID De Tim Kiem: ");
    while(getchar()!='\n');
    scanf(" %[^\n]", searchId);
    int found=0;
    printf("\n----------------------------------------------------------------------------------\n");
    printf("| %-10s | %-20s | %-20s | %-10s | %-5s |\n", "ID", "Name", "Email", "Phone", "Status");
    printf("----------------------------------------------------------------------------------\n");
    for(int i=0; i<userCount; i++){
        if(strstr(users[i].id, searchId)!=NULL){
            found=1;
            printf("| %-10s | %-20s | %-20s | %-10s | %-5s |\n",
                   users[i].id, users[i].name, users[i].email, users[i].phone, users[i].status);
        }
    }
    printf("---------------------------------------------------------------------------------\n");
    if(!found){
        printf("Khong Tim Thay Nguoi Dung ID %s\n", searchId);
    }
}

int isUnique(char id[], char email[], char phone[]){
    for(int i=0; i<userCount; i++){
        if(strcmp(users[i].id, id)==0 || strcmp(users[i].email, email)==0 || strcmp(users[i].phone, phone)==0){
            return 0;
        }
    }
    return 1;
}

//Kiem tra kich thuoc
int isUserInfoValid(char id[], char name[], char phone[]){
    if(strlen(id)<3|| 
        strlen(name)<=3 ||
        strlen(phone)!=10){
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
