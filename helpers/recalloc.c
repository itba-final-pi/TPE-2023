#include <stdlib.h>

#include "recalloc.h"

// Reallocs vec but setting all new fields to 0.
void * recalloc(void * vec, size_t len, size_t new_len){
	void * new = realloc(vec, new_len);

	if(new == NULL) return NULL;

	for(size_t i = len; i < new_len; i++){
		((char *)new)[i] = 0;
	}
	
	return new;
}
