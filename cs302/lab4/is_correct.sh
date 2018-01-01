Labdir=/home/plank/cs302/Labs/Lab4

if [ $# -lt 5 ]; then
  sh $Labdir/ic_usage.sh >&2
  exit 1
fi

n=$1
m=$2
s=$3
r=$4
w=$5

args=`echo $m $s | awk '{ print $1+$2+6 }'`
mps=`echo $m $s | awk '{ print $1+$2 }'`
if [ $# != $args ]; then
  sh $Labdir/ic_usage.sh >&2
  exit 1
fi
  
shift
shift
shift
shift
shift
a=$1
i=1
shift
while [ $i -lt $mps ]; do
  a=$a" "$1
  i=`echo $i | awk '{ print $1+1 }'`
  shift
done

if [ $1 = OK ]; then
  ans=`$Labdir/is_jls $n $m $s $r $w $a | tail -n 1 | awk '{ print $NF }'`
  if [ $ans != OK ]; then
    echo "Incorrect: You say OK, but it is not JLS because of scenario $ans"
  else 
    echo 'Correct'
  fi
else
  inv=`echo $1 | $Labdir/test_failures $n $m $s $r $w $a | grep "Not invertible" | wc | awk '{ print $1 }'`
  if [ $inv = 1 ]; then
    echo "Correct"
  else 
    echo "Incorrect: The failure scenario is either illegal or invertible (run test_failures on it)"
  fi
fi
