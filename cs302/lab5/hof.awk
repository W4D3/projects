{ place++ ; s = $1; i = 3; n = $i
    for (i++; $i != "XXX"; i++) n = n" "$i
    i++ 
    c = $i
    for (i++; i != NF+1 ; i++) c = c" "$i
    printf "<tr><td align=center>%d</td>\n", place
    printf "<td align=center>%.2lf</td>\n", s
    printf "<td align=center>%s</td>\n", n
    printf "<td align=center>%s</td></tr>\n", c
    printf("\n");

}
