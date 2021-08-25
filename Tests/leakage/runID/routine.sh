


for ((i = 364502; i <= 364519; i++))
do

if ((i != 364505 && i != 364506 && i != 364510 && i != 364511 && i != 364515 && i != 364516))
then
sed -i '43 d' Selector_CaloTrack.C                    
sed -i "43i int run_ID = $i;" Selector_CaloTrack.C

root -l -b /storage_tmp/atlas/fpiazza/MC_minitrees_65/mc16a_65.root <<-EOF
Zgamma->Process("Selector_CaloTrack.C")
.q
EOF

mv dati.txt Zgamma/"$i".txt
fi
done


for ((i = 364523; i <= 364535; i++))
do

if ((i != 364526 && i != 364527 && i != 364531 && i != 364532))
then
sed -i '43 d' Selector_CaloTrack.C
sed -i "43i int run_ID = $i;" Selector_CaloTrack.C

root -l -b /storage_tmp/atlas/fpiazza/MC_minitrees_65/mc16a_65.root <<-EOF
Wgamma->Process("Selector_CaloTrack.C")
.q

EOF

mv dati.txt Wgamma/"$i".txt
fi
done


