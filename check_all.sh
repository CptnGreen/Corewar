#!/bin/bash

declare bot_dir="${PWD}/resources/vm_champs/champs"

declare -i check_leacks=0

# Specify bots here:

declare -a bots
bots[0]="${bot_dir}/Car.s"
bots[1]="${bot_dir}/Death.s"
bots[2]="${bot_dir}/Gagnant.s"
bots[3]="${bot_dir}/Survivor.s"

while getopts "p:hm" opt; do
    case $opt in
        p)
            if (( "${OPTARG}" > 0 && "${OPTARG}" < 5 )); then
                echo -e "Good num of players"
            else
                echo -e "Bad num of players"
                exit 1
            fi
            ;;
        h)
            echo -e "Usage: check_all [-m] [-p N] [-h]"
            exit 0
            ;;
        m)
            check_leaks=1
            ;;
        *)
            exit 1
            ;;
    esac
done

log_leaks()
{
    if command -v valgrind; then
        bot_path="$1"
        bot_name_with_ext="${bot_path##*/}"
        bot_name="${bot_name_with_ext%.s}"
        printf "bot_name: %s\n" "$bot_name"
        valgrind \
            --leak-check=full \
            --show-leak-kinds=all \
            --track-origins=yes \
            --verbose \
            --log-file="${bot_name}_leaks.txt" \
            ./asm "$1"
        printf "Leaks report is saved to %s_leaks.txt\n" "$bot_name"
    else
        echo -e "Failed to run memcheck, valgrind is not installed"
    fi
}

main()
{
    for bot in "${bots[@]}"; do
        [[ "$check_leaks" ]] && log_leaks "$bot"
        "${PWD}"/asm "$bot"
        echo -e "=============="
    done
    # vm "{bots[@]/.s$/.cor$}"
}

main
