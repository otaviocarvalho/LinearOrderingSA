param n;
/*param k{0..n-1}, integer, >=0, <=n, default 0;*/
/*set k{0..2};*/

param x{u in 0..2, v in 0..2};

minimize lop: sum{u in 0..2, v in 0..2} ( (sum{i in 0..2} (x[u,i]*i)) - (sum{j in 0..2} (x[v,j]*j)) );

/*s.t. xvk{i in 0..2}:*/
        /*sum{j in 0..2} x[i,j] = 1;*/

s.t. xvk{i in 0..2, j in 0..2: x[i,j] != 0}:
        x[i,j] = (if x[i] = j then 1 else 0);

solve;

for {u in 0..2}{
    for {v in 0..2}{
        /*printf "%d\n", ( sum{u in 0..2, v in 0..2} ( (sum{i in 0..2} (x[u,i]*i)) - (sum{j in 0..2} (x[v,j]*j)) ) );*/
        printf "sum x[u,v]*i: %d\n", (sum{i in 0..2} x[u,v]*i);
    }
    printf "\n";
}

data;
    param n := 2;

    param x :  0 1 2 :=
            0  0 1 0
            1  1 0 1
            2  0 1 0
        ;

end;
