def absolute_loader(input_file):
    memory = {}

    # Read the input file
    with open(input_file, 'rb') as f:
        address = 0x1000  # Start address
        while True:
            data = f.read(4)
            if not data:
                break  # End of file

            # Convert the 4 bytes to an integer (little-endian)
            instruction = int.from_bytes(data, 'little')

            # Store the instruction in memory at the current address
            memory[address] = instruction

            # Move to the next address
            address += 4

    # Print memory contents
    print("Memory contents:")
    for addr, instruction in memory.items():
        print(f"{hex(addr)}: {bin(instruction)}")

if __name__ == "__main__":
    input_file = input("Enter the input file name (e.g., a.out or a.exe): ")
    absolute_loader(input_file)
