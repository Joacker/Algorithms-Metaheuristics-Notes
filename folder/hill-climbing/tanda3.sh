files=("ex2_1_9bis.bch")
#"ex6_2_8.bch" "ex6_1_3bis.bch" "ex6_2_12.bch" "launch.bch"
for file in ${files[@]}
do
  for seed in {1..5}
  do
    for i in {1..5}
    do
       ./__build__/src/ibexopt benchs/optim/blowup/$file --random-seed=$seed >> V1_tanda3.log
    done
  done
done