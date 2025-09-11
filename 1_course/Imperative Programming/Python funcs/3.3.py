import re

def evaluate_expression(expression):
    expression = expression.replace(" ", "")
    
    def precedence(op):
        if op == '+' or op == '-':
            return 1
        if op == '*' or op == '/':
            return 2
        return 0

    def apply_operation(a, b, op):
        if op == '+':
            return a + b
        elif op == '-':
            return a - b
        elif op == '*':
            return a * b
        elif op == '/':
            return a / b

    def calculate(expression):
        values = []
        ops = []
        i = 0
        
        while i < len(expression):
            if expression[i].isdigit():
                num = 0
                while (i < len(expression) and expression[i].isdigit()):
                    num = num * 10 + int(expression[i])
                    i += 1
                values.append(float(num))
                continue
            
            elif expression[i] == '(':
                ops.append(expression[i])
                
            elif expression[i] == ')':
                while ops and ops[-1] != '(':
                    val2 = values.pop()
                    val1 = values.pop()
                    op = ops.pop()
                    values.append(apply_operation(val1, val2, op))
                ops.pop()  
                
            else:
                while (ops and precedence(ops[-1]) >= precedence(expression[i])):
                    val2 = values.pop()
                    val1 = values.pop()
                    op = ops.pop()
                    values.append(apply_operation(val1, val2, op))
                ops.append(expression[i])
            i += 1
        
        while ops:
            val2 = values.pop()
            val1 = values.pop()
            op = ops.pop()
            values.append(apply_operation(val1, val2, op))
        
        return values[-1]

    return calculate(expression)

# Чтение входных данных
with open('input.txt', 'r') as infile:
    expression = infile.readline().strip()

result = evaluate_expression(expression)

with open('output.txt', 'w') as outfile:
    outfile.write(f"{result:.12f}\n")