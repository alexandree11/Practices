def add_item(item, price, stock):
    if item in inventory:
        print(f"Error: Item '{item}' already exists.")
    else:
        inventory[item] = {
            "price": price, 
            "stock": stock
            }
        print (f"Item '{item}' added successfully.")

def update_stock(item, quantity):
    if item not in inventory:
        print(f"Error: Item '{item}' not found.")
    else:
        inventory[item]["stock"] += quantity
        if inventory[item]["stock"] < 0:
            print(f"Error: Insufficient stock for '{item}'.")
            inventory[item]["stock"] -= quantity
        else:
            print(f"Stock for '{item}' updated successfully.")
            
def check_availability(item):
    if item not in inventory:
        return ("Item not found")
    else:
        return inventory[item]['stock']

def sales_report(sales):
    total = 0
    for key in sales.keys():
        if key not in inventory:
            print(f"Error: Item '{key}' not found.")
            continue
        stock = sales.get(key)
        if stock > inventory[key]['stock']:
            print(f"Error: Insufficient stock for '{key}'")
            continue
        else:
            inventory[key]['stock'] -= stock
            total = total + (stock * inventory[key]['price'])
    return(f"Total revenue: ${total:.2f}")

sales = {}
inventory = {}
add_item("Apple", 0.5, 50)
add_item("Banana", 0.2, 60)
sales = {"Apple": 30, "Banana": 20, "Orange": 10}  # Orange should print an error
print(sales_report(sales))  # Should output: 19.0
print(inventory)