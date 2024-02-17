// server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

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

int main() {
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
    server_addr.sin_port = htons(8888);

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

    return 0;
}
