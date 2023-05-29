#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_PORT 8080  // Puerto del servidor

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrLen = sizeof(clientAddr);
    char buffer[1024];

    // Crear un socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Error al crear el socket");
        exit(EXIT_FAILURE);
    }

    // Configurar la dirección del servidor
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(SERVER_PORT);

    // Enlazar el socket al puerto
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Error al enlazar el socket");
        exit(EXIT_FAILURE);
    }

    // Escuchar por conexiones entrantes
    if (listen(serverSocket, 1) == -1) {
        perror("Error al escuchar por conexiones entrantes");
        exit(EXIT_FAILURE);
    }

    printf("Servidor escuchando en el puerto %d...\n", SERVER_PORT);

    // Aceptar la conexión entrante
    clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &addrLen);
    if (clientSocket == -1) {
        perror("Error al aceptar la conexión");
        exit(EXIT_FAILURE);
    }

    printf("Cliente conectado: %s\n", inet_ntoa(clientAddr.sin_addr));

    // Recibir y enviar datos
    while (1) {
        memset(buffer, 0, sizeof(buffer));

        // Recibir datos del cliente
        if (recv(clientSocket, buffer, sizeof(buffer), 0) == -1) {
            perror("Error al recibir datos");
            exit(EXIT_FAILURE);
        }

        printf("Mensaje del cliente: %s", buffer);

        // Salir si el cliente envía "exit"
        if (strcmp(buffer, "exit\n") == 0)
            break;

        // Responder al cliente
        if (send(clientSocket, "Mensaje recibido", 16, 0) == -1) {
            perror("Error al enviar datos");
            exit(EXIT_FAILURE);
        }
    }

    // Cerrar los sockets
    close(clientSocket);
    close(serverSocket);
    return 0;
}
