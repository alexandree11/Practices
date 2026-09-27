key_N = 319
key_e = 11

# we will put wrong lines in this list
wrong_lines = []

# opening the inbox.txt in read mode
with open('./inbox.txt', 'r') as message:
    for line in message:    # separating lines
        line = line.strip()
        if not line:        # an empty line, skip it
            continue

        line_part = line.split(maxsplit=2)      # maxsplit = separate only first 2 spaces
        line_num = int(line_part[0])            # first string is line num then separate
        line_sign = int(line_part[1])           # second string is signature then separate
        line_text = line_part[2]                # third part is the message itself it goes to the end of the line

        # num letters a=1 to z=26 means get the ascii value and subtract 96 because 'a' starts at 97 so 'a'=1
        # skip everything except alphabetic letters = use isalpha() to make sure only letters included
        # sum the ascii value of all the letters in the message of this line
        # find the last 2 digits using remainder by 100
        for c in line_text:
            sum_letters = sum(ord(c) - 96 for c in line_text if c.isalpha())
        message_hash = sum_letters%100

        # real hash = (signature ** e) % N
        true_hash = (line_sign**key_e)%key_N

        # check if real hash is same as message hash
        # if not the same add it to the list of wrong lines
        if true_hash != message_hash:
            wrong_lines.append(line_num)
        # print(line_num, message_hash, true_hash) this was to check the comparison of hashes

print(*wrong_lines, sep=',')