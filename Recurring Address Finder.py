def get_file_addresses(list_name):
    print(f"\nEnter file addresses for {list_name} one per line.")
    print("Type 'DONE' (in all caps) when finished:\n")
    
    addresses = []
    while True:
        line = input()
        if line.strip().upper() == 'DONE':
            break
        if line.strip():  # avoid empty lines
            addresses.append(line.strip())
    return addresses

def find_common_addresses(list1, list2):
    """
    Finds and returns the common file paths between two lists.
    """
    return list(set(list1) & set(list2))

# Main Execution
print("=== Compare Two Lists of File Addresses ===")
addresses1 = get_file_addresses("List I")
addresses2 = get_file_addresses("List II")

common_files = find_common_addresses(addresses1, addresses2)

# Output
print("\n=== Common File Addresses Found ===")
if common_files:
    for file in common_files:
        print(file)
else:
    print("No common file addresses found.")
