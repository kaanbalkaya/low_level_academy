#include <stdio.h>
#include <kv.h>
#include <assert.h>
#include <string.h>

int main(){



	kv_t *db = kv_init(16);

	kv_put(db, "name", "alice");
	kv_put(db, "city", "berlin");
	kv_put(db, "lang", "c");

	kv_delete(db, "city");

	kv_free(db);
	// valgrind should report 0 bytes in use at exit
}
