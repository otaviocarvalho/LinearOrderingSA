param n:= 5;
param m := 8;

set I := {1..n};

param a{i in I};
var x{i in I} binary;

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
