#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ustr.h"
#include "pset1.h"

/*
Initializes a new UStr with contents
*/
UStr new_ustr(char* contents) {
	int32_t bytes = strlen(contents);
	int32_t codepoints = utf8_strlen(contents);
	uint8_t all_ascii = bytes == codepoints;
	char* contents_copy = malloc(bytes + 1);
	strcpy(contents_copy, contents);
	UStr s = {
		codepoints,
		bytes,
		all_ascii,
		contents_copy
	};
	return s;
}

/*
Returns length of string
*/
int32_t len(UStr s) {
	return s.codepoints;
}

/*
Returns a substring of str, starting at index start (inclusive) 
and ending at index end (exclusive).

Returns an empty string on invalid range.
*/
UStr substring(UStr s, int32_t start, int32_t end) {
	// TODO: implement this
int slen = len(s);
int nadd = 0;
if (!s.is_ascii) {
	int i = 0;
while (i < start) {
	unsigned char cbyte = (unsigned char) s.contents[i];
	if ((cbyte < 0x80)) {
		i++;
		nadd++;
	} else if ((cbyte & 0xE0) == 0xC0) {
		i += 2;
		nadd += 2;
	} else if ((cbyte & 0xF0) == 0xE0) {
		i += 3;
		nadd += 3;
	} else if ((cbyte & 0xF8) == 0xF0) {
		i += 4;
		nadd += 4;
	} else {
		i += 1;
		nadd++;
	}
}
}

	
int length = end - start + 1;
if (length - 1 <= 0 || start >= slen || length > slen) {
       return new_ustr("");
}
char* cont = calloc(length, sizeof(int));

strncpy(cont, s.contents + nadd, length - 1);
cont[length] = 0;
UStr nstr = new_ustr(cont);
return nstr;
}

/*
Given 2 strings s1 and s2, returns a string that is the result of 
concatenating s1 and s2. 
*/
UStr concat(UStr s1, UStr s2) {
	// TODO: implement this
int size = len(s1) + len(s2) + 1;
char* ncont = calloc(size, sizeof(char));
strncpy(ncont, s1.contents, len(s1));
strncpy(ncont + len(s1), s2.contents, len(s2));
ncont[size - 1] = 0;
free(s1.contents);
free(s2.contents);
UStr constr = new_ustr(ncont);
return constr;
}


/*
Given a string s and an index, return a string with the character at index 
removed from the original string. 

Returns the original string if index is out of bounds.
*/
UStr removeAt(UStr s, int32_t index) {
	// TODO: implement this

}

/*
Given a string s, return s reversed. 

Example: reverse("apples🍎 and bananas🍌") = "🍌sananab dna 🍎selppa")
*/
UStr reverse(UStr s) {
	// TODO: implement this

}


void print_ustr(UStr s) {
	printf("%s [codepoints: %d | bytes: %d]", s.contents, s.codepoints, s.bytes);
}

void free_ustr(UStr s) {
	if (s.contents != NULL) {
		free(s.contents);
		s.contents = NULL;
	}
}

