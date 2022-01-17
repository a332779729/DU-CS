# Complete the sorting algorithms below.
# Since Python uses pass-by-reference for function calls
# with objects, you should sort the copy of the input
# list instead of the input list itself.

# Question 1: Bubble Sort
def bubbleSort(inputLst):
    lst = inputLst.copy()
    n = len(lst)

    ### YOUR CODE HERE ###
    ###To start things off, let's implement bare-bones Bubble Sort. The name comes from the concept of "bubbling up" elements to their correct spot.
    ###Start by looking at the first two elements. If they are in the right order, swap them. Otherwise do nothing.
    ###Then look at the second and third elements, then the third and fourth, and so on through the list.
    ###Doing a single pass through the list does not guarantee the entire list is sorted, but it does guarantee the largest element is at the end of the list.
    ###Hence, if we do N such passes for a list with N elements, the entire list will be sorted (thereby yielding an O(n2) runtime).
    ###Alternatively (and slightly more efficiently), we can keep doing passes until we complete a pass without swapping, meaning the list is sorted.
    for i in range(n):
        for j in range(1,n-i):
            if lst[j-1] > lst[j]:
                lst[j-1], lst[j] = lst[j], lst[j-1]

    return lst

# Question 2: Cocktail Shaker Sort
def cocktailShakerSort(inputLst):
    lst = inputLst.copy()
    n = len(lst)

    ### YOUR CODE HERE ###
    ###More descriptively called "bidirectional bubble sort", this sorting algorithm is just a minor variant on Bubble Sort.
    ###Instead of doing N forward passes from 0 to N-1, you do a forward pass, then a backward pass, then a forward pass, and so on until the list is sorted.
    ###This is clearly still an O(n2) runtime, but it does help remove what are known as "turtles" in Bubble Sort (smaller elements toward the end of the list that take longer to move into their proper order at the beginning of the list).
    swapped = True
    first = 0
    final = n - 1
    while(swapped == True):
        swapped = False

        for i in range (first, final):
            if(lst[i] > lst[i+1]) :
                lst[i], lst[i+1] = lst[i+1], lst[i]
                swapped = True

        if (swapped == False ):
            break

        swapped = False

        final = final-1

        for i in range (first-1, final-1, -1):
            if(lst[i] > lst[i+1]):
                lst[i], lst[i+1] = lst[i+1], lst[i]
                swapped = True

        first = first+1

    return lst

# Question 3: Comb Sort
def combSort(inputLst):
    lst = inputLst.copy()
    n = len(lst)

    ### YOUR CODE HERE ###
    ###Comb Sort observes that Bubble Sort only considers swapping with adjacent elements. This is what causes "turtles".
    ###Comb Sort attempts to eliminate these by adding the concept of a "gap". Instead of swaps occurring between elements i and i+1 (or i and i-1 depending on how you implement normal Bubble Sort),
    ###they occur between elements i and i+gap. The gap is initially N, but is immediately shrunk by the shrink factor (set to a constant 1.3 as a result of empirical studies),
    ###otherwise the index would be out of bounds. This shrinking occurs on each loop, causing the gap to become smaller and smaller. Once the gap is 1, the algorithm continues as long as there are elements to swap,
    ###at that point effectively becoming generic Bubble Sort.
    gap = n
    swapped = True
    while gap> 1 or swapped == True:

        gap = max(1, int(gap / 1.25))

        swapped = False
        for i in range(n - gap):
            j = i+gap
            if lst[i] > lst[j]:
                lst[i], lst[j] = lst[j], lst[i]
                swapped = True

    return lst

# Question 4: Gnome Sort
def gnomeSort(inputLst):
    lst = inputLst.copy()
    n = len(lst)

    ### YOUR CODE HERE ###
    ###Lastly, we have the sorting algorithm that requires the least amount of code.

    index = 0
    while index < n:
        if index == 0:
            index = index + 1
            continue
        if lst[index] > lst[index - 1]:
            index = index + 1
        else:
            lst[index], lst[index-1] = lst[index-1], lst[index]
            index = index - 1

    return lst
