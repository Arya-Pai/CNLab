#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 17000
#define WINDOW_SIZE 3
#define FRAME_COUNT 10

int main()
{
    int sock, error;
    struct sockaddr_in server_addr;
    char buffer[1024];
    int base = 0, next_frame = 0, ack, expack = 0;

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Socket not created");
        exit(1);
    }

    // Define server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Connect to receiver
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("Connection failed");
        exit(1);
    }

    printf("Connected to receiver.\n");

    // base means count of already sent frames
    while (base < FRAME_COUNT)
    {
        // Send frames within window size
        while (next_frame < base + WINDOW_SIZE && next_frame <= FRAME_COUNT)
        {
            printf("Induce error in frame %d (1(yes)|0(no))", next_frame);
            scanf("%d", &error);
            if (!error)
            {
                sprintf(buffer, "Frame %d", next_frame);
                send(sock, buffer, strlen(buffer), 0);
                printf("Sent: %s\n", buffer);
                next_frame++;
            }
            else
            {
                printf("Sent: Frame %d (with error)", next_frame);
                next_frame++;
            }
        }

        // Wait for ACK
        recv(sock, &ack, sizeof(ack), 0);
        if (ack == expack)
        {
            printf("Received ACK for Frame %d\n", ack);
            ack = 0;
            expack++;
        }
        else
        {
            // printf("ack:%d\n",ack);
            printf("ACK for frame %d not recieved\n", expack);
            next_frame = expack;
        }

        // Move window base

        if (expack > base)
        {
            base = expack - 1;
        }
    }

    // Send termination message
    strcpy(buffer, "exit");
    send(sock, buffer, strlen(buffer), 0);

    close(sock);
    return 0;
}
