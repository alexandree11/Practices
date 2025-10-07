def concat(lst):
    if not lst:     #if lst empty, return nothing, at the end
        return ""
    else:
        #recursion with 1st lst element + function recall with updated lst starting from 2nd element
        return str(lst[0]) + concat(lst[1:])

def contains(lst, e):
    if not lst:     #if lst empty, return False
        return False
    else:       #check if 1st element equal to e
        if e == lst[0]:
            return True
        else:
            return contains(lst[1:], e)     #function recall with updated lst starting from 2nd element

def contains_duplicate(lst):
    if not lst:
        return False
    else:
        return contains(lst[1:], lst[0])
          
def contains_consecutive_duplicate(lst):
    if len(lst) <= 1:     #if theres only 1 num there could not be 2 consec duplicates
        return False
    else:
        if lst[0] == lst[1]:    #if 1st == next == True:
            return True
        else:
            return (contains_consecutive_duplicate(lst[1:]))    #function recall with updated lst

def is_sorted(lst):
    if len(lst) <= 1:     #empty or list of 1 element == sorted??
        return True
    else:
        if lst[0] > lst[1]:   #if 1st > next == not sorted
            return False
        else:       #function recall with updated list
            return (is_sorted(lst[1:]))

def equals(lst1, lst2):
    if len(lst1) != len(lst2):      #if lenghtes are different == False
        return False
    elif not lst1 and not lst2:      #if lists are empty == previous elements are equal == True
        return True
    elif lst1[0] == lst2[0]:      #if lst1[0] == lst2[0] check next element in updated lists
        return (equals(lst1[1:], lst2[1:]))
    else:   #if lengthes same, but some of the elements at some index not equal each other == False
        return False

#if __name__ == '__main__'
lst1 = []
lst2 = [1,2]
e = 15
print("use function_name(args)")