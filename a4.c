#define MAX_CHAR_SIZE 100
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct student {
    int id;
    char firstName[MAX_CHAR_SIZE];
    char lastName[MAX_CHAR_SIZE];
    int age;
    char courseCode[MAX_CHAR_SIZE];
    struct student* next;
} Student;
typedef Student* StudentPtr;
typedef struct studentGrades{
    int  studentId;
    int course1;
    int course2;
    int course3;
    int course4;
    int total;
    float percent;
    struct studentGrades* next;
} StudentGrades;
typedef StudentGrades* GradePtr;
typedef struct bst{
    int  studentId;
    int course1;
    int course2;
    int course3;
    int course4;
    int total;
    float percent;
    struct bst* left;
    struct bst* right;
}BST;
typedef BST* BstPtr;
void  bstMenu(GradePtr* grades, BstPtr* gradesBst);
enum bstMenuOptions { build = '1', search = '2', printBst = '3', destroy = '4', bstBack='5'};
enum MainMenuOptions {studentFunc='1', markEntry='2', computeTotal='3', displayGrades='4',insertionSort='5', quickSort='6', bst='7', displayGradesBackwards='8', quit ='9'};
enum studentMenuOptions {create='1', print='2', printBackwards='3', update='4', delete='5', back='6'};
void MainMenu(char *userInput){
    char buffer[16];
    printf("1> Student Menu (CRUD Operations)\n");
    printf("2> Enter Marks\n");
    printf("3> Compute Total And Percent\n");
    printf("4> Display Grades\n");
    printf("5> Sort Student By Id (Insertion Sort)\n");
    printf("6> Sort Student By Percentage (Quick Sort)\n");
    printf("7> Binary Search Tree Menu\n");
    printf("8> Display Grades (Backwards)\n");
    printf("9> Quit\n");
    while (1) {
        printf("Select an option: ");
        if (fgets(buffer, sizeof(buffer), stdin) != NULL && strlen(buffer) == 2 && buffer[1] == '\n') {
            *userInput = buffer[0];
            if (*userInput >= '1' && *userInput <= '9') break;
        }
        printf("Invalid input. Please enter a number between 1 and 9.\n");
    }
}
void studentMenuPrint(char *userInput)
{
    char buffer[16];
    printf("1> Create\n");
    printf("2> Print Students\n");
    printf("3> Print Students (Backwards)\n");
    printf("4> Update Student By Id\n");
    printf("5> Delete Student By Id\n");
    printf("6> Back To Main Menu\n");
    while (1) {
        printf("Select an option: ");
        if (fgets(buffer, sizeof(buffer), stdin) != NULL && strlen(buffer) == 2 && buffer[1] == '\n') {
            *userInput = buffer[0];
            if (*userInput >= '1' && *userInput <= '6') break;
        }
        printf("Invalid input. Please enter a number between 1 and 6.\n");
    }
}
int getNumberFromUser(char message[])
{
    int num;
    char buffer[256];
    while (1) {
        printf("%s", message);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            if (sscanf(buffer, "%d", &num) == 1) {
                return num;
            } else {
                printf("Invalid input. Please enter a valid number.\n");
            }
        } else {
            printf("Input error. Please try again.\n");
        }
    }
}
void getNumberFromUserInto(int* num, char message[]){
    char buffer[256];
    while (1) {
        printf("%s", message);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            if (sscanf(buffer, "%d", num) == 1) {
                return;
            } else {
                printf("Invalid input. Please enter a valid number.\n");
            }
        } else {
            printf("Input error. Please try again.\n");
        }
    }
}
void getStringFromUser(char string[], char message[])
{
    char buffer[MAX_CHAR_SIZE];
    printf("%s", message);
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') buffer[len - 1] = '\0';
        strncpy(string, buffer, MAX_CHAR_SIZE - 1);
        string[MAX_CHAR_SIZE - 1] = '\0';
    } else {
        printf("Input error. Please try again.\n");
        string[0] = '\0';
    }
}
void getStudentInfoFromUser(char fname[100], char lname[100], int* age, char courseCode[100])
{
    getStringFromUser(fname,"Please Enter Student First Name: ");
    getStringFromUser(lname,"Please Enter Student Last Name: ");
    getNumberFromUserInto(age,"Please Enter Student Age: ");
    getStringFromUser(courseCode, "Please Enter Student Course Code: ");
}
int studentIdExists(StudentPtr students, int id) {
    while (students != NULL) {
        if (students->id == id) return 1;
        students = students->next;
    }
    return 0;
}

void createStudent(StudentPtr* head){
    int id;
    while (1) {
        id = getNumberFromUser("Please Enter Student ID (positive integer): ");
        if (id < 0) {
            printf("ID must be a positive integer.\n");
            continue;
        }
        if (studentIdExists(*head, id)) {
            printf("ID already exists. Please enter a unique ID.\n");
            continue;
        }
        break;
    }
    char fname[MAX_CHAR_SIZE];
    char lname[MAX_CHAR_SIZE];
    int age;
    char courseCode[MAX_CHAR_SIZE];
    getStudentInfoFromUser(fname, lname, &age, courseCode);
    StudentPtr newStudent =  malloc(sizeof(Student));
    newStudent->id = id;
    newStudent->age=age;
    strcpy( newStudent->firstName, fname);
    strcpy( newStudent->lastName, lname);
    newStudent->age = age;
    strcpy(newStudent->courseCode, courseCode);
    newStudent->next=NULL;
    if (*head == NULL){
        *head = newStudent;
        return;
    }
    StudentPtr cur = *head;
    while (cur->next !=NULL){
        cur=cur->next;
    }
    cur->next=newStudent;
}
void println(char* message){
   printf("%s\n",message);
}
void printStudent(StudentPtr student){
    if ( student == NULL)    {
        println("Student is Null");
        return;
    }
    printf("Student %d: %s %s | Age: %d | Course: %s \n", student->id, student->firstName, student->lastName,  student->age, student->courseCode  );
}
void printStudents(StudentPtr students)
{
    if (students == NULL)
    {
        println("No Students");
        return;
    }
    while (students != NULL )
    {
        printStudent(students);
        students=students->next;
    }
}
void printStudentsReverse(StudentPtr students) {
    if (students == NULL) {
        println("No Students");
        return;
    }
    if (students->next != NULL) {
        printStudentsReverse(students->next);
    }
    printStudent(students);
}
StudentPtr getStudentById(StudentPtr students, int id)
{
    if (students == NULL)
    {
        println("No Students");
        return NULL;
    }else
    {
        StudentPtr cur = students;
        while (cur != NULL && cur->id !=id)
        {
            cur=cur->next;
        }
        if (cur == NULL)
        {
            println("no student found");
            return NULL;
        }else if (cur->id == id)
        {
            return cur;
        }else
        {
            return NULL;
        }
    }
}
StudentPtr studentPicker(StudentPtr students){
    printStudents(students);
    int studentId = getNumberFromUser("please enter student id: ");
    return getStudentById(students,studentId);
}
void freeStudents(StudentPtr* students) {
    StudentPtr cur = *students;
    while (cur != NULL) {
        StudentPtr next = cur->next;
        free(cur);
        cur = next;
    }
    *students = NULL;
}
void deleteStudentOption(StudentPtr* students){
    if (*students== NULL)    {
        println("No Students");
        return;
    }
   StudentPtr studentForDel= studentPicker(*students);
    if (studentForDel== NULL){return;}
    if (studentForDel == *students){
        StudentPtr toDelete = *students;
        *students = (*students)->next;
        free(toDelete);
        return;
    }
    StudentPtr parent = *students;
    while (parent->next != NULL && parent->next != studentForDel)    {
        parent=parent->next;
    }
    if (parent->next == NULL){
        return;
    }
    parent->next = studentForDel->next;
    free(studentForDel);
}
void updateStudentOption(StudentPtr students){
    if (students == NULL)    {
        println("No Students");
        return;
    }
   StudentPtr stu =  studentPicker(students);
    if (stu != NULL){
        char fname[MAX_CHAR_SIZE];
        char lname[MAX_CHAR_SIZE];
        int age;
        char courseCode[MAX_CHAR_SIZE];
        getStudentInfoFromUser(fname, lname, &age, courseCode);
        strcpy(stu->firstName, fname);
        strcpy(stu->lastName, lname);
        strcpy(stu->courseCode, courseCode);
        stu->age= age;
    }
}
void handleStudentMenuOption(char userInput, StudentPtr* students){
    switch (userInput)    {
    case create:
        createStudent(students);
        break;
    case print:
        printStudents(*students);
        break;
    case printBackwards:
        printStudentsReverse(*students);
        break;
    case update:
        updateStudentOption(*students);
        break;
    case delete:
        deleteStudentOption(students);
        break;
    case back:
        break;
    default:
        println("Please Enter a valid Option");
        break;
    }
}
void studentMenu( StudentPtr* students, GradePtr* grades ){
    char userInput='\0';
    do    {
        studentMenuPrint(&userInput);
        handleStudentMenuOption(userInput, students);
    }while (userInput != back);
}
int gradeIdExists(GradePtr grades, int id) {
    while (grades != NULL) {
        if (grades->studentId == id) return 1;
        grades = grades->next;
    }
    return 0;
}

GradePtr createGrade(int student_id){
    int mark1 = getNumberFromUser("please enter mark for course 1: ");
    int mark2 = getNumberFromUser("please enter mark for course 2: ");
    int mark3 = getNumberFromUser("please enter mark for course 3: ");
    int mark4 = getNumberFromUser("please enter mark for course 4: ");
    GradePtr newGrade = malloc(sizeof(StudentGrades));
    if (newGrade==NULL) return NULL;
    newGrade->studentId=student_id;
    newGrade->course1=mark1;
    newGrade->course2=mark2;
    newGrade->course3=mark3;
    newGrade->course4=mark4;
    newGrade->next=NULL;
    return newGrade;
}
void freeGrades(GradePtr* grades)
{
    GradePtr nextForDel = *grades;
    GradePtr forDel;
    while (nextForDel != NULL)
    {
        forDel = nextForDel;
        free(forDel);
        nextForDel = nextForDel->next;
    }
    *grades=NULL;
}
GradePtr findEndOfGrades(GradePtr grades)
{
    if (grades==NULL)
    {
        return grades;
    }
    while (grades->next !=NULL)
    {
        grades= grades->next;
    }
    return grades;
}
void printGrade(GradePtr grade) {
    if (grade == NULL) return;
    printf("Student %d:\n\tCourse 1: %d\n\tCourse 2: %d\n\tCourse 3: %d\n\tCourse 4: %d\n\tTotal: %d\n\tPercent: %.2f\n",
           grade->studentId, grade->course1, grade->course2, grade->course3, grade->course4, grade->total, grade->percent);
}
void printGradesReverse(GradePtr grades) {
    if (grades == NULL) {
        println("No Grades");
        return;
    }
    if (grades->next != NULL) {
        printGradesReverse(grades->next);
    }
    printGrade(grades);
}
void markEntryPath(StudentPtr* students,  GradePtr* grades )
{
    freeGrades(grades);
    if (*students == NULL) return;
    StudentPtr cur = *students;
    while (cur != NULL) {
        printf("Current ");
        printStudent(cur);
        GradePtr newGrade = createGrade(cur->id);
        if (*grades == NULL) {
            *grades = newGrade;
        } else {
            GradePtr last = *grades;
            while (last->next != NULL) last = last->next;
            last->next = newGrade;
        }
        printGrade(newGrade);
        cur = cur->next;
    }
}
void computeTotalAndPercentPath(GradePtr* grades)
{
    GradePtr cur =*grades;
    while (cur!=NULL)
    {
        cur->total=cur->course1+cur->course2+cur->course3+cur->course4;
        cur->percent= cur->total/4;
        cur=cur->next;
    }
}
void displayGradesPath(GradePtr* grades)
{
    GradePtr cur = *grades;
    while (cur!=NULL)
    {
        printGrade(cur);
        cur=cur->next;
    }
}
void insertionSortPath(StudentPtr* students) {
    int count = 0;
    if (*students == NULL) return;
    StudentPtr current = (*students)->next;
    StudentPtr sorted = *students;
    sorted->next = NULL;
    while (current != NULL) {
        StudentPtr node = current;
        current = current->next;
        count++;
        if (node->id < sorted->id) {
            node->next = sorted;
            sorted = node;
        } else {
            StudentPtr tmp = sorted;
            while (tmp->next != NULL && tmp->next->id < node->id) {
                tmp = tmp->next;
            }
            node->next = tmp->next;
            tmp->next = node;
        }
    }
    *students = sorted;
    printStudents(*students);
    printf("Insertion Sort By Id(Count:%d)\n", count);
}
GradePtr QuickSortAlgo(GradePtr head, int* count_measu){
    if(head == NULL || head->next == NULL){
        return head;
    }else {
        GradePtr pivot = head;
        head = head->next;
        GradePtr leftSideHead = NULL;
        GradePtr leftSideEnd = NULL;
        GradePtr rightSideHead = NULL;
        GradePtr rightSideEnd = NULL;
        while (head != NULL)        {
            (*count_measu)++;
            if (head->percent < pivot->percent)            {
                if (leftSideHead == NULL)                {
                    leftSideHead = head;
                    leftSideEnd = head;
                }else                {
                    leftSideEnd->next = head;
                    leftSideEnd = leftSideEnd->next;
                }
            }else   {
                if (rightSideHead == NULL)                {
                    rightSideHead = head;
                    rightSideEnd = head;
                }else                {
                    rightSideEnd->next = head;
                    rightSideEnd = rightSideEnd->next;
                }
            }
            head = head->next;
        }
        if (leftSideEnd != NULL) leftSideEnd->next = NULL;
        if (rightSideEnd != NULL) rightSideEnd->next = NULL;
        leftSideHead = QuickSortAlgo(leftSideHead, count_measu);
        rightSideHead = QuickSortAlgo(rightSideHead, count_measu);
        if (leftSideHead != NULL)
        {
            leftSideEnd = leftSideHead;
            while (leftSideEnd->next != NULL)            {
                leftSideEnd = leftSideEnd->next;
            }
            leftSideEnd->next = pivot;
        }
        pivot->next = rightSideHead;
        return leftSideHead != NULL ? leftSideHead : pivot;
    }
}
void quickSortPath(GradePtr* grades){
    int count_measu = 0;
    *grades = QuickSortAlgo(*grades, &count_measu);
    displayGradesPath(grades);
    printf("QuickSort Comparisons: %d\n", count_measu);
}
void handleMainMenuOption(char userInput,  StudentPtr* students,  GradePtr* grades, BstPtr* gradesBst )
{
    switch (userInput)
    {
    case studentFunc:
        studentMenu(students,grades);
        break;
    case markEntry:
        markEntryPath(students, grades );
        break;
    case computeTotal:
        computeTotalAndPercentPath(grades);
        break;
    case displayGrades:
            displayGradesPath(grades);
        break;
    case insertionSort:
        insertionSortPath(students);
        break;
    case quickSort:
        quickSortPath(grades);
        break;
    case bst:
      bstMenu( grades, gradesBst);
        break;
    case displayGradesBackwards:
        printGradesReverse(*grades);
        break;
    case quit:
        break;
    default:
        printf("please enter a valid option\n");
        break;
    }
}
void insertFakeStudents(StudentPtr* head)
{
    int ids[]={62,35,44,33,12};
    char* firstNames[] = {"Alice", "Bob", "Charlie", "Diana", "Evan"};
    char* lastNames[] = {"Smith", "Jones", "Brown", "Taylor", "White"};
    int ages[] = {20, 22, 21, 23, 19};
    char* courses[] = {"CS101", "CS102", "CS103", "CS104", "CS105"};
    for (int i = 0; i < 5; i++) {
        StudentPtr newStudent = malloc(sizeof(Student));
        newStudent->id = ids[i];
        strcpy(newStudent->firstName, firstNames[i]);
        strcpy(newStudent->lastName, lastNames[i]);
        newStudent->age = ages[i];
        strcpy(newStudent->courseCode, courses[i]);
        newStudent->next = NULL;
        if (*head == NULL) {
            *head = newStudent;
        } else {
            StudentPtr cur = *head;
            while (cur->next != NULL) cur = cur->next;
            cur->next = newStudent;
        }
    }
}
void insertFakeGrades(GradePtr* head)
{
    int ids[] = {62, 35, 44, 33, 12};
    int c1[] = {80, 90, 70, 85, 75};
    int c2[] = {82, 88, 72, 81, 77};
    int c3[] = {78, 91, 74, 83, 79};
    int c4[] = {85, 89, 76, 80, 78};
    for (int i = 0; i < 5; i++) {
        GradePtr newGrade = malloc(sizeof(StudentGrades));
        newGrade->studentId = ids[i];
        newGrade->course1 = c1[i];
        newGrade->course2 = c2[i];
        newGrade->course3 = c3[i];
        newGrade->course4 = c4[i];
        newGrade->total = c1[i] + c2[i] + c3[i] + c4[i];
        newGrade->percent = newGrade->total / 4.0f;
        newGrade->next = NULL;
        if (*head == NULL) {
            *head = newGrade;
        } else {
            GradePtr cur = *head;
            while (cur->next != NULL) cur = cur->next;
            cur->next = newGrade;
        }
    }
}
void bstMenuPrint(char *userInput)
{
    char buffer[16];
    printf("1> Build BST from grades\n");
    printf("2> Search student by ID\n");
    printf("3> Print BST (inorder)\n");
    printf("4> Destroy BST\n");
    printf("5> Back To Main Menu\n");
    while (1) {
        printf("Select an option: ");
        if (fgets(buffer, sizeof(buffer), stdin) != NULL && strlen(buffer) == 2 && buffer[1] == '\n') {
            *userInput = buffer[0];
            if (*userInput >= '1' && *userInput <= '5') break;
        }
        printf("Invalid input. Please enter a number between 1 and 5.\n");
    }
}
void deleteNode(BstPtr cur){
    if (cur==NULL)    {        return;    }
    deleteNode(cur->left);
    deleteNode(cur->right);
    free(cur);
}
void destroyBST(BstPtr *gradesBst){
     deleteNode(*gradesBst);
    (*gradesBst) = NULL;
}
BstPtr createBstNode(GradePtr grade) {
    BstPtr newNode = malloc(sizeof(BST));
    newNode->studentId = grade->studentId;
    newNode->course1 = grade->course1;
    newNode->course2 = grade->course2;
    newNode->course3 = grade->course3;
    newNode->course4 = grade->course4;
    newNode->total = grade->total;
    newNode->percent = grade->percent;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
void insertNodeIntoTree(BstPtr* gradesBst, BstPtr newNode){
    if (*gradesBst == NULL) {
        *gradesBst = newNode;
        return;
    }
    BstPtr cur = *gradesBst;
    while (1)    {
        if (newNode->studentId < cur->studentId)
        {
            if (cur->left==NULL){
                cur->left=newNode;
                return;
            }
            cur =cur->left;
        }else{
            if (cur->right==NULL){
                cur->right=newNode;
                return;
            }
            cur =cur->right;
        }
    }
}
void buildBST(GradePtr grades,BstPtr* gradesBst){
    destroyBST(gradesBst);
    while (grades != NULL) {
        BstPtr newNode = createBstNode(grades);
        insertNodeIntoTree(gradesBst, newNode);
        grades = grades->next;
    }
}
void printGradeBstNode(BstPtr grade){
    if (grade == NULL) return;
    printf("ID: %d | C1: %d | C2: %d | C3: %d | C4: %d | Total: %d | Percent: %.2f\n",
           grade->studentId,
           grade->course1,
           grade->course2,
           grade->course3,
           grade->course4,
           grade->total,
           grade->percent);
}
BstPtr getGradesFromBstById(int id, BstPtr grades, int* count_measu){
    *count_measu = 0;
    while (grades!=NULL){
        (*count_measu)++;
        if (grades->studentId==id)        {
            return grades;
        }else if (id< grades->studentId)        {
            grades=grades->left;
        }else        {
            grades=grades->right;
        }
    }
    return NULL;
}
void searchGrade(BstPtr grades){
    int student_id=getNumberFromUser("please enter a student id: ");
    int count_measu = 0;
    BstPtr foundGrade=getGradesFromBstById(student_id, grades, &count_measu);
    if (foundGrade==NULL){
        println("no node found");
        printf("BST Search Comparisons: %d\n", count_measu);
        return;
    }
    printGradeBstNode(foundGrade);
    printf("BST Search Comparisons: %d\n", count_measu);
}
void inOrderBST(BstPtr node){
    if (node==NULL){return;}
    inOrderBST(node->left);
    printGradeBstNode(node);
    inOrderBST(node->right);
}
void chooseBstPath(char userInput, GradePtr* grades,BstPtr* gradesBst){
    switch (userInput){
    case build:
        buildBST(*grades,gradesBst);
        break;
    case search:
        searchGrade(*gradesBst);
        break;
    case printBst:
        inOrderBST(*gradesBst);
        break;
    case destroy:
        destroyBST(gradesBst);
        break;
    case bstBack:
        return;
    default:
        printf("Invalid option\n");
    }
}
void  bstMenu(GradePtr* grades, BstPtr* gradesBst){
    char userInput='\0';
    do{
        bstMenuPrint(&userInput);
        chooseBstPath(userInput, grades, gradesBst);
    }while (userInput != bstBack);
}
int main(){
    char userInput='\0';
    StudentPtr students = NULL;
    GradePtr grades = NULL;
    BstPtr gradesBst = NULL;
    // insertFakeStudents(&students);
    // insertFakeGrades(&grades);
    do{
        MainMenu(&userInput);
        handleMainMenuOption(userInput, &students,&grades, &gradesBst);
    }while (userInput != quit);
    freeStudents(&students);
    freeGrades(&grades);
    destroyBST(&gradesBst);
    return 0;
}

