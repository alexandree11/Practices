hex_data = "6975783d7c68797469726f3d7b726f6a7c6f7978793d6975783d6a757271783d707c74717f72653d79686f74737a3d6975783d7268697c7a78"

# 2. Convert hex string to raw bytes
ciphertext = bytes.fromhex(hex_data)

# 3. Try all 256 possible single-byte XOR keys
for key in range(256):
    # XOR every byte in the ciphertext with the current key
    decrypted_bytes = bytes([b ^ key for b in ciphertext])
    
    try:
        # Convert bytes to string
        plaintext = decrypted_bytes.decode('ascii')
        
        # Check if the text consists strictly of lowercase letters and spaces
        if all(c in "abcdefghijklmnopqrstuvwxyz " for c in plaintext):
            print(f"Q1 (Plaintext): {plaintext}")
            print(f"Q2 (Key Byte) : {key}")
            break
    except UnicodeDecodeError:
        continue