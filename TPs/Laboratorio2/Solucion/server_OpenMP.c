#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "proto.h"
#include "server.h"
#include <omp.h>

// Global variables
int server_sockfd = 0, client_sockfd = 0;
ClientList *root, *now;

void catch_ctrl_c_and_exit(int sig) {
    ClientList *tmp;
    while (root != NULL) {
        printf("\nClose socketfd: %d\n", root->data);
        close(root->data); // close all socket include server_sockfd
        tmp = root;
        root = root->link;
        free(tmp);
    }
    printf("Bye\n");
    exit(EXIT_SUCCESS);
}

void send_to_all_clients(ClientList *np, char tmp_buffer[]) {
    ClientList *tmp = root->link;
    while (tmp != NULL) {
        if (np->data != tmp->data) { // all clients except itself.
            printf("Send to sockfd %d: \"%s\" \n", tmp->data, tmp_buffer);
            send(tmp->data, tmp_buffer, LENGTH_SEND, 0);
        }
        tmp = tmp->link;
    }
}

void client_handler(void *p_client) {
    int leave_flag = 0;
    char nickname[LENGTH_NAME] = {};
    char recv_buffer[LENGTH_MSG] = {};
    char send_buffer[LENGTH_SEND] = {};
    ClientList *np = (ClientList *)p_client;

    // Naming
    if (recv(np->data, nickname, LENGTH_NAME, 0) <= 0 || strlen(nickname) < 2 || strlen(nickname) >= LENGTH_NAME-1) {
        printf("%s didn't input name.\n", np->ip);
        leave_flag = 1;
    } else {
        strncpy(np->name, nickname, LENGTH_NAME);
        printf("%s(%s)(%d) join the chatroom.\n", np->name, np->ip, np->data);
        sprintf(send_buffer, "%s(%s) join the chatroom.", np->name, np->ip);
        send_to_all_clients(np, send_buffer);
    }

    // Conversation
    while (1) {
        if (leave_flag) {
            break;
        }
        int receive = recv(np->data, recv_buffer, LENGTH_MSG, 0);
        if (receive > 0) {
            if (strlen(recv_buffer) == 0) {
                continue;
            }
            sprintf(send_buffer, "%s：%s from %s", np->name, recv_buffer, np->ip);
        } else if (receive == 0 || strcmp(recv_buffer, "exit") == 0) {
            printf("%s(%s)(%d) leave the chatroom.\n", np->name, np->ip, np->data);
            sprintf(send_buffer, "%s(%s) leave the chatroom.", np->name, np->ip);
            leave_flag = 1;
        } else {
            printf("Fatal Error: -1\n");
            leave_flag = 1;
        }
        send_to_all_clients(np, send_buffer);
    }

    // Remove Node
    close(np->data);
    if (np == now) { // remove an edge node
        now = np->prev;
        now->link = NULL;
    } else { // remove a middle node
        np->prev->link = np->link;
        np->link->prev = np->prev;
    }
    free(np);
}

int main()
{
    signal(SIGINT, catch_ctrl_c_and_exit);

    // Create socket
    server_sockfd = socket(AF_INET , SOCK_STREAM , 0);
    if (server_sockfd == -1) {
        printf("Fail to create a socket.");
        exit(EXIT_FAILURE);
    }

    // Socket information
    struct sockaddr_in server_info, client_info;
    int s_addrlen = sizeof(server_info);
    int c_addrlen = sizeof(client_info);
    memset(&server_info, 0, s_addrlen);
    memset(&client_info, 0, c_addrlen);
    server_info.sin_family = PF_INET;
    server_info.sin_addr.s_addr = INADDR_ANY;
    server_info.sin_port = htons(8888);

    // Bind and Listen
    bind(server_sockfd, (struct sockaddr *)&server_info, s_addrlen);
    listen(server_sockfd, 5);

    // Print Server IP
    getsockname(server_sockfd, (struct sockaddr*) &server_info, (socklen_t*) &s_addrlen);
    printf("Start Server on: %s:%d\n", inet_ntoa(server_info.sin_addr), ntohs(server_info.sin_port));

    // Initial linked list for clients
    root = newNode(server_sockfd, inet_ntoa(server_info.sin_addr));
    now = root;
int OMP_NUM_THREADS=4; //definicion del numero de hilos, dependiende el numero de hilos se permitira el numero de conexiones, en este caso se definio 4 por lo tanto permitira hasta 4 conexiones
    while (1) {
	#pragma omp parallel num_threads(OMP_NUM_THREADS)// se define la seccion de  codigo donde el programa sera paralelizables 
	{

        client_sockfd = accept(server_sockfd, (struct sockaddr*) &client_info, (socklen_t*) &c_addrlen);// acepta la solicitud de conexion del cliente 

        // Print Client IP
        getpeername(client_sockfd, (struct sockaddr*) &client_info, (socklen_t*) &c_addrlen);
        printf("Client %s:%d come in.\n", inet_ntoa(client_info.sin_addr), ntohs(client_info.sin_port));

        // Append linked list for clients
        ClientList *c = newNode(client_sockfd, inet_ntoa(client_info.sin_addr)); genera un lista de todas las solicitudes de conexion 
	printf("la lista es ");
        c->prev = now;
        now->link = c;
        now = c;
	
		client_handler( (void *)c);// llamada a la funcion que se encarga de enviar los mensajes a cada nodo.
		//exit(EXIT_SUCCESS);
	}

        
    }

// Se debe paraleliza tanto la llamada de la funcion que se encarga de enviar los mensajes a cada nodo, como la aceptacion de la conexiones de los //usuarios, ya que sino se hace de esta forma, cuando un cliente se conecte, no exitira otro hilo que acepte una nueva conexion, limitanto a 1 la //cantidad de usuarios que se puedan conectar  
    return 0;
}
