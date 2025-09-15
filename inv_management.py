def add_item(item, price, stock):
    if item in inventory:
        raise ValueError(f"Error: Item '{item}' already exists.")
    else:
        inventory[item] = {
            "price": price, 
            "stock": stock
            }
        print (f"Item '{item}' added successfully.")

def update_stock(item, quantity):
    if item not in inventory:
        raise KeyError(f"Error: Item '{item}' not found.")
    new_stock = inventory[item]["stock"] + quantity
    if inventory[item]["stock"] < 0:
        raise ValueError(f"Error: Insufficient stock for '{item}'.")
    inventory[item]['stock'] += new_stock
    print(f"Stock for '{item}' updated successfully.")
            
def check_availability(item):
    if item not in inventory:
        raise KeyError("Item not found")
    return inventory[item]['stock']

def sales_report(sales):
    total = 0
    for item, quantity in sales.items():
        if item not in inventory:
            raise KeyError(f"Error: Item '{item}' not found.")
        if quantity > inventory[item]['stock']:
            raise ValueError(f"Error: Insufficient stock for '{item}'")
        inventory[item]['stock'] -= quantity
        total += quantity * inventory[item]['price']    
        
sales = {}
inventory = {}
add_item("Apple", 0.5, 50)
add_item("Banana", 0.2, 60)
sales = {"Apple": 30, "Banana": 20, "Orange": 10}  # Orange should print an error
print(sales_report(sales))  # Should output: 19.0
print(inventory)