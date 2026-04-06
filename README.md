# Algorithms and Data Structures 101


This repository contains the source code of two graded assignment completed as part of an introductory course in
**Algorithms and Data Structures** at **UTC** during the **Fall 2022** semester. 

While the assignments are introductory in scope, the project is an opportunity to demonstrate how software engineering practices such as testing, version control, and automation, can be applied.

## Graded Assignments

The following sections contain the instructions for both assignments. Each set of instructions includes an API, an implied list of expected functionalities, and descriptions of the data structures to be handled.

Each assignment was to be completed within a two-weeks period by groups of two. In addition to the source code, students were required to write a short report demonstrating the time complexity of each implemented function.

To preserve the confidentiality of the original academic material, the following assignment instructions are descriptions based on the original, rather than exact reproductions.

### Sparse Matrix
This assignment is based on an exam exercise proposed in 2016. Its goal is to familiarize students with **linked lists** and their operations.

A matrix is called sparse when the number of elements equal to zero is greater than the number of non-zero elements. As such, to save memory, it is possible to represent such a matrix by only keeping in memory the non-zero elements. 

A matrix of size **N*M** is represented by an array of **N** linked lists each holding the non-zero elements of a row, ordered by their column index. Each node of a linked list contains the column index and the value of the element.

The following functionalities were to be implemented:

- Fill a given matrix with user input
- Display a given matrix
- Search for a value in a matrix
- Put a value in a matrix, including zeroes
- Add two matrices, saving the result in the first matrix
- Compute the memory saved by using a linked list representation instead of a standard matrix

Finally, allocated memory must be deallocated properly.
### Patient indexer
The goal of this assignment is to familiarize students with **binary search trees** and their operations. 

A doctor wishes to implement a system to store their patients' medical records. The records are ordered by their patient last names. It is assumed that each last name is unique.

A patient record is represented by the patient's first and last name, as well as the number and list of their appointments.

An appointment is represented by its date, reason, and the emergency level, stored as an integer.

The following functionalities were to be implemented:
- Create and insert a patient into the tree
- Search for a patient
- Display a patient's file
- Display all patients using an inorder traversal
- Create an appointment for a patien
- Delete a patient
- Manage a backup tree

Finally, allocated memory must be deallocated properly.

## Quality and Continuous Integration process

### Branchin Strategy 
This repository follows a **Gitflow** branching strategy with the following structure:

#### Main Branches
- ``main``: The production branch. Code in this branch should be stable and tested.

#### Assigment Branches
Behave as it would be expected of a ``develop`` branch. To keep both assignment development isolated, each assigment has a dedicated branch:

- ``linked_list_assignment``: Development branch for the Sparse Matrix assignment implementation. Feature development and bug fixes for this assignment are integrated here before final merging to ``main``.

- ``bst_assignment``: Development branch for the Patient Indexer assignment implementation. Follows the same workflow as ``linked_list_assignment``

### Static Code Analysis

### Build Verification

### Automated Testing

## Usage
TODO

<br/>

## Licence

The source code present in this repository is distributed under the MIT [license](https://github.com/yannickLonjarret/data-structures-101/blob/main/LICENSE).