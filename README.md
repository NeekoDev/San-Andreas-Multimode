# San Andreas Multimode

## Getting started

### Requirements

To get started with San Andreas Multimode, you need the following tools installed on your computer :

- [Visual Studio Code](https://code.visualstudio.com/) *To avoid encoding or other worries, it is better to use this editor*
- [sampctl](https://github.com/Southclaws/sampctl) - *It includes a package manager, a build tool and a configuration manager*
- [MariaDB](https://mariadb.org/download/) or [MySQL](https://dev.mysql.com/downloads/mysql/) - *For the server data persistency*

## Installation

### Clone the repository

```bash
git clone https://github.com/NeekoGta/San-Andreas-Multimode.git
```

### Download dependencies (includes, plugins, etc)

```bash
sampctl package ensure
```

### Import database schema

...

### Build Gamemode

```bash
sampctl package build
```

### Run server

```bash
sampctl package run
```

## ToDo