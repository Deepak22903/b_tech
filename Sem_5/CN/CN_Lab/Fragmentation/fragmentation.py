
def ip_fragmentation_calculator(packet_size, mtu, header_size):
    # Data size in each fragment (MTU - header size)
    fragment_payload_size = mtu - header_size
    
    # Total number of fragments (ceiling of the division)
    num_fragments = (packet_size + fragment_payload_size - 1) // fragment_payload_size
    
    print(f"Original Packet Size: {packet_size} bytes")
    print(f"MTU: {mtu} bytes")
    print(f"Header Size: {header_size} bytes")
    print(f"Data Size per Fragment: {fragment_payload_size} bytes")
    print(f"Number of Fragments: {num_fragments}")
    
    # List to store details of each fragment
    fragments = []
    
    for i in range(num_fragments):
        # Determine the offset for each fragment
        offset = i * fragment_payload_size
        
        # The payload size for this fragment
        if i < num_fragments - 1:
            fragment_size = fragment_payload_size
        else:
            # For the last fragment, the remaining data might be smaller than fragment_payload_size
            fragment_size = packet_size - offset
        
        # The size of the fragment (including the IP header)
        total_fragment_size = fragment_size + header_size
        
        fragments.append({
            'Fragment Number': i + 1,
            'Fragment Offset': offset,
            'Fragment Payload Size': fragment_size,
            'Total Fragment Size (with header)': total_fragment_size
        })
    
    # Print fragment details
    for fragment in fragments:
        print(f"\nFragment {fragment['Fragment Number']}:")
        print(f"  Offset: {fragment['Fragment Offset']} bytes")
        print(f"  Payload Size: {fragment['Fragment Payload Size']} bytes")
        print(f"  Total Size (with header): {fragment['Total Fragment Size (with header)']} bytes")

# Example Input
packet_size = int(input("Enter the packet size (in bytes): "))
mtu = int(input("Enter the MTU (in bytes): "))
header_size = int(input("Enter the IP header size (in bytes): "))

# Calculate the fragments
ip_fragmentation_calculator(packet_size, mtu, header_size)
