# Note requires LaTeX installed, along with siunitx package and circuitikz package 

components.pdf: components.tex
	pdflatex components.tex
	# We need to compile twice to generate the table of contense.
	pdflatex components.tex
clean:
	rm components.pdf components.aux components.log components.toc
