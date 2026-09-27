hex_data = "6975783d7c68797469726f3d7b726f6a7c6f7978793d6975783d6a757271783d707c74717f72653d79686f74737a3d6975783d7268697c7a78"

# use built in function to convert from hex to bytes
ciphertext = bytes.fromhex(hex_data)

# do a loop 256 times to find the key
# each iteration = shifting bites
for key in range(256):
    # xor every byte in ciphertext with the current key
    decrypted_bytes = bytes([b ^ key for b in ciphertext])

    # convert the current bytes to plaintext using ascii numeration
    plaintext = decrypted_bytes.decode('ascii')

    # if every char in plaintext is a lowercase alphabet letter
    # print the text and the key and stop the loop
    if all(c in 'abcdefghijklmnopqrstuvwxyz ' for c in plaintext):
        print(f"Q1 (Plaintext): {plaintext}")
        print(f"Q2 (Key Byte) : {key}")
        break
    