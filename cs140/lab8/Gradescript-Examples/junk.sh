sleep 1 ; random_names 1000 | a.out 010 -1 | egrep 'INSERT|PRINT' > 066.txt
sleep 1 ; random_names 1000 | a.out 020 -1 | egrep 'INSERT|PRINT' > 067.txt
sleep 1 ; random_names 1000 | a.out 030 -1 | egrep 'INSERT|PRINT' > 068.txt
sleep 1 ; random_names 1000 | a.out 080 -1 | egrep 'INSERT|PRINT' > 069.txt
sleep 1 ; random_names 1000 | a.out 100 -1 | egrep 'INSERT|PRINT' > 070.txt
sleep 1 ; random_names 1000 | a.out 999 -1 | egrep 'INSERT|PRINT' > 071.txt
sleep 1 ; random_names 1000 | a.out 020 -1 | egrep 'INSERT|PRESENT|PRINT' >  072.txt
sleep 1 ; random_names 1000 | a.out 050 -1 | egrep 'INSERT|PRESENT|PRINT' >  073.txt
sleep 1 ; random_names 1000 | a.out 100 -1 | egrep 'INSERT|PRESENT|PRINT' >  074.txt
sleep 1 ; random_names 1000 | a.out 500 -1 | egrep 'INSERT|PRESENT|PRINT' >  075.txt
sleep 1 ; random_names 1000 | a.out 999 -1 | egrep 'INSERT|PRESENT|PRINT' >  076.txt
sleep 1 ; random_names 1000 | a.out 020 -1 | sed '/STRIP/d' | sed '/#/d' > 077.txt
sleep 1 ; random_names 1000 | a.out 050 -1 | sed '/STRIP/d' | sed '/#/d' > 078.txt
sleep 1 ; random_names 1000 | a.out 100 -1 | sed '/STRIP/d' | sed '/#/d' > 079.txt
sleep 1 ; random_names 1000 | a.out 500 -1 | sed '/STRIP/d' | sed '/#/d' > 080.txt
sleep 1 ; random_names 1000 | a.out 999 -1 | sed '/STRIP/d' | sed '/#/d' > 081.txt
sleep 1 ; random_names 1000 | a.out 020 -1 > 082.txt
sleep 1 ; random_names 1000 | a.out 020 -1 > 083.txt
sleep 1 ; random_names 1000 | a.out 030 -1 > 084.txt
sleep 1 ; random_names 1000 | a.out 030 -1 > 085.txt
sleep 1 ; random_names 1000 | a.out 040 -1 > 086.txt
sleep 1 ; random_names 1000 | a.out 040 -1 > 087.txt
sleep 1 ; random_names 1000 | a.out 050 -1 > 088.txt
sleep 1 ; random_names 1000 | a.out 050 -1 > 089.txt
sleep 1 ; random_names 1000 | a.out 100 -1 > 090.txt
sleep 1 ; random_names 1000 | a.out 100 -1 > 091.txt
sleep 1 ; random_names 1000 | a.out 150 -1 > 092.txt
sleep 1 ; random_names 1000 | a.out 150 -1 > 093.txt
sleep 1 ; random_names 1000 | a.out 150 -1 > 094.txt
sleep 1 ; random_names 1000 | a.out 200 -1 > 095.txt
sleep 1 ; random_names 1000 | a.out 200 -1 > 096.txt
sleep 1 ; random_names 1000 | a.out 500 -1 > 097.txt
sleep 1 ; random_names 1000 | a.out 500 -1 > 098.txt
sleep 1 ; random_names 1000 | a.out 999 -1 > 099.txt
sleep 1 ; random_names 1000 | a.out 999 -1 > 100.txt
