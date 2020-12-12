#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include <arpa/inet.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include<pthread.h>
char client_message[10];
char buffer[1024];
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
void * socketThread(void *arg)
{
  printf("Entro en el thread \n");
  int newSocket = *((int *)arg);
  recv(newSocket , client_message , 10 , 0);
  printf("Recibió del cliete: %s \n", client_message);
  // Send message to the client socket 
  pthread_mutex_lock(&lock);
  char *message = malloc(sizeof(client_message)+20);
  strcpy(message,"Hello Client : ");
  strcat(message,client_message);
  strcat(message,"\n");
  printf("Se envía : %s \n", message);
  strcpy(buffer,message);
  free(message);
  pthread_mutex_unlock(&lock);
  sleep(1);
  send(newSocket,buffer,sizeof(client_message)+20,0);
  printf("Exit socketThread \n");
  close(newSocket);
  pthread_exit(NULL);
}
int main(){
  int serverSocket, newSocket;
  struct sockaddr_in serverAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size;
  //Create the socket. 
  serverSocket = socket(PF_INET, SOCK_STREAM, 0);
  printf("Se creó el socket\n");
  // Configure settings of the server address struct
  // Address family = Internet 
  serverAddr.sin_family = AF_INET;
  //Set port number, using htons function to use proper byte order 
  serverAddr.sin_port = htons(8080);
  printf("Se define puerto de comunicación 8080 \n");
  //Set IP address to localhost 
  serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); //inet_addr("127.0.0.1");
  //Set all bits of the padding field to 0 
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
  //Bind the address struct to the socket 
  if(bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) !=0) { 
        printf("socket bind failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully binded..\n"); 
  
  //Listen on the socket, with 40 max connection requests queued 
  if(listen(serverSocket,50)==0)
    printf("Listening\n");
  else
    printf("Error\n");
    pthread_t tid[60];
    int i = 0;
    while(1)
    {
       printf("Espera paquete\n"); 
       //Accept call creates a new socket for the incoming connection
        addr_size = sizeof serverStorage;
        newSocket = accept(serverSocket, (struct sockaddr *) &serverStorage, &addr_size);
        printf("Llega al accept\n");
        //for each client request creates a thread and assign the client request to it to process
       //so the main thread can entertain next request
        if( pthread_create(&tid[i], NULL, socketThread, &newSocket) != 0 )
           printf("Failed to create thread\n");
        if( i >= 50)
        {
          i = 0;
          while(i < 50)
          {
            pthread_join(tid[i++],NULL);
          }
          i = 0;
        }
    }
  return 0;
}
