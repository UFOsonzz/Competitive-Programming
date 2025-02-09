@echo off
test__Generator > test.inp
test__Good < test.inp > test__good.out
test < test.inp > test__bad.out
start /d test__Generator
start /d test
start /d test__Good
type test.inp
echo.
type test__bad.out
echo.
type test__good.out
echo.
(fc test__bad.out test__good.out) >NUL && echo Same || pause
stress