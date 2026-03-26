#include <stdio.h>
#include <kv.h>
#include <assert.h>
#include <string.h>

int main(){



	kv_t *db = kv_init(16);

	kv_put(db, "name", "alice");
	kv_put(db, "city", "berlin");

	assert(kv_delete(db, "name") == 0);

	assert(kv_get(db, "name") == NULL);


	assert(db->count == 1);

	assert(kv_delete(db, "missing") == -1);



	//kv_free(db);	
	return 0;
}
