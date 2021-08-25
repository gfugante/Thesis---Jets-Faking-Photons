


sed -i '42 d' SelectorABCD.C                    
sed -i '42i string process = "Wgamma";' SelectorABCD.C

root -l -b /storage_tmp/atlas/fpiazza/MC_minitrees_65/mc16a_65.root <<-EOF
Wgamma->Process("SelectorABCD.C")
.q

EOF


sed -i '42 d' SelectorABCD.C                    
sed -i '42i string process = "Zgamma";' SelectorABCD.C

root -l -b /storage_tmp/atlas/fpiazza/MC_minitrees_65/mc16a_65.root <<-EOF
Zgamma->Process("SelectorABCD.C")
.q

EOF


sed -i '42 d' SelectorABCD.C                    
sed -i '42i string process = "Znunugamma";' SelectorABCD.C

root -l -b /storage_tmp/atlas/fpiazza/MC_minitrees_65/mc16a_65.root <<-EOF
Znunugamma->Process("SelectorABCD.C")
.q

EOF



sed -i '42 d' SelectorABCD.C                    
sed -i '42i string process = "gammajets";' SelectorABCD.C

root -l -b /storage_tmp/atlas/fpiazza/MC_minitrees_65/mc16a_65.root <<-EOF
gammajets->Process("SelectorABCD.C")
.q

EOF
