CPP="g++"
COMPILER="sukuna.cpp"
CC="gcc"

function comp {
	BN=$(basename -s .sk $1)
	TTOUTPUT=$(${CPP} ${COMPILER} -o sukuna $1 2>&1)
    BINOUT=$(./sukuna ${inputFile})
	if [ $? -ne 0 ]; then
		echo "${TTOUTPUT}"
	else
		mv out.c ${BN}.c
		CCOUTPUT=$(${CC} -o ${BN} ${BN}.c)
		if [ $? -ne 0 ]; then
			echo "${CCOUTPUT}"
		else
			echo "${TTOUTPUT}"
		fi
	fi
}

if [ $# -eq 0 ]; then
	for i in $(ls examples/*.teeny); do
		comp $i
	done
else
	comp $1
fi