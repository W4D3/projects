for i in *.script ; do
  echo $i
  sed 's/lab4/lab5/g' $i > backup/$i
done
