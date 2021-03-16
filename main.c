#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Name{
    char familyName[20];
    char surName[20];
    char lastName[20];
}name;
typedef struct Employee{
    char emID[20];
    name emName;
    double emSalaryLevel;
}employee;
void showColumnName() {
    printf("---------------------------------------------------------------------------------------------------------\n");
    printf("%-20s %-20s %-20s %-20s %-10s\n",
        "Employee ID", "Family Name", "Surname", "Last Name", "Employee salary level");
}
void inputEmloyeeName(name *);
employee inputEmployee()
{
    employee em;
    printf("ID: ");fflush(stdin);
    fgets(em.emID, 100, stdin);
    em.emID[strlen(em.emID)-1]='\0';
    inputEmloyeeName(&em.emName);
    fflush(stdin);
    printf("Employee salary level: ");
    scanf("%lf",&em.emSalaryLevel);
    fflush(stdin);
    system("clear");
    return em;
}

void showEmployeeInfo(employee);
void showEmployeeList(employee *, int );
void sortEmployee(employee *,int *);
void sortEmployeeID(employee *,int *);
void sortEmployeeName(employee *,int *);
void sortEmployeeSalaryLevel(employee *,int *);
void swap(employee*, employee*);
void findEmployee(employee *, int*);
void findEmployeeName(employee *,int*);
void findEmployeeID(employee*,int*);
void readFile(employee *, int *);
void writeFile(employee* , int );


int main()
{
    char option;
    employee employees[1000];
    int numberOfemployee=0;
    readFile(employees, &numberOfemployee);
    printf("                                     CURRENT EMPLOYEE LIST                    \n");
    showEmployeeList(employees,numberOfemployee );
    do {
        printf("\n\n=============== MENU ===============");
        printf("\n1. Add employees to the list.");
        printf("\n2. Show the employees list.");
        printf("\n3. Sort employees.");
        printf("\n4. Find employees information");
        printf("\n5. Write employees's information to file");
        printf("\n6. Exit");
        printf("\nYour selection: ");
        scanf("%c",&option);
        employee em;
        switch (option) {
            case '1':
                em = inputEmployee();
                employees[numberOfemployee++] = em;
                break;
            case '2':
                system("clear");
                showEmployeeList(employees,numberOfemployee );
                break;
            case '3':
                sortEmployee(employees, &numberOfemployee);
                break;
            case '4':
                findEmployee(employees, &numberOfemployee);
                break;
            case '5':
                writeFile(employees, numberOfemployee);
                break;
            case '6':
                break;
            default:
                printf("Invalid selection!\nPlease try again\n");
                break;
        }
    } while (option!='6');
}
void inputEmloyeeName(name *emName)
{
    printf("Family Name: ");
    fgets(emName->familyName, 100, stdin);
    emName->familyName[strlen(emName->familyName)-1]='\0';
    printf("Surname: ");
    fgets(emName->surName, 100, stdin);
    emName->surName[strlen(emName->surName)-1]='\0';
    printf("Last Name: ");
    fgets(emName->lastName, 100, stdin);
    emName->lastName[strlen(emName->lastName)-1]='\0';
}
void showEmployeeInfo(employee em){
    printf("%-20s %-20s %-20s %-20s %-30.2lf\n",em.emID,em.emName.familyName,em.emName.surName,em.emName.lastName,em.emSalaryLevel);
}
void showEmployeeList(employee *em, int  n){
    showColumnName();
    for (int i=0; i< n; i++) {
        showEmployeeInfo(em[i]);
    }
}
void swap(employee *xp, employee *yp)
{
    employee temp = *xp;
    *xp = *yp;
    *yp = temp;
}
void sortEmployee(employee *em,int *n){
    char option;
    do {
        printf("=============== MENU ===============");
        printf("\n1. Sort employees following ID.");
        printf("\n2. Sort employees following name.");
        printf("\n3. Sort employees following salary level.");
        printf("\n4. Return");
        printf("\nYour selection: ");
        scanf("%c",&option);
        switch (option) {
            case '1':
                sortEmployeeID(em, n);
                showEmployeeList(em,*n);
                break;
            case '2':
                sortEmployeeName(em, n);
                showEmployeeList(em, *n);
                break;
            case '3':
                sortEmployeeSalaryLevel(em, n);
                showEmployeeList(em, *n);
                break;
            case '4':
                break;
            default:
                printf("Invalid Selection!\nPlease try again!\n");
                break;
        }
    } while (option!='4');
    
}
void sortEmployeeID(employee *em, int *n)
{
    for (int i=0; i<*n-1; i++) {
        for (int j=0; j<*n-i-1; j++) {
            if (em[j].emID>em[j+1].emID) {
                swap(&em[j], &em[j+1]);
            }
        }
    }
}
void sortEmployeeName(employee *em,int *n)
{
    for (int i=0; i<*n-1; i++) {
        for (int j=0; j<*n-i-1; j++) {
            if (strcmp(em[j].emName.lastName,em[j+1].emName.lastName)>0) {
                swap(&em[j], &em[j+1]);
            }
        }
    }
}
void sortEmployeeSalaryLevel(employee *em,int *n)
{
    for (int i=0; i<*n-1; i++) {
        for (int j=0; j<*n-i-1; j++) {
            if (em[j].emSalaryLevel>em[j+1].emSalaryLevel) {
                swap(&em[j], &em[j+1]);
            }
        }
    }
}
void findEmployee(employee *em, int *n){
    fflush(stdin);
    char option;
    do {
        printf("=============== MENU ===============");
        printf("\n1. Find employee following ID.");
        printf("\n2. Find employee following name.");
        printf("\n3. Return");
        printf("\nYour selection: ");
        scanf("%c",&option);
        switch (option) {
            case '1':
                findEmployeeID(em, n);
                break;
            case '2':
                findEmployeeName(em, n);
                break;
            case '3':
                break;
            default:
                printf("Invalid Selection!\nPlease try again!\n");
                break;
        }
    } while (option!='3');
}
void findEmployeeID(employee *em,int *n)
{
    fflush(stdin);
    int check =0;
    char ID[20];
    do {
        printf("Input ID of employee you want to find: ");
        fgets(ID, 100, stdin);
        ID[strlen(ID)-1]='\0';
        for (int i=0; i<*n; i++)
        {
            if (strcmp(ID, em[i].emID)==0)
            {
                showColumnName();
                showEmployeeInfo(em[i]);
                check =1; break;
            }
        }
        if (check ==1 ) break;
        printf("Invalid ID!\nTry again!\n");
       
    } while (check == 0);
}
void findEmployeeName(employee *em, int *n)
{
    fflush(stdin);
    int check =0;
    char name[100];
    do {
        printf("Input name of employee you want to find: ");
        fgets(name, 100, stdin);
        name[strlen(name)-1]='\0';
        for (int i=0; i<*n; i++)
        {
            if (strcmp(name, em[i].emName.lastName)==0)
            {
                showColumnName();
                showEmployeeInfo(em[i]);
                check =1; break;
            }
            if (check ==1) break;
            printf("Invalid name!\nTry again!\n");
        }
    } while (check ==0);
}
void readFile(employee* em, int *n)
{
    FILE* fptr = fopen("em.txt", "r");
int i = 0;
if(fptr) {
    for(;;) {
        employee emp;
        fscanf(fptr,"%20s %20s %20s %20s  %30lf\n",emp.emID,emp.emName.familyName,emp.emName.surName,emp.emName.lastName,&emp.emSalaryLevel);
        //fread(&emp, sizeof(emp), 1, fptr);
        em[i++] = emp;
        if(feof(fptr)) {
            break;
        }
    }
}
fclose(fptr);
    *n = i;
}
void writeFile(employee* em, int n) {
    getchar();
    char fName[26];
    printf("File name: ");
    gets(fName);
    FILE* fOut = fopen(fName, "a");
    int i;
    for(i = 0; i < n; i++) {
        employee emp = em[i];
       fprintf(fOut,"%-20s %-20s %-20s %-20s %-30.2lf\n",emp.emID,emp.emName.familyName,emp.emName.surName,emp.emName.lastName,emp.emSalaryLevel);
        //fwrite(&emp, sizeof(emp), 1, fOut);
    }
    fclose(fOut);
}
