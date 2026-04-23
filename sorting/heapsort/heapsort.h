#define MAX_SIZE 1000000

typedef int element_type;

typedef struct
{
  element_type queue[MAX_SIZE];
  size_t size;
} priority_queue;

int parent(size_t index);
size_t left_child(size_t index);
size_t right_child(size_t index);

void print_array(element_type array[], size_t size);

void insert(priority_queue *pq, element_type element);
void bubble_up(priority_queue *pq, size_t index);
void swap(priority_queue *pq, size_t first, size_t second);

void make_heap(priority_queue *pq, element_type input[], size_t input_length);
void make_heap_optimized(priority_queue *pq, element_type input[], size_t input_length);

element_type extract_min(priority_queue *pq);
void percolate(priority_queue *pq, size_t index);

void heapsort(element_type input_array[], size_t input_length);