LATEX=latex
BIBTEX=bibtex
FILE=nfa2dfa
.phony:	all dvi ps pdf view
.SUFFIXES:	.tex .dvi .ps .pdf .bbl .bib .aux

all:	dvi ps pdf
dvi:	$(FILE).dvi
ps:	$(FILE).ps
pdf:	$(FILE).pdf

clean:
	rm -f *.aux *.blg *.bbl $(FILE).dvi $(FILE).ps $(FILE).pdf *.log

$(FILE).dvi: $(FILE).tex
	$(LATEX) $(FILE)
	$(LATEX) $(FILE)

$(FILE).bbl: $(FILE).tex reference
	$(LATEX) $(FILE)
	$(BIBTEX) $(FILE)

$(FILE).ps: $(FILE).dvi
$(FILE).pdf: $(FILE).ps

.dvi.ps:
	dvips -t letterSize -Ppdf -G0 -o $@ $<

.ps.pdf:
	ps2pdf13 $<

