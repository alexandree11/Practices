""" Aleksandr An CISC1215
    Programming assignments from chapter 2 """

from turtle import *

def personal_info():
    name = "John Doe"
    adress = "Brooklyn, NY, 11220"
    phone_num = "(347)123-4567"
    col_major = "Computer Science"

    print(f"""{name}
{adress}
{phone_num}
{col_major}\n""")

def sales_prediction(total_sales):
    annual_profit = total_sales*0.23
    print(f"The annual profit of the company is {annual_profit}\n")

def land_calc(sq_feet):
    acre = 43560
    print(f"{sq_feet/acre}")

def total_purchase():
    items_list = []
    total = 0
    taxes = 0.07

    while(True):
        choice = int(input("""Choose from the menu:
1. Add item
0. Calculate and exit
"""))

        if choice == 1:
            items_list.append(float(input("Enter the price of the item: ")))
            print("Item added successfully\n")
        elif choice == 0:
            if len(items_list) == 0:
                print("The list is empty\n")
            for i in range(len(items_list)):
                total += items_list[i]
            total = total + (total*taxes)
            print(f"The total is {total}")
            break
        else:
            print("Wrong input. Choose 1 or 0")

def distance_traveled():
    car_speed = 70
    print(f"""The distance the car will travel in 6 hours is {car_speed*6}
The distance the car will travel in 10 hours is {car_speed*10}
The distance the car will travel in 15 hours is {car_speed*15}""")

def sales_tax(subtotal):
    state_tax = 0.05
    fed_tax = 0.025
    sales_tax = subtotal*(state_tax+fed_tax)
    total = subtotal+sales_tax
    print(f"""The amount of purchase: {subtotal}
The state sales tax: {(subtotal*state_tax):.2f}
The Country sales tax: {(subtotal*fed_tax):.2f}
The total sales tax: {(sales_tax):.2f}
The total amount of purchase plus sales tax: {(total):.2f}""")

def miles_per_gallon(miles_driven, gal_used):
    mpg = miles_driven/gal_used
    print(f"MPG is {mpg}")

def restaurant_check(subtotal):
    tip_percent = 0.18
    tip_amount = subtotal*tip_percent
    sales_tax_percent = 0.07
    tax_amount = subtotal*sales_tax_percent
    total = subtotal + tip_amount + tax_amount
    print(f"""Subtotal: {subtotal}
Tip amount: {tip_amount}
Tax amount: {tax_amount}
Total: {total}""")

def cels_to_fahr(temp_in_c):
    temp_in_f = (9/5*temp_in_c)+32
    print(f"{temp_in_c} in Celsius is {temp_in_f} in Fahrenheits")

def ingridient_adj(cookies_amount):
    recipe = {
        "sugar": 1.5,
        "butter": 1,
        "flour": 2.75
    }
    print(f"For {cookies_amount} cookies you need {(recipe.get("sugar")/48*cookies_amount):.2f} cup(s) of sugar",
          f"{(recipe.get("butter")/48*cookies_amount):.2f} cup(s) of butter",
          f"{(recipe.get("flour")/48*cookies_amount):.2f} cup(s) of flour")

def percentages_in_zoo(lions, tigers):
    total = lions + tigers
    lions_per = lions/total
    tigers_per = tigers/total
    print(f"The percentage of lions in zoo: {(lions_per):.2f}%\n"
          f"The percentage of tigers in zoo: {(tigers_per):.2f}%" )

def stock_transaction():
    shares_bought = 2000
    buy_price = 40.00
    buy_commission = 0.03
    shares_sold = 2000
    sell_price = 42.75
    sell_commission = 0.03

    amount_paid = shares_bought*buy_price
    buy_commission_paid = amount_paid*buy_commission
    amount_sold = shares_sold*sell_price
    sell_commission_paid = amount_sold*sell_commission
    total_bought = amount_paid + buy_commission_paid
    total_sold = amount_sold + sell_commission_paid

    print(f"The amount paid for the stock: ${(amount_paid):.2f}")
    print(f"The amount of commission paid when bought the stock: ${(buy_commission_paid):.2f}")
    print(f"The amount for which the stock was sold: ${(amount_sold):.2f}")
    print(f"The amount of commission paid when sold the stock: ${(sell_commission_paid):.2f}")

    print(f"Amount of money left after stock was sold: ${(total_sold):.2f}")
    profit = total_sold - total_bought
    print(f"The amount of money left after paying the commission for selling to broker: ${(profit):.2f}")

    if profit > 0:
        print("Profit made.")
    else:
        print("Money lost.")


def planting_grapevines(row_length, space_used, space_between):
    vines_per_row = (row_length - 2*space_used)/space_between
    print(f"{vines_per_row} will fit in the row")

def compound_interest(dep_amount, int_rate, compound_per_year, num_years):
    final_amount = dep_amount*((1 + int_rate/compound_per_year)**(compound_per_year*num_years))
    print(f"The amount of money that will be in the account after {num_years} years is ${final_amount}")

""" def program15 """

def show_menu():
    print(f"""1. Personal Info
2. Sales Prediction
3. Land Calculation
4. Total Purchase
5. Distance Traveled
6. Sales Tax
7. Miles-per-Gallon
8. Tip, Tax, and Total
9. Celsius to Fahrenheit Temperature Converter
10. Ingridient Adjuster
11. Lion and Tiger Percentages
12. Stock Transaction Program
13. Planting Grapevines
14. Compound Interest
15. Turtle Graphics Drawings
""")

show_menu()
choices = [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
while(True):
    user_choice = int(input("Choose from menu(0 to show menu or 999 to close the program): "))
    if user_choice == 1:
        personal_info()
    elif user_choice == 2:
        total_sales = float(input("Enter the amount of total sales: "))
        sales_prediction(total_sales)
    elif user_choice == 3:
        sq_feet = float(input("Enter the total square feet in a tract of land: "))
        land_calc(sq_feet)
    elif user_choice == 4:
        total_purchase()
    elif user_choice == 5:
        distance_traveled()
    elif user_choice == 6:
        subtotal = float(input("Enter the amount of a purchase: "))
        sales_tax(subtotal)
    elif user_choice == 7:
        miles_driven = float(input("Enter the amount of miles driven: "))
        gal_used = float(input("Enter the amount of gallons of gas used: "))
        miles_per_gallon(miles_driven, gal_used)
    elif user_choice == 8:
        subtotal = float(input("Enter the subtotal: "))
        restaurant_check(subtotal)
    elif user_choice == 9:
        temp_in_c = float(input("Enter the temperature in Celsuius: "))
        cels_to_fahr(temp_in_c)
    elif user_choice == 10:
        cookies = float(input("How many cookies you want to make: "))
        ingridient_adj(cookies)
    elif user_choice == 11:
        lions = int(input("Enter the amount of lions in zoo: "))
        tigers = int(input("Enter the amount of tigers in zoo: "))
        percentages_in_zoo(lions, tigers)
    elif user_choice == 12:
        stock_transaction()
    elif user_choice == 13:
        row_length = float(input("Enter the length of the row(in feet): "))
        space_used = float(input("Enter the amount of space used by an end-post assembly(in feet): "))
        space_between = float(input("Enter the amount of space between vines(in feet): "))
    elif user_choice == 14:
        dep_amount = float(input("Enter the amount of principal originally deposited: ")) 
        int_rate = (float(input("Enter the annual interest rate paid by the account(in %): ")))/100
        compound_per_year = int(input("Enter the number of times per year that the interest is compounded: "))
        num_years = int(input("Enter the number of years the account will be left to earn interest: "))
    # elif user_choice == 15:
        
    elif user_choice == 0:
        show_menu()
    elif user_choice == 999:
        print("Exiting the program...")
        break
    else:
        print("Invalid choice. Please try again.")