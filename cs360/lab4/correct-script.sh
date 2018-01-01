ge=/home/plank/cs360/labs/lab4/Gradescript-Examples
rm -f testmain.c tf1.c tf2.c tf3.c tf4.c tf0.c s1_header.h s2_header.h
rm -f testmain.o tf1.o tf2.o tf3.o tf4.o tf0.o testexec testlib.a
cp $ge/allfile.c testmain.c
sed 's/first/first/' $ge/oneline-0.c > tf0.c
sed 's/first/second/' $ge/oneline-1.c > tf1.c
sed 's/first/third/' $ge/oneline-5.c > tf2.c
sed 's/first/fourth/' $ge/using_s1.c > tf3.c
cp $ge/s1_header-0.h s1_header.h
sed 's/first/fifth/' $ge/oneline-3.c > tf4.c
gcc -c tf0.c
gcc -c tf1.c
gcc -c tf2.c
ar ru testlib.a > /dev/null 2>&1 tf0.o tf1.o tf2.o
ranlib testlib.a
gcc -c testmain.c
touch -t 01011100.30 testmain.c
touch -t 01011100.35 testmain.o
gcc -c tf3.c
touch -t 01011101.30 tf3.c
touch -t 01011101.35 tf3.o
gcc -c tf4.c
touch -t 01011102.30 tf4.c
touch -t 01011102.35 tf4.o
touch -t 01011000.30 s1_header.h
gcc -o testexec testmain.c tf1.c tf2.c tf3.c tf4.c tf0.c -lm
touch -t 01011103.35 testexec
if /home/plank/cs360/labs/lab4/fakemake $ge/100.fm; then
  ./testexec
fi