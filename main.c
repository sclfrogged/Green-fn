#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int   id;
    char  name[50];
    float salary;
} Employee;

typedef struct {
    Employee *data;
    int       size;
    int       capacity;
} EmployeeArray;

void initArray(EmployeeArray *arr) {
    arr->data     = NULL;
    arr->size     = 0;
    arr->capacity = 0;
}

void printEmployee(const Employee *e) {
    printf("  [%d] %-20s  salary: %.2f\n", e->id, e->name, e->salary);
}

void printAll(const EmployeeArray *arr) {
    printf("  --- list (size=%d, capacity=%d) ---\n", arr->size, arr->capacity);
    if (arr->size == 0) {
        printf("  (empty)\n");
    } else {
        for (int i = 0; i < arr->size; i++) {
            printEmployee(&arr->data[i]);
        }
    }
    printf("  -----------------------------------\n\n");
}

void expandArray(EmployeeArray *arr, int extraCount) {
    if (extraCount <= 0) {
        printf("[expandArray] extraCount must be > 0, skipping.\n");
        return;
    }

    int newCapacity = arr->capacity + extraCount;

    Employee *newData = (Employee *)malloc(newCapacity * sizeof(Employee));
    if (newData == NULL) {
        fprintf(stderr, "Error: malloc failed!\n");
        exit(EXIT_FAILURE);
    }

    if (arr->data != NULL && arr->size > 0) {
        memcpy(newData, arr->data, arr->size * sizeof(Employee));
    }

    free(arr->data);

    arr->data     = newData;
    arr->capacity = newCapacity;

    printf("[expandArray] capacity: %d -> %d  (+%d slots)\n",
           newCapacity - extraCount, newCapacity, extraCount);
}

void pushBack(EmployeeArray *arr, Employee e) {
    if (arr->size >= arr->capacity) {
        expandArray(arr, 1);
    }
    arr->data[arr->size] = e;
    arr->size++;
    printf("[pushBack] added \"%s\"  (size=%d)\n", e.name, arr->size);
}

void popBack(EmployeeArray *arr) {
    if (arr->size == 0) {
        printf("[popBack] array is empty, nothing to remove.\n");
        return;
    }

    printf("[popBack] removing \"%s\"\n", arr->data[arr->size - 1].name);
    arr->size--;

    int newCapacity = arr->size;

    if (newCapacity == 0) {
        free(arr->data);
        arr->data     = NULL;
        arr->capacity = 0;
    } else {
        Employee *newData = (Employee *)malloc(newCapacity * sizeof(Employee));
        if (newData == NULL) {
            fprintf(stderr, "Error: malloc failed!\n");
            exit(EXIT_FAILURE);
        }
        memcpy(newData, arr->data, newCapacity * sizeof(Employee));
        free(arr->data);
        arr->data     = newData;
        arr->capacity = newCapacity;
    }

    printf("[popBack] capacity shrunk to %d\n", arr->capacity);
}

void freeArray(EmployeeArray *arr) {
    free(arr->data);
    arr->data     = NULL;
    arr->size     = 0;
    arr->capacity = 0;
    printf("[freeArray] all memory released. size=0, capacity=0\n");
}

/*
int main(void) {
    EmployeeArray arr;
    initArray(&arr);

    printf("========================================\n");
    printf("   Dynamic Employee Array — Demo        \n");
    printf("========================================\n\n");


       FEATURE 1: Insert new element at the END
       pushBack() adds to the end of the array.
       When there is no room — expandArray() is
       called automatically before inserting.
    printf("FEATURE 1: Insert element at the end (pushBack)\n");
    printf("------------------------------------------------\n");
    pushBack(&arr, (Employee){1, "Alice Johnson",  55000.0f});
    pushBack(&arr, (Employee){2, "Bob Smith",       48000.0f});
    pushBack(&arr, (Employee){3, "Carol White",     62000.0f});
    printAll(&arr);


       FEATURE 2: Expand array by N slots
       expandArray() allocates a brand-new block
       (old size + extra), copies all data into it,
       then frees the old block. No realloc used.
    printf("FEATURE 2: Expand array capacity by 3 slots (expandArray)\n");
    printf("----------------------------------------------------------\n");
    expandArray(&arr, 3);
    printAll(&arr);

    printf("  Adding 2 more employees into pre-expanded slots:\n");
    pushBack(&arr, (Employee){4, "David Brown",    71000.0f});
    pushBack(&arr, (Employee){5, "Eva Martinez",   59000.0f});
    printAll(&arr);


       FEATURE 3: Remove STRICTLY the last element
       popBack() drops the last item, then creates
       a smaller block and frees the old one.
    printf("FEATURE 3: Remove last element and shrink memory (popBack)\n");
    printf("-----------------------------------------------------------\n");
    popBack(&arr);
    printAll(&arr);
    popBack(&arr);
    printAll(&arr);

       FEATURE 4: Manual memory release
       freeArray() can be called at any point to
       release all memory and reset the array.
    printf("FEATURE 4: Manual memory release (freeArray)\n");
    printf("---------------------------------------------\n");
    freeArray(&arr);
    printAll(&arr);

    printf("  Array re-used after manual release:\n");
    pushBack(&arr, (Employee){10, "Frank Lee",  45000.0f});
    pushBack(&arr, (Employee){11, "Grace Kim",  53000.0f});
    printAll(&arr);

    printf("Final cleanup before program exit\n");
    printf("---------------------------------\n");
    freeArray(&arr);

    printf("Program finished. No memory leaks.\n");
    return 0;
}
*/
