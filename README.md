# 🌳 Tree Printer

A sleek C++ utility to **construct** and **beautifully render** binary trees as ASCII art with perfectly aligned `/` and `\` branches. 🚀💻📈✨

---

## 📖 Table of Contents

- [Overview](#overview)  
- [Features](#features)  
- [Installation](#installation)  
- [Usage](#usage)  
- [Input Format](#input-format)  
- [Example](#example)  
- [Source Code](#source-code)  

---

## 🔍 Overview

**Tree Printer** lets you interactively build any binary tree (nodes of type `string`, so you can use `int`, `char`, `float`, etc.) and prints it in a neat, hierarchical ASCII-art style. It centers the root, spaces siblings evenly, and draws branches under each parent—no external libraries needed.

---

## ✨ Features

- Interactive, line-by-line tree construction  
- Supports missing children (use `0` as a placeholder)  
- Automatic centering and spacing  
- Clean ASCII branches (`/` for left, `\` for right)  
- Zero extra banners or prompts—just the tree  

---

## 🛠 Installation

1. **Clone** or **download** this repo.  
2. Make sure you have a C++11-compatible compiler (e.g. g++).  

---

## 💻 Usage

### 1. Compile
```bash
g++ -std=c++11 treePrinter.cpp -o treePrinter
```
### 2. Run & Define Your Tree
```bash
./treePrinter
```
---


### Type your definitions one per line:

- First valid line sets the root (R above).
- Use 0 if a child is missing.
- Type end on its own line to finish input & render.

📝 Input Format
Parent -> Left,Right

- Parent, Left, Right : any string token (e.g. A, 42, foo).
- 0 denotes “no child.”
- The first valid line names the root.

🎉 Example
```bash
Input:
R -> A,B
A -> C,D
B -> E,F
C -> G,0
D -> H,I
end


Output:
       R
     /   \
    A     B
   / \   / \
  C   D E   F
 /     / \
G     H   I



