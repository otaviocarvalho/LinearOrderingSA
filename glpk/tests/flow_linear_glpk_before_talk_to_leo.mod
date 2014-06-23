param n, integer;
param givens{0..n-1, 0..n-1}, integer, >=0, <=n, default 0;

var x{i in 0..n-1, j in 0..n-1}, binary;
/* x[i,j] = 1 means that cell [i] is assigned to number j

maximize linearordering: sum{i in 0..n-1, j in 0..n-1, k in 0..n-1, l in 0..n-1} abs((x[i,j]*j) - (x[k,l]*l));

s.t. xra{i in 0..n-1, j in 0..n-1: givens[i] != 0}:
        x[i,j] = (if givens[i] = j then 1 else 0);
/* assign pre-defined numbers using the 'givens' */

s.t. xrb{i in 0..n-1}: sum{j in 0..n-1} x[i,j] = 1;
/* each cell must be assigned to exactly one number */

s.t. xrc{j in 0..n-1}: sum{i in 0..n-1} x[i,j] = 1;
/* cells must be assigned to distinct numbers */

solve;

for {i in 0..n-1}{
    for {j in 0..n-1}{
      printf " %d", x[i,j]*j;
      for {0..0: j = n-1} printf("\n");
   }
}
printf("\n");
for {k in 0..n-1}{
    for {l in 0..n-1}{
      printf " %d", x[k,l]*l;
      for {0..0: l = n-1} printf("\n");
   }
}
printf("\n");
for {i in 0..n-1}{
    for {j in 0..n-1}{
        for {k in 0..n-1}{
            for {l in 0..n-1}{
                printf "%d %d:%d - %d %d:%d - %d\n", i,j,x[i,j],k,l,x[k,l], abs(x[i,j]*j - x[k,l]*l);
            }
        }
    }
}
printf("\n");
printf "%d\n", sum{i in 0..n-1, j in 0..n-1, k in 0..n-1, l in 0..n-1: givens[i,j] != 0} abs((x[i,j]*j) - (x[k,l]*l));

data;

    param n := 3;
    param givens : 0 1 2 :=
                0  0 1 0
                1  1 0 1
                2  0 1 0
        ;

end;
