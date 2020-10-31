#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void pushValStack (int stack[], int *top, int value);
int popValStack (int stack[], int *top);
void pushOpStack (char *stack[], int *top, char *value);
char *popOpStack (char *stack[], int *top);
int processOp(int amt, char *op, int val);
int processPlus(int amt, int val);
int processDivide(int amt, int val);
int processPower(int amt, int val);
int processTimes(int amt, int val);
int processMinus(int amt, int val);

int main(int argc, char *argv[]) {
printf("welcome to the calculator \n");

int valStack[50];
int vTop = 0;
int *valTop = &vTop;

char *opStack[50];
int oTop = 0;
int *opTop = &oTop;



int i = 1;
for (i; i < argc; i++) {

char *token = argv[i];


if ((strcmp(token, "x") == 0) || (strcmp(token, "+") == 0) || (strcmp(token, "^") == 0) || (strcmp(token, "%") == 0) || (strcmp(token, "[") == 0)) { //if an operator push to the op stack
pushOpStack(opStack, opTop, token);
}

else if (strcmp(token, "]") == 0){ //right bracket signals to perform arithmeitc
  token = popOpStack (opStack, opTop);

  while (strcmp(token, "[") != 0) { //perform arithmetic until a left bracket

    int val = popValStack(valStack, valTop);
    int amt = popValStack(valStack, valTop);
    int answer = processOp(amt, token, val);
    pushValStack(valStack,valTop, answer);
    token = popOpStack (opStack, opTop);
  }
}

else { //convert chars to ints then push to stack
  int convert = atoi(token);
  pushValStack(valStack, valTop, convert);

}

}

 char *token;
 while (*opTop > 0) { //perform arithmetic with remaining operators
    token = popOpStack (opStack, opTop);
    int val = popValStack(valStack, valTop);
    int amt = popValStack(valStack, valTop);
    int answer = processOp(amt, token, val);
    pushValStack(valStack,valTop, answer);
  }
  int result;
  result = popValStack(valStack, valTop);
  printf("The result is: %d \n", result);
  return 0;
}


void pushOpStack(char *stack[], int *top, char *value) {
  if (*top == 50){
    printf("Stack overflow");
  }
  else{
    stack[*top] = value;
    *top = *top + 1;
  }
  return;
}

void pushValStack (int stack[], int *top, int value){
  if (*top == 50){
    printf("Stack overflow");
  }
  else {
    stack[*top] = value;
    *top = *top + 1;
  }
  return;
}

char *popOpStack (char *stack[], int *top){
  *top = *top-1;
  return stack[*top];

}

int popValStack (int stack[], int *top){
  *top = *top-1;
  return stack[*top];
}



int processOp(int amt, char *op, int val) { // math
   if (strcmp(op, "+") == 0)  return processPlus(amt, val);
   else if (strcmp(op, "-") == 0) return processMinus(amt, val);
   else if (strcmp(op, "x") == 0) return processTimes(amt, val);
   else if (strcmp(op, "/") == 0) return processDivide(amt, val);
   else if (strcmp(op, "^") == 0) return processPower(amt, val);
   else {
     printf("Bad Operator");
     return amt;
     }
  }
int processPlus(int amt, int val) {
  return amt + val;
}

int processMinus(int amt, int val) {
  return amt - val;
}
int processTimes(int amt, int val) {
  return amt * val;
}

int processDivide(int amt, int val) {
  return amt / val;
}

int processPower(int amt, int val) {
  double ans = pow(amt, val);
  int answer = ans;
  return answer;
}
