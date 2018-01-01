i=002
while [ $i -le 5 ]; do
  randnum < junk-empty.txt | tfill -c 34 | sed -n "$i"p | awk '{ printf "CREATE %.0lf %.0lf %.0lf\n", $1*10+1, $2*10+2, $3*254+1 }' > $i.txt
  i=`echo $i | awk '{ printf "%03d\n", $1+1 }'`
done

while [ $i -le 10 ]; do
  randnum < junk-empty.txt | tfill -c 34 | sed -n "$i"p | awk '{ printf "CREATE %.0lf %.0lf %.0lf\n", $1*100+1, $2*100+2, $3*254+1 }' > $i.txt
  i=`echo $i | awk '{ printf "%03d\n", $1+1 }'`
done
while [ $i -le 20 ]; do
  echo "CW" > $i.txt
  i=`echo $i | awk '{ printf "%03d\n", $1+1 }'`
done
while [ $i -le 30 ]; do
  echo "CCW" > $i.txt
  i=`echo $i | awk '{ printf "%03d\n", $1+1 }'`
done

while [ $i -le 53 ]; do
  randnum < junk-empty.txt | tfill -c 34 | sed -n "$i"p | awk '{ printf "PAD %.0lf %.0lf\n", $1*50+1, $3*254+1 }' > $i.txt
  i=`echo $i | awk '{ printf "%03d\n", $1+1 }'`
done

while [ $i -le 76 ]; do
  randnum < junk-empty.txt | tfill -c 34 | sed -n "$i"p | awk '{ printf "PANEL %.0lf %.0lf\n", $1*10+1, $3*10+1 }' > $i.txt
  i=`echo $i | awk '{ printf "%03d\n", $1+1 }'`
done

while [ $i -le 100 ]; do
  randnum < junk-empty.txt | tfill -c 45 | sed -n "$i"p | awk '{ printf "CROP %.0lf %.0lf %.0lf %.0lf\n", $1*10+1, $2*10+1, $3*20+1, $4*20+1 }' > $i.txt
  i=`echo $i | awk '{ printf "%03d\n", $1+1 }'`
done

