import ROOT


PATH_PESATI = "eventi_pesati.root"
PATH_NON_PESATI = "eventi_non_pesati.root"
regione = "SR - ISR1"

#bin tightness
tight = 5
tight3 = 1
tight4 = 2
tight5 = 3
nottight = 4



# ROOT.gStyle.SetOptStat(0)
c1 = ROOT.TCanvas("c1")
c2 = ROOT.TCanvas("c2")



file_p = ROOT.TFile(PATH_PESATI)

hist_p = file_p.Get(regione)


tight_p = hist_p.ProjectionX("tight", tight-1, tight)
tight4_p = hist_p.ProjectionX("tight4", tight4-1, tight4)


tight_p.Scale(1/tight_p.Integral())
tight4_p.Scale(1/tight4_p.Integral())


tight_p.SetLineColor(2)
tight4_p.SetLineColor(2)



file_np = ROOT.TFile(PATH_NON_PESATI)

hist_np = file_np.Get(regione)

tight_np = hist_np.ProjectionX("tight", tight-1, tight)
tight4_np = hist_np.ProjectionX("tight4", tight4-1, tight4)

tight_np.Scale(1/tight_np.Integral())
tight4_np.Scale(1/tight4_np.Integral())

tight_np.SetLineColor(4)
tight4_np.SetLineColor(4)




c1.cd()
tight_p.Draw("hist")
tight_np.Draw("histsame")

c2.cd()
tight4_p.Draw("hist")
tight4_np.Draw("histsame")


raw_input("Please press enter to continue.")

