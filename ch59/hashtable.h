#define CAPACITY 16

// Defines the HashTable item.
typedef struct Ht_item
{
    char *key;
    char *value;
} Ht_item;

// Defines the LinkedList.
typedef struct LinkedList
{
    Ht_item *item;
    struct LinkedList *next;
} LinkedList;

// Defines the HashTable.
typedef struct HashTable
{
    // Contains an array of pointers to items.
    Ht_item **items;
    LinkedList **overflow_buckets;
    int size;
    int count;
} HashTable;

HashTable *create_table(int size);
void ht_insert(HashTable *table, char *key, char *value);
char *ht_search(HashTable *table, char *key);
void ht_delete(HashTable *table, char *key);
void free_table(HashTable *table);