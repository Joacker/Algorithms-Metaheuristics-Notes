files=("hs102")
#"ex6_2_8.bch" "ex6_1_3bis.bch" "ex6_2_12.bch" "launch.bch"
for file in ${files[@]}
do
  for seed in {2..5}
  do
    for i in {1..3}
    do
      ./__build__/src/ibexopt benchs/optim/with10valorless/$file --random-seed=$seed >> tanda2.log
    done
  done
done