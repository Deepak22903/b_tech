class TripletGenerator:
    def __init__(self):
        self.triplets = []
        self.temp_counter = 0

    def new_temp(self):
        self.temp_counter += 1
        return f't{self.temp_counter}'

    def emit(self, op, arg1, arg2):
        self.triplets.append((op, arg1, arg2))

    def generate_code(self, expression):
        # The expression: a = b * -c + b * -c
        terms = expression.split('+')
        
        if len(terms) == 2: 
            left = self.process_term(terms[0].strip())
            right = self.process_term(terms[1].strip())
            self.emit('+', left, right)  

    def process_term(self, term):
        factors = term.split('*')
        
        if len(factors) == 2:
            arg1 = factors[0].strip()
            arg2 = factors[1].strip()
            if arg2.startswith('-'):
                neg_arg = arg2[1:]  
                self.emit('-', neg_arg, '')  
                neg_index = len(self.triplets) - 1  
                self.emit('*', arg1, neg_index) 
                return len(self.triplets) - 1  
        return term  

    def assign_variable(self, var):
        last_index = len(self.triplets) - 1
        self.emit('=', var, last_index)

    def generate_triplets(self):
        return self.triplets

# Example Usage
generator = TripletGenerator()

# Generate code for the expression 'a = b * -c + b * -c'
generator.generate_code('b * -c + b * -c')
generator.assign_variable('a')

# Print generated triplets
print("    OP      arg1    arg2")
for idx, triplet in enumerate(generator.generate_triplets()):
    print(f"{idx}  {triplet[0]:<8} {triplet[1]:<8} {triplet[2]:<8}")
