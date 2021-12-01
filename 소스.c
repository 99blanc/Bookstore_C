/*
프로그램 설명: 도서 관리 프로그램(Bookstore)
학번: 201810246
이름: 김세현
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#define USER_SIZE 50
#define BOOK_SIZE 100
#define MAX_SIZE 50
#define ADMIN_ID "2021"
#define ADMIN_PW 1202

typedef struct USER {
    char ID[USER_SIZE];
    int PW;
    int money;
} user;

char ID[USER_SIZE];
int PW;
int money;

typedef struct BOOK {
    char title[BOOK_SIZE];
    char author[BOOK_SIZE];
    char publish[BOOK_SIZE];
    int price;
} book;

void administermenu();
void listmenu();

void gotoxy(int x, int y) {
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int checkfile(char *filename) {
    FILE *file;
    if (file = fopen(filename, "r")) {
        return 1;
    }
    else {
        return 0;
    }
}

void gui(int scene) {
    int x = 0, y = 0;
    system("cls");
    gotoxy(x, y);
    for (int i = 0; i < 120; i++) {
        printf("─");
    }
    y = 1;
    switch (scene) {
        case 0:
            printf("[ LOGIN ]");
            break;
        case 1:
            printf("[ ADMINISTER ] ID : %s, CASH : %d", ID, money);
            break;
        case 2:
            printf("[ LIST ] ID : %s, CASH : %d", ID, money);
            break;
        case 3:
            printf("[ SHOP ] ID : %s, CASH : %d", ID, money);
            break;
        case 4:
            printf("[ WALLET ] ID : %s, CASH : %d", ID, money);
            break;
        case 5:
            printf("[ MODIFY ]");
            break;
        default:
            printf("[ MAIN ]");
            break;
    }
    x = 50;
    gotoxy(x, y);
    printf(":: Bookstore ::");
    x = 0; y = 2;
    gotoxy(x, y);
}

void booklist(int permit) {
    gui(2);
    FILE *file = fopen("bookstore.txt", "r");
    struct BOOK book;
    int count = 0;
    printf("\n도서 목록\n");
    while (!feof(file)) {
        fscanf(file, "%s %s %s %d\n", &book.title, &book.author, &book.publish, &book.price);
        printf("도서 이름 : %s, 저자 : %s, 출판사 : %s, 가격 : %d\n", book.title, book.author, book.publish, book.price);
    }
    getch();
    switch (permit) {
        case 0:
            administermenu();
            break;
        case 1:
            listmenu();
            break;
        default:
            printf("\n유효하지 않은 입력입니다.\n");
            break;
    }
    fclose(file);
}

void booksuch(int permit) {
    gui(2);
    FILE *file = fopen("bookstore.txt", "r");
    struct BOOK book;
    struct BOOK find;
    printf("\n찾고 싶은 도서의 제목을 입력하세요.\n");
    printf("\n [입력] : ");
    scanf("%s", &book.title);
    while (!feof(file)) {
        fscanf(file, "%s %s %s %d\n", &find.title, &find.author, &find.publish, &find.price);
        if (strcmp(find.title, book.title) == 0) {
            printf("도서 이름 : %s, 저자 : %s, 출판사 : %s, 가격 : %d\n", find.title, find.author, find.publish, find.price);
            break;
        }
    }
    getch();
    switch (permit) {
        case 0:
            administermenu();
            break;
        case 1:
            listmenu();
            break;
        default:
            printf("\n유효하지 않은 입력입니다.\n");
            break;
    }
    fclose(file);
}

void addbook() {
    gui(5);
    FILE *file = fopen("bookstore.txt", "a");
    struct BOOK book;
    int input = 0;
    printf("\n등록할 도서의 이름을 입력하세요.\n");
    printf("\n [입력] : ");
    scanf("%s", &book.title);
    printf("\n등록할 도서의 저자를 입력하세요.\n");
    printf("\n [입력] : ");
    scanf("%s", &book.author);
    printf("\n등록할 도서의 출판사를 입력하세요.\n");
    printf("\n [입력] : ");
    scanf("%s", &book.publish);
    printf("\n등록할 도서의 가격을 입력하세요.\n");
    printf("\n [입력] : ");
    scanf("%d", &book.price);
    printf("\n도서 정보\n이름 : %s\n저자 : %s\n출판사 : %s\n가격 : %d\n", book.title, book.author, book.publish, book.price);
    printf("\n위 정보가 맞으면 0 틀리면 1을 입력하세요.\n");
    printf("\n [입력] : ");
    scanf("%d", &input);
    switch (input) {
        case 0:
            fprintf(file, "%s %s %s %d\n", book.title, book.author, book.publish, book.price);
            break;
        case 1:
            printf("\n성공적으로 작업을 취소하였습니다.\n");
            break;
        default:
            printf("\n유효하지 않은 입력입니다.\n");
            break;
    }
    fclose(file);
    administermenu();
}

void delbook() {
    gui(5);
    FILE *file = fopen("bookstore.txt", "r");
    struct BOOK book;
    struct BOOK find[MAX_SIZE];
    int count = 0, value = 0, result;
    while (!feof(file)) {
        fscanf(file, "%s %s %s %d\n", &find[count].title, &find[count].author, &find[count].publish, &find[count].price);
        count++;
    }
    fclose(file);
    printf("\n삭제하고 싶은 도서의 제목을 입력하세요.\n");
    printf("\n [입력] : ");
    scanf("%s", &book.title);
    for (int i = 0; i < count; i++) {
        if (strcmp(find[i].title, book.title) == 0) {
            value = 1;
            result = i;
            break;
        }
    }
    if (value == 1) {
        printf("도서의 정보를 모두 삭제합니다.");
        file = fopen("bookstore.txt", "w");
        for (int i = 0; i < count; i++) {
            if (result == i) {

            }
            else {
            fprintf(file, "%s %s %s %d\n", find[i].title, find[i].author, find[i].publish, find[i].price);
            }
        }
        fclose(file);
    }
    else {
        printf("도서의 정보를 찾을 수 없었습니다.");
    }
    getch();
    booklist(0);
}

void modifymoney() {
    FILE *file = fopen("account.txt", "r");
    struct USER user;
    struct USER find[MAX_SIZE];
    int count = 0;
    printf("%d", money);
    while (!feof(file)) {
        fscanf(file, "%s %d %d\n", &find[count].ID, &find[count].PW, &find[count].money);
        count++;
    }
    fclose(file);
    file = fopen("account.txt", "w");
    for (int i = 0; i < count; i++) {
        if (strcmp(find[i].ID, ID) == 0) {
            fprintf(file, "%s %d %d\n", find[i].ID, find[i].PW, money);
        }
        else {
            fprintf(file, "%s %d %d\n", find[i].ID, find[i].PW, find[i].money);
        }
    }
    fclose(file);
}

void buybook() {
    gui(3);
    FILE *file = fopen("bookstore.txt", "r");
    struct BOOK book;
    struct BOOK find;
    printf("\n사고 싶은 도서의 제목을 입력하세요.\n");
    printf("\n [입력] : ");
    scanf("%s", &book.title);
    while (!feof(file)) {
        fscanf(file, "%s %s %s %d\n", &find.title, &find.author, &find.publish, &find.price);
        if (strcmp(find.title, book.title) == 0) {
            if (money == -1) {
                printf("\n관리자 권한으로 도서를 구입하였습니다.\n");
                break;
            }
            else if (money < find.price) {
                printf("\n금액이 부족합니다.\n");
                getch();
                listmenu();
            }
            else {
                money -= find.price;
                printf("\n성공적으로 도서를 구입하였습니다.\n");
                break;
            }
        }
    }
    fclose(file);
    modifymoney();
    getch();
    listmenu();
}

void bookpayment() {
    gui(4);
    int cash;
    printf("\n충전하고 싶은 금액의 수량을 입력하세요.\n");
    printf("\n [입력] : ");
    scanf("%d", &cash);
    money += cash;
    printf("\n충전하고 난 후의 금액 : %d\n", money);
    modifymoney();
    getch();
    listmenu();
}

void accountlist() {
    gui(1);
    FILE *file = fopen("account.txt", "r");
    struct USER user;
    int count = 0;
    printf("\n사용자 목록\n");
    while (!feof(file)) {
        fscanf(file, "%s %d %d\n", &user.ID, &user.PW, &user.money);
        printf("사용자 ID : %s, PW : %d, 충전 금액 : %d\n", user.ID, user.PW, user.money);
    }
    getch();
    administermenu();
    fclose(file);
}

void delaccount() {
    gui(1);
    FILE *file = fopen("account.txt", "r");
    struct USER user;
    struct USER find[MAX_SIZE];
    int count = 0, value = 0, result;
    while (!feof(file)) {
        fscanf(file, "%s %d %d\n", &find[count].ID, &find[count].PW, &find[count].money);
        count++;
    }
    fclose(file);
    printf("\n삭제하고 싶은 사용자의 아이디를 입력하세요.\n");
    printf("\n [입력] : ");
    scanf("%s", &user.ID);
    for (int i = 0; i < count; i++) {
        if (strcmp(find[i].ID, user.ID) == 0) {
            value = 1; result = i;
            break;
        }
    }
    if (value == 1) {
        printf("사용자의 정보를 모두 삭제합니다.");
        file = fopen("account.txt", "w");
        for (int i = 0; i < count; i++) {
            if (result == i) {

            }
            else {
                fprintf(file, "%s %d %d\n", find[i].ID, find[i].PW, find[i].money);
            }
        }
        fclose(file);
    }
    else {
        printf("사용자의 정보를 찾을 수 없었습니다.");
    }
    getch();
    accountlist();
}

void listmenu() {
    gui(2);
    int input = 0;
    printf("\n1. [도서 목록]\n2. [도서 검색]\n3. [도서 구매]\n4. [금액 충전]\n9. [메인 화면]\n");
    printf("\n [입력] : ");
    scanf("%d", &input);
    switch (input) {
    case 1:
        booklist(1);
        break;
    case 2:
        booksuch(1);
        break;
    case 3:
        buybook();
        break;
    case 4:
        bookpayment();
        break;
    case 9:
        main();
        break;
    default:
        printf("\n유효하지 않은 입력입니다.\n");
        break;
    }
}

void administermenu() {
    gui(1);
    int input = 0;
    printf("\n1. [도서 목록]\n2. [도서 검색]\n3. [도서 구매]\n4. [도서 등록]\n5. [도서 삭제]\n6. [회원계정 목록]\n7. [회원계정 삭제]\n9. [메인 화면]\n");
    printf("\n [입력] : ");
    scanf("%d", &input);
    switch (input) {
    case 1:
        booklist(0);
        break;
    case 2:
        booksuch(0);
        break;
    case 3:
        buybook();
        break;
    case 4:
        addbook();
        break;
    case 5:
        delbook();
        break;
    case 6:
        accountlist();
        break;
    case 7:
        delaccount();
        break;
    case 9:
        main();
        break;
    default:
        printf("\n유효하지 않은 입력입니다.\n");
        break;
    }
}

void registermenu() {
    gui(0);
    FILE *file = fopen("account.txt", "r");
    struct USER user;
    struct USER find;
    printf("\n회원가입을 위해 등록할 ID를 입력하세요.\n");
    printf("\n [입력] : ");
    scanf("%s", &user.ID);
    while (!feof(file)) {
        fscanf(file, "%s %d %d\n", &find.ID, &find.PW, &find.money);
        if (strcmp(find.ID, user.ID) == 0) {
            printf("\n이미 등록된 ID입니다.\n");
            getch();
            registermenu();
        }
    }
    fclose(file);
    printf("\n회원가입을 위해 등록할 PW를 입력하세요.\n");
    printf("\n [입력] : ");
    scanf("%d", &user.PW);
    file = fopen("account.txt", "a");
    fprintf(file, "%s %d %d\n", user.ID, user.PW, 0);
    fclose(file);
    printf("\n성공적으로 회원가입이 되었습니다.\n");
    main();
}

void loginmenu() {
    gui(0);
    FILE *file = fopen("account.txt", "r");
    struct USER user;
    struct USER find;
    int count = 0;
    printf("\n로그인할 ID를 입력하세요.\n");
    printf("\n [입력] : ");
    scanf("%s", &user.ID);
    while (!feof(file)) {
        fscanf(file, "%s %d %d\n", &find.ID, &find.PW, &find.money);
        if (strcmp(find.ID, user.ID) == 0) {
            printf("\n로그인할 PW를 입력하세요.\n");
            printf("\n [입력] : ");
            scanf("%d", &user.PW);
            if (find.PW == user.PW) {
                printf("\n성공적으로 로그인이 되었습니다.\n");
                strcpy(ID, user.ID);
                PW = user.PW;
                money = find.money;
                getch();
                listmenu();
                break;
            }
            else {
                loginmenu();
                break;
            }
        }
    }
    loginmenu();
    fclose(file);
}

void adminloginmenu() {
    gui(0);
    struct USER user;
    printf("\n로그인할 ID를 입력하세요.\n");
    printf("\n [입력] : ");
    scanf("%s", &user.ID);
    if (strcmp(ADMIN_ID, user.ID) == 0) {
        printf("\n로그인할 PW를 입력하세요.\n");
        printf("\n [입력] : ");
        scanf("%d", &user.PW);
        if (ADMIN_PW == user.PW) {
            printf("\n성공적으로 로그인이 되었습니다.\n");
            strcpy(ID, user.ID);
            money = -1;
            getch();
            administermenu();
        }
        else {
            adminloginmenu();
        }
    }
}

int main() {
    FILE* file;
    int input = 0;
    if (!checkfile("bookstore.txt")) {
        file = fopen("bookstore.txt", "w");
        fclose(file);
    }
    if (!checkfile("account.txt")) {
        file = fopen("account.txt", "w");
        fclose(file);
    }
    gui(-1);
    printf("\n1. [회원가입]\n2. [로그인]\n3. [관리자]");
    printf("\n [입력] : ");
    scanf("%d", &input);
    if (input == 1) {
        registermenu();
    }
    else if (input == 2) {
        loginmenu();
    }
    else if (input == 3) {
        adminloginmenu();
    }
    else {
        printf("\n유효하지 않은 입력입니다.\n");
    }

    return 0;
}