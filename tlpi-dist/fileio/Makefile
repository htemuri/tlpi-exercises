include ../Makefile.inc

GEN_EXE = atomic_append bad_exclusive_open copy \
	multi_descriptors seek_io t_readv t_truncate testing new_tee copy_holes \
	new_large_file append_beginning atomic_append_new

LINUX_EXE = large_file

EXE = ${GEN_EXE} ${LINUX_EXE}

all : ${EXE}

allgen : ${GEN_EXE}


clean : 
	${RM} ${EXE} *.o

showall :
	@ echo ${EXE}

${EXE} : ${TLPI_LIB}		# True as a rough approximation
