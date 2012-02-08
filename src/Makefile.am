bin_PROGRAMS = ffmtool
ffmtool_SOURCES = ImportData.cpp ImportData.h main.cpp \
			   Session.cpp Session.h ExportData.cpp ExportData.h \
			   GetReport.h GetReport.cpp
noinst_HEADERS = ImportData.h Session.h ExportData.h

ffmtool_CXXFLAGS = @PACKAGE_CFLAGS@ @BOOST_CFLAGS@ -DDATADIR='$(datadir)'
ffmtool_LDFLAGS = @PACKAGE_LIBS@ @BOOST_LIBS@

