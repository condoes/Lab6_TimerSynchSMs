# Test file for "Lab6_TimerSymchSMs"

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
test "Initial state = 7"
timeContinue
expect PORTB 0x07
checkResult

test "increment once"
setPINA ~0x01
timeContinue
expect PORTB 0x08
checkResult

test "increment again"
setPINA ~0x01
timeContinue
expect PORTB 0x09
checkResult

test "increment over 9"
setPINA ~0x01
timeContinue
expectPORTB 0x09
expect State incr
checkResult

test "decrements"
setPINA ~0x02
timeContinue
expectPORTB 0x08
setPINA ~0x02
timeContinue
setPINA ~0x02
timeContinue
expect PORTB 0x06
checkResult

test "reset"
setPINA ~0x03
timeContinue
expect PORTB 0x00

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
