#!/bin/bash

run_test() {
    expected_output="$1"
    input1="$2"
    operator="$3"
    input2="$4"
 
    output=$(./calculator.sh "$input1" "$operator" "$input2")

    if [ "$output" == "$expected_output" ]; then
        echo "Test passed for input $input1 $operator $input2."
    else
        echo "Test failed for input $input1 $operator $input2."
        echo "Expected: $expected_output"
        echo "Got: $output"
    fi
}

run_test "Result: 5" 2 + 3
run_test "Result: 0" 2 - 2
run_test "Result: 6" 2 '*' 3
run_test "Result: 2" 4 / 2
run_test "Error: Division by zero" 4 / 0


