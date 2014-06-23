/*
    Mapear problema: (http://www.optsicom.es/lolib/#instances)
        max sum(i,j pertencente a An) Cij*Xij
    s.a.
        Xij + Xji = 1, para todo i,j pertencente a Vn, i<j
        Xij + Xjk + Xki <= 2, para todo i,j,k pertencente a Vn, i<j, i<k, j!=k
        Xij binário, para todo i,j pertencente a Vn
*/

set VERTICES;
set ARCS within (VERTICES cross VERTICES);
param capacity{ARCS};

param n:= 5;
param m := 8;

set I := {1..n};

param a{i in I};
var x{(i,j) in ARCS} binary;

maximize cost: sum{i in I, j in I} ((a[i]*x[i]) - (a[j]*x[j]));
printf{i in I, j in I} a[i];

data;

    param : a :=
            1   5
            2   6
            3   7
            4   8
        ;
end;
