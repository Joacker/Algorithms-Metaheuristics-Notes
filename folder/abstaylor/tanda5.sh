files=("himmel16.bch" "ex2_1_7.bch" "ex2_1_8.bch" "launch.bch")
#"ex6_2_8.bch" "ex6_1_3bis.bch" "ex6_2_12.bch" "launch.bch"
for file in ${files[@]}
do
  for seed in {1..5}
  do
    for i in {1..5}
    do
      ./__build__/src/ibexopt benchs/optim/medium/$file --random-seed=$seed >> tanda5.log
    done
  done
done