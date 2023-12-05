./waf configure --lp-lib=soplex --interval-lib=gaol --lp-lib=soplex
./waf install
./__build__/src/ibexopt benchs/optim/medium/ex2_1_8.bch --random-seed=1