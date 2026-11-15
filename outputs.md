# Test Cases and Outputs

**Project:** Library Book Management System (C++)

Every output below was produced by running `library.cpp` (compiled with `g++ -std=c++11 -Wall -Wextra -pedantic`). To keep the output short, the menu listing that is printed before every prompt is omitted. Text after each prompt is what the user typed.

| No. | Test case | Result |
|---|---|---|
| 1 | [Add a valid book](#test-case-1-add-a-valid-book) | Pass |
| 2 | [Duplicate book ID (invalid input)](#test-case-2-duplicate-book-id-invalid-input) | Pass |
| 3 | [Non-numeric book ID (invalid input)](#test-case-3-non-numeric-book-id-invalid-input) | Pass |
| 4 | [Boundary value: ID 0](#test-case-4-boundary-value-id-0) | Pass |
| 5 | [Empty title (invalid input)](#test-case-5-empty-title-invalid-input) | Pass |
| 6 | [Search a book by ID](#test-case-6-search-a-book-by-id) | Pass |
| 7 | [Search a book by title (case-insensitive, partial)](#test-case-7-search-a-book-by-title-case-insensitive-partial) | Pass |
| 8 | [Search with an unknown ID](#test-case-8-search-with-an-unknown-id) | Pass |
| 9 | [Issue an available book](#test-case-9-issue-an-available-book) | Pass |
| 10 | [Issue a book that is already issued](#test-case-10-issue-a-book-that-is-already-issued) | Pass |
| 11 | [Issue a book with an unknown ID](#test-case-11-issue-a-book-with-an-unknown-id) | Pass |
| 12 | [Return a book that was not issued](#test-case-12-return-a-book-that-was-not-issued) | Pass |
| 13 | [Return an issued book](#test-case-13-return-an-issued-book) | Pass |
| 14 | [Data persists after closing and reopening](#test-case-14-data-persists-after-closing-and-reopening) | Pass |
| 15 | [Missing data file at startup](#test-case-15-missing-data-file-at-startup) | Pass |
| 16 | [Invalid menu choice](#test-case-16-invalid-menu-choice) | Pass |
| 17 | [Corrupted data file](#test-case-17-corrupted-data-file) | Pass |

## Test Case 1: Add a valid book

**Scenario:** Library file is empty. Add book ID 101.

**Input (in order):** `1`, `101`, `Let Us C`, `Yashavant Kanetkar`, `2`, `7`

**Output:**

```
0 book(s) loaded from file.
Enter your choice (1-7): 1
Enter book ID (positive number): 101
Enter title: Let Us C
Enter author: Yashavant Kanetkar
Book added successfully.
Enter your choice (1-7): 2
ID      Title                           Author                  Status
------------------------------------------------------------------------
101     Let Us C                        Yashavant Kanetkar      Available
Total books: 1
Enter your choice (1-7): 7
Thank you. Goodbye!
```

**Result:** Pass

---

## Test Case 2: Duplicate book ID (invalid input)

**Scenario:** Library has books 101, 102, 103. Add ID 101 again.

**Input (in order):** `1`, `101`, `Dup Book`, `X`, `7`

**Output:**

```
3 book(s) loaded from file.
Enter your choice (1-7): 1
Enter book ID (positive number): 101
Enter title: Dup Book
Enter author: X
Error: A book with ID 101 already exists. IDs must be unique.
Enter your choice (1-7): 7
Thank you. Goodbye!
```

**Result:** Pass

---

## Test Case 3: Non-numeric book ID (invalid input)

**Scenario:** Library has books 101, 102, 103. Enter ID `abc`.

**Input (in order):** `1`, `abc`, `7`

**Output:**

```
3 book(s) loaded from file.
Enter your choice (1-7): 1
Enter book ID (positive number): abc
Error: ID must be a positive whole number.
Enter your choice (1-7): 7
Thank you. Goodbye!
```

**Result:** Pass

---

## Test Case 4: Boundary value: ID 0

**Scenario:** Library has books 101, 102, 103. Enter ID `0`.

**Input (in order):** `1`, `0`, `7`

**Output:**

```
3 book(s) loaded from file.
Enter your choice (1-7): 1
Enter book ID (positive number): 0
Error: ID must be a positive whole number.
Enter your choice (1-7): 7
Thank you. Goodbye!
```

**Result:** Pass

---

## Test Case 5: Empty title (invalid input)

**Scenario:** Library has books 101, 102, 103. Add ID 104 and leave the title blank.

**Input (in order):** `1`, `104`, *(blank)*, `7`

**Output:**

```
3 book(s) loaded from file.
Enter your choice (1-7): 1
Enter book ID (positive number): 104
Enter title: 
Error: this field cannot be empty.
Enter your choice (1-7): 7
Thank you. Goodbye!
```

**Result:** Pass

---

## Test Case 6: Search a book by ID

**Scenario:** Library has books 101, 102, 103. Search ID 102.

**Input (in order):** `3`, `102`, `7`

**Output:**

```
3 book(s) loaded from file.
Enter your choice (1-7): 3
Enter book ID: 102
ID      Title                           Author                  Status
------------------------------------------------------------------------
102     The C++ Programming Language    Bjarne Stroustrup       Available
Enter your choice (1-7): 7
Thank you. Goodbye!
```

**Result:** Pass

---

## Test Case 7: Search a book by title (case-insensitive, partial)

**Scenario:** Library has books 101, 102, 103. Search `CLEAN`.

**Input (in order):** `4`, `CLEAN`, `7`

**Output:**

```
3 book(s) loaded from file.
Enter your choice (1-7): 4
Enter title (or part of it): CLEAN
ID      Title                           Author                  Status
------------------------------------------------------------------------
103     Clean Code                      Robert C. Martin        Available
Enter your choice (1-7): 7
Thank you. Goodbye!
```

**Result:** Pass

---

## Test Case 8: Search with an unknown ID

**Scenario:** Library has books 101, 102, 103. Search ID 999.

**Input (in order):** `3`, `999`, `7`

**Output:**

```
3 book(s) loaded from file.
Enter your choice (1-7): 3
Enter book ID: 999
No book found with ID 999.
Enter your choice (1-7): 7
Thank you. Goodbye!
```

**Result:** Pass

---

## Test Case 9: Issue an available book

**Scenario:** Book 101 is available. Issue it.

**Input (in order):** `5`, `101`, `2`, `7`

**Output:**

```
3 book(s) loaded from file.
Enter your choice (1-7): 5
Enter ID of the book to issue: 101
Book 'Let Us C' issued successfully.
Enter your choice (1-7): 2
ID      Title                           Author                  Status
------------------------------------------------------------------------
101     Let Us C                        Yashavant Kanetkar      Issued
102     The C++ Programming Language    Bjarne Stroustrup       Available
103     Clean Code                      Robert C. Martin        Available
Total books: 3
Enter your choice (1-7): 7
Thank you. Goodbye!
```

**Result:** Pass

---

## Test Case 10: Issue a book that is already issued

**Scenario:** Book 101 is already issued. Try to issue it again.

**Input (in order):** `5`, `101`, `7`

**Output:**

```
3 book(s) loaded from file.
Enter your choice (1-7): 5
Enter ID of the book to issue: 101
Error: Book 'Let Us C' is already issued.
Enter your choice (1-7): 7
Thank you. Goodbye!
```

**Result:** Pass

---

## Test Case 11: Issue a book with an unknown ID

**Scenario:** Library has books 101, 102, 103. Issue ID 999.

**Input (in order):** `5`, `999`, `7`

**Output:**

```
3 book(s) loaded from file.
Enter your choice (1-7): 5
Enter ID of the book to issue: 999
Error: No book found with ID 999.
Enter your choice (1-7): 7
Thank you. Goodbye!
```

**Result:** Pass

---

## Test Case 12: Return a book that was not issued

**Scenario:** Book 102 is available. Try to return it.

**Input (in order):** `6`, `102`, `7`

**Output:**

```
3 book(s) loaded from file.
Enter your choice (1-7): 6
Enter ID of the book to return: 102
Error: Book 'The C++ Programming Language' was not issued, so it cannot be returned.
Enter your choice (1-7): 7
Thank you. Goodbye!
```

**Result:** Pass

---

## Test Case 13: Return an issued book

**Scenario:** Book 101 is issued. Return it.

**Input (in order):** `6`, `101`, `2`, `7`

**Output:**

```
3 book(s) loaded from file.
Enter your choice (1-7): 6
Enter ID of the book to return: 101
Book 'Let Us C' returned successfully. It is now available.
Enter your choice (1-7): 2
ID      Title                           Author                  Status
------------------------------------------------------------------------
101     Let Us C                        Yashavant Kanetkar      Available
102     The C++ Programming Language    Bjarne Stroustrup       Available
103     Clean Code                      Robert C. Martin        Available
Total books: 3
Enter your choice (1-7): 7
Thank you. Goodbye!
```

**Result:** Pass

---

## Test Case 14: Data persists after closing and reopening

**Scenario:** Run 1: issue book 103 and exit. Run 2: start the program again and display all books.

**Input (in order):** `5`, `103`, `7`  
**Input for run 2:** `2`, `7`

**Output (run 1):**

```
3 book(s) loaded from file.
Enter your choice (1-7): 5
Enter ID of the book to issue: 103
Book 'Clean Code' issued successfully.
Enter your choice (1-7): 7
Thank you. Goodbye!
```

**Output (run 2):**

```
3 book(s) loaded from file.
Enter your choice (1-7): 2
ID      Title                           Author                  Status
------------------------------------------------------------------------
101     Let Us C                        Yashavant Kanetkar      Available
102     The C++ Programming Language    Bjarne Stroustrup       Available
103     Clean Code                      Robert C. Martin        Issued
Total books: 3
Enter your choice (1-7): 7
Thank you. Goodbye!
```

**Result:** Pass

---

## Test Case 15: Missing data file at startup

**Scenario:** No `books.txt` file exists. Start the program and display all books.

**Input (in order):** `2`, `7`

**Output:**

```
File not found. Starting with an empty library.
Enter your choice (1-7): 2
No books in the library.
Enter your choice (1-7): 7
Thank you. Goodbye!
```

**Result:** Pass

---

## Test Case 16: Invalid menu choice

**Scenario:** Enter `9`, `hello` and `0` as menu choices.

**Input (in order):** `9`, `hello`, `0`, `7`

**Output:**

```
3 book(s) loaded from file.
Enter your choice (1-7): 9
Invalid choice. Please enter a number from 1 to 7.
Enter your choice (1-7): hello
Invalid choice. Please enter a number from 1 to 7.
Enter your choice (1-7): 0
Invalid choice. Please enter a number from 1 to 7.
Enter your choice (1-7): 7
Thank you. Goodbye!
```

**Result:** Pass

---

## Test Case 17: Corrupted data file

**Scenario:** The file has a garbage line, a duplicate ID, a non-numeric ID, a bad status value and a blank line mixed with 2 valid records.

**Input (in order):** `2`, `7`

**Output:**

```
2 book(s) loaded from file.
Enter your choice (1-7): 2
ID      Title                           Author                  Status
------------------------------------------------------------------------
101     A Valid Book                    Author One              Available
103     Another Valid                   Author Two              Issued
Total books: 2
Enter your choice (1-7): 7
Thank you. Goodbye!
```

**Result:** Pass
