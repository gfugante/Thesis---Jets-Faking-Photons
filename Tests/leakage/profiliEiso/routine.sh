



sed -i '39 d' SelectorABCD.C                    
sed -i '39i #define PATH_OUT "Wgamma_Eiso.root"' SelectorABCD.C

root -l -b /storage_tmp/atlas/fpiazza/MC_minitrees_65/mc16a_65.root <<-EOF
Wgamma->Process("SelectorABCD.C")
.q
EOF


sed -i '39 d' SelectorABCD.C                    
sed -i '39i #define PATH_OUT "Zgamma_Eiso.root"' SelectorABCD.C

root -l -b /storage_tmp/atlas/fpiazza/MC_minitrees_65/mc16a_65.root <<-EOF
Zgamma->Process("SelectorABCD.C")
.q
EOF


sed -i '39 d' SelectorABCD.C                    
sed -i '39i #define PATH_OUT "Znunugamma_Eiso.root"' SelectorABCD.C

root -l -b /storage_tmp/atlas/fpiazza/MC_minitrees_65/mc16a_65.root <<-EOF
Znunugamma->Process("SelectorABCD.C")
.q
EOF



python confrontoEiso.py