#!/bin/bash

declare bot_dir="${PWD}/resources/vm_champs/champs"

# Specify bots here:

declare -a bots
bots[0]="${bot_dir}/Car.s"
bots[1]="${bot_dir}/Death.s"
bots[2]="${bot_dir}/Gagnant.s"
bots[3]="${bot_dir}/Survivor.s"

while getopts "p:h" opt; do
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
            echo -e "Usage: check_all [-p N] [-h]"
            exit 0
            ;;
        *)
            exit 1
            ;;
    esac
done

main()
{
    echo -e "Bots' names:\n============"
    for bot in "${bots[@]}"; do
        printf "%s\n" "${bot}"
        "${PWD}"/asm "$bot"
    done
    # vm "{bots[@]/.s$/.cor$}"
}

main
