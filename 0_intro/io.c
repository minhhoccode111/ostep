#include <assert.h> // for using assert() to validate conditions
#include <fcntl.h> // for file control options like open(), O_WRONLY, O_CREAT, etc
#include <stdio.h>     // for standard I/O operations like sprintf()
#include <string.h>    // for string handling functions like strlen()
#include <sys/stat.h>  // for file permissions and file status flags
#include <sys/types.h> // for system data types used in system calls
#include <unistd.h>    // for system calls like write(), close(), and fsync()

int main(int argc, char *argv[]) {
  // open the file "/tmp/file" for writing. If it does not exist, create it
  // (O_CREAT). If it exists, truncate its contents to zero length (O_TRUNC)
  // the file will have read and write permissions for the user (S_IRUSR |
  // S_IWUSR)
  int fd = open("/tmp/file", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
  // check if the file was successfully opened. If not, the program will
  // terminate
  assert(fd >= 0);

  // create a character buffer to hold the string "hello world\n"
  char buffer[20];
  // write the string "hello world\n" into the buffer using sprintf()
  sprintf(buffer, "hello world\n");

  // write the contents of the buffer to the file referred to by the file
  // descriptor `fd`. The function write() returns the number of bytes written
  // ensure that the number of bytes written matches the length of the string
  int rc = write(fd, buffer, strlen(buffer));
  // check if the number of bytes written is equal to the length of the string
  assert(rc == (strlen(buffer)));

  // force the file to be written to disk, ensuring all data is saved
  fsync(fd);

  // close the file descriptor to release resources
  close(fd);

  // return 0 to indicate successful program termination
  return 0;
}
