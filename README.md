<div align="center">

# xdsa

</div>

<details open="open">
<summary>Table of Contents</summary>

- [xdsa](#default)
  - [🧠 About](#-about)
  - [📁 Directory Structure](#-directory-structure)
  - [🛠️ Usage](#️-usage)
    - [💻 Installation](#-installation)
    - [🔧 Build the project](#-build-the-project)
    - [🧹 Clean build files](#-clean-build-files)
    - [🏃 Run the executable](#-run-the-executable)
  - [🧪 Running Tests](#-running-tests)
  - [📄 Dependencies](#-dependencies)
  - [📚 Documentation](#-documentation)
  - [🙌 Contributing](#-contributing)
  - [🪪 License](#-license)
  - [👤 Author](#-author)
  - [Acknowledgements](#acknowledgements)

</details>

## 🧠 About

xdsa is a C project that [brief description of what your program does].

It's written in standard C (C99) and uses GNU Make for building. The goal of this project is to [insert goal or motivation, e.g., build a simple CLI tool, implement data structures from scratch, etc.].

## 📁 Directory Structure

```bash
xdsa/
├── src/            # Source files
├── include/        # Header files
├── build/          # Build artifacts (created after make)
├── Makefile        # Build system
├── README.md       # This file
└── main.c          # Entry point (if not inside src/)
```

## 🛠️ Usage

### 💻 Installation

Clone the repository.

```bash
git clone git@github.com:ragibasif/xdsa.git
```

Make sure you have `gcc` and `make` installed.

### 🔧 Build the project

```bash
make
```

### 🧹 Clean build files

```bash
make clean
```

### 🏃 Run the executable

```bash
./build/xdsa
```

> The executable will be built inside the `build/` directory.

## 🧪 Running Tests

If you have a test suite:

```bash
make test
```

Or you can manually compile and run test files like:

```bash
gcc -Iinclude tests/test_foo.c src/foo.c -o test_foo
./test_foo
```

## 📄 Dependencies

This project uses:

- C99 Standard
- GNU Make
- (Optional) Any libraries you're using (e.g., `glib`, `SDL2`, etc.)

## 📚 Documentation

- All headers are documented in the `include/` folder.
- Inline comments are included in the source files.
- [Optional] Use `doxygen` if you plan to generate documentation.

## 🙌 Contributing

1. Fork the repository
2. Create a new branch (`git checkout -b feature/feature-name`)
3. Make your changes and commit (`git commit -am 'Add new feature'`)
4. Push to your fork (`git push origin feature/feature-name`)
5. Open a pull request

## 🪪 License

This project is licensed under the **MIT license**. See the [LICENSE](LICENSE) file for details.

## 👤 Author

[Ragib Asif](https://github.com/ragibasif)

## Acknowledgements
