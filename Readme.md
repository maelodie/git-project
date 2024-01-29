# Pseudo-Git 

Pseudo_Git is a simulation of the Git version control system developed in the C programming language. The project aims to provide a tool duplicating the git functionalities as commits and managing branches by utilizing data structures primarily based on linked lists and hash tables. The implementation also leverages bash functions and some library functions, such as stat and dirent.

## Installation
Start by cloning the project. When finished, execute the following command:
```
make
```
This will compile and link all necessary files into a single executable called `myGit`. You can know use the commands described below.

## Usage and main functionalities
To execute  the main functionalities of Pseudo-Git, you need to use the command line:
```
/bin./myGit  [command] [arguments...]
```

or go in the bin directory and use: 

```
./myGit [command] [arguments...]
```

The commands available are:

### Initialization:
- **init** : initializes a new repository with empy references.
- **list-refs**:  lists all refs in the repository. 
- **create-ref <name> <hash>**: creates a new reference named <name> that points to the commit identified by <hash>.
- **delete-ref <name>** : deletes the reference named <name>.

### Commits
- **add <elem> [<elem2> <elem3> ...]**: adds one or more files or directories to the staging area to be included in the next commit.
- **list-add**: displays the contents of the staging area.
- **clear-add**: clears the staging area, removing all added files and directories.
- **commit <branch_name> -m message**: commits changes to a branch named <branch_name> with an optional commit message <message>.

### Branch management
- **get-current-branch**: displays the currently active branch.
- **checkout-branch**: switches between branches.
- **checkout-commit <pattern>**: restores commits that begin with the specified <pattern>.