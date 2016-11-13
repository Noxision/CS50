import cs50

def main():
    
    array = [25, 10, 5, 1]
    coins = 0
    input = 0
    rest = 0
    
    while input <= 0:
        print("How much change is owed?")
        input = 100*cs50.get_float()
    
    for i in array:
        
        coins = coins + int(input/i)
        input = input - int(input/i)*i
        if input == 0:
            break
        
    print(coins)
    
if __name__ == "__main__":
    main()