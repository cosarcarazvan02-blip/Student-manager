#include <stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct{
    char name[50];
    int age;
    float gpa;
}Student;

void ReadStudent(Student *s){
    printf("Name:");
    scanf("%49s", s->name);
    printf("age:");
    scanf("%d", &s->age);
    printf("GPA:");
    scanf("%f", &s->gpa);
}

void PrintStudent(const Student *s){
    printf("Name: %s\n", s->name);
    printf("Age: %d\n", s->age);
    printf("GPA: %.2f\n", s->gpa);
}

void AddStudent(Student **lista, int *n){
    Student *temp=realloc(*lista, (*n + 1) * sizeof(Student));
    if (temp == NULL){
        printf("Error!");
        return;
    }
   *lista = temp;
   (*n)++;
}

void ShowStudent(const Student *lista, int n){
    if(n == 0){
        printf("List is empty");
    }
    else {
        for(int i=0; i<n; i++){
            printf("Student:%d\n", i+1);
            PrintStudent(&lista[i]);
            printf("\n");
        }
    }
}

int FindStudent(const Student *lista, int n, const char *name){
    for(int i=0;i<n;i++){
         if(strcmp(lista[i].name, name) == 0) {
            return i;
         }
    }
    return -1;
}

int DeleteStudentByIndex(Student **lista, int *n, int pos) {
    if (pos < 0 || pos >= *n) {
        return 0; 
    }

    for (int k = pos; k < *n - 1; k++) {
        (*lista)[k] = (*lista)[k + 1];
    }

    (*n)--;

    if (*n == 0) {
        free(*lista);
        *lista = NULL;
        return 1;
    }

    Student *temp = realloc(*lista, (*n) * sizeof(Student));
    if (temp == NULL) {
       
        return 1;
    }
    *lista = temp;
    return 1;
}

int main() {
    Student *lista = NULL;
    int n = 0;

    int opt;
    while (1) {
        printf("\n--- STUDENT MANAGER ---\n");
        printf("1. Add student\n");
        printf("2. Show students\n");
        printf("3. Find student\n");
        printf("4. Delete student\n");
        printf("0. Exit\n");
        printf("Option: ");
        scanf("%d", &opt);

        if (opt == 0) {
            break;
        }

        if (opt == 1) {
            int old_n = n;
            AddStudent(&lista, &n);     

            if (n > old_n) {
                ReadStudent(&lista[n - 1]);
                printf("Added.\n");
            } else {
                printf("Could not add.\n");
            }
        }
        else if (opt == 2) {
            ShowStudent(lista, n);
        }
        else if (opt == 3) {
            char target[50];
            printf("Name to find: ");
            scanf("%49s", target);

            int pos = FindStudent(lista, n, target);
            if (pos == -1) {
                printf("Not found.\n");
            } else {
                printf("Found at index %d:\n", pos);
                PrintStudent(&lista[pos]);
            }
        }
        else if (opt == 4) {
            char target[50];
            printf("Name to delete: ");
            scanf("%49s", target);

            int pos = FindStudent(lista, n, target);
            if (pos == -1) {
                printf("Not found.\n");
            } else {
                if (DeleteStudentByIndex(&lista, &n, pos)) {
                    printf("Deleted.\n");
                } else {
                    printf("Delete failed.\n");
                }
            }
        }
        else {
            printf("Error!\n");
        }
    }

    free(lista);
    lista = NULL;
    printf("Bye!\n");
    return 0;
}

