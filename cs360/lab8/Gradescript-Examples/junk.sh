for i in *input.txt ; do
  sed 's/[^|]//g' < $i | wc
done
