#include <kv.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

size_t hash(const char *val, size_t capacity){
	size_t hash =0x13371337deadbeef;

	while(*val){
		hash ^= *val;
		hash = hash<<8;
		hash += *val;
		val++;
	}

	return hash % capacity;
}



int kv_put(kv_t *db, const char *key, const char *value){
	if(!db || !key || !value) return -1;
	size_t idx=hash(key, db->capacity);
	
	for(int i= 0; i< db->capacity-1; ++i){
		size_t real_idx=(idx+i)%db->capacity;
		
		kv_entry_t *entry=&db->entries[real_idx];	
		if(entry->key && entry->key != (void *)TOMBSTONE && !strcmp(entry->key, key)){
			char* newval=strdup(value);
			if(!newval) return -1;
			entry->value=newval;
			return 0;
		}

		if(entry->key== NULL || entry->key == (void *)TOMBSTONE ){
			char* newkey=strdup(key);
			char* newval=strdup(value);
            if(!newval||!newkey) {
				free(newkey);
				free(newval);
				return -1;
			}
			entry->key=newkey;
            entry->value=newval;
            db->count++;
		    return 0;
		}

	}
	return -2;	

}

char  *kv_get(kv_t *db, const char *key){
	if(!db || !key ) return NULL;
	size_t idx=hash(key, db->capacity);

	for(int i= 0; i< db->capacity-1; ++i){

		size_t real_idx=(idx+i)%db->capacity;

		kv_entry_t *entry=&db->entries[real_idx];

		if(entry->key==NULL) return NULL;

		if(entry->key == (void *)TOMBSTONE) return NULL;
		if(entry->key && !strcmp(entry->key, key)  ){

			return entry->value;
		}

	}

	return NULL;

}

int    kv_delete(kv_t *db, const char *key){
	if(!db || !key ) return -1;
	size_t idx=hash(key, db->capacity);

	for(int i= 0; i< db->capacity-1; ++i){
		size_t real_idx=(idx+i)%db->capacity;
		kv_entry_t *entry=&db->entries[real_idx];
		if(entry->key==NULL) return -1;
		if(entry->key && !strcmp(entry->key, key)){
			free(entry->key);
			free(entry->value);
			entry->key=(void *)TOMBSTONE;
			entry->value=NULL;
			db->count--;
			return 0;
		}
	}
	return -1;
}


void   kv_free(kv_t *db){
	if(!db) return;
	for(int i=0;i<db->capacity-1;++i){
		kv_entry_t *e=&db->entries[i];
		if(e->key && e->key!=(void*)TOMBSTONE){
			free(e->key);
			free(e->value);
			e->key=NULL;
			e->value=NULL;
		}
	}
	free(db->entries);
	free(db);
}



kv_t *kv_init(size_t capacity){
	if(capacity ==0 ){
		return NULL;
	}
	
	kv_t *table= malloc(sizeof(kv_t));
	if(table==NULL){
		return NULL;
	}

	table->capacity=capacity;
	table->count=0;
	table->entries=calloc(sizeof(kv_entry_t), capacity);
	if(table->entries==NULL){
		return NULL;
	}

	return table;
}
