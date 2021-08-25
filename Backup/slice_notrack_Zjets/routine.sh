for ((i = 364100; i <= 364155; i++))
do

if ((i <= 364141 || i >= 364148))
then
sed -i '43 d' SelectorABCD.C                    
sed -i "43i int run_ID = $i;" SelectorABCD.C

root -l -b /storage_tmp/atlas/fpiazza/MC_minitrees_65/mc16a_65.root <<-EOF
Zjets->Process("SelectorABCD.C")
.q

EOF

python R.py
mv R_pesati/R.txt R_pesati/"$i".txt
fi
done
