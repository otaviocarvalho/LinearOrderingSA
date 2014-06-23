/* glpsol --model flow_linear_glpk.mod --data graph_5_8.dat */
set VERTICES;
set ARCS within (VERTICES cross VERTICES);

param capacity{ARCS};
param weight{ARCS};
param demand{VERTICES} default 0;

var x{(i,j) in ARCS} >= 0;

minimize cost: sum{(i,j) in ARCS} x[i,j]*weight[i,j];

s.t. CAP {(i,j) in ARCS}: x[i,j]<=capacity[i,j];

s.t. BALANCE{i in VERTICES}:
          sum{j in VERTICES: (i,j) in ARCS} x[i,j] 
        - sum{j in VERTICES: (j,i) in ARCS} x[j,i]
        = demand[i];

data;
    param: VERTICES: demand := 
            1     5
            2     5
            3     0 
            4     0
            5    -10
        ;

    param: ARCS: capacity weight := 
            1     2     6    10
            1     3     2     6
            1     4     2     5
            2     3     4     3
            2     5     4     5	    
            3     5     5     9
            4     3     6     3
            4     5     4    10
        ;

end;
