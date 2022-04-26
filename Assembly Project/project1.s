/*I have neither given nor received any unauthorized aid on this assignment.*/
.section .data
array:	.int	89, -5, 91, 23, -67, 31, 46, -71, -14, -10, 3, 67 /*Declare Array A Values.*/
string1:	.asciz	"A[%d] = %d\n" /*Declare First String for Printf.*/
string2:	.asciz	"SUM = %d\n" /*Declare Second String for Printf.*/

.section .text

.global main

main:
	LDR X19, =array /*Load the Address of Array A in X19.*/
	MOV X20, #100 /*Initialize the min variable as 100 in X20.*/
	MOV X21, #0 /*Initialize the index variable as 0 in X21.*/
	MOV X22, #0 /*Initialize the sum variable as 0 in X22.*/
	MOV X23, #0 /*Initialize the i loop variable as 0 in X23.*/
	B checkloop1 /*Start the first for loop.*/

checkloop1:
	CMP X23, #12 /*Compare i with 12.*/
	B.LT forloop1 /*If i < 12, continue the loop.*/
	B print1 /*Otherwise, print the result.*/

forloop1:
	LSL X9, X23, #2 /*Multiply i by 4 to store the current offset in X9.*/
	LDRSH X10, [X19, X9] /*Store A[i] in X10 as a sign extended half word using the address of A offset by 4*i.*/
	CMP X10, X20 /*Compare A[i] with min.*/
	B.GE iterate1 /*If A[i] >= min, continue to next iteration.*/
	CMP X10, XZR /*Compare A[i] with 0.*/
	B.LE iterate1 /*If A[i] <= 0, continue to next iteration.*/
	/*Otherwise, then A[i] < min and A[i] > 0, so a new positive minimum has been found.*/
	MOV X20, X10 /*Set the new minimum equal to A[i].*/
	MOV X21, X23 /*Set the index equal to i.*/
	B iterate1 /*Continue to the next iteration.*/

iterate1:
	ADD X23, X23, #1 /*Increment i by 1.*/
	B checkloop1 /*Check if i is out of bounds.*/

print1:
	LDR X0, =string1 /*Set string1 as the string to print.*/
	MOV X1, X21 /*Set the index as the first integer variable for printf.*/
	MOV X2, X20 /*Set the minimum as the second integer variable for printf.*/
	BL printf /*Print the string, replacing each %d with the two variables respectively.*/
	MOV X23, #0 /*Reset i back to 0 for the second for loop.*/
	B checkloop2 /*Start the second for loop.*/

checkloop2:
	CMP X23, #12 /*Compare i with 12.*/
	B.LT forloop2 /*If i < 12, continue the loop.*/
	B print2 /*Otherwise, print the result.*/

forloop2:
	LSL X9, X23, #2 /*Multiply i by 4 to store the current offset in X9.*/
	LDRSH X10, [X19, X9] /*Store A[i] in X10 as a sign extended half word using the address of A offset by 4*i.*/
	CMP X10, XZR /*Compare A[i] with 0.*/
	B.LE iterate2 /*If A[i] <= 0, continue to the next iteration.*/
	CMP X10, X20 /*Compare A[i] with min.*/
	B.EQ iterate2 /*If A[i] == min, continue to the next iteration.*/
	/*Otherwise, then A[i] > 0 and A[i] != min, so a positive number not equal to the minimum has been found.*/
	ADD X22, X22, X10 /*Add the number to the current sum.*/
	B iterate2 /*Continue to the next iteration.*/

iterate2:
	ADD X23, X23, #1 /*Increment i by 1.*/
	B checkloop2 /*Check if i is out of bounds.*/

print2:
	LDR X0, =string2 /*Set string2 as the string to print.*/
	MOV X1, X22 /*Set the sum as the first integer variable for printf.*/
	BL printf /*Print the string, replacing %d with the sum.*/
	B exit /*Exit the program.*/

/*Standard Exit Label.*/
exit:
	MOV X0, #0
	MOV X8, #93
	SVC #0
	RET
	
