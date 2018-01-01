echo "" > 001.txt
cp ../comp-1.txt 002.txt
cp ../comp-2.txt 003.txt

randcompress 1000 i 30 0 | sed 's/^ *//' | sed -n 1p > 004-uncompressed.txt
randcompress 1000 i 30 0 | sed 's/^ *//' | sed -n 2p > 005-uncompressed.txt
randcompress 1000 i 30 0 | sed 's/^ *//' | sed -n 3p > 006-uncompressed.txt
randcompress 1000 i 30 0 | sed 's/^ *//' | sed -n 5p > 007-uncompressed.txt
randcompress 1000 i 30 0 | sed 's/^ *//' | sed -n 6p > 008-uncompressed.txt
randcompress 1000 i 30 0 | sed 's/^ *//' | sed -n 7p > 009-uncompressed.txt

randcompress 1000 d 30 0 | sed 's/^ *//' | sed -n 8p > 010-uncompressed.txt
randcompress 1000 d 30 0 | sed 's/^ *//' | sed -n 9p > 011-uncompressed.txt
randcompress 1000 d 30 0 | sed 's/^ *//' | sed -n 10p > 012-uncompressed.txt
randcompress 1000 d 30 0 | sed 's/^ *//' | sed -n 11p > 013-uncompressed.txt
randcompress 1000 d 30 0 | sed 's/^ *//' | sed -n 12p > 014-uncompressed.txt

randcompress 1000 s 30 12 | sed 's/^ *//' | sed -n 13p > 015-uncompressed.txt
randcompress 1000 s 30 12 | sed 's/^ *//' | sed -n 14p > 016-uncompressed.txt
randcompress 1000 s 30 12 | sed 's/^ *//' | sed -n 15p > 017-uncompressed.txt
randcompress 1000 s 30 12 | sed 's/^ *//' | sed -n 16p > 018-uncompressed.txt
randcompress 1000 s 30 12 | sed 's/^ *//' | sed -n 17p > 019-uncompressed.txt

randcompress 1000 id 30 0 | sed 's/^ *//' | sed -n 20,29p > 020-uncompressed.txt
randcompress 1000 id 30 0 | sed 's/^ *//' | sed -n 30,39p > 021-uncompressed.txt
randcompress 1000 id 30 0 | sed 's/^ *//' | sed -n 40,49p > 022-uncompressed.txt
randcompress 1000 id 30 0 | sed 's/^ *//' | sed -n 50,59p > 023-uncompressed.txt
randcompress 1000 id 30 0 | sed 's/^ *//' | sed -n 60,69p > 024-uncompressed.txt

randcompress 1000 is 30 12 | sed 's/^ *//' | sed -n 100,109p > 025-uncompressed.txt
randcompress 1000 is 30 12 | sed 's/^ *//' | sed -n 110,119p > 026-uncompressed.txt
randcompress 1000 is 30 12 | sed 's/^ *//' | sed -n 120,129p > 027-uncompressed.txt
randcompress 1000 is 30 12 | sed 's/^ *//' | sed -n 130,139p > 028-uncompressed.txt
randcompress 1000 is 30 12 | sed 's/^ *//' | sed -n 140,149p > 029-uncompressed.txt

randcompress 1000 sd 30 12 | sed 's/^ *//' | sed -n 200,209p > 030-uncompressed.txt
randcompress 1000 sd 30 12 | sed 's/^ *//' | sed -n 210,219p > 031-uncompressed.txt
randcompress 1000 sd 30 12 | sed 's/^ *//' | sed -n 220,229p > 032-uncompressed.txt
randcompress 1000 sd 30 12 | sed 's/^ *//' | sed -n 230,239p > 033-uncompressed.txt
randcompress 1000 sd 30 12 | sed 's/^ *//' | sed -n 240,249p > 034-uncompressed.txt

randcompress 2000 s 30 ONLY-256 | sed 's/^ *//' | sed -n 250,259p > 035-uncompressed.txt
randcompress 2000 s 30 ONLY-256 | sed 's/^ *//' | sed -n 260,269p > 036-uncompressed.txt
randcompress 2000 s 30 ONLY-256 | sed 's/^ *//' | sed -n 270,279p > 037-uncompressed.txt
randcompress 2000 s 30 ONLY-256 | sed 's/^ *//' | sed -n 280,289p > 038-uncompressed.txt
randcompress 2000 s 30 ONLY-256 | sed 's/^ *//' | sed -n 290,299p > 039-uncompressed.txt

randcompress 2000 sid 300 ONLY-256 | sed 's/^ *//' | sed -n 300,309p > 040-uncompressed.txt
randcompress 2000 sid 300 ONLY-256 | sed 's/^ *//' | sed -n 310,319p > 041-uncompressed.txt
randcompress 2000 sid 300 ONLY-256 | sed 's/^ *//' | sed -n 320,329p > 042-uncompressed.txt
randcompress 2000 sid 300 ONLY-256 | sed 's/^ *//' | sed -n 330,339p > 043-uncompressed.txt
randcompress 2000 sid 300 ONLY-256 | sed 's/^ *//' | sed -n 340,349p > 044-uncompressed.txt
randcompress 2000 sid 300 ONLY-256 | sed 's/^ *//' | sed -n 350,359p > 045-uncompressed.txt
randcompress 2000 sid 300 ONLY-256 | sed 's/^ *//' | sed -n 360,369p > 046-uncompressed.txt
randcompress 2000 sid 300 ONLY-256 | sed 's/^ *//' | sed -n 370,379p > 047-uncompressed.txt
randcompress 2000 sid 300 ONLY-256 | sed 's/^ *//' | sed -n 380,389p > 048-uncompressed.txt
randcompress 2000 sid 300 ONLY-256 | sed 's/^ *//' | sed -n 390,399p > 049-uncompressed.txt


sleep 1

randcompress 2000 sid 300 ONLY-256 | sed 's/^ *//' | sed -n 300,309p > 050-uncompressed.txt
randcompress 2000 sid 300 ONLY-256 | sed 's/^ *//' | sed -n 310,319p > 051-uncompressed.txt
randcompress 2000 sid 300 ONLY-256 | sed 's/^ *//' | sed -n 320,329p > 052-uncompressed.txt
randcompress 2000 sid 300 ONLY-256 | sed 's/^ *//' | sed -n 330,339p > 053-uncompressed.txt
randcompress 2000 sid 300 ONLY-256 | sed 's/^ *//' | sed -n 340,349p > 054-uncompressed.txt
randcompress 2000 sid 300 ONLY-256 | sed 's/^ *//' | sed -n 350,359p > 055-uncompressed.txt
randcompress 2000 sid 300 ONLY-256 | sed 's/^ *//' | sed -n 360,369p > 056-uncompressed.txt
randcompress 2000 sid 300 ONLY-256 | sed 's/^ *//' | sed -n 370,379p > 057-uncompressed.txt
randcompress 2000 sid 300 ONLY-256 | sed 's/^ *//' | sed -n 380,389p > 058-uncompressed.txt
randcompress 2000 sid 300 ONLY-256 | sed 's/^ *//' | sed -n 390,399p > 059-uncompressed.txt

randcompress 2000 sid 1000 256 | sed 's/^ *//' | sed -n 200,209p > 060-uncompressed.txt
randcompress 2000 sid 1000 256 | sed 's/^ *//' | sed -n 210,219p > 061-uncompressed.txt
randcompress 2000 sid 1000 256 | sed 's/^ *//' | sed -n 220,229p > 062-uncompressed.txt
randcompress 2000 sid 1000 256 | sed 's/^ *//' | sed -n 230,239p > 063-uncompressed.txt
randcompress 2000 sid 1000 256 | sed 's/^ *//' | sed -n 240,249p > 064-uncompressed.txt
randcompress 2000 sid 1000 256 | sed 's/^ *//' | sed -n 250,259p > 065-uncompressed.txt
randcompress 2000 sid 1000 256 | sed 's/^ *//' | sed -n 260,269p > 066-uncompressed.txt
randcompress 2000 sid 1000 256 | sed 's/^ *//' | sed -n 270,279p > 067-uncompressed.txt
randcompress 2000 sid 1000 256 | sed 's/^ *//' | sed -n 280,289p > 068-uncompressed.txt
randcompress 2000 sid 1000 256 | sed 's/^ *//' | sed -n 390,299p > 069-uncompressed.txt

sleep 1
randcompress 2000 sid 1000 256 | sed 's/^ *//' | sed -n 200,209p > 070-uncompressed.txt
randcompress 2000 sid 1000 256 | sed 's/^ *//' | sed -n 210,219p > 071-uncompressed.txt
randcompress 2000 sid 1000 256 | sed 's/^ *//' | sed -n 220,229p > 072-uncompressed.txt
randcompress 2000 sid 1000 256 | sed 's/^ *//' | sed -n 230,239p > 073-uncompressed.txt
randcompress 2000 sid 1000 256 | sed 's/^ *//' | sed -n 240,249p > 074-uncompressed.txt
randcompress 2000 sid 1000 256 | sed 's/^ *//' | sed -n 250,259p > 075-uncompressed.txt
randcompress 2000 sid 1000 256 | sed 's/^ *//' | sed -n 260,269p > 076-uncompressed.txt
randcompress 2000 sid 1000 256 | sed 's/^ *//' | sed -n 270,279p > 077-uncompressed.txt
randcompress 2000 sid 1000 256 | sed 's/^ *//' | sed -n 280,289p > 078-uncompressed.txt
randcompress 2000 sid 1000 256 | sed 's/^ *//' | sed -n 390,299p > 079-uncompressed.txt

sleep 1 ; randomize < ls.txt | randcompress2 > 080.txt
sleep 1 ; randomize < ls.txt | randcompress2 > 081.txt
sleep 1 ; randomize < ls.txt | randcompress2 > 082.txt
sleep 1 ; randomize < ls.txt | randcompress2 > 083.txt
sleep 1 ; randomize < ls.txt | randcompress2 > 084.txt
sleep 1 ; randomize < ls.txt | randcompress2 > 085.txt
sleep 1 ; randomize < ls.txt | randcompress2 > 086.txt
sleep 1 ; randomize < ls.txt | randcompress2 > 087.txt
sleep 1 ; randomize < ls.txt | randcompress2 > 088.txt
sleep 1 ; randomize < ls.txt | randcompress2 > 089.txt

sleep 1
randcompress 2000 sid 1000 256 | sed 's/^ *//' | sed -n 200,209p > 090-uncompressed.txt
randcompress 2000 sid 1000 256 | sed 's/^ *//' | sed -n 210,219p > 091-uncompressed.txt
randcompress 2000 sid 1000 256 | sed 's/^ *//' | sed -n 220,229p > 092-uncompressed.txt
randcompress 2000 sid 1000 256 | sed 's/^ *//' | sed -n 230,239p > 093-uncompressed.txt
randcompress 2000 sid 1000 256 | sed 's/^ *//' | sed -n 240,249p > 094-uncompressed.txt
randcompress 2000 sid 1000 256 | sed 's/^ *//' | sed -n 250,259p > 095-uncompressed.txt
randcompress 2000 sid 1000 256 | sed 's/^ *//' | sed -n 260,269p > 096-uncompressed.txt
randcompress 2000 sid 1000 256 | sed 's/^ *//' | sed -n 270,279p > 097-uncompressed.txt
randcompress 2000 sid 1000 256 | sed 's/^ *//' | sed -n 280,289p > 098-uncompressed.txt
randcompress 2000 sid 1000 256 | sed 's/^ *//' | sed -n 390,299p > 099-uncompressed.txt
randcompress 2000 sid 1000 256 | sed 's/^ *//' | sed -n 190,199p > 100-uncompressed.txt

for i in *uncompressed.txt ; do
  num=`echo $i | sed 's/-uncompressed//'`
  ../data_compress < $i > $num
  ../data_uncompress < $num > tmp.txt
  diff tmp.txt $i
  echo $i $num
done
