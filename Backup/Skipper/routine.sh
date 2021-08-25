
# This script runs all the code neded by the purity estimation


# create storage directories

if [ ! -d "dati" ]; then
  printf "\nCreating directory: dati...\n"
  mkdir dati
fi

if [ ! -d "dati/txt files 15-16" ]; then
  printf "\nCreating directory: dati/txt files 15-16...\n"
  mkdir dati/txt\ files\ 15-16
fi

if [ ! -d "dati/txt files 17" ]; then
  printf "\nCreating directory: dati/txt files 17...\n"
  mkdir dati/txt\ files\ 17
fi

if [ ! -d "dati/txt files 18" ]; then
  printf "\nCreating directory: dati/txt files 1...\n"
  mkdir dati/txt\ files\ 18
fi

printf "\n\n"



# analyzing samples

declare -a samples=("Wgamma" "Zgamma" "Znunugamma" "Wjets" "Zjets")

declare -a MC=("mc16a" "mc16d" "mc16e")
declare -a data=("data15_16/data15_16_13TeV" "data17/data17_13TeV" "data18/data18_13TeV")
declare -a directory=("15-16" "17" "18")




for i in 0 1 2
do

	printf "\nAnalyzing 20${directory[i]} data\n"

	sed -i '19 d' SelectorMC.h
	sed -i "19i #define directory \" ${directory[i]}\"" SelectorMC.h

	sed -i '19 d' SelectorData.h
	sed -i "19i #define directory \" ${directory[i]}\"" SelectorData.h


	# MC processing
	for sample in "${samples[@]}"
	do

		printf "\n\nProcessing $sample sample..."

		sed -i '18 d' SelectorMC.h
		sed -i "18i #define sample \"$sample\"" SelectorMC.h

		root -l -b /storage_tmp/atlas/fpiazza/MC_75/${MC[i]}.root <<-EOF
		$sample->Process("SelectorMC.C")
		.q

		EOF

	done

	# MC gammajets processing (switch on background and signal)
	for sample in "gammajets_sig" "gammajets_bkg"
	do

		printf "\n\nProcessing $sample sample..."

		sed -i '18 d' SelectorMC.h
		sed -i "18i #define sample \"$sample\"" SelectorMC.h

		root -l -b /storage_tmp/atlas/fpiazza/MC_75/${MC[i]}.root <<-EOF
		gammajets->Process("SelectorMC.C")
		.q

		EOF

	done




	# data processing
	printf "\n\nProcessing data sample..."

	root -l -b  /storage_tmp/atlas/fpiazza/data_rel75/${data[i]}.root <<-EOF
	nominal->Process("SelectorData.C")
	.q

	EOF



	printf "\n\n"

done




