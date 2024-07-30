import math

def main():
    datasize = int(input("Enter DATA SIZE: "))
    mtu = int(input("Enter MTU: "))

    n = math.ceil((datasize - 20) / (mtu - 20))

    if datasize >= mtu:
        print("\n" + str(n) + " fragments were created:")
        print("----------------------------------------------")
        print(f"{'#':<2} {'TOTAL LENGTH':<20} {'MF FLAG':<10} {'OFFSET':<10}")
        print("----------------------------------------------")

        for i in range(1, n):
            length = mtu
            flags = 1
            offset = int(math.ceil(((mtu - 20) * (i - 1)) / 8))

            print(f"{i:<2} {length:<20} {flags:<10} {offset:<10}")
            print("----------------------------------------------")

        final_length = datasize - (mtu - 20) * (n - 1)
        final_flags = 0
        final_offset = ((mtu - 20) * (n - 1)) // 8

        print(f"{n:<2} {final_length:<20} {final_flags:<10} {final_offset:<10}")
        print("----------------------------------------------")
    else:
        print("\nSince MTU > DATA SIZE, the packet moves on to the next encapsulation phase without fragmentation:")
        print("----------------------------------------------")
        print(f"{'#':<2} {'TOTAL LENGTH':<20} {'FLAG':<10} {'OFFSET':<10}")
        print("----------------------------------------------")
        print(f"1 {'datasize':<20} 0 {'0':<10}")
        print("----------------------------------------------")

if __name__ == "__main__":
    main()
