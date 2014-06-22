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

s.t. ORDER{i in VERTICES, j in VERTICES: i < j}:
    x[i,j] + x[j,i] = 1;

s.t. TRANSITIVEORDER{i in VERTICES, j in VERTICES, k in VERTICES: i < j and i < k and j != k}:
       x[i,j] + x[j,k] + x[k,i] <= 2;

solve;

/*for {i in VERTICES}{*/
    /*for {j in VERTICES}{*/
        /*printf "%d %d %d", weight[i,j], x[i,j], sum{(i,j) in ARCS} weight[i,j]*x[i,j];*/
    /*}*/
/*}*/

data;
    param: VERTICES: vert :=
            0   0
            1   1
            2   2
            3   3
            4   4
        ;

/*
    param: ARCS: weight :=
            1   1   0
            1   2   1
            1   3   0
            1   4   3
            1   5   0
            1   6   5
            2   1   0
            2   2   0
            2   3   0
            2   4   0
            2   5   3
            2   6   4
            3   1   0
            3   2   0
            3   3   0
            3   4   0
            3   5   2
            3   6   0
            4   1   0
            4   2   0
            4   3   0
            4   4   0
            4   5   0
            4   6   2
            5   1   0
            5   2   0
            5   3   0
            5   4   0
            5   5   0
            5   6   0
            6   1   0
            6   2   0
            6   3   0
            6   4   0
            6   5   0
            6   6   0
        ;
*/

    /* digrafo completo */
    param: ARCS: weight :=
            0     0     0
            0     1     1
            0     2     0
            0     3     3
            0     4     4
            1     0     0
            1     1     0
            1     2     1
            1     3     0
            1     4     3
            2     0     0
            2     1     0
            2     2     0
            2     3     1
            2     4     2
            3     0     0
            3     1     0
            3     2     0
            3     3     0
            3     4     1
            4     0     0
            4     1     0
            4     2     0
            4     3     0
            4     4     0
        ;

end;
