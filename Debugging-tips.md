# How to Write More Professional C++  

This section collects lessons, patterns, and practices that push your C++ beyond classroom code into something closer to what professionals write in industry.  

---

## Topics  


---
ideas:
- templates?
- vectors?
- classes?
- auto?

- **Smart Pointers & Ownership**  
  - [`unique_ptr` example](./articles/unique-ptr.md)  
  - [`shared_ptr` example](./articles/shared-ptr.md)  

- **Initialization & Type Deduction**  
  - [Uniform initialization `{}`](./articles/initialization.md)  
  - [`auto` and modern type deduction](./articles/auto.md)  

- **Safer Abstractions**  
  - [`std::optional` instead of sentinel values](./articles/optional.md)  
  - RAII: Resource Acquisition Is Initialization  
  - Using `chrono` for time instead of `clock_t`  

- **Containers & Iterators**  
  - Prefer `std::vector` over raw arrays  
  - Range-based for loops  

- **General Best Practices**  
  - Keep headers minimal (`.h` only for declarations)  
  - Use namespaces to avoid name collisions  
  - Separate interface from implementation (`.h` vs `.cpp`)  
  - Avoid macros; prefer `constexpr`, `inline`, or templates  

---

## Suggested Reading  

- [ISO C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)  
- [CppReference](https://en.cppreference.com/)  
- [LearnCpp.com](https://www.learncpp.com/)  

---

👉 Add more `.md` files for each topic (like `unique-ptr.md`, `auto.md`, etc.), and link them here. GitHub Pages will render them as proper HTML without you writing HTML manually.  

---
