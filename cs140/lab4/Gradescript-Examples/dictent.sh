for i do
  echo `echo $i | openssl md5`  $i
done
