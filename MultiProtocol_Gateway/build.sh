#!/bin/bash
opp_makemake -f --deep -O out \
-I../inet/src \
-I../FiCo4OMNeT/src \
-L../inet/src -lINET \
-L../FiCo4OMNeT/src -lFiCo4OMNeT \
-KINET_PROJ=../inet \
-KFI_CO4_OMNE_T_PROJ=../FiCo4OMNeT \
-DINET_IMPORT -DFI_CO4_OMNE_T_IMPORT
make
