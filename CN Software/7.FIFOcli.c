#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>

int main() {
   char s[100] = "";
   char s1[1000] = "";
   int fd, fd1;
   // Open FIFOs for writing and reading
   fd = open("fifo1", O_WRONLY);
   fd1 = open("fifo2", O_RDONLY);
   printf("\nEnter the file name: ");
   scanf("%s", s);
   // Send the filename to FIFO1
   write(fd, s, strlen(s));

   // Read the file content from FIFO2 and display it

   while (read(fd1, s1, 1000) != 0) {

      printf("File Content: %s", s1);

   }
   // Close file descriptors
   close(fd);
   close(fd1);
   return 0;

}