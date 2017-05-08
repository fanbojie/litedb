#
# Copyright(c) 2011, ZheJiang Dahua, All rights reserved.
# Makefile
#

.PHONY : all clean 

all : $(SUBPRJ)
	$(MAKE) -C Build -f makefile_litebase
	$(MAKE) -C Build -f makefile_litedb
	$(MAKE) -C Build -f makefile_dbtest

clean : 
	$(MAKE) -C Build -f makefile_litebase clean
	$(MAKE) -C Build -f makefile_litedb clean
	$(MAKE) -C Build -f makefile_dbtest clean



