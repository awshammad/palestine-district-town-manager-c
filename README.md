# Palestine District & Town Population Manager (C)

## Overview
A C program for managing **Palestinian districts and their towns** using **doubly linked lists**.  
It loads data from a text file, allows sorting and editing (add/delete/update), computes statistics, and exports the sorted results to an output file.

This was built for an **Architecture / Data Structures** style assignment focusing on pointers, dynamic memory, and linked-list operations.

---

## Features (Menu Options)
1. Load the input file  
2. Print the loaded information (before sorting)  
3. Sort districts alphabetically  
4. Sort towns in each district by population (ascending)  
5. Print the sorted information  
6. Add a new district (and keep the list sorted)  
7. Add a new town to a specific district  
8. Delete a town from a district  
9. Delete a complete district  
10. Calculate total population of Palestine + max/min town population  
11. Print districts and their total population  
12. Change a town population  
13. Save to output file  
14. Exit  

---

## Data Structures
- **Districts**: Doubly linked list (`next`, `prev`)
- **Towns**: Doubly linked list per district (`headTown`)

Each district stores:
- `districtName`
- `district_population` (sum of its towns)
- pointer to the first town node (`headTown`)

---

## Input File
The program loads from a file named **`districts.txt`** (must exist in the same folder when you run the program).

### Format (one record per line)
```
DistrictName | TownName | Population
```

### Example `districts.txt`
```txt
Ramallah | Birzeit | 5000
Ramallah | Ramallah | 40000
Nablus | Nablus | 150000
Nablus | Sebastia | 4500
```

Notes:
- Spaces around names are handled (trimmed).
- Population is read as an integer.

---

## Output File
When you choose **option 13**, the program writes the sorted data into:
- **`sorted_districts.txt`**

Example output format:
```txt
Ramallah District, Population = 45000
Birzeit, 5000
Ramallah, 40000
```

---

## How to Compile & Run

### Windows (MinGW / gcc)
```bash
gcc Project1.c -o Project1
Project1.exe
```

### Linux / macOS
```bash
gcc Project1.c -o Project1
./Project1
```

Make sure `districts.txt` is in the same directory as the executable before running.

---

## Files
- `Project1.c` — main program source code
- `districts.txt` — input dataset (you create/provide it)
- `sorted_districts.txt` — generated output file

---

## Notes
- If you upload this repo to GitHub, consider **not uploading** `sorted_districts.txt` (it is generated).
- If you want, you can include a small `districts.txt` as a sample input.

---

## Author
- Aws Hammad (1221697)
