#!/bin/bash

#
# This script is meant to be called via "make memcheck"
#
# Edit the list of bots your program to be checked against (below)
#

# Specify bots to be checked here:
declare -a bots
bots[0]="Car"
bots[1]="Death"
bots[2]="Gagnant"
bots[3]="Survivor"

declare bot_dir="${PWD}/resources/vm_champs/champs"
declare logs_dir="${PWD}/leaks_logs"

[[ ! -d $logs_dir ]] && mkdir -p "${logs_dir}"

declare program=""

print_usage()
{
    echo -e "\nUsage: check_leaks [-a] [-v] [-r] [-h]\n"
    echo -e "Run valgrind against a list of bots specified in the script\n"
    echo -e "-a\tlog assembler leaks"
    echo -e "-v\tlog virtual machine leaks"
    echo -e "-r\tclear (remove) logs"
    echo -e "-h\tdisplay this help and exit"
}

log_leaks()
{
    if command -v valgrind >/dev/null; then
        bot_name="$1"
        if [[ "$program" = "asm" ]]; then
            bot_path="${bot_dir}/${bot_name}.s"
        else
            bot_path="${bot_dir}/${bot_name}.cor"
        fi
        printf "\n%s bot: %s\n" "--->" "$bot_name"
        valgrind \
            --leak-check=full \
            --show-leak-kinds=all \
            --track-origins=yes \
            --verbose \
            --log-file="${logs_dir}/${program}_${bot_name}_leaks.log" \
            ./"$program" "$bot_path"
        printf "%s Leaks report is saved to %s/%s_%s_leaks.log\n" "--->" "$logs_dir" "$program" "$bot_name"
    else
        echo -e "Failed to run memcheck, valgrind is not installed\n" >&2
    fi
}

run_memcheck()
{
    if [[ "$program" = "asm" || "$program" = "vm" ]]; then
        echo -e "\n*** Checking leaks for ${program} ***"
        for bot in "${bots[@]}"; do
            log_leaks "${bot}"
        done
    fi
}

while getopts "avrh" opt; do
    case $opt in
        h)
            print_usage
            exit 0
            ;;
        a)
            program="asm" && run_memcheck
            ;;
        v)
            program="vm" && run_memcheck
            ;;
        r)
            rm -rf "${logs_dir}"
            exit 0
            ;;
        *)
            print_usage >&2
            exit 1
            ;;
    esac
done

if [[ ! "$program" = "asm" && ! "$program" = "vm" ]]; then
    print_usage >&2
    exit 1
fi

exit 0