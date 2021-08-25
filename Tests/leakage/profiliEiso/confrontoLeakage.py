
import ROOT


PATH1 = "root_files/Znunugamma_profili.root"



file1 = ROOT.TFile(PATH1)

hist1 = file1.Get("ISR1");
hist2 = file1.Get("ISR2");
hist3 = file1.Get("ISR3");

legend = ROOT.TLegend(0.9,0.9,0.75,0.75)



hist1.SetTitle("Z(#nu#nu) + #gamma")



c1 = ROOT.TCanvas("c1")
c1.cd()
#c1.SetLogy()
ROOT.gStyle.SetOptStat(0)


hist1.SetLineColor(58)
hist1.Scale(1./hist1.Integral())
hist1.Draw("histL")
legend.AddEntry(hist1, "ISR1")

hist2.SetLineColor(63)
hist2.Scale(1./hist2.Integral())
hist2.Draw("histLSAME")
legend.AddEntry(hist2, "ISR2")

hist3.SetLineColor(68)
hist3.Scale(1./hist3.Integral())
hist3.Draw("histLSAME")
legend.AddEntry(hist3, "ISR3")



legend.Draw("same")







raw_input("Press enter to quit.")