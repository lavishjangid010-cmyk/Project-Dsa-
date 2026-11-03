/*
 * ============================================================
 *  ONLINE EXAMINATION RESULT ANALYZER (C Language)
 *  DSA Concepts: Arrays (1D & 2D), Searching, Sorting
 * ============================================================
 *  Team Members:
 *    25egjcc0XX - Member Name 1
 *    25egjcc0XX - Member Name 2
 *    25egjcc0XX - Member Name 3
 *    25egjcc0XX - Member Name 4
 * ============================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STUDENTS 100
#define NUM_SUBJECTS 5
#define NAME_LEN     50
#define MAX_MARKS    100
#define PASS_MARKS   33   /* minimum marks required in EACH subject */

static const char *SUBJECTS[NUM_SUBJECTS] = {
    "Mathematics", "Physics", "Chemistry", "English", "Computer Sci"
};

/* ---------------- Global data (array based storage) ---------------- */
int   studentCount = 0;
int   rollNo[MAX_STUDENTS];
char  names[MAX_STUDENTS][NAME_LEN];
int   marks[MAX_STUDENTS][NUM_SUBJECTS];   /* 2D array: student x subject */
int   total[MAX_STUDENTS];
float percentage[MAX_STUDENTS];
char  grade[MAX_STUDENTS][3];
int   passed[MAX_STUDENTS];                /* 1 = PASS, 0 = FAIL */

/* ---------------- Safe input helpers ---------------- */
void readLine(char *buf, int size) {
    if (fgets(buf, size, stdin) == NULL) {
        buf[0] = '\0';
        return;
    }
    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n') {
        buf[len - 1] = '\0';
    } else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }  /* discard extra input */
    }
}

int readInt(const char *prompt, int min, int max) {
    char buf[64];
    char *end;
    long val;
    while (1) {
        printf("%s", prompt);
        readLine(buf, sizeof(buf));
        val = strtol(buf, &end, 10);
        if (end != buf && *end == '\0' && val >= min && val <= max)
            return (int)val;
        printf("  [!] Invalid input. Enter a number between %d and %d.\n", min, max);
    }
}

void pressEnter(void) {
    char buf[8];
    printf("\nPress Enter to continue...");
    readLine(buf, sizeof(buf));
}

void toLowerStr(const char *src, char *dst) {
    int i;
    for (i = 0; src[i] != '\0'; i++)
        dst[i] = (char)tolower((unsigned char)src[i]);
    dst[i] = '\0';
}

int findIndexByRoll(int roll) {              /* Linear Search */
    int i;
    for (i = 0; i < studentCount; i++)
        if (rollNo[i] == roll)
            return i;
    return -1;
}

void printLine(char ch, int n) {
    int i;
    for (i = 0; i < n; i++) putchar(ch);
    putchar('\n');
}

/* ============================================================
 *  MODULE 2: RESULT CALCULATION
 * ============================================================ */
void calculateResult(int i) {
    int j, allPass = 1;
    total[i] = 0;
    for (j = 0; j < NUM_SUBJECTS; j++) {
        total[i] += marks[i][j];
        if (marks[i][j] < PASS_MARKS) allPass = 0;
    }
    percentage[i] = (float)total[i] * 100.0f / (NUM_SUBJECTS * MAX_MARKS);
    passed[i] = allPass;

    if (!allPass)                strcpy(grade[i], "F");
    else if (percentage[i] >= 90) strcpy(grade[i], "A+");
    else if (percentage[i] >= 80) strcpy(grade[i], "A");
    else if (percentage[i] >= 70) strcpy(grade[i], "B+");
    else if (percentage[i] >= 60) strcpy(grade[i], "B");
    else if (percentage[i] >= 50) strcpy(grade[i], "C");
    else                          strcpy(grade[i], "D");
}

void printResultHeader(void) {
    int j;
    printLine('-', 40 + NUM_SUBJECTS * 6 + 30);
    printf("%-6s %-20s", "Roll", "Name");
    for (j = 0; j < NUM_SUBJECTS; j++) printf(" S%-4d", j + 1);
    printf(" %-6s %-8s %-6s %-6s\n", "Total", "Percent", "Grade", "Status");
    printLine('-', 40 + NUM_SUBJECTS * 6 + 30);
}

void printResultRow(int i) {
    int j;
    printf("%-6d %-20s", rollNo[i], names[i]);
    for (j = 0; j < NUM_SUBJECTS; j++) printf(" %-5d", marks[i][j]);
    char pct[16];
    snprintf(pct, sizeof(pct), "%.2f%%", percentage[i]);
    printf(" %-6d %-8s %-6s %-6s\n", total[i], pct, grade[i],
           passed[i] ? "PASS" : "FAIL");
}

void calculateAndDisplayAll(void) {
    int i, j;
    if (studentCount == 0) { printf("\n[!] No student data available.\n"); return; }

    for (i = 0; i < studentCount; i++) calculateResult(i);

    printf("\n===== RESULT SHEET OF ALL STUDENTS =====\n");
    printf("Subjects: ");
    for (j = 0; j < NUM_SUBJECTS; j++)
        printf("S%d=%s%s", j + 1, SUBJECTS[j], j < NUM_SUBJECTS - 1 ? ", " : "\n");
    printf("Pass criteria: minimum %d marks in every subject.\n\n", PASS_MARKS);
    printResultHeader();
    for (i = 0; i < studentCount; i++) printResultRow(i);
    printLine('-', 40 + NUM_SUBJECTS * 6 + 30);
}

/* ============================================================
 *  MODULE 1: RESULT DATA ENTRY
 * ============================================================ */
void addStudent(void) {
    int i, j, roll;
    char prompt[80];

    if (studentCount >= MAX_STUDENTS) {
        printf("\n[!] Storage full. Cannot add more students.\n");
        return;
    }

    printf("\n===== ADD STUDENT RESULT =====\n");
    roll = readInt("Enter Roll Number (1-99999): ", 1, 99999);
    if (findIndexByRoll(roll) != -1) {
        printf("[!] Roll number %d already exists. Entry rejected.\n", roll);
        return;
    }

    i = studentCount;
    rollNo[i] = roll;

    do {
        printf("Enter Student Name: ");
        readLine(names[i], NAME_LEN);
        if (strlen(names[i]) == 0) printf("  [!] Name cannot be empty.\n");
    } while (strlen(names[i]) == 0);

    for (j = 0; j < NUM_SUBJECTS; j++) {
        snprintf(prompt, sizeof(prompt), "Marks in %s (0-%d): ", SUBJECTS[j], MAX_MARKS);
        marks[i][j] = readInt(prompt, 0, MAX_MARKS);   /* validates marks range */
    }

    studentCount++;
    calculateResult(i);
    printf("\n[+] Record added successfully!\n");
}

/* ============================================================
 *  MODULE 3: SEARCH
 * ============================================================ */
void displayMarksheet(int i) {
    int j;
    printf("\n");
    printLine('=', 52);
    printf("                 STUDENT MARKSHEET\n");
    printLine('=', 52);
    printf("Roll Number : %d\n", rollNo[i]);
    printf("Name        : %s\n", names[i]);
    printLine('-', 52);
    printf("%-20s %-10s %-10s %-8s\n", "Subject", "Marks", "Out Of", "Result");
    printLine('-', 52);
    for (j = 0; j < NUM_SUBJECTS; j++)
        printf("%-20s %-10d %-10d %-8s\n", SUBJECTS[j], marks[i][j], MAX_MARKS,
               marks[i][j] >= PASS_MARKS ? "Pass" : "Fail");
    printLine('-', 52);
    printf("Total       : %d / %d\n", total[i], NUM_SUBJECTS * MAX_MARKS);
    printf("Percentage  : %.2f%%\n", percentage[i]);
    printf("Grade       : %s\n", grade[i]);
    printf("Final Status: %s\n", passed[i] ? "PASS" : "FAIL");
    printLine('=', 52);
}

void searchByRoll(void) {
    int roll, idx;
    if (studentCount == 0) { printf("\n[!] No student data available.\n"); return; }
    printf("\n===== SEARCH BY ROLL NUMBER (Linear Search) =====\n");
    roll = readInt("Enter Roll Number to search: ", 1, 99999);
    idx = findIndexByRoll(roll);
    if (idx == -1) printf("\n[!] Record Not Found for roll number %d.\n", roll);
    else           displayMarksheet(idx);
}

void searchByName(void) {
    char query[NAME_LEN], qLow[NAME_LEN], nLow[NAME_LEN];
    int i, found = 0;
    if (studentCount == 0) { printf("\n[!] No student data available.\n"); return; }
    printf("\n===== SEARCH BY NAME (case-insensitive) =====\n");
    printf("Enter full or partial name: ");
    readLine(query, NAME_LEN);
    toLowerStr(query, qLow);

    for (i = 0; i < studentCount; i++) {
        toLowerStr(names[i], nLow);
        if (strstr(nLow, qLow) != NULL) {
            displayMarksheet(i);
            found++;
        }
    }
    if (!found) printf("\n[!] Record Not Found for name \"%s\".\n", query);
    else        printf("\n%d record(s) found.\n", found);
}

/* ============================================================
 *  MODULE 4: ANALYSIS AND RANKING
 * ============================================================ */

/* Bubble Sort on an index array (descending by total marks).
 * Original 2D marks array stays untouched. */
void sortByTotal(int order[]) {
    int i, j, tmp;
    for (i = 0; i < studentCount; i++) order[i] = i;

    for (i = 0; i < studentCount - 1; i++) {
        int swapped = 0;
        for (j = 0; j < studentCount - i - 1; j++) {
            if (total[order[j]] < total[order[j + 1]]) {
                tmp = order[j];
                order[j] = order[j + 1];
                order[j + 1] = tmp;
                swapped = 1;
            }
        }
        if (!swapped) break;
    }
}

void showRankList(void) {
    int order[MAX_STUDENTS];
    int i, rank = 0;

    if (studentCount == 0) { printf("\n[!] No student data available.\n"); return; }
    sortByTotal(order);

    printf("\n===== RANK LIST (Sorted by Total Marks - Bubble Sort) =====\n");
    printLine('-', 78);
    printf("%-6s %-6s %-20s %-8s %-9s %-6s %-6s\n",
           "Rank", "Roll", "Name", "Total", "Percent", "Grade", "Status");
    printLine('-', 78);
    for (i = 0; i < studentCount; i++) {
        int s = order[i];
        if (i == 0 || total[s] != total[order[i - 1]]) rank = i + 1;  /* ties share rank */
        char pct[16];
        snprintf(pct, sizeof(pct), "%.2f%%", percentage[s]);
        printf("%-6d %-6d %-20s %-8d %-9s %-6s %-6s\n",
               rank, rollNo[s], names[s], total[s], pct, grade[s],
               passed[s] ? "PASS" : "FAIL");
    }
    printLine('-', 78);
}

void findTopper(void) {
    int i, maxTotal, count = 0;
    if (studentCount == 0) { printf("\n[!] No student data available.\n"); return; }

    maxTotal = total[0];
    for (i = 1; i < studentCount; i++)
        if (total[i] > maxTotal) maxTotal = total[i];

    printf("\n===== TOPPER =====\n");
    for (i = 0; i < studentCount; i++) {
        if (total[i] == maxTotal) {
            printf("*** TOPPER: %s (Roll %d) | Total: %d | %.2f%% | Grade: %s ***\n",
                   names[i], rollNo[i], total[i], percentage[i], grade[i]);
            count++;
        }
    }
    if (count > 1) printf("(%d students are tied for the top position)\n", count);
}

void subjectAnalysis(void) {
    int i, j;
    if (studentCount == 0) { printf("\n[!] No student data available.\n"); return; }

    printf("\n===== SUBJECT-WISE ANALYSIS =====\n");
    printLine('-', 80);
    printf("%-16s %-8s %-20s %-8s %-8s %-8s\n",
           "Subject", "Highest", "(Scored By)", "Average", "Lowest", "Pass %");
    printLine('-', 80);

    for (j = 0; j < NUM_SUBJECTS; j++) {
        int hi = marks[0][j], lo = marks[0][j], hiIdx = 0, sum = 0, passCount = 0;
        for (i = 0; i < studentCount; i++) {
            if (marks[i][j] > hi) { hi = marks[i][j]; hiIdx = i; }
            if (marks[i][j] < lo) lo = marks[i][j];
            sum += marks[i][j];
            if (marks[i][j] >= PASS_MARKS) passCount++;
        }
        char pct[16];
        snprintf(pct, sizeof(pct), "%.2f%%", (float)passCount * 100.0f / studentCount);
        printf("%-16s %-8d %-20s %-8.2f %-8d %-8s\n",
               SUBJECTS[j], hi, names[hiIdx], (float)sum / studentCount, lo, pct);
    }
    printLine('-', 80);
}

void passPercentage(void) {
    int i, passCount = 0;
    if (studentCount == 0) { printf("\n[!] No student data available.\n"); return; }

    for (i = 0; i < studentCount; i++) passCount += passed[i];

    printf("\n===== OVERALL PASS PERCENTAGE =====\n");
    printf("Total Students : %d\n", studentCount);
    printf("Passed         : %d\n", passCount);
    printf("Failed         : %d\n", studentCount - passCount);
    printf("Pass Percentage: %.2f%%\n", (float)passCount * 100.0f / studentCount);
}

/* ---------------- Demo data ---------------- */
void loadSampleData(void) {
    static const char *demoNames[] = {
        "Aarav Sharma", "Priya Verma", "Rohan Meena", "Sneha Gupta",
        "Karan Singh", "Neha Joshi", "Vikram Rathore", "Pooja Jain"
    };
    static const int demoMarks[8][NUM_SUBJECTS] = {
        {92, 88, 95, 85, 98},
        {78, 82, 75, 90, 88},
        {45, 52, 38, 60, 55},
        {88, 91, 84, 79, 93},
        {30, 55, 48, 62, 50},   /* fails Mathematics */
        {67, 71, 64, 72, 80},
        {56, 49, 61, 58, 66},
        {92, 88, 95, 85, 98}    /* ties with the first student */
    };
    int i, j, added = 0;

    for (i = 0; i < 8 && studentCount < MAX_STUDENTS; i++) {
        int roll = 101 + i;
        if (findIndexByRoll(roll) != -1) continue;
        rollNo[studentCount] = roll;
        strncpy(names[studentCount], demoNames[i], NAME_LEN - 1);
        names[studentCount][NAME_LEN - 1] = '\0';
        for (j = 0; j < NUM_SUBJECTS; j++) marks[studentCount][j] = demoMarks[i][j];
        calculateResult(studentCount);
        studentCount++;
        added++;
    }
    printf("\n[+] %d demo record(s) loaded.\n", added);
}

/* ---------------- Menu ---------------- */
void printMenu(void) {
    printf("\n==================================================\n");
    printf("      ONLINE EXAMINATION RESULT ANALYZER\n");
    printf("==================================================\n");
    printf(" [Module 1: Result Data Entry]\n");
    printf("   1. Add Student Result (2D Array Entry)\n\n");
    printf(" [Module 2: Result Calculation]\n");
    printf("   2. Calculate & Display All Results\n\n");
    printf(" [Module 3: Search]\n");
    printf("   3. Search by Roll Number (Linear Search)\n");
    printf("   4. Search by Student Name\n\n");
    printf(" [Module 4: Analysis and Ranking]\n");
    printf("   5. Rank List (Sort by Total Marks)\n");
    printf("   6. Find Topper\n");
    printf("   7. Subject-wise Highest / Average / Lowest\n");
    printf("   8. Overall Pass Percentage\n\n");
    printf("   9. Load Demo Data\n");
    printf("   0. Exit System\n");
    printf("==================================================\n");
}

int main(void) {
    int choice;
    do {
        printMenu();
        choice = readInt("Enter your choice: ", 0, 9);
        switch (choice) {
            case 1: addStudent();             break;
            case 2: calculateAndDisplayAll(); break;
            case 3: searchByRoll();           break;
            case 4: searchByName();           break;
            case 5: showRankList();           break;
            case 6: findTopper();             break;
            case 7: subjectAnalysis();        break;
            case 8: passPercentage();         break;
            case 9: loadSampleData();         break;
            case 0: printf("\nThank you for using the Result Analyzer. Goodbye!\n"); break;
        }
        if (choice != 0) pressEnter();
    } while (choice != 0);
    return 0;
}
