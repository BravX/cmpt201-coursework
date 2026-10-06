#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 128

struct header {
  uint64_t size;
  struct header *next;
};

void handle_error(char *err) { return; }

void print_out(char *format, void *data, size_t data_size) {
  char buf[BUF_SIZE];
  ssize_t len = snprintf(buf, BUF_SIZE, format,
                         data_size == sizeof(uint64_t) ? *(uint64_t *)data : *(void **)data);

  if (len < 0) {
    handle_error("snprintf");
  }

  write(STDOUT_FILENO, buf, len);
}

int main() {
  void *start = sbrk(256); // sbrk will increase heap size by 256 byes. *start on success returns
                           // previous break memory address
  if (start == (void *)-1) {
    handle_error("sbrk");
  }

  // Create two equal size memory blocks:
  size_t block_size = 128;

  struct header *first_block = (struct header *)start;
  struct header *second_block = (struct header *)(start + block_size);

  first_block->next = NULL;
  second_block->next = first_block;
  first_block->size = block_size;
  second_block->size = block_size;

  print_out("first block:       %p\n", &first_block, sizeof(first_block));
  print_out("second block:      %p\n", &second_block, sizeof(second_block));
  print_out("first block size:  %lu\n", &first_block->size, sizeof(first_block->size));
  print_out("first block next:  %p\n", &first_block->next, sizeof(first_block->next));
  print_out("second block size: %lu\n", &second_block->size, sizeof(second_block->size));
  print_out("second block next: %p\n", &second_block->next, sizeof(second_block->next));

  // initialize the data of first block & second block (initialized to 0 & 1 respectively - except
  // for header)
  unsigned char *first_data = (unsigned char *)(first_block + 1);
  unsigned char *second_data = (unsigned char *)(second_block + 1);

  memset(first_data, 0, block_size - sizeof(struct header));
  memset(second_data, 1, block_size - sizeof(struct header));

  for (size_t i = 0; i < block_size - sizeof(struct header); i++) {
    uint64_t byte = first_data[i];
    print_out("%lu\n", &byte, sizeof(byte));
  }

  for (size_t i = 0; i < block_size - sizeof(struct header); i++) {
    uint64_t byte = second_data[i];
    print_out("%lu\n", &byte, sizeof(byte));
  }

  return 0;
}
