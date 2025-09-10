def print_welcome():
    print("Welcome to the Daily Expense Tracker!\n")

def print_menu():
    print("""Menu:
    1. Add a new expense
    2. View all expenses
    3. Calculate total and average expense
    4. Clear all expenses
    5. Exit""")

print_welcome()
print_menu()
expenses_list = []
choices = [0, 1, 2, 3, 4, 5]

while True:
    user_choice = int(input("Choose from menu (0 to show menu again): "))
    if user_choice == 1:
        expenses_list.append(float(input("Enter the value for the expense: ")))
        print("Expense added successfully!\n")

    elif user_choice == 2:
        if len(expenses_list) == 0:
            print("No expenses recorded yet.\n")
        else:
            print("Your expenses:")
            for i in range (len(expenses_list)):
                print(f"{i+1}. {expenses_list[i]}")

    elif user_choice == 3:
        if len(expenses_list) == 0:
            print("No expenses recorded yet.\n")
        else:
            total = 0
            avg = 0
            for i in range (len(expenses_list)):
                total += expenses_list[i]
            avg = total / len(expenses_list)
            print(f"""Total expense: {total}
Average expense: {avg}\n""")

    elif user_choice == 4:
        expenses_list.clear()
        print("All expenses cleared.\n")

    elif user_choice == 5:
        print("\nExiting the Daily Expense Tracker. Goodbye!\n")
        break

    elif user_choice == 0:
        print_menu()

    elif user_choice not in choices:
        print("Invalid choice. Please try again.\n")