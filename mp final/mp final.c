#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

typedef struct
{
    int index;
    char data[256];
    int prevHash;
    int hash;
    int nonce;
} Block;

int index;

struct
{
    int index;
    int facc;
    int tacc;
    int amount;

} tran;

int hash(char data[])
{ //  hash algorithm
    int hash = 0, i;
    for (i = 0; i < strlen(data); i++)
    {
        hash = hash ^ data[i];
        hash = hash * 0x123456789;
    }

    return hash;
}
int temp, chash;
float n = 0.0;

int mine_block(char *data)
{
    int nonce = 0;
    int hash1;

    char dataToHash[256];
    while (1)
    {
        sprintf(dataToHash, "%s%d", data, nonce);
        hash1 = hash(dataToHash);

        if ((hash1 & 0xff) == 0x00)
        {
            temp = hash1;
            chash = temp;
            return nonce;
        }

        nonce++;
        printf("%x\n", hash1);
    }
    return nonce;
}

int i, j;
int main_exit;
void menu();
struct date
{
    int month, day, year;
};
struct
{
    char name[60];
    int accountNo, age;
    char address[60];
    double phone;
    float amount;
    struct date dateOfBirth;
    struct date deposit;
    struct date withdraw;
    char password[10];

} add, update, check, rem, transaction, recipient, add1;

void fordelay(int j)
{
    int i, k;
    for (i = 0; i < j; i++)
        k = i;
}

void newAccount()
{
    int choice;
    FILE *ptr;

    ptr = fopen("record.dat", "ab+");
account_no:
    system("cls");
    printf("\t\t\t\xB2\xB2\xB2\ ADD RECORD  \xB2\xB2\xB2\xB2");
    printf("\n\n\nEnter today's date(mm/dd/yyyy):");
    scanf("%d/%d/%d", &add.deposit.month, &add.deposit.day, &add.deposit.year);
    printf("\nEnter the account number:");
    scanf("%d", &check.accountNo);
    while (fread(&add, sizeof(add), 1, ptr))
    {
        if (check.accountNo == add.accountNo)
        {
            printf("Account no. already in use!");
            fordelay(1000000000);
            goto account_no;
        }
    }
    add.accountNo = check.accountNo;
    printf("\nEnter the name:");
    scanf("%s", add.name);
    printf("\nEnter password(upto 10 chars):");
    scanf(" %s", add.password);
    printf("\nEnter the date of birth(mm/dd/yyyy):");
    scanf("%d/%d/%d", &add.dateOfBirth.month, &add.dateOfBirth.day, &add.dateOfBirth.year);
    printf("\nEnter the age:");
    scanf("%d", &add.age);
    printf("\nEnter the address:");
    scanf("%s", add.address);
    printf("\nEnter the phone number: ");
    scanf("%lf", &add.phone);
    printf("\nEnter the amount to deposit:$");
    scanf("%f", &add.amount);
    fwrite(&add, sizeof(add), 1, ptr);

    fclose(ptr);
    printf("\nAccount created successfully!");
add_invalid:
    printf("\n\n\n\t\tEnter 1 to go to the main menu and 0 to exit:");
    scanf("%d", &main_exit);
    system("cls");
    if (main_exit == 1)
        menu();
    else if (main_exit == 0)
        close();
    else
    {
        printf("\nInvalid!\a");
        goto add_invalid;
    }
}

void transfer()
{

    int l1 = 0, l2 = 0;
    FILE *old, *newrec, *ptr;
    old = fopen("record.dat", "rb+");
    newrec = fopen("new.dat", "wb");
    ptr = fopen("list.dat", "ab+");
    int test = 0;
    while (fread(&tran, sizeof(tran), 1, ptr))
    {
        test++;
        index = tran.index;
    }
    if (test == 0)
    {
        index = 0;
    }
    fclose(ptr);
    ptr = fopen("list.dat", "ab+");
    printf("Enter the amount you want to deposit:$ ");
    scanf("%f", &transaction.amount);
    tran.amount = transaction.amount;
    printf("Enter your account no :");
    scanf(" %d", &transaction.accountNo);
    while (fread(&add, sizeof(add), 1, old))
    {
        if (add.accountNo == transaction.accountNo)
        {
            if (add.amount < transaction.amount)
            {

                printf("LOW ON CASH!!PRESS ANY KEY TO EXIT");
                getch();
                menu();
            }
            else
            {
                l1++;
                tran.facc = transaction.accountNo;
                add.amount -= transaction.amount;
                fwrite(&add, sizeof(add), 1, newrec);
            }
        }
        else
        {
            fwrite(&add, sizeof(add), 1, newrec);
        }
    }

    if (l1 == 0)
    {

        printf("\n\nRecord not found!!");
    transact_invalid1:
        printf("\n\n\nEnter 0 to try again,1 to return to main menu and 2 to exit:");
        scanf("%d", &main_exit);
        system("cls");
        if (main_exit == 0)
            transfer();
        else if (main_exit == 1)
            menu();
        else if (main_exit == 2)
            close();
        else
        {
            printf("\nInvalid!");
            goto transact_invalid1;
        }
    }

    fclose(old);
    fclose(newrec);
    remove("record.dat");
    rename("new.dat", "record.dat");
    ///////////////////////////////////////////////////////////////////
    if (l1 != 0)
    {
        printf("Enter the account no of recipient:");
        scanf("%d", &recipient.accountNo);

        old = fopen("record.dat", "rb+");
        newrec = fopen("new.dat", "wb");
        while (fread(&add, sizeof(add), 1, old))
        {
            if (add.accountNo == recipient.accountNo)
            {
                l2++;
                tran.tacc = recipient.accountNo;
                add.amount += transaction.amount;
                fwrite(&add, sizeof(add), 1, newrec);
            }
            else
            {
                fwrite(&add, sizeof(add), 1, newrec);
            }
        }

        if (l2 == 0)
        {

            printf("\n\nRecord not found!!");
        transact_invalid:
            printf("\n\n\nEnter 0 to try again,1 to return to main menu and 2 to exit:");
            scanf("%d", &main_exit);
            system("cls");
            if (main_exit == 0)
                transfer();
            else if (main_exit == 1)
                menu();
            else if (main_exit == 2)
                close();
            else
            {
                printf("\nInvalid!");
                goto transact_invalid;
            }
        }

        fclose(old);
        fclose(newrec);
        remove("record.dat");
        rename("new.dat", "record.dat");
    }

    if (l1 == 1 && l2 == 1)
    {
        printf("\n\nTRANSFERRED SUCCESFULLY");
        index++;
        tran.index = index;
        fwrite(&tran, sizeof(tran), 1, ptr);
        fclose(ptr);
        printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d", &main_exit);
        system("cls");
        if (main_exit == 1)
            menu();
        else
            close();
    }
}

void list_all()
{
    FILE *ptr;
    int test = 0;
    ptr = fopen("list.dat", "rb");
    while (fread(&tran, sizeof(tran), 1, ptr))
    {
        printf("\n\n\nINDEX:%d\nFROM:%d \nTO:%d \nAMOUNT:%d ", tran.index, tran.facc, tran.tacc, tran.amount);
        test++;
    }
    if (test == 0)
    {
        system("cls");
        printf("\nNO RECORDS!!\n");
        //tran.index=0;
    }
    FILE *newrec;
    newrec = fopen("new.dat", "wb");
    int c;
    char data1[256];
    printf("\n\nEnter the index of transaction you want to mine:");
    scanf("%d", &c);
    fseek(ptr, 0, SEEK_SET);
    while (fread(&tran, sizeof(tran), 1, ptr))
    {
        printf("hi");
        if (tran.index == c)
        {
            printf("hi");
            sprintf(data1, "%d%d%d", tran.facc, tran.tacc, tran.amount);
            printf("%s", data1);
            add_block(data1);
        }
        else
        {
            fwrite(&tran, sizeof(tran), 1, newrec);
        }
    }
    fclose(ptr);
    fclose(newrec);
    remove("list.dat");
    rename("new.dat", "list.dat");
}
void gen_block()
{
    Block genesis;
    strcpy(genesis.data, "this is the GENISIS BLOCK");
    genesis.prevHash = 0;
    char dataToHash[256];
    sprintf(dataToHash, "%s%d", genesis.data, genesis.prevHash);
    genesis.nonce = mine_block(dataToHash);
    genesis.hash = temp;
    chash = temp;
    FILE *fp;
    fp = fopen("block.dat", "wb");
    fwrite(&genesis, sizeof(Block), 1, fp);
    fclose(fp);
edit_invalid:
    printf("\nEnter 1 to return to main menu and 2 to exit:");
    scanf("%d", &main_exit);
    //system("cls");
    if (main_exit == 1)

        minmenu();
    else if (main_exit == 2)
        close();
    else
    {
        printf("\nInvalid!\a");
        goto edit_invalid;
    }
}

void add_block(char *data1)
{
    Block b;
    int test, h;
    FILE *fp;
    fp = fopen("block.dat", "rb");
    while (fread(&b, sizeof(b), 1, fp))
    {

        test++;
        h = b.hash;
    }
    fclose(fp);
    int main_exit;
    strcpy(b.data, data1);
    b.prevHash = h;
    char dataToHash1[256];
    sprintf(dataToHash1, "%s%d", b.data, b.prevHash);
    b.nonce = mine_block(dataToHash1);
    b.hash = temp;
    chash = temp;
    printf("NEW BLOCK CREATED \n\n");
    fp = fopen("block.dat", "ab+");
    fwrite(&b, sizeof(b), 1, fp);
    fclose(fp);

edit_invalid:
    printf("\nEnter 1 to return to main menu and 2 to exit:");
    scanf("%d", &main_exit);
    //system("cls");
    if (main_exit == 1)

        minmenu();
    else if (main_exit == 2)
        close();
    else
    {
        printf("\nInvalid!\a");
        goto edit_invalid;
    }
}
void view_block()
{
    Block b;
    FILE *fp;
    fp = fopen("block.dat", "rb");
    while (fread(&b, sizeof(b), 1, fp))
    {
        printf("\nBlock\nBlock data: %s\nPrevious Hash: %x\nHash:%x\nNonce: %d\n", b.data, b.prevHash, b.hash, b.nonce);
        n += b.nonce * 0.005;
        printf("\n\t\t||\n\t\t||\n\t\t||");
    }
    printf("%D", n);
    int main_exit;
edit_invalid:
    printf("\nEnter 1 to return to main menu and 2 to exit:");
    scanf("%d", &main_exit);
    //system("cls");
    if (main_exit == 1)

        minmenu();
    else if (main_exit == 2)
        close();
    else
    {
        printf("\nInvalid!\a");
        goto edit_invalid;
    }
}
void view_list()
{
    FILE *view;
    view = fopen("record.dat", "rb");
    int test = 0;
    system("cls");
    printf("\nACC. NO.\tNAME\t\t\tADDRESS\t\t\tBALANCE\n");

    while (fread(&add, sizeof(add), 1, view))
    {
        printf("\n%6d\t %10s\t\t\t%10s\t\t%.0lf", add.accountNo, add.name, add.address, add.amount);
        test++;
    }

    fclose(view);
    if (test == 0)
    {
        system("cls");
        printf("\nNO RECORDS!!\n");
    }

view_list_invalid:
    printf("\n\nEnter 1 to go to the main menu and 0 to exit:");
    scanf("%d", &main_exit);
    system("cls");
    if (main_exit == 1)
        minmenu();
    else if (main_exit == 0)
        main();
    else
    {
        printf("\nInvalid!\a");
        goto view_list_invalid;
    }
}

void edit(void)
{
    int choice, test = 0;
    FILE *old, *newrec;
    old = fopen("record.dat", "rb");
    newrec = fopen("new.dat", "wb");

    printf("\nEnter the account no. of the customer whose info you want to change:");
    scanf("%d", &update.accountNo);
    while (fread(&add, sizeof(add), 1, old))
    {
        if (add.accountNo == update.accountNo)
        {
            test = 1;
            printf("\nWhich information do you want to change?\n1.Address\n2.Phone\n\nEnter your choice(1 for address and 2 for phone):");
            scanf("%d", &choice);
            system("cls");
            if (choice == 1)
            {
                update = add;
                printf("Enter the new address:");
                scanf("%s", update.address);
                fwrite(&update, sizeof(update), 1, newrec);
                system("cls");
                printf("Changes saved!");
            }
            else if (choice == 2)
            {
                update = add;
                printf("Enter the new phone number:");
                scanf("%lf", &add.phone);
                fwrite(&add, sizeof(add), 1, newrec);
                system("cls");
                printf("Changes saved!");
            }
        }
        else
            fwrite(&add, sizeof(add), 1, newrec);
    }
    fclose(old);
    fclose(newrec);
    remove("record.dat");
    rename("new.dat", "record.dat");

    if (test != 1)
    {
        system("cls");
        printf("\nRecord not found!!\a\a\a");
    edit_invalid:
        printf("\nEnter 0 to try again,1 to return to main menu and 2 to exit:");
        scanf("%d", &main_exit);
        system("cls");
        if (main_exit == 1)

            menu();
        else if (main_exit == 2)
            close();
        else if (main_exit == 0)
            edit();
        else
        {
            printf("\nInvalid!\a");
            goto edit_invalid;
        }
    }
    else
    {
        printf("\n\n\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d", &main_exit);
        system("cls");
        if (main_exit == 1)
            menu();
        else
            main();
    }
}

void erase(void)
{
    FILE *old, *newrec;
    int test = 0;
    old = fopen("record.dat", "r");
    newrec = fopen("new.dat", "w");
    printf("Enter the account no. of the customer you want to delete:");
    scanf("%d", &rem.accountNo);
    while (fread(&add, sizeof(add), 1, old))
    {
        if (add.accountNo != rem.accountNo)
            fwrite(&add, sizeof(add), 1, newrec);
        else
        {
            test++;
            printf("\nRecord deleted successfully!\n");
        }
    }
    fclose(old);
    fclose(newrec);
    remove("record.dat");
    rename("new.dat", "record.dat");
    if (test == 0)
    {
        printf("\nRecord not found!!\a\a\a");
    erase_invalid:
        printf("\nEnter 0 to try again,1 to return to main menu and 2 to exit:");
        scanf("%d", &main_exit);

        if (main_exit == 1)
        {
            system("cls");
            minmenu();
        }
        else if (main_exit == 2)
        {
            system("cls");
            main();
        }

        else if (main_exit == 0)
            erase();
        else
        {
            printf("\nInvalid!\a");
            goto erase_invalid;
        }
    }
    else
    {
        printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d", &main_exit);
        system("cls");
        if (main_exit == 1)
        {
            system("cls");
            minmenu();
        }

        else
            close();
    }
}

void see1(void) // see second used in function
{
    FILE *ptr;
    int test = 0, rate, acc1_no;
    int choice;
    float time;
    printf("Enter your account number: ");
    scanf("%d", &acc1_no);
    ptr = fopen("record.dat", "rb");

    while (fread(&add, sizeof(add), 1, ptr))
    {
        if (acc1_no == add.accountNo)
        {
            system("cls");
            test = 1;

            printf("\nAccount NO.:%d\nName:%s \ndateOfBirth:%d/%d/%d \nAge:%d \nAddress:%s\nPhone number:%.0lf \n\nAmount :$ %.2f \n\n\n", add.accountNo, add.name, add.dateOfBirth.month, add.dateOfBirth.day, add.dateOfBirth.year, add.age, add.address, add.phone, add.amount);
        }
    }

    fclose(ptr);
    if (test != 1)
    {
        system("cls");
        printf("\nRecord not found!!\a\a\a");
    see_invalid:
        printf("\nEnter 0 to try again,1 to return to main menu and 2 to exit:");
        scanf("%d", &main_exit);
        system("cls");
        if (main_exit == 1)
            menu();
        else if (main_exit == 2)
            main();
        else if (main_exit == 0)
            see1();
        else
        {
            system("cls");
            printf("\nInvalid!\a");
            goto see_invalid;
        }
    }
    else
    {
        printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d", &main_exit);
    }
    if (main_exit == 1)
    {
        system("cls");
        menu();
    }

    else
    {
        system("cls");
        main();
    }
}

void see(void)
{
    FILE *ptr;
    int test = 0, rate;
    int choice;
    float time;
    ptr = fopen("record.dat", "rb");
    printf("Do you want to check by\n1.Account no\n2.Name\nEnter your choice:");
    scanf("%d", &choice);
    if (choice == 1)
    {
        printf("Enter the account number:");
        scanf("%d", &check.accountNo);

        while (fread(&add, sizeof(add), 1, ptr))
        {
            if (add.accountNo == check.accountNo)
            {
                system("cls");
                test = 1;

                printf("\nAccount NO.:%d\nName:%s \ndateOfBirth:%d/%d/%d \nAge:%d \nAddress:%s\nPhone number:%.0lf \n\nAmount :$ %.2f \n", add.accountNo, add.name, add.dateOfBirth.month, add.dateOfBirth.day, add.dateOfBirth.year, add.age, add.address, add.phone, add.amount);
            }
        }
    }
    else if (choice == 2)
    {
        printf("Enter the name:");
        scanf("%s", &check.name);
        while (fread(&add, sizeof(add), 1, ptr))
        {
            if (strcmpi(add.name, check.name) == 0)
            {
                system("cls");
                test = 1;
                printf("\nAccount NO.:%d\nName:%s \ndateOfBirth:%d/%d/%d \nAge:%d \nAddress:%s\nPhone number:%.0lf \n\nAmount :$ %.2f \n\n", add.accountNo, add.name, add.dateOfBirth.month, add.dateOfBirth.day, add.dateOfBirth.year, add.age, add.address, add.phone, add.amount);
            }
        }
    }

    fclose(ptr);
    if (test != 1)
    {
        system("cls");
        printf("\nRecord not found!!\a\a\a");
    see_invalid:
        printf("\nEnter 0 to try again,1 to return to main menu and 2 to exit:");
        scanf("%d", &main_exit);
        system("cls");
        if (main_exit == 1)
            minmenu();
        else if (main_exit == 2)
            main();
        else if (main_exit == 0)
            see();
        else
        {
            system("cls");
            printf("\nInvalid!\a");
            goto see_invalid;
        }
    }
    else
    {
        printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d", &main_exit);
    }
    if (main_exit == 1)
    {
        system("cls");
        minmenu();
    }
    else
    {

        system("cls");
        main();
    }
}

void close(void)
{
    system("cls");
}

void menu(void)
{
    int choice;
    system("cls");
    system("color 9");
    printf("\n\n\n\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 WELCOME TO THE MAIN MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    printf("\n\n\t\t1.update information of existing account\n\t\t2.Transfer\n\t\t3.View your details\n\t\t4.View Block Chain\n\t\t5.log out\n\n\n\n\t\t Enter your choice:");
    scanf("%d", &choice);

    system("cls");
    switch (choice)
    {
    case 1:
        edit();
        break;
    case 2:
        transfer();
        break;
    case 3:
        see1();
        break;
    case 4:
        view_block();
        break;
    case 5:
        main();
    default:
        menu();
        break;
    }
}
int main()
{
    char so;
    system("color 9");
    printf("\n                                                          Welcome                            \n\n\n");
    printf("\n1.user login\n2.Miner\n3.New user\n4.Exit");
    printf("\nPlease enter any options (1/2/3/4):");
    so = getch();
    switch (so)
    {
    case '1':
        system("cls");
        menues();
        break;

    case '2':
        system("cls");
        minmenu();
        break;

    case '3':
        system("cls");
        newAccount();
        break;

    case '4':
        close();
    }
    return 0;
}

void minmenu(void) // miner function
{
    int i, c = 0, main_exit;
    char miner_name[100], miner_pasw[100] = "miner", so, pass[10];
    system("color 9");
login_try:
    printf("\n\tEnter your name: ");
    scanf("%s", miner_name);
    printf("\n\tEnter your password: ");
    for (i = 0; i < strlen(miner_pasw); i++)
    {
        pass[i] = getch();
        printf("*");
    }
    for (i = 0; i < strlen(miner_pasw); i++)
    {
        if (pass[i] == miner_pasw[i])
        {
            c++;
        }
    }

    if (c == strlen(miner_pasw) && strcmp(miner_name, "miner") == 0)
    {
        printf("\n\nPassword Matched!\n\t\t\t\tLOADING");
        for (i = 0; i <= 60; i++)
        {
            fordelay(10000000);
            printf(".");
        }
        system("cls");
        printf("\n\t\t\t\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2Welcome\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n\n\n");
        printf("\n\n\t\t\t\t\t\t\t\t\t\tBITCOIN AMOUNT:");
        printf("%d", n);
        printf("\n1.VIEW ALL ACCOUNTS\n2.SEARCH AN ACCOUNT\n3.MINE & ADD BLOCKS\n4.Genesis Block\n5.View Block Chain\n6.Remove Account\n7.Log Out");
        printf("\nPlease enter any options (1/2/3/4):");
        so = getch();
        switch (so)
        {
        case '1':
            system("cls");
            view_list();
            break;
        case '2':
            system("cls");
            see();
            break;
        case '3':
            system("cls");
            list_all();
            break;
        case '4':
            system("cls");
            gen_block();
            break;
        case '5':
            system("cls");
            view_block();
            break;
        case '6':
            system("cls");
            erase();
            break;
        case '7':
            system("cls");
            main();
            break;
        }
    }

    else
    {
        printf("\n\nWrong password!!\a\a\a");
        printf("\nEnter 1 to try again and 0 to exit:");
        scanf("%d", &main_exit);
        if (main_exit == 0)
        {
            system("cls");
            main();
        }
        else
        {
            fordelay(1000000000);
            system("cls");
            goto login_try;
        }
    }
}

int menues()
{
    char pass[10], password[11] = "blockchain", usern[20];
    int i = 0, c = 0, t = 0;
    FILE *ptr;
    ptr = fopen("record.dat", "rb");

login_try:
    printf("\n\n\tEnter username:");
    scanf("%s", usern);
    while (fread(&add, sizeof(add), 1, ptr))
    {
        if (strcmp(add.name, usern) == 0)
        {
            strcpy(password, add.password);
            t++;
        }
    }
    fclose(ptr);
    if (t == 0)
    {
        printf("\n\nNo username found!!\a\a\a");
        printf("\nEnter 1 to try again and 0 to exit:");
        scanf("%d", &main_exit);
        if (main_exit == 0)
        {
            system("cls");
            main();
        }
        else
        {
            fordelay(1000000000);
            system("cls");
            goto login_try;
        }
    }
    printf("\n\n\tEnter the password to login:");
    for (i = 0; i < strlen(password); i++)
    {
        pass[i] = getch();
        printf("*");
    }
    for (i = 0; i < strlen(password); i++)
    {
        if (pass[i] == password[i])
        {
            c++;
        }
    }
    if (c == strlen(password))
    {
        printf("\n\nPassword Matched!\n\t\t\t\tLOADING");
        for (i = 0; i <= 60; i++)
        {
            fordelay(10000000);
            printf(".");
        }
        system("cls");
        menu();
    }
    else
    {
        printf("\n\nWrong password!!\a\a\a");
        printf("\nEnter 1 to try again and 0 to exit:");
        scanf("%d", &main_exit);
        if (main_exit == 0)
        {
            system("cls");
            main();
        }
        else
        {
            fordelay(1000000000);
            system("cls");
            goto login_try;
        }
    }
    return 0;
}
