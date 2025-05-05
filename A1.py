"""Consider telephone book database of N clients. Make use of a hash table implementation
to quickly look up client‘s telephone number. Make use of two collision handling
techniques and compare them using number of comparisons required to find a set of
telephone numbers"""

class HashTable1:
    """Linear Probing without replacement"""

    def __init__(self, size: int) -> None:
        self.record = []
        self.m = size

        for _ in range(size):
            self.record.append([0, ""])  # [telephone, name]

    def display_table(self) -> None:
        print("Hash table using linear probing (without replacement):")
        for i in range(len(self.record)):
            if self.record[i][0] != 0:  # If the slot is not empty
                # Calculate the number of comparisons to find this record
                tel = self.record[i][0]
                _, comparisons = self.search_rec(tel)
                print(f"{i}: {self.record[i]} (Comparisons: {comparisons})")
            else:  # If the slot is empty
                print(f"{i}: {self.record[i]} (Comparisons: 0)")

    def hash_function(self, tel: int) -> int:
        return tel % self.m

    def generate_table(self, recs: list[list]) -> None:
        for rec in recs:
            self.insert_rec(rec)

    def insert_rec(self, rec: list) -> None:
        key = self.hash_function(rec[0])
        
        # Linear probing to find an empty slot
        while self.record[key][0] != 0:
            key = (key + 1) % self.m

        # Insert the record into the found empty slot
        self.record[key][0] = rec[0]
        self.record[key][1] = rec[1]

    def search_rec(self, tel: int) -> tuple:
        comparisons = 0
        key = self.hash_function(tel)
        original_key = key
        
        while True:
            comparisons += 1
            if self.record[key][0] == tel:  # Record found
                return self.record[key], comparisons
            if self.record[key][0] == 0 or (key + 1) % self.m == original_key:  # Empty slot or full cycle
                return None, comparisons
            key = (key + 1) % self.m


class HashTable2:
    """Linear Probing with replacement"""

    def __init__(self, size: int) -> None:
        self.record = []
        self.m = size

        for _ in range(size):
            self.record.append([0, "", -1])  # [telephone, name, link]

    def display_table(self) -> None:
        print("Hash table using linear probing (with replacement):\t")
        for i in range(len(self.record)):
            print(i, self.record[i])

    def hash_function(self, tel: int) -> int:
        return tel % self.m

    def generate_table(self, recs: list[list]) -> None:
        for rec in recs:
            self.insert_rec(rec)

    def insert_rec(self, rec: list) -> None:
        key = self.hash_function(rec[0])
        if self.record[key][0] == 0:  # If the slot is empty
            self.record[key][0] = rec[0]
            self.record[key][1] = rec[1]
            self.record[key][2] = -1
        else:  # Handle collision
            if self.hash_function(self.record[key][0]) == key:  # Original slot
                last_elmt = key
                while self.record[last_elmt][2] != -1:  # Traverse to the end of the chain
                    last_elmt = self.record[last_elmt][2]
                k = last_elmt
                while self.record[k][0] != 0:  # Find the next empty slot
                    k = (k + 1) % self.m
                self.record[last_elmt][2] = k  # Link to the new slot
                self.record[k][0] = rec[0]
                self.record[k][1] = rec[1]
                self.record[k][2] = -1
            else:  # Replacement case
                for i in range(self.m):
                    if self.record[i][2] == key:
                        prev_link_key = i
                        break

                # Save the old record
                old_rec_tel = self.record[key][0]
                old_rec_name = self.record[key][1]
                old_rec_link = self.record[key][2]

                # Insert the new record
                self.record[key][0] = rec[0]
                self.record[key][1] = rec[1]
                self.record[key][2] = -1

                # Find a new slot for the old record
                k = key
                while self.record[k][0] != 0:
                    k = (k + 1) % self.m

                # Insert the old record into the new slot
                self.record[prev_link_key][2] = k
                self.record[k][0] = old_rec_tel
                self.record[k][1] = old_rec_name
                self.record[k][2] = old_rec_link

    def search_rec(self, tel: int) -> tuple:
        comparisons = 0
        key = self.hash_function(tel)
        current = key

        while True:
            comparisons += 1
            if self.record[current][0] == tel:  # Record found
                return self.record[current], comparisons
            if self.record[current][2] == -1:  # End of chain
                return None, comparisons
            current = self.record[current][2]  # Move to the next linked record


class HashTable3:
    """Quadratic Probing"""

    def __init__(self, size: int) -> None:
        self.record = []
        self.m = size

        for _ in range(size):
            self.record.append([0, ""])  # [telephone, name]

    def display_table(self) -> None:
        print("Hash table using quadratic probing:")
        for i in range(len(self.record)):
            if self.record[i][0] != 0:  # If the slot is not empty
                # Calculate the number of comparisons to find this record
                tel = self.record[i][0]
                _, comparisons = self.search_rec(tel)
                print(f"{i}: {self.record[i]} (Comparisons: {comparisons})")
            else:  # If the slot is empty
                print(f"{i}: {self.record[i]} (Comparisons: 0)")

    def hash_function(self, tel: int) -> int:
        return tel % self.m

    def generate_table(self, recs: list[list]) -> None:
        for rec in recs:
            self.insert_rec(rec)

    def insert_rec(self, rec: list) -> None:
        key = self.hash_function(rec[0])
        i = 0  # Probe counter

        # Use quadratic probing to find an empty slot
        while self.record[(key + i * i) % self.m][0] != 0:
            i += 1
            if i == self.m:  # Table is full
                print("Error: Hash table is full!")
                return

        # Insert the record into the found empty slot
        self.record[(key + i * i) % self.m][0] = rec[0]
        self.record[(key + i * i) % self.m][1] = rec[1]

    def search_rec(self, tel: int) -> tuple:
        comparisons = 0
        key = self.hash_function(tel)
        i = 0

        while True:
            index = (key + i * i) % self.m
            comparisons += 1
            if self.record[index][0] == tel:  # Record found
                return self.record[index], comparisons
            if self.record[index][0] == 0 or i == self.m:  # Empty slot or full cycle
                return None, comparisons
            i += 1

class HashTable4:
    """Double Hashing"""

    def __init__(self, size: int) -> None:
        self.record = []
        self.m = size

        for _ in range(size):
            self.record.append([0, ""])  # [telephone, name]

    def display_table(self) -> None:
        print("Hash table using double hashing:")
        for i in range(len(self.record)):
            if self.record[i][0] != 0:
                tel = self.record[i][0]
                _, comparisons = self.search_rec(tel)
                print(f"{i}: {self.record[i]} (Comparisons: {comparisons})")
            else:
                print(f"{i}: {self.record[i]} (Comparisons: 0)")

    def hash_function1(self, tel: int) -> int:
        return tel % self.m

    def hash_function2(self, tel: int) -> int:
        # Make sure this secondary hash function never returns 0
        return 1 + (tel % (self.m - 1))

    def generate_table(self, recs: list[list]) -> None:
        for rec in recs:
            self.insert_rec(rec)

    def insert_rec(self, rec: list) -> None:
        key1 = self.hash_function1(rec[0])
        key2 = self.hash_function2(rec[0])
        i = 0

        while i < self.m:
            index = (key1 + i * key2) % self.m
            if self.record[index][0] == 0:
                self.record[index][0] = rec[0]
                self.record[index][1] = rec[1]
                return
            i += 1

        print("Error: Hash table is full!")

    def search_rec(self, tel: int) -> tuple:
        comparisons = 0
        key1 = self.hash_function1(tel)
        key2 = self.hash_function2(tel)
        i = 0

        while i < self.m:
            index = (key1 + i * key2) % self.m
            comparisons += 1
            if self.record[index][0] == tel:
                return self.record[index], comparisons
            if self.record[index][0] == 0:
                return None, comparisons
            i += 1

        return None, comparisons


def input_records(n: int) -> list[list]:
    records = []
    for i in range(n):
        print(f"--- PERSON {i+1} ---")
        name = input("Name of the person:\t")
        tel = int(input("Telephone number:\t"))
        records.append([tel, name])
        print("--- DETAILS SAVED ---")
    return records


def main():
    print("Choose the probing method:")
    print("1 -> Linear Probing (without replacement)")
    print("2 -> Linear Probing (with replacement)")
    print("3 -> Quadratic Probing")
    print("4 -> Double Hashing") 
    choice = int(input("Enter your choice (1, 2 , 3 or 4):\t"))

    size = int(input("Enter the size of the hash table:\t"))

    if choice == 1:
        hash_table = HashTable1(size)
    elif choice == 2:
        hash_table = HashTable2(size)
    elif choice == 3:
        hash_table = HashTable3(size)
    elif choice == 4:
        hash_table = HashTable4(size)
    else:
        print("Invalid choice!")
        return

    while True:
        print("\n--- MAIN MENU ---")
        print("1 -> Add a record")
        print("2 -> Search for a record")
        print("3 -> Display the hash table")
        print("4 -> Exit")
        ch = int(input("Choose an option (1-4):\t"))

        if ch == 1:
            n = int(input("Total number of records to add:\t"))
            records = input_records(n)
            hash_table.generate_table(records)
        elif ch == 2:
            tel = int(input("Enter the telephone number to search:\t"))
            result, comparisons = hash_table.search_rec(tel)
            if result:
                print(f"Record found: {result}")
            else:
                print("Record not found.")
            print(f"Number of comparisons made: {comparisons}")
        elif ch == 3:
            hash_table.display_table()
        elif ch == 4:
            print("\n## END OF CODE\n")
            break
        else:
            print("Please choose a valid option (1-4).")


if __name__ == "__main__":
    main()
