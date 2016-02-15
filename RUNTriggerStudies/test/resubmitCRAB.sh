for ifile in `ls -1 crab_projects/`
do
	if [[ $ifile == *"${1}"* ]]
	then
		crab resubmit crab_projects/$ifile
	fi
done
