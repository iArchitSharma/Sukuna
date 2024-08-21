CPP="g++"
COMPILER="src/sukuna.cpp"

function comp {
    BN=$(basename -s .sk $1)  

    # Compile the C++ code (sukuna.cpp)
    TTOUTPUT=$(${CPP} ${COMPILER} -o bin/sukuna 2>&1)
    if [ $? -ne 0 ]; then
        echo "${TTOUTPUT}"  # Print the compiler output if there was an error
    else
        # Execute the compiled binary with the input file as an argument
        BINOUT=$(./bin/sukuna $1 2>&1)
        if [ $? -ne 0 ]; then
            echo "Execution Error: ${BINOUT}"
        else
            echo "${BINOUT}"  
        fi
    fi
}

if [ $# -eq 0 ]; then
    echo "No input file provided."
    echo "Usage: $0 <inputFile>"
else
    comp $1  
fi
