
import ROOT


PATH1 = "hist_Zgamma_SR.root"
PATH2 = "hist_Zgamma_2muCR.root"
PATH3 = "hist_Zgamma_2eCR.root"
PATH4 = "hist_Wgamma_SR.root"
PATH5 = "hist_Wgamma_1muCR.root"


file1 = ROOT.TFile(PATH1)
file2 = ROOT.TFile(PATH2)
file3 = ROOT.TFile(PATH3)
file4 = ROOT.TFile(PATH4)
file5 = ROOT.TFile(PATH5)

hist1 = file1.Get("SR - ISR1");
hist2 = file2.Get("SR - ISR1");
hist3 = file3.Get("SR - ISR1");
hist4 = file4.Get("SR - ISR1");
hist5 = file5.Get("SR - ISR1");



intervallix = 60;
minx = -20.;
maxx = 100.;
intervalliy = 20;
miny = 0.;
maxy = 1.;

hist = ROOT.TH2F("Difference ISR1","Difference ISR1",intervallix,minx,maxx,intervalliy,miny,maxy)


for b in range(intervalliy*intervallix + 2):
	z1 = hist1.GetBinContent(b)/hist1.Integral()
	z2 = hist2.GetBinContent(b)/hist2.Integral()
	z3 = hist3.GetBinContent(b)/hist3.Integral()
	w1 = hist4.GetBinContent(b)/hist4.Integral()
	w2 = hist5.GetBinContent(b)/hist5.Integral()
	
	hist.SetBinContent(b, (z1+z2+z3)/3 - ((w1+w2)/2))






c1 = ROOT.TCanvas("c1")
c1.cd()
hist.Draw("LEGO")




raw_input("Press enter to quit.")