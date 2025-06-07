# Linear Algebra & Regression Project

## 👨‍🎓 Student Info
- **Name:** [Phan Anh Minh]
- **Student ID:** [10423191]
- **Course:** Programming 2 (Summer Semester - Year 2)

---

## 📌 Project Overview
**Who?**

Hello! I'm Phan Anh Minh, a second-year Computer Science of the Vietnamese-German University, I'm from group 1. Within this course, I've learned a lot about Programming, specifically, Object Oriented Programming (OOP) using C++.  
Within the instruction of Professor Huynh Trung Hieu, I've had the opportunity to take on this project called "tiny project", and I'm very glad that I have completed this myself.

**What?**

This project demonstrates the implementation of **core linear algebra structures and algorithms** using C++, as well as applying them to solve a **real-world linear regression problem**.

**When?**

I took my very first step into building "vector.h" somewhere between May 26 - May 30, and June 6 is the day that completed this project, I would say it took about 2 weeks.

**Where?** 

For most of the time I did this project either at my house, or at the VGU's dormitory.

**How?**

I used Visual Studio Code as my one and only text editor, for compiling and running C++ I used Intellisence and c++ gdb, also extensions like "C/C++ for Visual Studio Code" and "Code Runner" provided by VS Code.
I do use chat GPT to answer a lot of questions, and I do acknowledge that it is not suggested to do things like copy code. However, I did ask for help regarding topics that I haven't learned about such as Moore Penrose and Tikhonov.

**Why?**
- Sharpen my understanding and skills on C++ in general and OOP to be precise
- Review what we've learned so far as well as prepare for the final exam
- Bonus points (I don't know about the bonus points at the time I started this project)

Below is the file structure of the project, please note that it does not prove chronological order, meaning from top-to-bottom is not the same as I'm doing that file first. In the working period, I accidentally deleteted some .cpp files, and when I created it back, it appears at random order in the structure, and I have no idea how to arrange it.
Despite how the final file structure looks, I have followed strictly the order given in the tiny_project instructions, that is from vector -> matrix -> linear system -> posSymLinSystem -> part B. 

---
### 📁 File Structure

```
.vscode/
├── launch.json
├── settings.json
├── tasks.json
├── data/
│   ├── machine.data
├── src/
│   ├── linearSystem.cpp
│   ├── linearSystem.h
│   ├── machine.names
│   ├── main.cpp
│   ├── main.exe
│   ├── matrix.cpp
│   ├── matrix.h
│   ├── posSymLinSystem.cpp
│   ├── posSymLinSystem.h
│   ├── readfile.cpp
│   ├── readfile.h
│   ├── vector.cpp
│   ├── vector.h
│
│
└── README.md
```


## 🧱 Part A: Linear Algebra Classes

**Note:** This is an overview of what each class has and its features. It's not meant to list everything in the class. Features such as assert and import will not be included.

## 1. Vector Class

The `Vector` class implements a dynamic 1D array with manual memory management and 1-based indexing. Key features include:

- **Operator Overloading**:
  - `+`, `-` for vector addition and subtraction  
  - `*` for scalar multiplication  
  - `-` (unary) for vector negation  
  - `=` for deep copy assignment  
- **Element Access**:
  - `[]` and `()` operators for reading/writing elements with bounds checking  
- **Memory Handling**:
  - Uses `new` and `delete` to allocate and deallocate memory  
  - Implements deep copy constructor and destructor

## 2. Matrix Class

The `Matrix` class supports 2D arrays with rich matrix operations and numerical computations:

- **Operator Overloading**:
  - `+`, `-` for matrix addition/subtraction  
  - `*` for scalar and matrix multiplication  
- **Element Access**:
  - `()` operator for 1-based element access  
- **Matrix Computations**:
  - Determinant (recursive Laplace expansion)  
  - Transpose  
  - Adjugate matrix  
  - Inverse (for square matrices)  
  - Moore-Penrose pseudo-inverse (for non-square matrices)

### 3. `LinearSystem` Class
Solves systems of linear equations `Ax = b` using multiple techniques, ranging from classical Gaussian Elimination to advanced methods like Moore-Penrose pseudo-inverse and Tikhonov regularization.

- **Core Attributes:**
  - `mpA`: pointer to the matrix \( A \)
  - `mpb`: pointer to the right-hand side vector \( b \)
  - `mSize`: size of the system (number of equations)

- **Provided Methods:**

#### 🔹 a. Gaussian Elimination
- **Function:** `Solve()`
- **Technique:** Forward elimination + back substitution with partial pivoting.
- **Use Case:** Solving square, non-singular systems.
- **Limitation:** Fails for singular or ill-conditioned matrices.

#### 🔹 b. Moore-Penrose Pseudo-Inverse
- **Function:** `SolvebyMoorePenrose()`
- **Purpose:** Solves over- or under-determined systems using least-squares approximation.
- **Formulas:**
  - Over-determined (\( m > n \)):
    \[
    x = (A^T A)^{-1} A^T b
    \]
  - Under-determined (\( m < n \)):
    \[
    x = A^T (A A^T)^{-1} b
    \]
- **Use Case:** Real-world data where `A` is not square or inconsistent.
- **Advantage:** Stable solution for ill-posed problems.

#### 🔹 c. Tikhonov Regularization (Ridge Regression)
- **Function:** `SolvebyTikhonov(double lambda)`
- **Purpose:** Regularizes ill-conditioned systems to avoid overfitting or noise amplification.
- **Formula:**
  \[
  x = (A^T A + \lambda I)^{-1} A^T b
  \]
- **Where:**
  - \( \lambda \): Regularization parameter
  - \( I \): Identity matrix
- **Use Case:** Numerical stability in regression, especially when \( A^T A \) is close to singular.
- **Advantage:** Improves generalization by controlling variance.

> All methods are built upon custom `Matrix` and `Vector` classes with overloaded operators and 1-based indexing. Memory is manually managed using `new` and `delete` to enhance learning and control.
  

### 4. `PosSymLinSystem` (Derived Class)
Solves systems with **positive definite symmetric matrices** using:
- **Conjugate Gradient Method**
- Validates matrix symmetry

---

## 📊 Part B: Linear Regression on CPU Performance

### 🔗 Dataset
- Source: [UCI Machine Learning Repository](https://archive.ics.uci.edu/ml/datasets/Computer+Hardware)
- 209 samples, 6 predictive attributes
- Goal: Predict `PRP` (Published Relative Performance)

### 🧮 Regression Model
We solve the following equation:
PRP ≈ x1MYCT + x2MMIN + x3MMAX + x4CACH + x5CHMIN + x6CHMAX

- The training set (80%) is used to **estimate coefficients**
- The testing set (20%) is used to **evaluate predictions**
- Solved using **Tikhonov Regularization**: x = (AᵗA + λI)^(-1) Aᵗb


### 📉 Evaluation
- Performance measured using **RMSE** (Root Mean Square Error)
- My Weight Vector: -0.00903028 0.020056 0.00257914 0.578622 2.40204 -0.38354
- My RMSE: 135.326

## 🛠️ How to Use

### ⚙️ Requirements
- C++ compiler (e.g., g++)
- Visual Studio Code (recommended, with C++ extensions)
- Dataset `machine.data` placed inside the `./data/` directory

---

### 🔧 Build & Run

Please use <**g++ main.cpp linearSystem.cpp matrix.cpp posSymLinSystem.cpp readfile.cpp vector.cpp -o main.exe**> to compile the code and <**./main.exe**> to run it

**Note:** the main.cpp already provided some code for testing, it includes: Matrix * vector, Solving Linear System and PosSymLinSystem, Symmetric checking, Solving linear system using Moore Penrose,
and all of Part B's testing.

### Testing

If you want to test other features, I recommend you to comment out the code in main.cpp **first** and do your testing, here are some codes for testing Matrix and Vector's operations:

    // Create another matrix for operations
    Matrix mat2(3, 3);
    mat2(1,1) = 9; mat2(1,2) = 8; mat2(1,3) = 7;
    mat2(2,1) = 6; mat2(2,2) = 5; mat2(2,3) = 4;
    mat2(3,1) = 3; mat2(3,2) = 2; mat2(3,3) = 1;

    cout << "Matrix mat2:\n";
    for (int i = 1; i <= mat2.GetNumRows(); ++i) {
        for (int j = 1; j <= mat2.GetNumCols(); ++j) {
            cout << mat2(i, j) << " ";
        }
        cout << "\n";
    }

    // Matrix addition and subtraction
    Matrix matAdd = mat + mat2;
    Matrix matSub = mat - mat2;

    cout << "mat + mat2:\n";
    for (int i = 1; i <= matAdd.GetNumRows(); ++i) {
        for (int j = 1; j <= matAdd.GetNumCols(); ++j) {
            cout << matAdd(i, j) << " ";
        }
        cout << "\n";
    }

    cout << "mat - mat2:\n";
    for (int i = 1; i <= matSub.GetNumRows(); ++i) {
        for (int j = 1; j <= matSub.GetNumCols(); ++j) {
            cout << matSub(i, j) << " ";
        }
        cout << "\n";
    }

    // Scalar multiplication and division on matrix
    double scalar = 2.0;
    Matrix matScalarMul = mat * scalar;


    cout << "mat * " << scalar << ":\n";
    for (int i = 1; i <= matScalarMul.GetNumRows(); ++i) {
        for (int j = 1; j <= matScalarMul.GetNumCols(); ++j) {
            cout << matScalarMul(i, j) << " ";
        }
        cout << "\n";
    }



    // Create a vector of size 3
    Vector vec(3);
    vec[1] = 10; vec[2] = 20; vec[3] = 30;

    cout << "Vector vec:\n";
    for (int i = 1; i <= vec.size(); ++i) {
        cout << vec[i] << " ";
    }
    cout << "\n";

    // Vector addition and subtraction
    Vector vec2 = vec;
    Vector add = vec + vec2;
    Vector sub = vec - vec2;

    cout << "vec + vec2:\n";
    for (int i = 1; i <= add.size(); ++i) {
        cout << add[i] << " ";
    }
    cout << "\n";

    cout << "vec - vec2:\n";
    for (int i = 1; i <= sub.size(); ++i) {
        cout << sub[i] << " ";
    }
    cout << "\n";

    // Scalar multiplication and division on vector
    Vector vecScalarMul = vec * scalar;


    cout << "vec * " << scalar << ":\n";
    for (int i = 1; i <= vecScalarMul.size(); ++i) {
        cout << vecScalarMul[i] << " ";
    }
    cout << "\n";


    // Multiply matrix by vector
    Vector result = mat * vec;
    cout << "Result of mat * vec:\n";
    for (int i = 1; i <= result.size(); ++i) {
        cout << result[i] << " ";
    }
    cout << "\n";

    cout << "--- End of Matrix and Vector tests ---\n";

## Conclusion

Through this project, I've learned a lot about programming in C++ and OOP, it will certainly help me in the final exam, but more importantly, my whole career. 
I want to say thankyou to Professor Huỳnh Trung Hiếu for providing me the opportunity and encouraging me with bonus points, you also guided me throughout my study period.
Thankyou for reading my README all the way through, I wish you all the best!
