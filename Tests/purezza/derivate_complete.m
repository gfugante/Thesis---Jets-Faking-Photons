
a = Mb + Na c3 - Nb c2 R - Ma c1 R;
b = c1 c2 R - c3;
rad = Sqrt[1 + (4 b (Na Mb - Nb Ma R) / (a^2)) ];

f =  a (-1 + rad) / (2 Na b); 


DNa = D[f, Na];
DNb = D[f, Nb];
DMa = D[f, Ma];
DMb = D[f, Mb];
Dc1 = D[f, c1];
Dc2 = D[f, c2];
Dc3 = D[f, c3];
DR = D[f, R];





tutte = {DNa, DNb, DMa, DMb, Dc1, Dc2, Dc3, DR};



