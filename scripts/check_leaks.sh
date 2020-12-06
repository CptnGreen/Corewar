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

# Must be global:

declare -a bots=()
declare program=""

declare -i found_valgrind=0
declare -i found_leaks_util=0

get_checkers()
{
    printf "\nFound checkers:\n"
    command -v valgrind >/dev/null 2>&1 && { found_valgrind=1; printf "%s valgrind\n" "-->"; }
    command -v leaks >/dev/null 2>&1 && { found_leaks_util=1; printf "%s leaks\n" "-->"; }
    [[ $found_valgrind -eq 0 && $found_leaks_util -eq 0 ]] && { printf "Neither valgrind nor leaks utility were found, aborting.\n"; exit 1; }
    printf "%s\n" "-----------"
}

get_checkers

get_bots()
{
    declare -i n_bots

    [[ -d $bots_dir ]] || { mkdir "${bots_dir}"; echo -e "Dir ${bots_dir} was created; put no more than 4 bots there." >&2; exit 1; }
    mapfile -t bots < <(for bot in "${bots_dir}"/*.s; do basename "${bot}" | sed -E ' s/(.s|.cor)$// '; done | uniq)
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

log_leaks()
{
    declare valgr

    valgr=$(printf "valgrind %s %s %s %s" "--leak-check=full" "--show-leak-kinds=all" "--track-origins=yes" "--verbose")
    if [[ "$program" = "asm" ]]; then
        bot_name="$1"
        printf "\n%s bot: %s\n" "--->" "$bot_name"
        bot_path="${bots_dir}/${bot_name}.s"
        log_file="${logs_dir}/${program}_${bot_name}_valgrind.log"
        [[ $found_valgrind -eq 1 ]] && eval "${valgr} --log-file=${log_file} ./${program} ${bot_path}"
        log_file="${logs_dir}/${program}_${bot_name}_leaks.log"
        [[ $found_leaks_util -eq 1 ]] && eval "sh -c 'leaks $$ > "${log_file}" 2>&1; exec ./"${program}" "${bot_path}"'"
    elif [[ "$program" = "corewar" ]]; then
        echo -e ""
        log_file="${logs_dir}/${program}_"$(for bot in $(ls ${bots_dir}/*.cor); do printf "%s" $(basename -s .cor "${bot}")_; done)"valgrind.log"
        [[ $found_valgrind -eq 1 ]] && eval "${valgr} --log-file=${log_file} ./${program} bots/*.cor"
        log_file="${logs_dir}/${program}_"$(for bot in $(ls ${bots_dir}/*.cor); do printf "%s" $(basename -s .cor "${bot}")_; done)"leaks.log"
        [[ $found_leaks_util -eq 1 ]] && eval "sh -c 'leaks $$ > "${log_file}" 2>&1; exec ./"${program}" bots/*.cor'"
    else
        echo -e "Internal error: smth wrong with \`program\` var." >&2
        exit 1
    fi
    printf "%s Leaks report is saved to %s\n" "--->" "$log_file"
}

run_memcheck()
{
    [[ ! -d $logs_dir ]] && { mkdir -p "${logs_dir}"; echo -e "Created ${logs_dir} to store logs."; }
    echo -e "\n<<<<< Checking leaks for ${program} >>>>>"
    if [[ "$program" = "asm" ]]; then
        for bot in "${bots[@]}"; do
            log_leaks "${bot}"
        done
    elif [[ "$program" = "corewar" ]]; then
        log_leaks
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
            program="asm" && run_memcheck
            ;;
        v)
            [[ ! ${bots} ]] && get_bots
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