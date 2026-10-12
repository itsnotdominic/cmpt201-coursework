#define _DEFAULT_SOURCE
#define BUF_SIZE 1024
#define handle_error(msg)                                                                          \
  do {                                                                                             \
    perror(msg);                                                                                   \
    _exit(1);                                                                                      \
  } while (0) // from the manual
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
struct header {
  uint64_t size;
  struct header *next;
};

void print_out(char *format, void *data, size_t data_size) {
  char buf[BUF_SIZE];
  ssize_t len = snprintf(buf, BUF_SIZE, format,
                         data_size == sizeof(uint64_t) ? *(uint64_t *)data : *(void **)data);
  if (len < 0) {
    handle_error("snprintf");
  }
  write(STDOUT_FILENO, buf, len);
}
void initialize_block(struct header *header, char data) {
  memset(header + 1, data, header->size - sizeof(struct header));
}

void *increase_heap_size(int bytes) {
  void *sbreakptr = sbrk(bytes);
  if (sbreakptr == (void *)-1) {
    perror("sbrk");
  }
  return sbreakptr;
}
void print_block_data(struct header *header) {
  unsigned char *data = (unsigned char *)(header + 1);
  int data_bytes = header->size - sizeof(struct header);

  for (int i = 0; i < data_bytes; ++i) {
    uint64_t value = data[i];
    print_out("%lu\n", &value, sizeof(value));
  }
}
int main(void) {

  intptr_t bytes = 256;
  void *sbreakptr = increase_heap_size(bytes);

  struct header *header1 = (struct header *)sbreakptr;
  struct header *header2 = (struct header *)(sbreakptr + 128);

  header1->next = NULL;
  header1->size = 128;
  header2->next = header1;
  header2->size = 128;

  initialize_block(header1, 0);
  initialize_block(header2, 1);

  print_out("first block:        %p\n", &header1, sizeof(header1));
  print_out("second block:       %p\n", &header2, sizeof(header2));
  print_out("first block size:   %lu\n", &header1->size, sizeof(header1->size));
  print_out("first block next:   %p\n", &header1->next, sizeof(header1->next));
  print_out("second block size:  %lu\n", &header2->size, sizeof(header2->size));
  print_out("second block next:  %p\n", &header2->next, sizeof(header2->next));
  print_block_data(header1);
  print_block_data(header2);

  return 0;
}
