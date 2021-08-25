
import math

def DNa(Na,Nb,Ma,Mb,c1,c2,c3,R_MC):

  return \
  ((Mb + c3*Na - c1*Ma*R_MC - c2*Nb*R_MC)*((4*Mb*(-c3 + c1*c2*R_MC))/                 \
  pow((Mb + c3*Na - c1*Ma*R_MC - c2*Nb*R_MC),2) -                                     \
  (8*c3*(-c3 + c1*c2*R_MC)*(Mb*Na - Ma*Nb*R_MC))/                                     \
  pow((Mb + c3*Na - c1*Ma*R_MC - c2*Nb*R_MC),3)))/(4*Na*(-c3 + c1*c2*R_MC)*           \
  math.sqrt(1 + (4*(-c3 + c1*c2*R_MC)*(Mb*Na - Ma*Nb*R_MC))/                          \
  pow((Mb + c3*Na - c1*Ma*R_MC - c2*Nb*R_MC),2))) +                                   \
  (c3*(-1 + math.sqrt(1 + (4*(-c3 + c1*c2*R_MC)*(Mb*Na - Ma*Nb*R_MC))/                \
  pow((Mb + c3*Na - c1*Ma*R_MC - c2*Nb*R_MC),2))))/(2*Na*(-c3 + c1*c2*R_MC)) -        \
  ((Mb + c3*Na - c1*Ma*R_MC - c2*Nb*R_MC)*                                            \
  (-1 + math.sqrt(1 + (4*(-c3 + c1*c2*R_MC)*(Mb*Na - Ma*Nb*R_MC))/                    \
  pow((Mb + c3*Na - c1*Ma*R_MC - c2*Nb*R_MC),2))))/(2*pow(Na,2)*(-c3 + c1*c2*R_MC))   



def DNb(Na,Nb,Ma,Mb,c1,c2,c3,R_MC):

  return \
  ((Mb + c3*Na - c1*Ma*R_MC - c2*Nb*R_MC)*((-4*Ma*R_MC*(-c3 + c1*c2*R_MC))/   \
  pow((Mb + c3*Na - c1*Ma*R_MC - c2*Nb*R_MC),2) +                             \
  (8*c2*R_MC*(-c3 + c1*c2*R_MC)*(Mb*Na - Ma*Nb*R_MC))/                        \
  pow((Mb + c3*Na - c1*Ma*R_MC - c2*Nb*R_MC),3)))/(4*Na*(-c3 + c1*c2*R_MC)*   \
  math.sqrt(1 + (4*(-c3 + c1*c2*R_MC)*(Mb*Na - Ma*Nb*R_MC))/                  \
  pow((Mb + c3*Na - c1*Ma*R_MC - c2*Nb*R_MC),2))) -                           \
  (c2*R_MC*(-1 + math.sqrt(1 + (4*(-c3 + c1*c2*R_MC)*(Mb*Na - Ma*Nb*R_MC))/   \
  pow((Mb + c3*Na - c1*Ma*R_MC - c2*Nb*R_MC),2))))/(2*Na*(-c3 + c1*c2*R_MC))  





def DMa(Na,Nb,Ma,Mb,c1,c2,c3,R_MC):

  return \
  ((Mb + c3*Na - c1*Ma*R_MC - c2*Nb*R_MC)*((-4*Nb*R_MC*(-c3 + c1*c2*R_MC))/   \
  pow((Mb + c3*Na - c1*Ma*R_MC - c2*Nb*R_MC),2) +                             \
  (8*c1*R_MC*(-c3 + c1*c2*R_MC)*(Mb*Na - Ma*Nb*R_MC))/                        \
  pow((Mb + c3*Na - c1*Ma*R_MC - c2*Nb*R_MC),3)))/(4*Na*(-c3 + c1*c2*R_MC)*   \
  math.sqrt(1 + (4*(-c3 + c1*c2*R_MC)*(Mb*Na - Ma*Nb*R_MC))/                  \
  pow((Mb + c3*Na - c1*Ma*R_MC - c2*Nb*R_MC),2))) -                           \
  (c1*R_MC*(-1 + math.sqrt(1 + (4*(-c3 + c1*c2*R_MC)*(Mb*Na - Ma*Nb*R_MC))/   \
  pow((Mb + c3*Na - c1*Ma*R_MC - c2*Nb*R_MC),2))))/(2*Na*(-c3 + c1*c2*R_MC))  





def DMb(Na,Nb,Ma,Mb,c1,c2,c3,R_MC):

  return \
  ((Mb + c3*Na - c1*Ma*R_MC - c2*Nb*R_MC)*((4*Na*(-c3 + c1*c2*R_MC))/                           \
  pow((Mb + c3*Na - c1*Ma*R_MC - c2*Nb*R_MC),2) -                                               \
  (8*(-c3 + c1*c2*R_MC)*(Mb*Na - Ma*Nb*R_MC))/pow((Mb + c3*Na - c1*Ma*R_MC - c2*Nb*R_MC),3)))/  \
  (4*Na*(-c3 + c1*c2*R_MC)*                                                                     \
  math.sqrt(1 + (4*(-c3 + c1*c2*R_MC)*(Mb*Na - Ma*Nb*R_MC))/                                    \
  pow((Mb + c3*Na - c1*Ma*R_MC - c2*Nb*R_MC),2))) +                                             \
  (-1 + math.sqrt(1 + (4*(-c3 + c1*c2*R_MC)*(Mb*Na - Ma*Nb*R_MC))/                              \
  pow((Mb + c3*Na - c1*Ma*R_MC - c2*Nb*R_MC),2)))/(2*Na*(-c3 + c1*c2*R_MC))





def Dc1(Na,Nb,Ma,Mb,c1,c2,c3,R_MC):

  return \
  ((Mb + c3*Na - c1*Ma*R_MC - c2*Nb*R_MC)*                                          \
  ((8*Ma*R_MC*(-c3 + c1*c2*R_MC)*(Mb*Na - Ma*Nb*R_MC))/                             \
  pow((Mb + c3*Na - c1*Ma*R_MC - c2*Nb*R_MC),3) + (4*c2*R_MC*(Mb*Na - Ma*Nb*R_MC))/ \
  pow((Mb + c3*Na - c1*Ma*R_MC - c2*Nb*R_MC),2)))/(4*Na*(-c3 + c1*c2*R_MC)*         \
  math.sqrt(1 + (4*(-c3 + c1*c2*R_MC)*(Mb*Na - Ma*Nb*R_MC))/                        \
  pow((Mb + c3*Na - c1*Ma*R_MC - c2*Nb*R_MC),2))) -                                 \
  (Ma*R_MC*(-1 + math.sqrt(1 + (4*(-c3 + c1*c2*R_MC)*(Mb*Na - Ma*Nb*R_MC))/         \
  pow((Mb + c3*Na - c1*Ma*R_MC - c2*Nb*R_MC),2))))/(2*Na*(-c3 + c1*c2*R_MC)) -      \
  (c2*R_MC*(Mb + c3*Na - c1*Ma*R_MC - c2*Nb*R_MC)*                                  \
  (-1 + math.sqrt(1 + (4*(-c3 + c1*c2*R_MC)*(Mb*Na - Ma*Nb*R_MC))/                  \
  pow((Mb + c3*Na - c1*Ma*R_MC - c2*Nb*R_MC),2))))/(2*Na*pow((-c3 + c1*c2*R_MC),2))





def Dc2(Na,Nb,Ma,Mb,c1,c2,c3,R_MC):

  return \
  ((Mb + c3*Na - c1*Ma*R_MC - c2*Nb*R_MC)*                                          \
  ((8*Nb*R_MC*(-c3 + c1*c2*R_MC)*(Mb*Na - Ma*Nb*R_MC))/                             \
  pow((Mb + c3*Na - c1*Ma*R_MC - c2*Nb*R_MC),3) + (4*c1*R_MC*(Mb*Na - Ma*Nb*R_MC))/ \
  pow((Mb + c3*Na - c1*Ma*R_MC - c2*Nb*R_MC),2)))/(4*Na*(-c3 + c1*c2*R_MC)*         \
  math.sqrt(1 + (4*(-c3 + c1*c2*R_MC)*(Mb*Na - Ma*Nb*R_MC))/                        \
  pow((Mb + c3*Na - c1*Ma*R_MC - c2*Nb*R_MC),2))) -                                 \
  (Nb*R_MC*(-1 + math.sqrt(1 + (4*(-c3 + c1*c2*R_MC)*(Mb*Na - Ma*Nb*R_MC))/         \
  pow((Mb + c3*Na - c1*Ma*R_MC - c2*Nb*R_MC),2))))/(2*Na*(-c3 + c1*c2*R_MC)) -      \
  (c1*R_MC*(Mb + c3*Na - c1*Ma*R_MC - c2*Nb*R_MC)*                                  \
  (-1 + math.sqrt(1 + (4*(-c3 + c1*c2*R_MC)*(Mb*Na - Ma*Nb*R_MC))/                  \
  pow((Mb + c3*Na - c1*Ma*R_MC - c2*Nb*R_MC),2))))/(2*Na*pow((-c3 + c1*c2*R_MC),2)) 





def Dc3(Na,Nb,Ma,Mb,c1,c2,c3,R_MC):

  return \
  ((Mb + c3*Na - c1*Ma*R_MC - c2*Nb*R_MC)*((-8*Na*(-c3 + c1*c2*R_MC)*(Mb*Na - Ma*Nb*R_MC))/ \
  pow((Mb + c3*Na - c1*Ma*R_MC - c2*Nb*R_MC),3) - (4*(Mb*Na - Ma*Nb*R_MC))/                 \
  pow((Mb + c3*Na - c1*Ma*R_MC - c2*Nb*R_MC),2)))/(4*Na*(-c3 + c1*c2*R_MC)*                 \
  math.sqrt(1 + (4*(-c3 + c1*c2*R_MC)*(Mb*Na - Ma*Nb*R_MC))/                                \
  pow((Mb + c3*Na - c1*Ma*R_MC - c2*Nb*R_MC),2))) +                                         \
  (-1 + math.sqrt(1 + (4*(-c3 + c1*c2*R_MC)*(Mb*Na - Ma*Nb*R_MC))/                          \
  pow((Mb + c3*Na - c1*Ma*R_MC - c2*Nb*R_MC),2)))/(2*(-c3 + c1*c2*R_MC)) +                  \
  ((Mb + c3*Na - c1*Ma*R_MC - c2*Nb*R_MC)*                                                  \
  (-1 + math.sqrt(1 + (4*(-c3 + c1*c2*R_MC)*(Mb*Na - Ma*Nb*R_MC))/                          \
  pow((Mb + c3*Na - c1*Ma*R_MC - c2*Nb*R_MC),2))))/(2*Na*pow((-c3 + c1*c2*R_MC),2))         





def DR_MC(Na,Nb,Ma,Mb,c1,c2,c3,R_MC):

  return \
  ((Mb + c3*Na - c1*Ma*R_MC - c2*Nb*R_MC)*((-4*Ma*Nb*(-c3 + c1*c2*R_MC))/               \
  pow((Mb + c3*Na - c1*Ma*R_MC - c2*Nb*R_MC),2) -                                       \
  (8*(-(c1*Ma) - c2*Nb)*(-c3 + c1*c2*R_MC)*(Mb*Na - Ma*Nb*R_MC))/                       \
  pow((Mb + c3*Na - c1*Ma*R_MC - c2*Nb*R_MC),3) + (4*c1*c2*(Mb*Na - Ma*Nb*R_MC))/       \
  pow((Mb + c3*Na - c1*Ma*R_MC - c2*Nb*R_MC),2)))/(4*Na*(-c3 + c1*c2*R_MC)*             \
  math.sqrt(1 + (4*(-c3 + c1*c2*R_MC)*(Mb*Na - Ma*Nb*R_MC))/                            \
  pow((Mb + c3*Na - c1*Ma*R_MC - c2*Nb*R_MC),2))) +                                     \
  ((-(c1*Ma) - c2*Nb)*(-1 + math.sqrt(1 + (4*(-c3 + c1*c2*R_MC)*(Mb*Na - Ma*Nb*R_MC))/  \
  pow((Mb + c3*Na - c1*Ma*R_MC - c2*Nb*R_MC),2))))/(2*Na*(-c3 + c1*c2*R_MC)) -          \
  (c1*c2*(Mb + c3*Na - c1*Ma*R_MC - c2*Nb*R_MC)*                                        \
  (-1 + math.sqrt(1 + (4*(-c3 + c1*c2*R_MC)*(Mb*Na - Ma*Nb*R_MC))/                      \
  pow((Mb + c3*Na - c1*Ma*R_MC - c2*Nb*R_MC),2))))/(2*Na*pow((-c3 + c1*c2*R_MC),2))     




