#!/bin/bash

#
# This script is meant to be called via "make memcheck"
#
# Put no more than 4 bots you want to test into $bots_dir
# and run `make memcheck` to do all the functional testing
#
# Leaks' reports will be saved into $logs_dir
#

# Specify where to store logs
declare logs_dir="${PWD}/logs/leaks"

# Specify where to look for bots
declare bots_dir="${PWD}/bots"

# Must be global
declare -a bots=()
declare program=""

get_bots()
{
    declare -i n_bots

    [[ -d $bots_dir ]] || { mkdir "${bots_dir}"; echo -e "Dir ${bots_dir} was created; put no more than 4 bots there." >&2; exit 1; }
    bots=($(for bot in $(ls "${bots_dir}"); do echo $bot | sed -r ' s/(.s|.cor)$// '; done | uniq))
    n_bots=${#bots[@]}
    [[ $n_bots -le 4 && $n_bots -ge 1 ]] || { echo -e "Put 1 to 4 bots in the ${bots_dir}." >&2; exit 1; }
    echo -e "\nFound bots:"
    echo -e "--> ${bots[0]}"
    echo -e "--> ${bots[1]}"
    echo -e "--> ${bots[2]}"
    echo -e "--> ${bots[3]}"
    echo -e "-----------"
}

print_usage()
{
    echo -e "\nUsage: check_leaks [-a] [-v] [-r] [-h]\n"
    echo -e "Run valgrind against a list of bots specified in the script\n"
    echo -e "-a\tlog assembler leaks"
    echo -e "-v\tlog virtual machine leaks"
    echo -e "-r\tclear (remove) logs"
    echo -e "-h\tdisplay this help and exit"
}

log_leaks_using_valgrind()
{
    if [[ "$program" = "asm" ]]; then
        bot_name="$1"
        printf "\n%s bot: %s\n" "--->" "$bot_name"
        bot_path="${bots_dir}/${bot_name}.s"
        log_file="${logs_dir}/${program}_${bot_name}_valgrind.log"
        valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose \
            --log-file="${log_file}" \
            ./"$program" "$bot_path"
    elif [[ "$program" = "corewar" ]]; then
        echo -e ""
        log_file="${logs_dir}/${program}_"$(for bot in $(ls ${bots_dir}/*.cor); do printf "%s" $(basename -s .cor "${bot}")_; done)"valgrind.log"
        valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose \
            --log-file="${log_file}" \
            ./"$program" bots/*.cor
    else
        echo -e "Internal error: smth wrong with \`program\` var." >&2
        exit 1
    fi
    printf "%s Leaks report is saved to %s\n" "--->" "$log_file"
}

# TODO
log_leaks_using_leaks()
{
    printf "\n%s bot: %s\n" "--->" "$bot_name"
    bot_name="$1"
    if [[ "$program" = "asm" ]]; then
        bot_path="${bots_dir}/${bot_name}.s"
        iprofiler -leaks -d "${logs_dir}/${program}_${bot_name}_leaks.log" ./"$program" "$bot_path"
    else
        bot_path="${bots_dir}/${bot_name}.cor"
        iprofiler -leaks -d "${logs_dir}/${program}_${bot_name}_leaks.log" ./"$program" "${bots}"
    fi
    printf "%s Leaks report is saved to %s/%s_%s_leaks.log\n" "--->" "$logs_dir" "$program" "$bot_name"
}

run_memcheck()
{
    echo -e "\n<<<<< Checking leaks for ${program} >>>>>"
    if [[ "$program" = "asm" ]]; then
        for bot in "${bots[@]}"; do
            if command -v valgrind >/dev/null 2>&1; then
                log_leaks_using_valgrind "${bot}"
            elif command -v leaks >/dev/null 2>&1; then
                log_leaks_using_leaks "${bot}"
            else
                printf "%s Neither valgrind nor leaks utilities was found, aborting.\n" "--->"
                exit 1
            fi
        done
    elif [[ "$program" = "corewar" ]]; then
        if command -v valgrind >/dev/null 2>&1; then
            log_leaks_using_valgrind
        elif command -v leaks >/dev/null 2>&1; then
            log_leaks_using_leaks
        else
            printf "%s Neither valgrind nor leaks utilities was found, aborting.\n" "--->"
            exit 1
        fi
    fi
}

while getopts "avrh" opt; do
    case $opt in
        h)
            print_usage
            exit 0
            ;;
        a)
            [[ ! ${bots} ]] && get_bots
            [[ ! -d $logs_dir ]] && { mkdir -p "${logs_dir}"; echo -e "Created ${logs_dir} to store logs."; }
            program="asm" && run_memcheck
            ;;
        v)
            [[ ! ${bots} ]] && get_bots
            [[ ! -d $logs_dir ]] && { mkdir -p "${logs_dir}"; echo -e "Created ${logs_dir} to store logs."; }
            program="corewar" && run_memcheck
            ;;
        r)
            if [[ -d $logs_dir ]]; then
                rm -rf "${logs_dir}" && echo -e "Removed ${logs_dir}."
            else
                echo -e "${logs_dir} is absent."
            fi
            exit 0
            ;;
        *)
            print_usage >&2
            exit 1
            ;;
    esac
done

if [[ ! "$program" = "asm" && ! "$program" = "corewar" ]]; then
    print_usage >&2
    exit 1
fi

exit 0