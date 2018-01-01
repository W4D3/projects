proc nothing { } { }

proc do_high_scores { } {
  exec ./hscore -
}

proc pbtoggle { } {
  global g
  if { $g("printboard") == 0 } {
    set g("printboard") 1
    .mv.commands.spit.b configure -text "Don't Print"  -command pbtoggle
  } else {
    set g("printboard") 0
    .mv.commands.spit.b configure -text "Print Boards"  -command pbtoggle
  }
}

proc restart { } {
  global g

  set w $g("w")
  set h $g("h")
  set g("total") 80
  set g("score") 0
  .mv.commands.score.t configure -text "Score: 0"
  .mv.commands.gameover.t configure -text ""  -background white
  .mv.commands.collect.b configure -text "Collect"  -command collect
  for { set i 0 } { $i < $h } { incr i } {
    for { set j 0 } { $j < $w } { incr j } {
      set v [ .mv.matrix.$i.$j cget -text ] 
      if { $v < 5 } {
        findandchange $i $j $v 6
      }
    }
  }
  after 1000 addnew 5
}

proc addnew { n } {
  global g

  set w $g("w")
  set h $g("h")

  set target [ expr $g("total") - $n ]

  while { $g("total") > $target } {
    if { $g("total") == 0 } {
      .mv.commands.gameover.t configure -text "Game Over" -background lightpink
      .mv.commands.collect.b configure -text "Exit" -width 10  -command exit
      for { set i 0 } { $i < $h } { incr i } {
        for { set j 0 } { $j < $w } { incr j } {
          .mv.matrix.$i.$j configure -command exit
        }
      }
      set un [ .mv.commands.pname.t get ]
      if { $un != "" } {
        exec ./hscore $un $g("score")
      } else {
        exec ./hscore $g("score")
      }
      return
    } 

    gets stdin ind
    set r [ expr $ind / $w ]
    set c [ expr $ind % $w ]
    set img [ .mv.matrix.$r.$c cget -image ]
    set key "6.gif"
    set gray $g($key)
    set key "6-g.gif"
    set grayg $g($key)

    if { $img == $gray || $img == $grayg } {
      gets stdin newc
      set newc [ expr $newc % 5 ]
      if { $img == $gray } {
        set key "$newc.gif"
        .mv.matrix.$r.$c configure -image $g($key) 
      } else {
        set key "$newc-g.gif"
        .mv.matrix.$r.$c configure -image $g($key) 
      }
      .mv.matrix.$r.$c configure -command  "mark $r $c" -text $newc
      incr g("total") -1
      set t $g("total")
      .mv.commands.gameover.t configure -text "Empty: $t"
    }
  }
  for { set i 0 } { $i < $h } { incr i } {
    set s ""
    for { set j 0 } { $j < $w } { incr j } {
      set val [ .mv.matrix.$i.$j cget -text ]
      if { ($j < 2 || $j >= $w-2) && ( $i >= 2 && $i < $h-2 ) } {
        set val [ expr $val + 10 ]
      }
      append s $g($val)
    }
    if { $g("printboard") != 0 } { puts $s }
  }
  if { $g("printboard") != 0 } { puts "" }
}

proc mark { r c } {
  global g
  
  set val [ .mv.matrix.$r.$c cget -text ]
  set img [ .mv.matrix.$r.$c cget -image ]
  set key1 "$val-g.gif"
  if { $img == $g($key1) } { set goal "yes" } else { set goal "no" }

  if { $g("markr") == -1 } {
    set g("markr") $r
    set g("markc") $c
    set g("val") $val
    set g("goal") $goal
    set key1 "$val-g.gif"
    if { $goal == "yes" } {
      set key "$val-gd.gif"
      .mv.matrix.$r.$c configure -image $g($key)
    } else {
      set key "$val-d.gif"
      .mv.matrix.$r.$c configure -image $g($key)
    }
  } elseif { $g("markr") == $r && $g("markc") == $c } {
    set g("markr") -1
    set g("markc") -1
    if { $g("goal") == "yes" } {
      set key "$val-g.gif"
      .mv.matrix.$r.$c configure -image $g($key)
    } else {
      set key "$val.gif"
      .mv.matrix.$r.$c configure -image $g($key)
    }
  } else {
    set tr $g("markr")
    set tc $g("markc")
    set g("markr") -1
    set g("markc") -1
    if { $g("goal") == "yes" } {
      set key "$val-g.gif"
    } else {
      set key "$val.gif"
    }
    .mv.matrix.$tr.$tc configure -image $g($key) -text $val
    set v $g("val")
    if { $goal == "yes" } {
      set key "$v-g.gif"
    } else {
      set key "$v.gif"
    }
    .mv.matrix.$r.$c configure -image $g($key) -text $v
    after 1000 addnew 5
  }
}

global g

set g("markr") -1
set g("markc") -1

frame .mv
wm title . "Lame-O-Ball"
pack .mv
frame .mv.matrix
pack .mv.matrix -side left
  
set g("w") 10
set g("h") 8
  
set w $g("w")
set h $g("h")
  
for { set i 0 } { $i < 7 } { incr i } {
  set key "$i.gif"
  set g($key) [ image create photo -file $key ]
  set key "$i-g.gif"
  set g($key) [ image create photo -file $key ]
  if { $i < 5 } {
    set key "$i-d.gif"
    set g($key) [ image create photo -file $key ]
    set key "$i-gd.gif"
    set g($key) [ image create photo -file $key ]
  }
}

frame .mv.matrix.top -background black

for { set i 0 } { $i < $h } { incr i } {
  frame .mv.matrix.$i -background black
  for { set j 0 } { $j < $w } { incr j } {
    set key "6.gif"
    button .mv.matrix.$i.$j -image $g($key) -command nothing -bd 0 -text 6
  }
  pack .mv.matrix.$i -side top -fill x -expand yes
  for { set j 0 } { $j < $w } { incr j } {
     pack .mv.matrix.$i.$j -side left -fill x -expand yes
  }
}
  
set r [ expr $w - 1 ]
set pr [ expr $w - 2 ]
set key "6-g.gif"
for { set i 2 } { $i < 6 } { incr i } {
  .mv.matrix.$i.0 configure -image $g($key)
  .mv.matrix.$i.$r configure -image $g($key)
  .mv.matrix.$i.1 configure -image $g($key)
  .mv.matrix.$i.$pr configure -image $g($key)
}
  
frame .mv.commands 
pack .mv.commands -side left -expand n
  

frame .mv.commands.gameover
pack .mv.commands.gameover -side top 
label .mv.commands.gameover.t -text "Empty: 80" -bg yellow
pack .mv.commands.gameover.t -side left

frame .mv.commands.score
pack .mv.commands.score -side top 
label .mv.commands.score.t -text "Score: 0" -background lightblue
pack .mv.commands.score.t -side left
  
frame .mv.commands.blank
pack .mv.commands.blank -side top 
label .mv.commands.blank.t -text ""
pack .mv.commands.blank.t -side left

frame .mv.commands.collect
pack .mv.commands.collect -side top 
button .mv.commands.collect.b -text "Collect"  -command collect
pack .mv.commands.collect.b -side left 

frame .mv.commands.highscores
pack .mv.commands.highscores -side top 
button .mv.commands.highscores.b -text "High Scores"  -command do_high_scores
pack .mv.commands.highscores.b -side left 

frame .mv.commands.restart
pack .mv.commands.restart -side top 
button .mv.commands.restart.b -text "Start Over"  -command restart
pack .mv.commands.restart.b -side left 

frame .mv.commands.spit
pack .mv.commands.spit -side top 
set g("printboard") 0
button .mv.commands.spit.b -text "Print Boards"  -command pbtoggle
pack .mv.commands.spit.b -side left 

frame .mv.commands.bottom
pack .mv.commands.bottom -side top 
label .mv.commands.bottom.t -text ""
pack .mv.commands.bottom.t -side left

frame .mv.commands.namestring
pack .mv.commands.namestring -side top 
label .mv.commands.namestring.t -text "Player Name"
pack .mv.commands.namestring.t -side left

frame .mv.commands.pname
pack .mv.commands.pname -side top 
entry .mv.commands.pname.t -width 12
.mv.commands.pname.t insert 0 $env(USER)
pack .mv.commands.pname.t -side left

frame .mv.commands.1
pack .mv.commands.1 -side top 
label .mv.commands.1.t -text ""

set g("total") 80
set g("score") 0
set g(0) "p"
set g(1) "b"
set g(2) "y"
set g(3) "r"
set g(4) "g"
set g(5) "."
set g(6) "."

set g(10) "P"
set g(11) "B"
set g(12) "Y"
set g(13) "R"
set g(14) "G"
set g(15) "*"
set g(16) "*"


addnew 5

proc collect { } {
  global g

  set w $g("w")
  set h $g("h")

  if { $g("markr") == -1 || $g("goal") != "yes" } {
     tk_dialog .mv.reset "Must have a goal square marked to collect"  "Must have a goal square marked to collect"  {} 0  "OK"
     return
  }
  set v $g("val")
  set key "$v-g.gif"
  set r $g("markr")
  set c $g("markc")
  set g("markr") -1
  set g("markc") -1

  .mv.matrix.$r.$c configure -image $g($key)
  
  set tpieces [ findandchange $r $c $v 5 ]

  if { $tpieces < 5 } {
     tk_dialog .mv.reset "Must be a block of 5 or more"  "Must be a block of 5 or more"  {} 0  "OK"
     findandchange $r $c 5 $v
     return
  }

  set val [ expr $v + 2 ]

  incr g("total") $tpieces
  incr g("score") [ expr $tpieces * $val  ]
  set s $g("score")
  .mv.commands.score.t configure -text "Score: $s" 

  after 1000 fc $r $c
}

proc fc { r c } {
  findandchange $r $c 5 6
  after 1000 addnew 3
}

proc findandchange { r c c1 c2 } {
  global g

  set w $g("w")
  set h $g("h")

  if { $r < 0 || $r >= $h } { return 0; }
  if { $c < 0 || $c >= $w } { return 0; }

  if { [ .mv.matrix.$r.$c cget -text ] != $c1 } { return 0 }
  .mv.matrix.$r.$c configure -text $c2

  set key1 "$c1.gif"
  set key1g "$c1-g.gif"
  set key2 "$c2.gif"
  set key2g "$c2-g.gif"

  set i1 [ .mv.matrix.$r.$c cget -image ]
  if { $i1 == $g($key1) } {
    .mv.matrix.$r.$c configure -image $g($key2)
  } else {
    .mv.matrix.$r.$c configure -image $g($key2g)
  }

  set total 1
  incr total [ findandchange [ expr $r + 1 ] $c $c1 $c2 ]
  incr total [ findandchange [ expr $r - 1 ] $c $c1 $c2 ]
  incr total [ findandchange $r [ expr $c + 1 ] $c1 $c2 ]
  incr total [ findandchange $r [ expr $c - 1 ] $c1 $c2 ]

  return $total
}
