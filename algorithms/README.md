# Algorithms and Data-Structures

- [Home](/README.md#async-table-of-contents)
- [OS](#os)
  - [Thread](#thread)

## OS
[top](#algorithms-and-data-structures)

### Thead
[top](#algorithms-and-data-structures)

```C
typedef thread_structure{
    char* thread_name;
    int thread_number;
    int thread_status; //ready, run blocked
    int program_counter;
    int stack_pointer;
    int registers [32];
}
```