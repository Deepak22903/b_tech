class QuadrupleGenerator:
    def __init__(self):
        self.quadruples = []
        self.temp_counter = 0

    def new_temp(self):
        self.temp_counter += 1
        return f't{self.temp_counter}'

    def emit(self, op, arg1, arg2, result):
        self.quadruples.append((op, arg1, arg2, result))

    def generate_code(self, expression):
        terms = expression.split('+')
        
        if len(terms) == 2: 
            left = self.process_term(terms[0].strip())
            right = self.process_term(terms[1].strip())
            temp_result = self.new_temp()
            self.emit('+', left, right, temp_result) 
            return temp_result 

    def process_term(self, term):
        factors = term.split('*')
        
        if len(factors) == 2:
            arg1 = factors[0].strip()
            arg2 = factors[1].strip()
            if arg2.startswith('-'):
                neg_arg = arg2[1:] 
                temp_neg = self.new_temp()
                self.emit('-', neg_arg, '', temp_neg) 
                temp_mul = self.new_temp()
                self.emit('*', arg1, temp_neg, temp_mul)
                return temp_mul 
        return term 

    def assign_variable(self, var):
        last_index = len(self.quadruples) - 1
        temp_result = self.quadruples[last_index][3] 
        self.emit('=', '', '', var)  
        return temp_result

    def generate_quadruples(self):
        return self.quadruples

# Example Usage
generator = QuadrupleGenerator()

# Generate code for the expression 'a = b * -c + b * -c'
result_temp = generator.generate_code('b * -c + b * -c')
generator.assign_variable('a')

print("    OP  arg1        arg2    result")
for idx, quadruple in enumerate(generator.generate_quadruples()):
    print(f"{idx}   {quadruple[0]:<2} {quadruple[1]:<10} {quadruple[2]:<10} {quadruple[3]:<10}")
