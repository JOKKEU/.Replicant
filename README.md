# .Replicant
Program for searching files in the Linux system. Output to console or file.

install: 
```
git clone https://github.com/JOKKEU/.Replicant
cd .Replicant
if install.sh - non executable file: sudo chmod +x install.sh
./install.sh
output:
[+] directory created
[+] moved to -> build
[+] g++ found
[+] program compiled
[sudo] password for jokkeu: 
[+] program copied to /usr/local/bin
===== PROG INSTALLED =====
[+] run program (global scope) -> Replicant
[+] Usage: Replicant --help

```
Usage: Replicant --help
```
output:
Usage: <program> [options]
IF NOT OPTIONS - OUTPUT TO CONSOLE
OPTIONS: 
--help - display this help message
write to file:
program wto filename - create and write to file
program wato filename - create and appending to file
```
Start
```
Example:
Replicant      <- output to terminal
Output:
Found: 6
[1] "/home/jokkeu/Desktop/replicant_find/main.cpp"
[2] "/home/jokkeu/Desktop/replicant_find/print_logo.cpp"
[3] "/home/jokkeu/Desktop/replicant_find/start.cpp"
[4] "/home/jokkeu/Desktop/replicant_find/class_file.cpp"
[5] "/home/jokkeu/Desktop/replicant_find/finds.cpp"
[6] "/home/jokkeu/Desktop/replicant_find/console_loading.cpp"
```
P.S: For a broader search coverage, use "sudo Replicant [options]"

