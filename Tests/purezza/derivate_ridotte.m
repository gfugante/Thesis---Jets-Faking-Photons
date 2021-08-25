

b = Na - ((Nb Ma R)/ Mb);
f = 1 + ((Na c3 - Nb c2 R - Ma c1 R)/Mb);


p =  b / (Na f); 


DNa = D[p, Na];
DNb = D[p, Nb];
DMa = D[p, Ma];
DMb = D[p, Mb];
Dc1 = D[p, c1];
Dc2 = D[p, c2];
Dc3 = D[p, c3];
DR = D[p, R];





tutte = {DNa, DNb, DMa, DMb, Dc1, Dc2, Dc3, DR};
