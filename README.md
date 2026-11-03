# Online Examination Result Analyzer (C Language)

A terminal-based Online Examination Result Analyzer developed in C using fundamental Data Structures and Algorithms (DSA) concepts: Arrays, Sorting, and Searching.

---

## 👥 Team Members

| Roll Number | Student Name |
|-------------|--------------|
| `25EGJIT014` | Krishna Sharma 1 |
| `25EGJIT015` | Kuldeep Prjapat 2 |
| `25EGJIT017` | Lavish Jangid 3 |
| `25EGJIT018` | Laxmi Kumavat 4 |

---

## 📌 Project Overview & Module Breakdown

This project is divided into 4 distinct modules as per the DSA project curriculum:

### 1. Result Data Entry Module
* **Subject-wise Marks Entry:** Accepts `Roll Number`, `Name`, and marks of 5 subjects, stored in a **2D array** (`marks[student][subject]`).
* **Marks Range Validation:** Rejects any marks outside the range `0 – 100` and asks again.
* **Duplicate Validation:** Prevents adding a student with an existing roll number.

### 2. Result Calculation Module
* **Total & Percentage:** Computes total marks and percentage for each student.
* **Grade Assignment:** `A+` (≥90), `A` (≥80), `B+` (≥70), `B` (≥60), `C` (≥50), `D` (below 50), `F` (fail).
* **Pass/Fail Status:** A student passes only if they score at least **33 marks in every subject**.
* **Result Sheet:** Prints all students in a neatly formatted table.

### 3. Search Module
* **Search by Roll Number:** Uses **Linear Search** and displays the detailed marksheet.
* **Search by Name:** Case-insensitive, supports partial names (e.g. `neha`).
* **Error Handling:** Gracefully reports `Record Not Found` scenarios.

### 4. Analysis and Ranking Module
* **Sort by Total Marks:** Descending order using **Bubble Sort** (applied on an index array, so original data stays intact).
* **Rank List & Topper:** Generates the full rank list (ties share the same rank) and highlights the TOPPER(s).
* **Subject-wise Analysis:** Highest (with student name), Average, Lowest marks and pass % for every subject.
* **Overall Pass Percentage:** Total students, passed, failed, and pass percentage.

---

## 🛠️ DSA Concepts Implemented

* **1D Arrays:** Parallel arrays for roll numbers, totals, percentages, grades and status.
* **2D Arrays:** `marks[MAX_STUDENTS][NUM_SUBJECTS]` for subject-wise marks storage.
* **Linear Search:** O(n) search algorithm for searching by roll number and name.
* **Bubble Sort:** O(n²) comparison sorting algorithm (with early-exit optimization) for ranking by total marks.
* **Input Stream Handling:** Safe reading with `fgets` + `strtol` preventing infinite input loops or buffer overflow.

---

## 🚀 How to Compile and Run

### 1. Prerequisites
* A C compiler like `gcc` (MinGW / MSYS2 / Clang / Linux GCC).

### 2. Compilation
Open your terminal in the project directory and run:
```bash
gcc main.c -o result_analyzer
```

### 3. Execution
* **On Windows:**
  ```bash
  result_analyzer.exe
  ```
* **On Linux / macOS:**
  ```bash
  ./result_analyzer
  ```

> 💡 **Tip:** Choose option `9` (Load Demo Data) to instantly load 8 sample students and test all modules.

---

## 💻 Sample Program Menu

```text
==================================================
      ONLINE EXAMINATION RESULT ANALYZER
==================================================
 [Module 1: Result Data Entry]
   1. Add Student Result (2D Array Entry)

 [Module 2: Result Calculation]
   2. Calculate & Display All Results

 [Module 3: Search]
   3. Search by Roll Number (Linear Search)
   4. Search by Student Name

 [Module 4: Analysis and Ranking]
   5. Rank List (Sort by Total Marks)
   6. Find Topper
   7. Subject-wise Highest / Average / Lowest
   8. Overall Pass Percentage

   9. Load Demo Data
   0. Exit System
==================================================
```

---

## 📊 Sample Output (Rank List)

```text
Rank   Roll   Name                 Total    Percent   Grade  Status
------------------------------------------------------------------------------
1      101    Aarav Sharma         458      91.60%    A+     PASS
1      108    Pooja Jain           458      91.60%    A+     PASS
3      104    Sneha Gupta          435      87.00%    A      PASS
4      102    Priya Verma          413      82.60%    A      PASS
...
8      105    Karan Singh          245      49.00%    F      FAIL
```
