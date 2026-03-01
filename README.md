# Simple Client Manager

Basic application developed in **C** and using **SQLITE** to manage a database with clients data (id, name, email and unencrypted password).

---

## Functions

- Client register
- Edit client data
- Delete client data
- No graphical interface

---

## Used Technologies

- **C**
- **SQLite (Relational database)**

---

## Project Structure

```
├───.vscode
├───build       → Executable File
├───include     → File headers
└───src         → Source files (.c) and database (.db)
```

## Data Table

- Id
- Name
- Email
- Password

---

## How to Execute

1. Clone the repository:

```bash
git clone https://github.com/dav-jsb/Gerenciador-Clientes-Simples.git
```

**OBS**: Make Sure you have a C compiler.

2. Compile the project:

- In terminal, write: 

```bash
make all
```

- If Linux, write:

```bash
make linux
```

3. Run the project:

- Double click the file **ClientManager.exe** or

- In terminal, write:

```bash
make run
```