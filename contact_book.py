def display_menu():
    print("Contact Book Menu:", "1. Add Contact",
    "2. View Contact", "3. Edit Contact", "4. Delete Contact",
    "5. List All Contacts", "6. Exit", sep = "\n")
    print()

def add_contact(contact_book):
    print("Adding a new contact:")
    name = input("Name: ")
    phone = input("Phone: ")
    email = input("Email: ")
    address = input("Address: ")
    if name in contact_book:
        print('Contact already exists!')
    else:
        contact_book[name] = {
            "phone": phone,
            "email": email,
            "address": address
        }
        print('Contact added successfully!')
    print()

def view_contact(contact_book):
    print("Enter the contact name to search: ")
    search_name = input()
    print()
    if search_name not in contact_book.keys():
        print("Contact not found!")
    else:
        for key in contact_book.keys():
            if search_name == key:
                print(f"Name: {search_name}")
                for key, value in contact_book[search_name].items():
                    print(f"{key.capitalize()}: {value}")
    print()
        
def edit_contact(contact_book):
    print("Enter the contact name to edit: ")
    search_name = input()
    print()
    if search_name not in contact_book.keys():
        print("Contact not found!")
    else:
        for key in contact_book.keys():
            if search_name == key:
                for key, value in contact_book[search_name].items():
                    new_info = input(f"{key.capitalize()}: ")
                    if new_info == ():
                        continue
                    else:
                        contact_book[search_name][key] = new_info
                print("Contact updated successfully!")
    print()

def delete_contact(contact_book):
    print("Enter the contact name to delete: ")
    search_name = input()
    if search_name not in contact_book.keys():
        print("Contact not found!")
    else:
        del contact_book[search_name]
        print("Contact deleted successfully!")
    print()

def list_all_contacts(contact_book):
    print("The list of all contacts:")
    if not contact_book:
        print("No contacts available.")
    else:
        for name in contact_book.keys():
            print(f"Name: {name}")
            for key, value in contact_book[name].items():
                print(f"{key.capitalize()}: {value}")
            print()
    print()

contact_book = {}
while True:
    display_menu()
    menu_choice = int(input("Enter your choice from the menu: "))
    if menu_choice == 1:
        add_contact(contact_book)
    if menu_choice == 2:
        view_contact(contact_book)
    if menu_choice == 3:
        edit_contact(contact_book)
    if menu_choice == 4:
        delete_contact(contact_book)
    if menu_choice == 5:
        list_all_contacts(contact_book)
    if menu_choice == 6:
        exit()
    



