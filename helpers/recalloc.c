#include <stdlib.h>

// Hace un realloc de vec pero con todos los nuevos elementos inicializados en 0
void * recalloc(void * vec, size_t len, size_t new_len){
	void * new = realloc(vec, new_len);

	if(new == NULL) return NULL;

	for(int i = len; i < new_len; i++){
		new[i] = 0;
	}
	
	return new;
}
