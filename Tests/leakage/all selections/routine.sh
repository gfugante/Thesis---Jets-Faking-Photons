
# This script runs all the code neded by the purity estimation


declare -a samples=("Wgamma" "Zgamma" "Znunugamma" "gammajets" "Wjets" "Zjets")

declare -a MC=("mc16a" "mc16d" "mc16e")
declare -a data=("data15_16/data15_16_13TeV" "data17/data17_13TeV" "data18/data18_13TeV")
declare -a directory=(" 15-16" " 17" " 18")
s


for i in 0 1 2
do

	printf "\nAnalyzing 20${directory[i]} data\n"

	sed -i '74 d' SelectorABCD.h
	sed -i "74i #define directory \"${directory[i]}\"" SelectorABCD.h


	for sample in "${samples[@]}"
	do

		printf "\n\nProcessing $sample sample..."

		sed -i '75 d' SelectorABCD.h
		sed -i "75i #define sample \"$sample\"" SelectorABCD.h

		root -l -b /storage_tmp/atlas/fpiazza/MC_75/${MC[i]}.root <<-EOF
		$sample->Process("SelectorABCD.C")
		.q

		EOF

	done



	printf "\n\n"

done