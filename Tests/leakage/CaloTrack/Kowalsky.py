
import ROOT

PATH1 = "root_files/isolamento2_Wgamma.root"
PATH2 = "root_files/isolamento2_Zgamma.root"
PATH3 = "root_files/isolamento2_Znunugamma.root"
PATH4 = "root_files/isolamento2_gammajets.root"


file1 = ROOT.TFile(PATH1)
file2 = ROOT.TFile(PATH2)
file3 = ROOT.TFile(PATH3)
file4 = ROOT.TFile(PATH4)

hist1 = file1.Get("Eiso_gammajetCR");
hist2 = file2.Get("Eiso_gammajetCR");
hist3 = file3.Get("Eiso_gammajetCR");
hist4 = file4.Get("Eiso_gammajetCR");

hist1.SetTitle("gammajetCR isolation profiles")
hist2.SetTitle("gammajetCR isolation profiles")
hist3.SetTitle("gammajetCR isolation profiles")
hist4.SetTitle("gammajetCR isolation profiles")

hist1.GetXaxis().SetTitle("Calorimeter Isolation [GeV]")
hist2.GetXaxis().SetTitle("Calorimeter Isolation [GeV]")
hist3.GetXaxis().SetTitle("Calorimeter Isolation [GeV]")
hist4.GetXaxis().SetTitle("Calorimeter Isolation [GeV]")

hist1.GetYaxis().SetTitle("Number of events")
hist2.GetYaxis().SetTitle("Number of events")
hist3.GetYaxis().SetTitle("Number of events")
hist4.GetYaxis().SetTitle("Number of events")

hist1.GetXaxis().CenterTitle()
hist2.GetXaxis().CenterTitle()
hist3.GetXaxis().CenterTitle()
hist4.GetXaxis().CenterTitle()

hist1.GetYaxis().CenterTitle()
hist2.GetYaxis().CenterTitle()
hist3.GetYaxis().CenterTitle()
hist4.GetYaxis().CenterTitle()


legend = ROOT.TLegend(0.9,0.9,0.70,0.7)

c1 = ROOT.TCanvas("c1")
c1.cd()
c1.SetLogy()
ROOT.gStyle.SetOptStat(0)


hist1.SetLineColor(2)
hist2.SetLineColor(3)
hist3.SetLineColor(4)
hist4.SetLineColor(93)

legend.AddEntry(hist1, "Wgamma")
legend.AddEntry(hist2, "Zgamma")
legend.AddEntry(hist3, "Znunugamma")
legend.AddEntry(hist4, "gammajets")

hist1.DrawNormalized("histSAME")
hist2.DrawNormalized("histSAME")
hist3.DrawNormalized("histSAME")
hist4.DrawNormalized("histSAME")

legend.Draw("SAME")

raw_input("Press enter to quit.")




