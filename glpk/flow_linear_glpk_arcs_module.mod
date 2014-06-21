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
param weight{ARCS};
param vert{VERTICES};

var x{(i,j) in ARCS} binary;

maximize linearordering: sum{(i,j) in ARCS} weight[i,j]*x[i,j];
/*printf{i in I, j in I} a[i];*/

/*
s.t. ORDER{i in VERTICES, j in VERTICES}:
    x[i,j] + x[j,i] = 1 AND i<j

s.t. TRANSITIVEORDER{i in VERTICES, j in VERTICES, k in VERTICES}:
       x[i,j] + x[j,k] + x[j,i] <= 2 AND i<j AND i<k AND j!=k
*/

data;
    param: VERTICES: vert :=
            0   1
            1   1
            2   1
            3   1
            4   1
        ;

    param: ARCS: weight :=
            0     1     1
            0     3     3
            0     4     4
            1     2     1
            1     4     3
            2     3     1
            2     4     2
            3     4     1
        ;

    /* digrafo completo */
    /*
    param: ARCS: weight :=
            0     0     0
            0     1     1
            0     2     0
            0     3     3
            0     4     4
            1     0     1
            1     1     0
            1     2     1
            1     3     0
            1     4     3
            2     0     0
            2     1     1
            2     2     0
            2     3     1
            2     4     2
            3     0     0
            3     1     0
            3     2     1
            3     3     0
            3     4     1
            4     0     4
            4     1     3
            4     2     2
            4     3     1
            4     4     0
        ;
    */

end;
