#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ustr.h"
#include "list.h"

/*
Returns an empty list of initial_capacity
*/
List new_list(int32_t initial_capacity) {
    List list;
    list.size = 0;
    list.capacity = initial_capacity;
    list.data = malloc(initial_capacity * sizeof(struct UStr));
    return list;
}

/*
Initializes an list of length size with elements from array
*/
List new_list_from_array(struct UStr* array, int32_t size) {
    List list = new_list(size);
    for (int32_t i = 0; i < size; i++) {
        list.data[i] = array[i];
    }
    list.size = size;
    return list;
}


/*
Given a list of strings and a separator string, returns a single string 
containing all the strings in list joined by the separator.
*/

/*UStr join(List* list, UStr separator) {
    if (list == NULL) {
        UStr empty = {0}; // or call a helper like new_String_empty()
        return empty; //making sure string isn't empty
    }

    if (list->size >= list->capacity) {
        uint32_t new_capacity = (list->capacity == 0) ? 1 : list->capacity * 2;
        struct UStr* new_data = malloc(new_capacity * sizeof(struct UStr));
        if (new_data == NULL) {
            UStr empty = {0};
            return empty;
        }
        
        for (uint32_t i =0;i < list->size; ++i) {
            new_data[i] = list->data[i]; // Shallow copy
        }

        free(list->data);
        list->data = new_data;
        list->capacity = new_capacity;
    }
    
    list->data[list->size] = new_ustr(separator.contents);
    list->size += 1;
    //Storing the returned UStr in the list->data array at position list->size.


    //UStr result = {0}; // placeholder return value
    UStr result = new_ustr(new_data);
    free(new_data);
    return result;
}

*/

UStr join(List* list, UStr separator) {
    if (list == NULL) {
        UStr empty = (UStr){0};
        return empty;
    }

    // Resize list if needed, (I had this logic already)
    if (list->size >= list->capacity) {
        uint32_t new_capacity = (list->capacity == 0) ? 1 : list->capacity * 2;
        struct UStr* new_data = malloc(new_capacity * sizeof(struct UStr));
        if (new_data == NULL) {
            UStr empty = (UStr){0};
            return empty;
        }

        for (uint32_t i = 0; i < list->size; ++i) {
            new_data[i] = list->data[i]; // shallow copy
        }

        free(list->data);
        list->data = new_data;
        list->capacity = new_capacity;
    }

    // Compute total length needed
    int total_length = 0;
    int sep_len = strlen(separator.contents);
    for (int i = 0; i < list->size; i++) {
        total_length += strlen(list->data[i].contents);
        if (i < list->size - 1) {
            total_length += sep_len;
        }
    }

    // Allocate buffer
    char* joined = malloc(total_length + 1); // +1 for '\0'
    if (joined == NULL) {
        UStr empty = (UStr){0};
        return empty;
    }

    // Fill the buffer
    joined[0] = '\0'; // start with empty string
    for (int i = 0; i < list->size; i++) {
        strcat(joined, list->data[i].contents);
        if (i < list->size - 1) {
            strcat(joined, separator.contents);
        }
    }

    // Wrap in UStr and return
    UStr result = new_ustr(joined);
    free(joined);
    return result;
}



/*
Inserts string s into list at index s, shifting elements to the right.
Expands the list's capacity if necessary (double the capacity, or set to 1 if 0).

Returns 1 on success, 0 if the index is invalid (out of bounds).
*/
int8_t insert(List* list, UStr s, int32_t index) {
    // TODO: implement this

}

/*
Removes the element at the given index and shifts all subsequent elements left.

Returns 1 on success, 0 if the index is invalid (out of bounds).
*/
int8_t listRemoveAt(List* list, int32_t index) {
	// Checks if index if valid ( within bounds )
	// if invalid returns 0 as per instructions
	if ( index < 0 || index >= list->size ) {
		return 0;
	}
	// for loop iterates beginning at index until it hits the last character ( list->size - 1 )
	for ( int i = index; i < list->size - 1; i++ ) {
	// replaces each value with value ahead of index to shift all elements to the left, overwritting the character at index
		list->data[i] = list->data[ i + 1 ];
	}
	// removes extra space
	list->size = list->size - 1;
	// returns 1 if successful
	return 1;
}

/*
Splits the given string s into substrings separated by the given delimiter string.

Returns a List of String objects, each containing a segment between delimiters.

If the delimiter is the empty string, return a list containing the original 
string as a single element.

If the input string ends with the delimiter, include an empty string at the 
end of the result.

Note that the delimiter could be of a length of more than 1 character
*/
List split(UStr s, UStr separator) {
    // TODO: implement this

}
