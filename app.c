#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STUDENTS 100
#define MAX_GRADES 5

typedef struct Student{
    unsigned int id;
    char code[13];
    char name[50];
    float grades[5];
    float final_grade;
    unsigned int num_absences;
    char status[50];
};


Student student;

int numStudents = 0;

// Declare function prototypes
int main();
void registerStudent();
void searchStudent();
void alterStudent();
void listStudents();
int findStudentByID(int id);
void calculateSituation(Student *student);



void print_student(Student *student) {
    printf("ID: %d\n", student->id);
    printf("Code: %s\n", student->code);
    printf("Name: %s\n", student->name);
    printf("Grades: ");
    for (int i = 0; i < 5; i++) {
        printf("%1.f ", student->grades[i]);
    }
    printf("\nFinal Grade: %1.f\n", student->final_grade);
    printf("Number of Absences: %d\n", student->num_absences);
    printf("Status: %s\n", student->status);
    system("pause");
    system("cls");
    main();
    
}
// Compare function for sorting students by ID
int compareById(const void* a, const void* b) {
    const Student* s1 = (const Student*)a;
    const Student* s2 = (const Student*)b;
    return s1->id - s2->id;
}

// Compare function for sorting students by name
int compareByName(const void* a, const void* b) {
    const Student* s1 = (const Student*)a;
    const Student* s2 = (const Student*)b;
    return strcmp(s1->name, s2->name);
}

// Compare function for sorting students by code
int compareByCode(const void* a, const void* b) {
    const Student* s1 = (const Student*)a;
    const Student* s2 = (const Student*)b;
    return strcmp(s1->code, s2->code);
}

// Sort students by ID (ascending order)
void sortStudentsById(FILE *file, int num_students) {
    Student students[num_students];
    fread(students, sizeof(Student), num_students, file);
    qsort(students, num_students, sizeof(Student), compareById);
    rewind(file);
    fwrite(students, sizeof(Student), num_students, file);
}

// Sort students by name (alphabetical order)
void sortStudentsByName() {
	FILE *file;
	int num_students;
    Student students[num_students];
    fread(students, sizeof(Student), num_students, file);
    qsort(students, num_students, sizeof(Student), compareByName);
    rewind(file);
    fwrite(students, sizeof(Student), num_students, file);
}

// Sort students by code (ascending order)
void sortStudentsByCode() {
	int num_students;
	FILE *file;
    Student students[num_students];
    fread(students, sizeof(Student), num_students, file);
    qsort(students, num_students, sizeof(Student), compareByCode);
    rewind(file);
    fwrite(students, sizeof(Student), num_students, file);
}
void printStudents() {
	FILE *file;
    int num_students;
    printf("\nID\tCode\t\tName\t\t\t\t\tGrades\tAvg\tAbsences\tStatus\n");
    printf("-----------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < num_students; i++) {
        fread(&student, sizeof(Student), 1, file);
        printf("%d\t%s\t%s\t", student.id, student.code, student.name);
        for (int j = 0; j < 5; j++) {
            printf("%.1f ", student.grades[j]);
        }
        printf("\t%.1f\t", student.final_grade);
        printf("%d\t\t%s\n", student.num_absences, student.status);
    }
}

void registerStudent() {
    char filename[50];
    unsigned int id;
    printf("Enter the filename for the class: ");
    scanf("%s", filename);

    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error: Failed to create file %s\n", filename);
        return ;
    }

    int num_students = 0;
    while (num_students < MAX_STUDENTS) {
        printf("Enter the ID of the student (0 to exit): ");
        getchar();
        scanf("%u", &id);
        if (id == 0) {
            break;
        }else{

        Student student;
        student.id = id;

        printf("Enter the code for the student (11 characters): ");
        scanf("%s", student.code);

        printf("Enter the name of the student: ");
        scanf(" %[^\n]s", student.name);

        printf("Enter the 5 test grades for the student: ");
        for (int i = 0; i < 5; i++) {
            scanf("%f", &student.grades[i]);
            student.final_grade = student.final_grade + student.grades[i];
        	setbuf(stdin, NULL);
            
        }        
        student.final_grade /=5;
   
        printf("Enter the number of absences for the student: ");
        scanf("%u", &student.num_absences);

        if (student.num_absences <= (128*0.25) && student.final_grade >= 6.0) {
            strcpy(student.status, "Approved");
        } else if (student.num_absences > (128*0.25) && student.final_grade >= 6.0) {
            strcpy(student.status, "Failed due to absence");
        } else if (student.num_absences <= (128*0.25) && student.final_grade < 6.0) {
            strcpy(student.status, "Failed by Grade");
        } else {
            strcpy(student.status, "Failure due to absence and grade");
        }

        print_student(&student);
        fwrite(&student, sizeof(Student), 1, fp);

        num_students++;
    }
    }

    fclose(fp);
    printf("Registration complete. %d students registered.\n", num_students);
    return ;
}

void searchStudent(){
char filename[50];
    FILE *fp;
    int num_students = 0;
    Student students[MAX_STUDENTS];

    while (1) {
        printf("Enter the filename for the class (or 'end' to exit): ");
        scanf("%s", filename);

        if (strcmp(filename, "end") == 0) {
            break;
        }

        fp = fopen(filename, "r");
        if (fp == NULL) {
            printf("Error: Failed to open file %s\n", filename);
            continue;
        }

        num_students = 0;
        while (fread(&students[num_students], sizeof(Student), 1, fp) == 1) {
            num_students++;
        }

        fclose(fp);
        printf("%d students found in file %s.\n", num_students, filename);

        while (1) {
            printf("Enter a key value (ID, code, name) to search for (or 'end' to exit): ");
            char key[50];
            scanf("%s", key);

            if (strcmp(key, "end") == 0) {
                break;
            }

            int found = 0;
            for (int i = 0; i < num_students; i++) {
                if (strcmp(key, students[i].code) == 0 ||
                    strcmp(key, students[i].name) == 0 ||
                    atoi(key) == students[i].id) {
                    print_student(&students[i]);
                    found = 1;
                    break;
                }
            }

            if (!found) {
                printf("No student found with key '%s'.\n", key);
            }
        }
    }

    printf("Search complete. Exiting program.\n");
    return ;
}
void alterStudent() {
    char filename[50];
    FILE *fp;
    int num_students = 0;
    Student students[MAX_STUDENTS];

    while (1) {
        printf("Enter the filename for the class (or 'end' to exit): ");
        scanf("%s", filename);

        if (strcmp(filename, "end") == 0) {
            break;
        }

        fp = fopen(filename, "r+");
        if (fp == NULL) {
            printf("Error: Failed to open file %s\n", filename);
            continue;
        }

        num_students = 0;
        while (fread(&students[num_students], sizeof(Student), 1, fp) == 1) {
            num_students++;
        }

        printf("%d students found in file %s.\n", num_students, filename);

        unsigned int id_to_alter;
        int student_index_to_alter = -1;

        printf("Enter the ID of the student to alter: ");
        scanf("%u", &id_to_alter);

        for (int i = 0; i < num_students; i++) {
            if (students[i].id == id_to_alter) {
                student_index_to_alter = i;
                break;
            }
        }

        if (student_index_to_alter == -1) {
            printf("Error: Student with ID %u not found.\n", id_to_alter);
            fclose(fp);
            continue;
        }

        printf("Student found:\n");
        print_student(&students[student_index_to_alter]);

        int field_to_alter;
        while (1) {
            printf("Enter the number of the field to alter (1-7) or 0 to exit: ");
            scanf("%d", &field_to_alter);

            if (field_to_alter == 0) {
                break;
            } else if (field_to_alter < 1 || field_to_alter > 7) {
                printf("Error: Invalid field number.\n");
                continue;
            }

            switch (field_to_alter) {
                case 1:
                    printf("Enter the new ID: ");
                    scanf("%u", &students[student_index_to_alter].id);
                    break;
                case 2:
                    printf("Enter the new code: ");
                    scanf("%s", students[student_index_to_alter].code);
                    break;
                case 3:
                    printf("Enter the new name: ");
                    scanf(" %[^\n]", students[student_index_to_alter].name);
                    break;
                case 4:
                    printf("Enter the new grades (separated by spaces): ");
                    for (int i = 0; i < 5; i++) {
                        scanf("%f", &students[student_index_to_alter].grades[i]);
                        students[student_index_to_alter].final_grade += students[student_index_to_alter].grades[i];
                    }
                    students[student_index_to_alter].final_grade = students[student_index_to_alter].final_grade/5.0;
                    break;
                case 5:
                    printf("Enter the new number of absences: ");
                    scanf("%u", &students[student_index_to_alter].num_absences);
                    break;
                case 6:
                    printf("Enter the new status: ");
                    scanf(" %[^\n]", students[student_index_to_alter].status);
                    break;
                case 7:
                    printf("Enter the new final grade: ");
                    scanf("%f", &students[student_index_to_alter].final_grade);
                    break;
            }

            fseek(fp, student_index_to_alter * sizeof(Student), SEEK_SET);
            fwrite(&students[student_index_to_alter], sizeof(Student), 1, fp);
fflush(fp);
  printf("Field altered successfully.\n");
    }

    fclose(fp);
}
}

void listStudents() {
    char filename[50];
    int option;
    do {
        printf("Enter the filename of the class: ");
        scanf("%s", filename);
        FILE *file = fopen(filename, "rb");
        if (file == NULL) {
            printf("File not found. Please try again or enter 'end' to exit.\n");
            continue;
        }
        fclose(file);
        printf("Select an option:\n");
        printf("1 - List students by ID in ascending order\n");
        printf("2 - List students by name in alphabetical order\n");
        printf("3 - List students by code in ascending order\n");
        printf("4 - Re-enter class filename\n");
        printf("5 - Go back to homepage\n");
        printf("Option: ");
        scanf("%d", &option);
        switch(option) {
            case 1:
                printStudents();

                break;
            case 2:
                sortStudentsByName();
                printStudents();
                break;
            case 3:
                printStudents();
                break;
            case 4:
                break;
            case 5:
                return;
            default:
                printf("Invalid option. Please try again.\n");
                break;
        }
    } while(option != 5 && option != 4);
}

int main() {
    int option;

    while (1) {
        printf("\n");
        printf("1 - Register student\n");
        printf("2 - Search student\n");
        printf("3 - Alter student\n");
        printf("4 - List students\n");
        printf("5 - Exit\n");
        printf("Enter an option: ");

        if (scanf("%d", &option) != 1) {
            printf("Invalid input\n");
            exit(1);
        }

        switch (option) {
            case 1:
                registerStudent();
                break;
            case 2:
                searchStudent();
                break;
            case 3:
                alterStudent();
                break;
            case 4:
                listStudents();
                break;
            case 5:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid option\n");
        }
    }

    return 0;
}

