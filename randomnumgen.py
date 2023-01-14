#random number generator without using random module

import time

def randomnumgen(lower=0, upper=100):
    # generate a random number between lower and upper
    # using the current time as a seed
    # seed = time.time()
    # seed = int(seed)
    # seed

    # generate a random number between lower and upper
    

if __name__ == "__main__":
    # generate n random numbers
    n = int(input("How many random numbers do you want to generate? "))
    upper = int(input("What is the upper bound? "))
    lower = int(input("What is the lower bound? "))

    for i in range(n):
        print(randomnumgen(lower, upper))
