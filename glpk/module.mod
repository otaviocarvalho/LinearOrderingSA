set n := 1..3;
set m := 1..3;

param a{i in n};
param b{i in m};
var x, binary;

maximize cost: sum{i in n, j in m} abs(a[i]+b[j]);

solve;

for {i in 1..3}{
    for {j in 1..3}{
      printf "|%d - %d| == %d\n", a[i], b[j], abs(a[i]-b[j]);
   }
}
printf "\n %d \n", (sum{i in n, j in m} (a[i]+b[j]));

data;
    param a := 1 0
               2 0
               3 0
        ;
    param b := 1 -1
               2 -1
               3 -1
        ;
end;
