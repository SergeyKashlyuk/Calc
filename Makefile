all:
	gcc main.c calc.c -o Calc
	gcc calc.c calc_ut.c -o RunTests