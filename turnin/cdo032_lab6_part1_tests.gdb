# Test file for "Lab6_TimerSychSMs"

echo ======================================================\n
echo Running all tests..."\n\n

define timeContinue
    if $argc > 0
        set $i = $arg0
    else
        set $i =1
    end
    while $i > 0
        set TimerFlag = 1
        continue
        set $i = $i - 1
    end
end

# Add tests below
test "Initial LED = B0"
timeContinue
expect PORTB 0x01
checkResult

test "1 second = B1"
timeContinue
expect PORTB 0x02
checkResult

test "2 seconds = B2"
timeContinue
expect PORTB 0x04
checkResult

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
