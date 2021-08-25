from ROOT import TCanvas, TLegend, TFile, gStyle


variable_to_be_plotted = 'Ecalo'

directory = ['test']#['simple plots', 'tight applied', 'track isolation applied', 'MET significance applied', 'delta phi applied', 'all MET cuts applied', 'test']
selection = ['', ' tight selection applied', ' track isolation applied']
process   = ['Wgamma', 'Zgamma', 'Znunugamma', 'gammajets']
colors    = [2, 3, 4, 93]
MET_slice  = [150, 225, 300, 2000]
eta_bin   = ['endcap', 'barrel']



if (True):
##################################################################################
############################ bin di MET fissati ###################################
##################################################################################

	canvas = []
	legend = []
	file   = []
	hist   = []

	for k in range(len(directory)):

		canvas.append([])
		legend.append([])
		file.append([])
		hist.append([])

		for l in range(2):

			canvas[k].append([])
			legend[k].append([])
			file[k].append([])
			hist[k].append([])

			for j in range(3):


				canvas[k][l].append(TCanvas('c' + repr(6*k + 3*l + j)))
				canvas[k][l][j].cd()
				canvas[k][l][j].SetLogy()
				gStyle.SetOptStat(0)

				legend[k][l].append(TLegend(0.9,0.9,0.70,0.7))


				file[k][l].append([])
				hist[k][l].append([])


				for i in range(len(process)):

					file[k][l][j].append(TFile('/users2/gfugante/Test/plots/root_files_MET/'+ directory[k] + '/' + process[i] + '_' + variable_to_be_plotted + '.root'))

					hist[k][l][j].append(file[k][l][j][i].Get('slice' + repr(j+1) + '_' + eta_bin[l]))
						
					hist[k][l][j][i].SetTitle('isolation profiles  eta: ' + eta_bin[l] + ' MET: ' + repr(MET_slice[j]) + '-' + repr(MET_slice[j+1]) + ' GeV ' + selection[k])
					hist[k][l][j][i].GetXaxis().SetTitle('Calorimetric Isolation [GeV]')
					hist[k][l][j][i].SetLineColor(colors[i])
					legend[k][l][j].AddEntry(hist[k][l][j][i], process[i], 'l')
					hist[k][l][j][i].DrawNormalized('histSame')




				legend[k][l][j].Draw("SAME")

				canvas[k][l][j].SaveAs('/users2/gfugante/Test/plots/PDF MET/' + directory[k] + '/isolation profiles MET ' + repr(MET_slice[j]) + '-' + repr(MET_slice[j+1]) + ' eta ' + eta_bin[l] + '.pdf')

	raw_input("\nPress enter to continue.")






##################################################################################
############################ processi fissati ###################################
##################################################################################


canvas = []
legend = []
file   = []
hist   = []

colors2 = [98, 94, 90]


for k in range(len(directory)):

	canvas.append([])
	legend.append([])
	file.append([])
	hist.append([])

	for l in range(2):

		canvas[k].append([])
		legend[k].append([])
		file[k].append([])
		hist[k].append([])

		for i in range(len(process)):


			canvas[k][l].append(TCanvas('d' + repr(8*k + 4*l + i)))
			canvas[k][l][i].cd()
			canvas[k][l][i].SetLogy()
			gStyle.SetOptStat(0)

			legend[k][l].append(TLegend(0.9,0.9,0.70,0.7))


			file[k][l].append([])
			hist[k][l].append([])


			for j in range(3):

				file[k][l][i].append(TFile('/users2/gfugante/Test/plots/root_files_MET/'+ directory[k] + '/' + process[i] + '_' + variable_to_be_plotted + '.root'))

				hist[k][l][i].append(file[k][l][i][j].Get('slice' + repr(j+1) + '_' + eta_bin[l]))
					
				hist[k][l][i][j].SetTitle(process[i] + ' isolation profiles  eta: ' + eta_bin[l] + ' ' + selection[k])
				hist[k][l][i][j].GetXaxis().SetTitle('Calorimetric Isolation [GeV]')
				hist[k][l][i][j].SetLineColor(colors2[j])
				legend[k][l][i].AddEntry(hist[k][l][i][j], 'MET: ' + repr(MET_slice[j]) + '-' + repr(MET_slice[j+1]) + ' GeV', 'l')
				hist[k][l][i][j].DrawNormalized('histSame')




			legend[k][l][i].Draw("SAME")

			canvas[k][l][i].SaveAs('/users2/gfugante/Test/plots/PDF MET/' + directory[k] + '/' + process[i] + ' isolation profiles eta ' + eta_bin[l] + '.pdf')

raw_input("\nPress enter to continue.")

