
# This script runs all the code neded by the purity estimation


# Monte Carlo samples
declare -a samples=("Wgamma" "Zgamma" "Znunugamma" "gammajets" "Wjets" "Zjets")


for sample in "${samples[@]}"
do

	printf "\n\nProcessing $sample sample..."

	sed -i '18 d' SelectorMC.h
	sed -i "18i #define sample \"$sample\"" SelectorMC.h

	root -l -b /storage_tmp/atlas/fpiazza/MC_minitrees_65/mc16a_65.root <<-EOF
	$sample->Process("SelectorMC.C")
	.q

	EOF

done

# data processing
printf "\n\nProcessing data sample..."

root -l -b /storage_tmp/atlas/fpiazza/data_65/data13TeV_36.4fb.root <<-EOF
data->Process("SelectorData.C")
.q

EOF



printf "\n\n"