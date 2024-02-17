// client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int client_socket;
    struct sockaddr_in server_addr;

    // Create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Error creating socket");
        exit(1);
    }

    // Initialize server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server IP address
    server_addr.sin_port = htons(8888); // Server port

    // Connect to the server
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error connecting to server");
        exit(1);
    }

    // Input height and weight and calculate BMI
    float height, weight;
    for (int i = 0; i < 4; i++) {
        printf("Enter your height (in meters): ");
        scanf("%f", &height);
        printf("Enter your weight (in kilograms): ");
        scanf("%f", &weight);

        // Send height and weight to the server
        send(client_socket, &height, sizeof(float), 0);
        send(client_socket, &weight, sizeof(float), 0);

        // Receive and print the BMI from the server
        float bmi;
        recv(client_socket, &bmi, sizeof(float), 0);
        printf("Your BMI: %.2f\n", bmi);
    }

    // Close the client socket
    close(client_socket);

    return 0;
}
