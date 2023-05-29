#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_IP "127.0.0.1"  // Dirección IP del servidor
#define SERVER_PORT 8080       // Puerto del servidor

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[1024];

    // Crear un socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("Error al crear el socket");
        exit(EXIT_FAILURE);
    }

    // Configurar la dirección del servidor
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, SERVER_IP, &serverAddr.sin_addr) <= 0) {
        perror("Dirección inválida/No soportada");
        exit(EXIT_FAILURE);
    }

    // Conectar al servidor
    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Error de conexión");
        exit(EXIT_FAILURE);
    }

    // Enviar y recibir datos
    printf("Conexión establecida. Escribe 'exit' para salir.\n");
    while (1) {
        printf("Enviar mensaje al servidor: ");
        fgets(buffer, 1024, stdin);

        // Enviar datos al servidor
        if (send(clientSocket, buffer, strlen(buffer), 0) == -1) {
            perror("Error al enviar datos");
            exit(EXIT_FAILURE);
        }

        // Salir si el usuario ingresa "exit"
        if (strcmp(buffer, "exit\n") == 0)
            break;

        // Recibir datos del servidor
        memset(buffer, 0, sizeof(buffer));
        if (recv(clientSocket, buffer, sizeof(buffer), 0) == -1) {
            perror("Error al recibir datos");
            exit(EXIT_FAILURE);
        }

        printf("Respuesta del servidor: %s\n", buffer);
    }

    // Cerrar el socket
    close(clientSocket);
    return 0;
}
