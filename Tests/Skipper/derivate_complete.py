
import math

def DNa(Na,Nb,Ma,Mb,c1,c2,c3,R):

  return \
  ((Mb + c3*Na - c1*Ma*R - c2*Nb*R)*((4*Mb*(-c3 + c1*c2*R))/                 \
  pow((Mb + c3*Na - c1*Ma*R - c2*Nb*R),2) -                                     \
  (8*c3*(-c3 + c1*c2*R)*(Mb*Na - Ma*Nb*R))/                                     \
  pow((Mb + c3*Na - c1*Ma*R - c2*Nb*R),3)))/(4*Na*(-c3 + c1*c2*R)*           \
  math.sqrt(1 + (4*(-c3 + c1*c2*R)*(Mb*Na - Ma*Nb*R))/                          \
  pow((Mb + c3*Na - c1*Ma*R - c2*Nb*R),2))) +                                   \
  (c3*(-1 + math.sqrt(1 + (4*(-c3 + c1*c2*R)*(Mb*Na - Ma*Nb*R))/                \
  pow((Mb + c3*Na - c1*Ma*R - c2*Nb*R),2))))/(2*Na*(-c3 + c1*c2*R)) -        \
  ((Mb + c3*Na - c1*Ma*R - c2*Nb*R)*                                            \
  (-1 + math.sqrt(1 + (4*(-c3 + c1*c2*R)*(Mb*Na - Ma*Nb*R))/                    \
  pow((Mb + c3*Na - c1*Ma*R - c2*Nb*R),2))))/(2*pow(Na,2)*(-c3 + c1*c2*R))   



def DNb(Na,Nb,Ma,Mb,c1,c2,c3,R):

  return \
  ((Mb + c3*Na - c1*Ma*R - c2*Nb*R)*((-4*Ma*R*(-c3 + c1*c2*R))/   \
  pow((Mb + c3*Na - c1*Ma*R - c2*Nb*R),2) +                             \
  (8*c2*R*(-c3 + c1*c2*R)*(Mb*Na - Ma*Nb*R))/                        \
  pow((Mb + c3*Na - c1*Ma*R - c2*Nb*R),3)))/(4*Na*(-c3 + c1*c2*R)*   \
  math.sqrt(1 + (4*(-c3 + c1*c2*R)*(Mb*Na - Ma*Nb*R))/                  \
  pow((Mb + c3*Na - c1*Ma*R - c2*Nb*R),2))) -                           \
  (c2*R*(-1 + math.sqrt(1 + (4*(-c3 + c1*c2*R)*(Mb*Na - Ma*Nb*R))/   \
  pow((Mb + c3*Na - c1*Ma*R - c2*Nb*R),2))))/(2*Na*(-c3 + c1*c2*R))  





def DMa(Na,Nb,Ma,Mb,c1,c2,c3,R):

  return \
  ((Mb + c3*Na - c1*Ma*R - c2*Nb*R)*((-4*Nb*R*(-c3 + c1*c2*R))/   \
  pow((Mb + c3*Na - c1*Ma*R - c2*Nb*R),2) +                             \
  (8*c1*R*(-c3 + c1*c2*R)*(Mb*Na - Ma*Nb*R))/                        \
  pow((Mb + c3*Na - c1*Ma*R - c2*Nb*R),3)))/(4*Na*(-c3 + c1*c2*R)*   \
  math.sqrt(1 + (4*(-c3 + c1*c2*R)*(Mb*Na - Ma*Nb*R))/                  \
  pow((Mb + c3*Na - c1*Ma*R - c2*Nb*R),2))) -                           \
  (c1*R*(-1 + math.sqrt(1 + (4*(-c3 + c1*c2*R)*(Mb*Na - Ma*Nb*R))/   \
  pow((Mb + c3*Na - c1*Ma*R - c2*Nb*R),2))))/(2*Na*(-c3 + c1*c2*R))  





def DMb(Na,Nb,Ma,Mb,c1,c2,c3,R):

  return \
  ((Mb + c3*Na - c1*Ma*R - c2*Nb*R)*((4*Na*(-c3 + c1*c2*R))/                           \
  pow((Mb + c3*Na - c1*Ma*R - c2*Nb*R),2) -                                               \
  (8*(-c3 + c1*c2*R)*(Mb*Na - Ma*Nb*R))/pow((Mb + c3*Na - c1*Ma*R - c2*Nb*R),3)))/  \
  (4*Na*(-c3 + c1*c2*R)*                                                                     \
  math.sqrt(1 + (4*(-c3 + c1*c2*R)*(Mb*Na - Ma*Nb*R))/                                    \
  pow((Mb + c3*Na - c1*Ma*R - c2*Nb*R),2))) +                                             \
  (-1 + math.sqrt(1 + (4*(-c3 + c1*c2*R)*(Mb*Na - Ma*Nb*R))/                              \
  pow((Mb + c3*Na - c1*Ma*R - c2*Nb*R),2)))/(2*Na*(-c3 + c1*c2*R))





def Dc1(Na,Nb,Ma,Mb,c1,c2,c3,R):

  return \
  ((Mb + c3*Na - c1*Ma*R - c2*Nb*R)*                                          \
  ((8*Ma*R*(-c3 + c1*c2*R)*(Mb*Na - Ma*Nb*R))/                             \
  pow((Mb + c3*Na - c1*Ma*R - c2*Nb*R),3) + (4*c2*R*(Mb*Na - Ma*Nb*R))/ \
  pow((Mb + c3*Na - c1*Ma*R - c2*Nb*R),2)))/(4*Na*(-c3 + c1*c2*R)*         \
  math.sqrt(1 + (4*(-c3 + c1*c2*R)*(Mb*Na - Ma*Nb*R))/                        \
  pow((Mb + c3*Na - c1*Ma*R - c2*Nb*R),2))) -                                 \
  (Ma*R*(-1 + math.sqrt(1 + (4*(-c3 + c1*c2*R)*(Mb*Na - Ma*Nb*R))/         \
  pow((Mb + c3*Na - c1*Ma*R - c2*Nb*R),2))))/(2*Na*(-c3 + c1*c2*R)) -      \
  (c2*R*(Mb + c3*Na - c1*Ma*R - c2*Nb*R)*                                  \
  (-1 + math.sqrt(1 + (4*(-c3 + c1*c2*R)*(Mb*Na - Ma*Nb*R))/                  \
  pow((Mb + c3*Na - c1*Ma*R - c2*Nb*R),2))))/(2*Na*pow((-c3 + c1*c2*R),2))





def Dc2(Na,Nb,Ma,Mb,c1,c2,c3,R):

  return \
  ((Mb + c3*Na - c1*Ma*R - c2*Nb*R)*                                          \
  ((8*Nb*R*(-c3 + c1*c2*R)*(Mb*Na - Ma*Nb*R))/                             \
  pow((Mb + c3*Na - c1*Ma*R - c2*Nb*R),3) + (4*c1*R*(Mb*Na - Ma*Nb*R))/ \
  pow((Mb + c3*Na - c1*Ma*R - c2*Nb*R),2)))/(4*Na*(-c3 + c1*c2*R)*         \
  math.sqrt(1 + (4*(-c3 + c1*c2*R)*(Mb*Na - Ma*Nb*R))/                        \
  pow((Mb + c3*Na - c1*Ma*R - c2*Nb*R),2))) -                                 \
  (Nb*R*(-1 + math.sqrt(1 + (4*(-c3 + c1*c2*R)*(Mb*Na - Ma*Nb*R))/         \
  pow((Mb + c3*Na - c1*Ma*R - c2*Nb*R),2))))/(2*Na*(-c3 + c1*c2*R)) -      \
  (c1*R*(Mb + c3*Na - c1*Ma*R - c2*Nb*R)*                                  \
  (-1 + math.sqrt(1 + (4*(-c3 + c1*c2*R)*(Mb*Na - Ma*Nb*R))/                  \
  pow((Mb + c3*Na - c1*Ma*R - c2*Nb*R),2))))/(2*Na*pow((-c3 + c1*c2*R),2)) 





def Dc3(Na,Nb,Ma,Mb,c1,c2,c3,R):

  return \
  ((Mb + c3*Na - c1*Ma*R - c2*Nb*R)*((-8*Na*(-c3 + c1*c2*R)*(Mb*Na - Ma*Nb*R))/ \
  pow((Mb + c3*Na - c1*Ma*R - c2*Nb*R),3) - (4*(Mb*Na - Ma*Nb*R))/                 \
  pow((Mb + c3*Na - c1*Ma*R - c2*Nb*R),2)))/(4*Na*(-c3 + c1*c2*R)*                 \
  math.sqrt(1 + (4*(-c3 + c1*c2*R)*(Mb*Na - Ma*Nb*R))/                                \
  pow((Mb + c3*Na - c1*Ma*R - c2*Nb*R),2))) +                                         \
  (-1 + math.sqrt(1 + (4*(-c3 + c1*c2*R)*(Mb*Na - Ma*Nb*R))/                          \
  pow((Mb + c3*Na - c1*Ma*R - c2*Nb*R),2)))/(2*(-c3 + c1*c2*R)) +                  \
  ((Mb + c3*Na - c1*Ma*R - c2*Nb*R)*                                                  \
  (-1 + math.sqrt(1 + (4*(-c3 + c1*c2*R)*(Mb*Na - Ma*Nb*R))/                          \
  pow((Mb + c3*Na - c1*Ma*R - c2*Nb*R),2))))/(2*Na*pow((-c3 + c1*c2*R),2))         





def DR(Na,Nb,Ma,Mb,c1,c2,c3,R):

  return \
  ((Mb + c3*Na - c1*Ma*R - c2*Nb*R)*((-4*Ma*Nb*(-c3 + c1*c2*R))/               \
  pow((Mb + c3*Na - c1*Ma*R - c2*Nb*R),2) -                                       \
  (8*(-(c1*Ma) - c2*Nb)*(-c3 + c1*c2*R)*(Mb*Na - Ma*Nb*R))/                       \
  pow((Mb + c3*Na - c1*Ma*R - c2*Nb*R),3) + (4*c1*c2*(Mb*Na - Ma*Nb*R))/       \
  pow((Mb + c3*Na - c1*Ma*R - c2*Nb*R),2)))/(4*Na*(-c3 + c1*c2*R)*             \
  math.sqrt(1 + (4*(-c3 + c1*c2*R)*(Mb*Na - Ma*Nb*R))/                            \
  pow((Mb + c3*Na - c1*Ma*R - c2*Nb*R),2))) +                                     \
  ((-(c1*Ma) - c2*Nb)*(-1 + math.sqrt(1 + (4*(-c3 + c1*c2*R)*(Mb*Na - Ma*Nb*R))/  \
  pow((Mb + c3*Na - c1*Ma*R - c2*Nb*R),2))))/(2*Na*(-c3 + c1*c2*R)) -          \
  (c1*c2*(Mb + c3*Na - c1*Ma*R - c2*Nb*R)*                                        \
  (-1 + math.sqrt(1 + (4*(-c3 + c1*c2*R)*(Mb*Na - Ma*Nb*R))/                      \
  pow((Mb + c3*Na - c1*Ma*R - c2*Nb*R),2))))/(2*Na*pow((-c3 + c1*c2*R),2))     




