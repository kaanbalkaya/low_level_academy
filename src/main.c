#include <stdio.h>
#include <kv.h>
#include <assert.h>
int main(){

	kv_t *kv=kv_init(3);

	if(kv==NULL){
		return -1;
	}

	printf("%p\n",kv);
	printf("%ld\n",kv->capacity);

	kv_t *db = kv_init(16);
	assert(db != NULL);
	assert(db->capacity == 16);
	assert(db->count == 0);
	//kv_free(db);
		
	return 0;
}
