/*
John Dickson, Oliver Hansson, Sebastian Vingård Larsson
wp4 - exercise 4
2026-02-24
group: 27
submission code: XlvS5W
*/

// search function - returns index of first occurrence, -1 if not found
int search_number(int number, int tab[], int size) {
    for (int i = 0; i < size; i++) {
        if (tab[i] == number)
            return i;
    }
    return -1; // if not found
}

// sort using selection sort (based on the exercise description)
void sort(int number, int tab[]) {
    for (int i = 0; i < number - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < number; j++) {
            if (tab[j] < tab[min_idx])
                min_idx = j;
        }
      	// swap
        int temp = tab[i];
        tab[i] = tab[min_idx];
        tab[min_idx] = temp;
    }
}

void setup() {
    Serial.begin(9600);

    int test[] = {1, 2, 34, 34, 67, 3, 34, 12, 13, 10};
    int size = 10;
  
  
    // sort and print
    sort(size, test);
    Serial.print("sorted: ");
    for (int i = 0; i < size; i++) {
        Serial.print(test[i]);
        Serial.print(" ");
    }
    Serial.println();

    // test searches
  	// 34 to check if it works
    int idxA = search_number(34, test, size);
    Serial.print("search 34: index = ");
    Serial.println(idxA); //should be 2nd index
	
  	// 99 to test number not in array
    int idxB = search_number(99, test, size);
    Serial.print("search 99: index = ");
    Serial.println(idxB);  // should be -1
  
  	//test for index 0
  	int idxC = search_number(1, test, size);
  	Serial.print("search 1: index = ");
  	Serial.println(idxC); // shoudld be index 0

}

void loop() {
    // run once since nothing needs to repeat
}

