#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define SERVER_PORT 8888

// Function to calculate BMI
float calculate_bmi(float height, float weight) {
    return weight / (height * height);
}

// Function to handle client connections
void *handle_client(void *arg) {
    int client_socket = *((int *)arg);

    while (1) {
        // Receive client data (height and weight)
        float height, weight;
        int bytes_received = recv(client_socket, &height, sizeof(float), 0);
        if (bytes_received <= 0) {
            // Client disconnected or error occurred, exit thread
            break;
        }

        bytes_received = recv(client_socket, &weight, sizeof(float), 0);
        if (bytes_received <= 0) {
            // Client disconnected or error occurred, exit thread
            break;
        }

        // Calculate BMI
        float bmi = calculate_bmi(height, weight);

        // Send the BMI back to the client
        send(client_socket, &bmi, sizeof(float), 0);

        // Open a file for writing results (append mode)
        FILE *file = fopen("bmi_results.txt", "a");
        if (!file) {
            perror("Error opening file");
            exit(1);
        }

        // Write BMI result to the file
        fprintf(file, "Client BMI: %.2f\n", bmi);

        // Close the file
        fclose(file);
    }

    // Close the client socket
    close(client_socket);

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <client/server>\n", argv[0]);
        exit(1);
    }

    if (strcmp(argv[1], "server") == 0) {
        int server_socket, client_socket;
        struct sockaddr_in server_addr, client_addr;
        socklen_t client_len = sizeof(client_addr);

        // Create socket
        server_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (server_socket < 0) {
            perror("Error creating socket");
            exit(1);
        }

        // Initialize server address
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = INADDR_ANY;
        server_addr.sin_port = htons(SERVER_PORT);

        // Bind socket to address
        if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
            perror("Error binding");
            exit(1);
        }

        // Listen for incoming connections
        if (listen(server_socket, 5) < 0) {
            perror("Error listening");
            exit(1);
        }

        printf("Server is listening...\n");

        while (1) {
            // Accept a client connection
            client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
            if (client_socket < 0) {
                perror("Error accepting client connection");
                exit(1);
            }

            // Create a thread to handle the client
            pthread_t thread;
            if (pthread_create(&thread, NULL, handle_client, &client_socket) != 0) {
                perror("Error creating thread");
                exit(1);
            }
        }

        // Close the server socket (never reached in this example)
        close(server_socket);
    } else if (strcmp(argv[1], "client") == 0) {
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
        server_addr.sin_port = htons(SERVER_PORT); // Server port

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
    } else {
        printf("Invalid argument: Use 'client' or 'server'\n");
        exit(1);
    }

    return 0;
}

