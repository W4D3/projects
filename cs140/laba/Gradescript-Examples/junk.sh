for i in  \
090.txt \
091.txt \
092.txt \
093.txt \
094.txt \
095.txt \
096.txt \
097.txt \
098.txt \
100.txt \
099.txt ; do\
  random_names 1000 | genins 100 > $i
  echo $i
  sleep 1
done
