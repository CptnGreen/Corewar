#!/bin/bash

#
# This script is supposed to be called via `make norm`
# so $PWD resolves to project root
#

declare project_root="${PWD}"

declare logs_dir="${project_root}/logs"
declare log="${logs_dir}/norminette.log"

declare norminette="${HOME}/.norminette/norminette.rb"

main()
{
	[[ -d $logs_dir ]] || mkdir "$logs_dir"
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