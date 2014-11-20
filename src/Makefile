projectdir=$(shell cd ..; pwd)
docdir=$(projectdir)/doc
srcdir=$(projectdir)/src

doc: ../doc/Doxyfile
	cd $(docdir) && \
		doxygen Doxyfile

