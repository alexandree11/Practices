def add_student(name, age, courses):
    if name in student_records:
        print(f"Student '{name}' already exists.")
    else:
        student_records[name] = {
            "age": age,
            "grades": set(),
            "courses": courses
        }
        print(f"Student '{name}' added successfully.")

def add_grade(name, grade):
    if name not in student_records:
        print(f"Student '{name}' not found.")
    else:
        student_records[name]["grades"].add(grade)
        print(f"Grade {grade} added for student '{name}'.")

def is_enrolled(name, course):
    if name not in student_records:
        print(f"Student '{name}' not found.")
        return False
    else:
        if course in student_records[name]["courses"]:
            return True
        else:
            return False

def calculate_average_grade(name):
    if name not in student_records:
        print(f"Student '{name}' not found.")
    else:
        student_avg = None
        student_total = 0
        for grade in student_records[name]["grades"]:
            student_total += grade
        return (student_total/len(student_records[name]["grades"]))

def list_students_by_course(course):
    list_of_student_enrolled = []
    for student in student_records:
        if course in student_records[student]["courses"]:
            list_of_student_enrolled.append(student)
    return list_of_student_enrolled

def filter_top_students(threshold):
    list_of_students_above_threshold = []
    for student in student_records:
        if calculate_average_grade(student) > threshold:
            list_of_students_above_threshold.append(student)
    return list_of_students_above_threshold
        

student_records = {}
add_student("Alice", 20, ["Math", "Physics"])
add_student("Bob", 22, ["Math", "Biology"])
add_student("Diana", 23, ["Chemistry", "Physics"])
add_grade("Alice", 90)
add_grade("Alice", 85)
add_grade("Bob", 75)
add_grade("Diana", 95)
print(filter_top_students(80))  # Should return ["Alice", "Diana"]
print(filter_top_students(90))  # Should return ["Diana"]
print(filter_top_students(100))  # Should return an empty list