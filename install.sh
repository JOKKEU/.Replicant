#!/bin/bash

DIR_NAME="build"
PROG_NAME="Replicant"

if [ -d "$DIR_NAME" ]; then 
    echo "[+] dir exists, clearing dir"
    rm -rf "$DIR_NAME"
    mkdir "$DIR_NAME"
    echo "[+] directory created"
else 
    mkdir "$DIR_NAME"
    echo "[+] directory created"
fi

cd "$DIR_NAME" || exit
echo "[+] moved to -> $DIR_NAME"

if command -v g++ > /dev/null 2>&1; then
    echo "[+] g++ found"
    g++ -Wall -Werror -O2 ../main.cpp ../start.cpp ../print_logo.cpp ../class_file.cpp ../finds.cpp ../console_loading.cpp -o $PROG_NAME
    if [ $? -eq 0 ]; then 
        echo "[+] program compiled"
    else 
        echo "[-] compilation error"
        exit 1
    fi
else
    echo "[-] g++ not found, checking your OS"
    os_name=$(grep '^ID=' /etc/os-release | cut -d '=' -f2 | tr -d '"')
    
    if [[ "${os_name,,}" == "fedora" ]] || [[ "${os_name,,}" == "centos" ]]; then
        echo "[+] installing g++"
        sudo dnf install g++ -y  
        echo "[+] finished installing g++"
    elif [[ "${os_name,,}" == "ubuntu" ]] || [[ "${os_name,,}" == "kali" ]]; then
        echo "[+] installing g++"
        sudo apt install g++ -y
        echo "[+] finished installing g++"
    elif [[ "${os_name,,}" == "arch" ]]; then
        echo "[+] installing g++"
        sudo pacman -S g++ --noconfirm 
        echo "[+] finished installing g++"
    else
        echo "Could not determine your OS"
        exit 1
    fi

    g++ -Wall -Werror -O2 ../main.cpp ../start.cpp ../print_logo.cpp ../class_file.cpp ../finds.cpp ../console_loading.cpp -o $PROG_NAME
    if [ $? -eq 0 ]; then 
        echo "[+] program compiled"
    else 
        echo "[-] compilation error"
        exit 1
    fi
fi

sudo cp $PROG_NAME /usr/local/bin
echo "[+] program copied to /usr/local/bin"
echo "===== PROG INSTALLED ====="
echo "[+] run program (global scope) -> $PROG_NAME"
echo "[+] Usage: $PROG_NAME --help"
cd .. || exit
