import matplotlib.pyplot as plt
import math
import copy
import derivate_complete as dc

CR = ['SR', 'onemuCR', 'twomuCR', 'twoeCR']
CR_label = ['SR', '1muCR', '2muCR', '2eCR']
met_regions = ['ISR1', 'ISR2', 'ISR3', 'ESR1', 'ESR2']


tight_selections = ['tight','tight3', 'tight4', 'tight5', 'nottight']
not_tight_selections = ['tight3', 'tight4', 'tight5']
isolation_variations = ['up', 'iso', 'down']


def merge(sample, key, tightness, isolation, Na_Nb):
# first argument: dictionary
# all other arguments: string
 
    return_array = [0 for _ in range(5)]
    
    if key == 'Wgamma' or key == 'Wjets':
        selected_regions = ['SR', 'onemuCR']
    
    if key == 'Zgamma' or key == 'Zjets':
        selected_regions = ['SR', 'twomuCR', 'twoeCR']
    
    if key == 'Znunugamma':
        selected_regions = ['SR']
    
    if key == 'gammajets_sig' or key == 'gammajets_bkg':
        #return [ sample[key]['gammajetCR'][tightness][Na_Nb] ]
        selected_regions = ['SR']

    for cr in selected_regions:
        return_array = [ return_array[i] + sample[key][cr][met_regions[i]][tightness][isolation][Na_Nb] for i in range(5) ]
    
    return return_array + [ sample[key]['gammajetCR'][tightness][isolation][Na_Nb] ]
        
        
def leakage_coefficient(num, den):
    
    ci    = [ 0 for _ in range(len(num)) ]
    sigma = [ 0 for _ in range(len(num)) ]
    
    for i in range(len(ci)):
        
        if num[i] > 0 and den[i] > 0:
            
            ci[i]    = num[i]/den[i]
            sigma[i] = ci[i] * math.sqrt((1/num[i]) + (1/den[i]))
    
    return {'mean': ci, 'sigma': sigma}


def correlation_factor(Na, Nb, Ma, Mb):
   
    R     = [ 0 for _ in range(len(Na)) ]
    sigma = [ 0 for _ in range(len(Na)) ]
    
    for i in range(len(R)):
        
        if Na[i]>0 and Nb[i]>0 and Ma[i]>0 and Mb[i]>0:
            
            R[i]     = (Na[i]*Mb[i])/(Nb[i]*Ma[i])
            sigma[i] = R[i] * math.sqrt((1/Na[i]) + (1/Nb[i]) + (1/Ma[i]) + (1/Mb[i]))
            
            
    return {'mean': R, 'sigma': sigma}


def plot_coefficient(coeff, title):
    
    color = ['r', 'b', 'g', 'orangered']
    linestyle = ''
    j = 0
    
    plt.figure(num=None, figsize=(30, 12), dpi=80, facecolor='w', edgecolor='k')
        
    
    for key in coeff:
        
        if title != 'R':            
            linestyle = '-'
        
        if key != 'gammajets_sig' and key != 'gammajets_bkg':
            plt.errorbar([ i-0.04 + j*0.04 for i in range(len(coeff[key]['mean'])) ], coeff[key]['mean'], yerr=coeff[key]['sigma'], fmt=color[j], marker='o', linestyle=linestyle, linewidth=2, label=key)
        
        if key == 'gammajets_sig' or key == 'gammajets_bkg':
            plt.errorbar([5+j*0.04], coeff[key]['mean'][5], yerr=coeff[key]['sigma'][5], fmt=color[j], marker='o', linestyle=linestyle, linewidth=2, label='gammajets')
        
        j = j + 1
    
    
    plt.xticks(range(6), ["ISR1", "ISR2", "ISR3", "ESR1", "ESR2", "gammajetCR"], fontsize=20)
    
    
    plt.yticks(fontsize=20)
    plt.legend(fontsize="xx-large")
    plt.grid()
    

    plt.ylabel(title + '    ', rotation=0, fontsize=30)
        
        
def avarage_mean(data):
    
    num = [ 0 for _ in range(len(data[0]['mean'])) ]
    den = [ 0 for _ in range(len(data[0]['mean'])) ]
    
    for i in range(len(data)):
        for j in range(len(data[i]['mean'])):
            
            if data[i]['sigma'][j] > 0:
                num[j] = num[j] + data[i]['mean'][j]/pow(data[i]['sigma'][j],2)
                den[j] = den[j] + 1./pow(data[i]['sigma'][j],2)
            
    mean  = [num[i]/den[i]       for i in range(len(num))]
    sigma = [math.sqrt(1/den[i]) for i in range(len(den))]
    
    return({'mean': mean, 'sigma': sigma})


def purity(Na, Nb, Ma, Mb, c1, c2, c3, R):
    
    number_of_regions = len(Na)
    return_dict = {'mean':     [0 for _ in range(number_of_regions)], 
                   'sigma':    [0 for _ in range(number_of_regions)],
                   'sigma_c1': [0 for _ in range(number_of_regions)],
                   'sigma_c2': [0 for _ in range(number_of_regions)],
                   'sigma_c3': [0 for _ in range(number_of_regions)],
                   'sigma_R':  [0 for _ in range(number_of_regions)]}
    
    
    for i in range(number_of_regions):
        
        if Na[i]>0 and Nb[i]>0 and Ma[i]>0 and Mb[i]>0 and c1['mean'][i]>0 and c2['mean'][i]>0 and c3['mean'][i]>0 and R['mean'][i]>0:
            
            # complete formula
            x = Mb[i] + Na[i]*c3['mean'][i] - Nb[i]*c2['mean'][i]*R['mean'][i] - Ma[i]*c1['mean'][i]*R['mean'][i]
            y = c1['mean'][i]*c2['mean'][i]*R['mean'][i] - c3['mean'][i]
            z = 4*y*(Na[i]*Mb[i] - Nb[i]*Ma[i]*R['mean'][i])/pow(x,2)

            try:

                p = 100*x*(-1 + math.sqrt(1 + z))/ (2*y*Na[i])

                # if p > 100:
                #     return_dict['mean'][i] = 100
                # else:
                return_dict['mean'][i] = p

                # reducted formula
                # x = Na[i] - Nb[i]*Ma[i]*R['mean'][i]/Mb[i]
                # y = (c3['mean'][i]*Na[i] - c2['mean'][i]*Nb[i]*R['mean'][i] - c1['mean'][i]*Ma[i]*R['mean'][i])/Mb[i]

                # return_dict['mean'][i] = 100*x/(Na[i]*(1+y))

        
                DNa = dc.DNa(Na[i],Nb[i],Ma[i],Mb[i],c1['mean'][i],c2['mean'][i],c3['mean'][i],R['mean'][i])
                DNb = dc.DNb(Na[i],Nb[i],Ma[i],Mb[i],c1['mean'][i],c2['mean'][i],c3['mean'][i],R['mean'][i])
                DMa = dc.DMa(Na[i],Nb[i],Ma[i],Mb[i],c1['mean'][i],c2['mean'][i],c3['mean'][i],R['mean'][i])
                DMb = dc.DMb(Na[i],Nb[i],Ma[i],Mb[i],c1['mean'][i],c2['mean'][i],c3['mean'][i],R['mean'][i])

                Dc1 = dc.Dc1(Na[i],Nb[i],Ma[i],Mb[i],c1['mean'][i],c2['mean'][i],c3['mean'][i],R['mean'][i])
                Dc2 = dc.Dc2(Na[i],Nb[i],Ma[i],Mb[i],c1['mean'][i],c2['mean'][i],c3['mean'][i],R['mean'][i])
                Dc3 = dc.Dc3(Na[i],Nb[i],Ma[i],Mb[i],c1['mean'][i],c2['mean'][i],c3['mean'][i],R['mean'][i])
                DR  =  dc.DR(Na[i],Nb[i],Ma[i],Mb[i],c1['mean'][i],c2['mean'][i],c3['mean'][i],R['mean'][i])
                


                # return_dict['sigma'][i] = 100*math.sqrt( Na[i]*pow(DNa,2) + Nb[i]*pow(DNb,2) + Ma[i]*pow(DMa,2) + Mb[i]*pow(DMb,2) + pow(Dc1*c1['sigma'][i],2) + pow(Dc2*c2['sigma'][i],2) + pow(Dc3*c3['sigma'][i],2) + pow(DR*R['sigma'][i],2) )

                return_dict['sigma'][i]    = 100*math.sqrt( Na[i]*pow(DNa,2) + Nb[i]*pow(DNb,2) + Ma[i]*pow(DMa,2) + Mb[i]*pow(DMb,2) )
                return_dict['sigma_c1'][i] = abs(100*Dc1*c1['sigma'][i])
                return_dict['sigma_c2'][i] = abs(100*Dc2*c2['sigma'][i])
                return_dict['sigma_c3'][i] = abs(100*Dc3*c3['sigma'][i])
                return_dict['sigma_R'][i]  = abs(100*DR*R['sigma'][i])
        
            except (ValueError):
                print('ValueError:\t1+z = ' + repr(1+z))
        
    return return_dict


def merge_years(sample, data=False):

    if (data is False):
        a = 36.2/140.
        d = 44.3/140.
        e = 58.5/140.
    
    if (data is True):
        a = 1
        d = 1
        e = 1


    for cr in CR:
        for met in met_regions:
            for tight in tight_selections:
                for iso in isolation_variations:
                    sample[0][cr][met][tight][iso]['Na'] = a*sample[0][cr][met][tight][iso]['Na'] #+ d*sample[1][cr][met][tight][iso]['Na'] + e*sample[2][cr][met][tight][iso]['Na']
                    sample[0][cr][met][tight][iso]['Nb'] = a*sample[0][cr][met][tight][iso]['Nb'] #+ d*sample[1][cr][met][tight][iso]['Nb'] + e*sample[2][cr][met][tight][iso]['Nb']
    
    for tight in tight_selections:
        for iso in isolation_variations:
            sample[0]['gammajetCR'][tight][iso]['Na'] = a*sample[0]['gammajetCR'][tight][iso]['Na'] #+ d*sample[1]['gammajetCR'][tight][iso]['Na'] + e*sample[2]['gammajetCR'][tight][iso]['Na']
            sample[0]['gammajetCR'][tight][iso]['Nb'] = a*sample[0]['gammajetCR'][tight][iso]['Nb'] #+ d*sample[1]['gammajetCR'][tight][iso]['Nb'] + e*sample[2]['gammajetCR'][tight][iso]['Nb']
            
    return sample[0]



def analyze_coefficient(coeff):

    avarage_array = avarage_mean([coeff[key] for key in coeff if key != 'gammajets_bkg' and key != 'gammajets_sig'])
    avarage_array_gj = avarage_mean([coeff[key] for key in coeff])

    avarage_array['mean'][5]  = avarage_array_gj['mean'][5]
    avarage_array['sigma'][5] = avarage_array_gj['sigma'][5]

    keys = [key for key in coeff]
    N = len(keys)
    M = len(avarage_array['mean'])



    xi_m2_sum = [ 0 for _ in range(M) ]

    for i in range(M):
        for j in range(N):

            if keys[j] != 'gammajets_bkg' and keys[j] != 'gammajets_sig':
                xi_m2_sum[i] = xi_m2_sum[i] + pow( coeff[keys[j]]['mean'][i] - avarage_array['mean'][i] , 2)

    for j in range(N):

            if keys[j] == 'gammajets_bkg' or keys[j] == 'gammajets_sig':
                xi_m2_sum[M-1] = xi_m2_sum[M-1] + pow( coeff[keys[j]]['mean'][M-1] - avarage_array['mean'][M-1] , 2)    

    

    sigma_systematics = [ math.sqrt(xi_m2_sum[i]/(N*(N-1))) for i in range(M) ]
    


    return {'mean' : [ avarage_array['mean'][i%(M-1)] for i in range(20) ] + [ avarage_array['mean'][M-1] ], \
            'sigma': [ avarage_array['sigma'][i%(M-1)] for i in range(20) ] + [ avarage_array['sigma'][M-1] ],\
            'systematics': [ sigma_systematics[i%(M-1)] for i in range(20) ] + [ sigma_systematics[M-1] ]}




