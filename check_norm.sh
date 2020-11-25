#!/bin/bash

declare log="norminette.log"
declare norminette="${HOME}/.norminette/norminette.rb"

main()
{
	[[ -f $log ]] && rm "${log}"
	echo -e "------------------\nNorminette check\n"
	ruby "${norminette}" src includes > "${log}"
	cat "${log}"
	if cat "${log}" | grep "Error"; then
		exit 1
	else
		exit 0
	fi
}

main