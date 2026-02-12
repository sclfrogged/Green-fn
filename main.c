#include <stdio.h>
#include <string.h>

#define SIZE 10
#define STR_LEN 100

struct Project {
    char name[STR_LEN];
    char description[STR_LEN];
    char status[STR_LEN];      // vipolnen / v processe
    char startDate[STR_LEN];
    char endDate[STR_LEN];
};

void inputProjects(struct Project projects[], int count) {
    for (int i = 0; i < count; i++) {
        printf("\nProekt #%d\n", i);

        printf("Nazvanie: ");
        fgets(projects[i].name, STR_LEN, stdin);
        projects[i].name[strcspn(projects[i].name, "\n")] = 0;

        printf("Opisanie: ");
        fgets(projects[i].description, STR_LEN, stdin);
        projects[i].description[strcspn(projects[i].description, "\n")] = 0;

        printf("Status (vipolnen / v processe): ");
        fgets(projects[i].status, STR_LEN, stdin);
        projects[i].status[strcspn(projects[i].status, "\n")] = 0;

        printf("Data nachala: ");
        fgets(projects[i].startDate, STR_LEN, stdin);
        projects[i].startDate[strcspn(projects[i].startDate, "\n")] = 0;

        printf("Data zaversheniya: ");
        fgets(projects[i].endDate, STR_LEN, stdin);
        projects[i].endDate[strcspn(projects[i].endDate, "\n")] = 0;
    }
}

void printProjects(struct Project projects[], int count) {
    for (int i = 0; i < count; i++) {
        printf("\nIndex: %d\n", i);
        printf("Nazvanie: %s\n", projects[i].name);
        printf("Opisanie: %s\n", projects[i].description);
        printf("Status: %s\n", projects[i].status);
        printf("Data nachala: %s\n", projects[i].startDate);
        printf("Data zaversheniya: %s\n", projects[i].endDate);
    }
}

void editProject(struct Project *project) {
    int choice;
    printf("\nChto redaktirovat?\n");
    printf("1. Nazvanie\n");
    printf("2. Opisanie\n");
    printf("3. Status\n");
    printf("4. Data nachala\n");
    printf("5. Data zaversheniya\n");
    printf("Vibor: ");
    scanf("%d", &choice);
    getchar();

    switch (choice) {
        case 1:
            printf("Novoe nazvanie: ");
            fgets(project->name, STR_LEN, stdin);
            project->name[strcspn(project->name, "\n")] = 0;
            break;
        case 2:
            printf("Novoe opisanie: ");
            fgets(project->description, STR_LEN, stdin);
            project->description[strcspn(project->description, "\n")] = 0;
            break;
        case 3:
            printf("Noviy status: ");
            fgets(project->status, STR_LEN, stdin);
            project->status[strcspn(project->status, "\n")] = 0;
            break;
        case 4:
            printf("Novaya data nachala: ");
            fgets(project->startDate, STR_LEN, stdin);
            project->startDate[strcspn(project->startDate, "\n")] = 0;
            break;
        case 5:
            printf("Novaya data zaversheniya: ");
            fgets(project->endDate, STR_LEN, stdin);
            project->endDate[strcspn(project->endDate, "\n")] = 0;
            break;
        default:
            printf("Neverniy vibor\n");
    }
}

void searchProject(struct Project projects[], int count, char key[]) {
    int found = 0;

    for (int i = 0; i < count; i++) {
        if (strcmp(projects[i].name, key) == 0) {
            printf("\nProekt nayden:\n");
            printf("Opisanie: %s\n", projects[i].description);
            printf("Status: %s\n", projects[i].status);
            printf("Data nachala: %s\n", projects[i].startDate);
            printf("Data zaversheniya: %s\n", projects[i].endDate);
            found = 1;
        }
    }

    if (!found) {
        printf("Proekt ne nayden\n");
    }
}

int main() {
    struct Project projects[SIZE];
    int count;

    printf("Vvedite kolichestvo proektov (do 10): ");
    scanf("%d", &count);
    getchar();

    if (count > SIZE) {
        printf("Slishkom mnogo proektov\n");
        return 1;
    }

    inputProjects(projects, count);

    printf("\nSpisok proektov:");
    printProjects(projects, count);

    int index;
    printf("\nVvedite index proekta dlya redaktirovaniya: ");
    scanf("%d", &index);
    getchar();

    if (index >= 0 && index < count) {
        editProject(&projects[index]);
    } else {
        printf("Neverniy index\n");
    }

    char searchName[STR_LEN];
    printf("\nVvedite nazvanie proekta dlya poiska: ");
    fgets(searchName, STR_LEN, stdin);
    searchName[strcspn(searchName, "\n")] = 0;

    searchProject(projects, count, searchName);

    return 0;
}