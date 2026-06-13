<div align="center">

# 🧠 Smart Pointers & `shared_ptr` / `weak_ptr` in Modern C++

**A hands-on lab series exploring shared ownership, cyclic dependencies, and safe observer patterns**

![C++](https://img.shields.io/badge/C%2B%2B-17-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Platform](https://img.shields.io/badge/Platform-Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)
![Compiler](https://img.shields.io/badge/Compiler-MinGW%20GCC-F16522?style=for-the-badge&logo=gnu&logoColor=white)
![License](https://img.shields.io/badge/License-Educational-green?style=for-the-badge)

---

> *"Shared ownership is powerful, but only when it is managed deliberately."*

</div>

---

## 📖 Overview

This repository is a **progressive lab series** that teaches C++ smart pointer ownership patterns using `shared_ptr` and `weak_ptr`. It starts with shared ownership problems and then moves into practical solutions for dangling references, memory leaks, and cyclic dependencies.

```
  raw pointers  ──►  shared_ptr  ──►  weak_ptr observer  ──►  cyclic dependency resolver
      §01              §02              §03 / §04                §05
```

---

## 🗂️ Course Structure

| # | Section | Core Concepts | Status |
|---|---------|---------------|--------|
| 01 | [Introduction](#-section-01--introduction) | raw pointers, ownership ambiguity, observer patterns | ✅ |
| 02 | [Shared Ptr Fundamentals](#-section-02--shared-ptr-fundamentals) | `std::shared_ptr`, reference counting, double delete | ✅ |
| 03 | [Replacing Raw Ptrs With Shared](#-section-03--replacing-raw-ptrs-with-shared) | `shared_ptr` for ownership, avoiding leaks, dangling pointer fixes | ✅ |
| 04 | [Practical Usage](#-section-04--practical-usage) | custom deleters, managing non-heap resources | ✅ |
| 07 | [Weak Ptrs](#-section-07--weak-ptrs) | `std::weak_ptr`, safe observing, breaking cycles | ✅ |

---

## 🔬 Section 01 — Introduction

> The first step is understanding why raw pointers are dangerous when ownership is unclear.

This section shows how ordinary pointers can lead to dangling references and accidental lifetime violations when objects are shared between owners and observers.

**Key lessons:**
- raw pointers do not express ownership
- multiple owners require explicit lifetime management
- observer relationships should not extend ownership

---

## 🔬 Section 02 — Shared Ptr Fundamentals

> Shared ownership with automatic reference counting.

`std::shared_ptr` allows multiple owners to share one resource. It uses a control block to track ownership, and the resource is destroyed once the last owning pointer goes away.

**Key concepts:**
- shared ownership semantics
- reference count tracking with `use_count()`
- avoiding double deletion

```cpp
auto ptr = std::make_shared<int>(10);
auto alias = ptr;          // both share ownership
std::cout << ptr.use_count(); // 2
```

---

## 🔬 Section 03 — Replacing Raw Ptrs With Shared

> Replace manual lifetime management with shared ownership.

This section converts raw pointers into `shared_ptr` so object lifetimes are tied to actual owners rather than scattered raw references.

**Topics covered:**
- uninitialized pointers
- dangling pointer elimination
- leak prevention with `shared_ptr`
- polymorphism and containers with `shared_ptr`

---

## 🔬 Section 04 — Practical Usage

> Use smart pointers for real resources, not just heap objects.

This section covers custom cleanup actions and how to manage resources that are not plain `delete` targets.

```cpp
std::unique_ptr<FILE, decltype(fileDeleter)> file(
    fopen("data.txt", "r"), fileDeleter);
```

**Takeaways:**
- custom deleters for non-heap resources
- using `shared_ptr` with file handles or C APIs
- safe cleanup in RAII style

---

## 🔬 Section 07 — Weak Ptrs

> A non-owning observer for shared resources.

`std::weak_ptr` breaks cycles and lets you hold a reference without extending lifetime. It is ideal for caches, observers, and parent/child links where ownership should remain unidirectional.

**What it solves:**
- preventing dangling observers
- detecting expired resources safely
- breaking cyclic `shared_ptr` ownership graphs

```cpp
std::weak_ptr<Node> backRef = forwardRef;
if (auto locked = backRef.lock()) {
    locked->doSomething();
}
```

---

## 🧠 Why this repo exists

Modern C++ is not just about syntax — it is about expressing ownership correctly.

This lab series helps you understand:
- when to use `shared_ptr` vs. `weak_ptr`
- why `weak_ptr` is the right tool for observers
- how cycles silently leak memory without a weak observer
- how to keep ownership graphs clear and safe

---

## 🛠️ Build Instructions

Each lab is a standalone `main.cpp`. Use VS Code with the provided `.vscode/tasks.json`, or compile directly with MinGW.

### Using VS Code
Open a lab file and press **Ctrl+Shift+B**.

### From the terminal

```powershell
cd e:\Courses\smart-pointers-shared-weak-ptr-cpp
g++ -std=c++17 -fdiagnostics-color=always -g \
    Section07_Weak_Ptrs\05_weak_ptrs_cyclic_depedency\main.cpp \
    -o Section07_Weak_Ptrs\05_weak_ptrs_cyclic_depedency\main.exe
.\Section07_Weak_Ptrs\05_weak_ptrs_cyclic_depedency\main.exe
```

> Make sure to keep `-std=c++17` for modern pointer syntax and `weak_ptr` support.

---

## 📋 Code Style

Labs follow a consistent structure:
- file header with `@file`, `@brief`, `@author`, `@date`
- section banners for includes, types, functions, globals
- `using namespace std;`
- `main()` only calls demo logic
- placeholder `/* None */` for empty sections

---

## 📚 Further Reading

- [cppreference: `std::shared_ptr`](https://en.cppreference.com/w/cpp/memory/shared_ptr)
- [cppreference: `std::weak_ptr`](https://en.cppreference.com/w/cpp/memory/weak_ptr)
- [cppreference: `std::make_shared`](https://en.cppreference.com/w/cpp/memory/shared_ptr/make_shared)
- [ISO C++ Smart Pointers](https://isocpp.org/wiki/faq/freestore-mgmt)

---

<div align="center">

Made with 💙 for C++ learners.

</div>
