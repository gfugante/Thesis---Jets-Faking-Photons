import math



def DNa(Na,Nb,Ma,Mb,c1,c2,c3,R_MC):

	return \
	-((c3*(Na - (Ma*Nb*R_MC)/Mb))/(Mb*Na*pow((1 + (c3*Na - c1*Ma*R_MC - c2*Nb*R_MC)/Mb),2))) + \
	1/(Na*(1 + (c3*Na - c1*Ma*R_MC - c2*Nb*R_MC)/Mb)) - \
	(Na - (Ma*Nb*R_MC)/Mb)/(pow(Na,2)*(1 + (c3*Na - c1*Ma*R_MC - c2*Nb*R_MC)/Mb)) \




def DNb(Na,Nb,Ma,Mb,c1,c2,c3,R_MC):

	return \
	(c2*R_MC*(Na - (Ma*Nb*R_MC)/Mb))/(Mb*Na*pow((1 + (c3*Na - c1*Ma*R_MC - c2*Nb*R_MC)/Mb),2)) - \
	(Ma*R_MC)/(Mb*Na*(1 + (c3*Na - c1*Ma*R_MC - c2*Nb*R_MC)/Mb))



def DMa(Na,Nb,Ma,Mb,c1,c2,c3,R_MC):

	return \
	(c1*R_MC*(Na - (Ma*Nb*R_MC)/Mb))/(Mb*Na*pow((1 + (c3*Na - c1*Ma*R_MC - c2*Nb*R_MC)/Mb),2)) - \
	(Nb*R_MC)/(Mb*Na*(1 + (c3*Na - c1*Ma*R_MC - c2*Nb*R_MC)/Mb))



def DMb(Na,Nb,Ma,Mb,c1,c2,c3,R_MC):

	return \
	((c3*Na - c1*Ma*R_MC - c2*Nb*R_MC)*(Na - (Ma*Nb*R_MC)/Mb))/ \
	(pow(Mb,2)*Na*pow((1 + (c3*Na - c1*Ma*R_MC - c2*Nb*R_MC)/Mb),2)) + \
	(Ma*Nb*R_MC)/(pow(Mb,2)*Na*(1 + (c3*Na - c1*Ma*R_MC - c2*Nb*R_MC)/Mb))



def Dc1(Na,Nb,Ma,Mb,c1,c2,c3,R_MC):

	return \
	(Ma*R_MC*(Na - (Ma*Nb*R_MC)/Mb))/(Mb*Na*pow((1 + (c3*Na - c1*Ma*R_MC - c2*Nb*R_MC)/Mb),2))



def Dc2(Na,Nb,Ma,Mb,c1,c2,c3,R_MC):

	return \
	(Nb*R_MC*(Na - (Ma*Nb*R_MC)/Mb))/(Mb*Na*pow((1 + (c3*Na - c1*Ma*R_MC - c2*Nb*R_MC)/Mb),2))



def Dc3(Na,Nb,Ma,Mb,c1,c2,c3,R_MC):

	return \
	-((Na - (Ma*Nb*R_MC)/Mb)/(Mb*pow((1 + (c3*Na - c1*Ma*R_MC - c2*Nb*R_MC)/Mb),2)))



def DR_MC(Na,Nb,Ma,Mb,c1,c2,c3,R_MC):

	return \
	-(((-(c1*Ma) - c2*Nb)*(Na - (Ma*Nb*R_MC)/Mb))/ \
	(Mb*Na*pow((1 + (c3*Na - c1*Ma*R_MC - c2*Nb*R_MC)/Mb),2))) - \
	(Ma*Nb)/(Mb*Na*(1 + (c3*Na - c1*Ma*R_MC - c2*Nb*R_MC)/Mb))

