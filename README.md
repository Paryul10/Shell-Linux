## SHELL

This is a linux shell made in 'C'. 

## TO RUN 

Type the following commands after getting into the 'codes' directory

```sh
$ make
$ ./shell
```

- type 'quit' to exit the shell

## FEATURES

### CD

    
  - "cd (absolute path)" - goes to absolute path
  - "cd" - goes to ~/
  - "cd ~/(pathname)" - goes to ~/(pathname)
  - "cd .." - goes to previous directory
  - "cd ." - goes to same directory
 
### PWD

  - "pwd" - prints absolute path of present working directory

### LS


   - ls takes arguments as flags (in the form -(flagname))    and directories (in the form -(directory name)) in any   order.
   - It lists the files of all the directories mentioned,     in the form of option selected by the flags.
   - If there is no directory mentioned, it lists the files   of current directory

   - "ls" - lists in alphabetical order
   - "ls -a" - display hidden files
   - "ls -l" - long list
   - "ls -al"/"ls -la"/"ls -l -a"/"ls -a -l" - long list including hidden files

   - Similarities to real command: "ls -a" displays files     sorted in alphabetical order.

### PINFO


  - "pinfo" : prints the process related info of the           shell program
  - "pinfo " : prints the process info about given pid

  - pid --
  - Process status -- {R/S/S+/Z}
  - Memory
  - Executable path -- (Absolute path - includes ~/ if        executable is present inside the shell directory)



