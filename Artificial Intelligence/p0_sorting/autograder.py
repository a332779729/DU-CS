# Script for autograding sorting questions.
# Test lists are generated randomly with a seed
# (so the random lists are the same each time)
# and each sorting algorithm is tested on the same
# lists. Passing each test is worth 0.5 points.

import random
import sorting

random.seed(100)

# Generate a random list of integers between -maxVal and maxVal
def generateRandomLst(n=10, maxVal=100):
    return [random.randint(-maxVal, maxVal) for _ in range(n)]

if __name__ == "__main__":
    testLsts = {
        "empty": [],
        "single element": generateRandomLst(1),
        "fifty elements": generateRandomLst(50),
        "sorted order": sorted(generateRandomLst(50)),
        "reverse order": list(reversed(sorted(generateRandomLst(50)))),
        "all positives": [abs(x) for x in generateRandomLst(50)],
        "all negatives": [-abs(x) for x in generateRandomLst(50)],
        "all same element": [42] * 50
    }

    answerLsts = {test : sorted(lst) for test, lst in testLsts.items()}

    def runTests(sortingFunction=sorting.bubbleSort):
        # Keep track of how many lists are sorted correctly
        numCorrect = 0
        for test, lst in testLsts.items():
            # Get the list as sorted by the student's implementation
            studentLst = sortingFunction(lst)
            answerLst = answerLsts[test]
            # Print output based on whether the implementation was correct
            if studentLst != answerLst:
                print("FAILED: " + test)
                print("\tOriginal list: " + str(lst))
                print("\tStudent list: " + str(studentLst))
                print("\tAnswer list: " + str(answerLst))
            else:
                print("\tPASSED: " + test)
                numCorrect += 1
        return numCorrect

    def runQuestion(i, name, sortingFunction):
        print(f"Question {i}: {name}")
        numCorrect = runTests(sortingFunction)
        print("#########################################")
        print()
        return numCorrect

    # Run tests on each sorting function
    q1Correct = runQuestion(1, "BubbleSort", sorting.bubbleSort)
    q2Correct = runQuestion(2, "CocktailShakerSort", sorting.cocktailShakerSort)
    q3Correct = runQuestion(3, "CombSort", sorting.combSort)
    q4Correct = runQuestion(4, "GnomeSort", sorting.gnomeSort)

    total = len(testLsts)

    # Print results
    print("Scores:")
    print(f"q1: {q1Correct/2}/{total/2}")
    print(f"q2: {q2Correct/2}/{total/2}")
    print(f"q3: {q3Correct/2}/{total/2}")
    print(f"q4: {q4Correct/2}/{total/2}")
