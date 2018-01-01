random_names 100 > tmp-rn.txt
randnum < tmp-rn.txt | sed 's/ .*//' > tmp-num.txt

d=/home/plank/cs140/Labs/Lab4/Gradescript-Examples/

# for i in 001 002 003 004 005 006 007 ; do
#   sed -n $i"p" tmp-rn.txt | genrandom 1 1 > $i-input.txt
#   n=`sed -n $i"p" tmp-num.txt`
#   j=`echo $i | awk '{ printf "%d\n", $1/2 }'`
#   echo $n $i $j | awk '{ printf("%.0lf %s %s\n", $1*15+2, ($2%2) ? "Last7" : "XOR", ($3%2) ? "Linear" : "Double" ) }' > $i-cli.txt
#   sleep 1
# done

# i=008
# while [ $i -le 14 ]; do
#   sed -n $i"p" tmp-rn.txt | genrandom 1 0 1 > $i-input.txt
#   n=`sed -n $i"p" tmp-num.txt`
#   j=`echo $i | awk '{ printf "%d\n", $1/2 }'`
#   echo $n $i $j | awk '{ printf("%.0lf %s %s\n", $1*15+2, ($2%2) ? "Last7" : "XOR", ($3%2) ? "Linear" : "Double" ) }' > $i-cli.txt
#   sleep 1
#   i=`echo $i | awk '{ printf "%03d\n", $1+1 }'`
# done

# i=015
# while [ $i -le 21 ]; do
#   echo $i
#   sed -n $i"p" tmp-rn.txt | genrandom 1 0 0 1 > $i-input.txt
#   n=`sed -n $i"p" tmp-num.txt`
#   j=`echo $i | awk '{ printf "%d\n", $1/2 }'`
#   echo $n $i $j | awk '{ printf("%.0lf %s %s\n", $1*15+2, ($2%2) ? "Last7" : "XOR", ($3%2) ? "Linear" : "Double" ) }' > $i-cli.txt
#   sleep 1
#   i=`echo $i | awk '{ printf "%03d\n", $1+1 }'`
# done

# i=022
# while [ $i -le 28 ]; do
#   echo $i
#   n=`sed -n $i"p" tmp-num.txt`
#   j=`echo $i | awk '{ printf "%d\n", $1/2 }'`
#   echo $n $i $j | awk '{ printf("%.0lf %s %s\n", $1*15+5, ($2%2) ? "Last7" : "XOR", ($3%2) ? "Linear" : "Double" ) }' > $i-cli.txt
#   i=`echo $i | awk '{ printf "%03d\n", $1+1 }'`
# done

# i=029
# while [ $i -le 35 ]; do
#   sleep 1
#   echo $i
#   n=`sed -n $i"p" tmp-num.txt`
#   j=`echo $i | awk '{ printf "%d\n", $1/2 }'`
#   ts=`echo $n | awk '{ printf("%.0lf\n", $1*15+10 ) }'`
#   ne=`echo $ts | awk '{ printf("%d\n", $1/2) }'`
#   echo $n $ne $ts
#   echo $ts $i $j | awk '{ printf("%d %s %s\n", $1, ($2%2) ? "Last7" : "XOR", ($3%2) ? "Linear" : "Double" ) }' > $i-cli.txt
#   random_names $ne | sed 's/ /-/g' | genrandom $ne 0 0 1 > $i-input.txt
#   i=`echo $i | awk '{ printf "%03d\n", $1+1 }'`
# done

# i=036
# while [ $i -le 42 ]; do
#   sleep 1
#   echo $i
#   n=`sed -n $i"p" tmp-num.txt`
#   j=`echo $i | awk '{ printf "%d\n", $1/2 }'`
#   ts=`echo $n | awk '{ printf("%.0lf\n", $1*15+20 ) }'`
#   ne=`echo $ts | awk '{ printf("%d\n", $1/2) }'`
#   echo $n $ne $ts
#   echo $ts $i $j | awk '{ printf("%d %s %s\n", $1, ($2%2) ? "Last7" : "XOR", ($3%2) ? "Linear" : "Double" ) }' > $i-cli.txt
#   random_names $ne | sed 's/ /-/g' | genrandom $ne 0 0 0 1 > $i-input.txt
#   i=`echo $i | awk '{ printf "%03d\n", $1+1 }'`
# done

# i=043
# while [ $i -le 49 ]; do
#   sleep 1
#   echo $i
#   n=`sed -n $i"p" tmp-num.txt`
#   j=`echo $i | awk '{ printf "%d\n", $1/2 }'`
#   ts=`echo $n | awk '{ printf("%.0lf\n", $1*15+20 ) }'`
#   ne=`echo $ts | awk '{ printf("%d\n", $1/2) }'`
#   echo $n $ne $ts
#   echo $ts $i $j | awk '{ printf("%d %s %s\n", $1, ($2%2) ? "Last7" : "XOR", ($3%2) ? "Linear" : "Double" ) }' > $i-cli.txt
#   random_names $ts | sed 's/ /-/g' | genrandom $ts $ne $ne 0 0 > $i-input.txt
#   i=`echo $i | awk '{ printf "%03d\n", $1+1 }'`
# done

# i=050
# while [ $i -le 56 ]; do
#   sleep 1
#   echo $i
#   n=`sed -n $i"p" tmp-num.txt`
#   j=`echo $i | awk '{ printf "%d\n", $1/2 }'`
#   ts=`echo $n | awk '{ printf("%.0lf\n", $1*15+20 ) }'`
#   ne=`echo $ts | awk '{ printf("%d\n", $1+1) }'`
#   echo $n $ne $ts
#   echo $ts $i $j | awk '{ printf("%d %s %s\n", $1, ($2%2) ? "Last7" : "XOR", ($3%2) ? "Linear" : "Double" ) }' > $i-cli.txt
#   random_names $ne | sed 's/ /-/g' | genrandom $ne > $i-input.txt
#   i=`echo $i | awk '{ printf "%03d\n", $1+1 }'`
# done
# 
# i=057
# while [ $i -le 63 ]; do
#   sleep 1
#   echo $i
#   n=`sed -n $i"p" tmp-num.txt`
#   j=0
#   ts=`echo $n | awk '{ printf("%.0lf\n", $1*15+20 ) }'`
#   ne=`echo $ts | awk '{ printf("%d\n", $1+1) }'`
#   echo $n $ne $ts
#   echo $ts $i $j | awk '{ printf("%d %s %s\n", $1, ($2%2) ? "Last7" : "XOR", ($3%2) ? "Linear" : "Double" ) }' > $i-cli.txt
#   random_names $ne | sed 's/ /-/g' | genrandom $ne > $i-input.txt
#   i=`echo $i | awk '{ printf "%03d\n", $1+1 }'`
# done

i=064
while [ $i -le 100 ]; do
  random_names 100 | sed 's/ /-/g' > tmp-rn.txt
  randnum < tmp-rn.txt | sed 's/ .*//' > tmp-num.txt
  n=`sed -n 1"p" tmp-num.txt`
  n2=`sed -n 2"p" tmp-num.txt`
  n3=`sed -n 3"p" tmp-num.txt`
  n4=`sed -n 4"p" tmp-num.txt`
  n5=`sed -n 5"p" tmp-num.txt`
  n6=`sed -n 6"p" tmp-num.txt`
  sh dictent.sh `cat tmp-rn.txt` | sed 's/-/ /g' > $i-dict.txt
  random_names 500 | sed 's/ /-/g' | sed '1,100d' > tmp-rn.txt
  
  echo $i
  j=`echo $i | awk '{ printf "%d\n", $1/2 }'`
  ts=`echo $n | awk '{ printf("%.0lf\n", $1*100+150 ) }'`
  ne=`echo $n2 $ts | awk '{ printf("%.0lf\n", $1*($2/6)+10) }'`
  nf=`echo $n3 $ts | awk '{ printf("%.0lf\n", $1*($2/2)) }'`
  nm=`echo $n4 $ts | awk '{ printf("%.0lf\n", $1*($2/2)) }'`
  nt=6
  np=2
  echo $ts $i $j $d | awk '{ printf("%d %s %s %s%s-dict.txt\n", $1, ($2%2) ? "Last7" : "XOR", ($3%2) ? "Linear" : "Double",  $4, $2) }' > $i-cli.txt
  cat tmp-rn.txt | genrandom $ne $nf $nm $np $nt $i-dict.txt > $i-input.txt
  sleep 1
  i=`echo $i | awk '{ printf "%03d\n", $1+1 }'`
done

