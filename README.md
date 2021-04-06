Amigos do Beto - ICPC Library
=================

Algorithms and data structures library for competitive programming, mainly ICPC.

Script to generate the pdf by Stanford University ACM team.

Generating team notebook
========================
Requires: [Python 2/3](https://www.python.org/), [latexmk](https://www.ctan.org/pkg/latexmk/)

The included Python script can generate the notebook in PDF format. The script read the contents of the notebook from `contents.txt`.

Script for generating the PDF file is `generate_pdf.py`.
The LaTeX template that the script uses is `notebook.tex`. It recognizes common file extensions for C/C++/Java/Python and applies syntax highlighting. In order to change the color scheme or add additional languages, both `notebook.tex` and `generate_pdf.py` should be modified accordingly.
