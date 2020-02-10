/* Auther   : Phlimon Fahim              */
/* Date     : 02/09/2020                 */
/* FIle Name: ClientTempWithTHingSpeak   */
/* Component: Data to and from ThingSpeak*/
/* Version  : 1.4                        */
/*****************************************/

/*Dependences*/
#include <stdio.h>
#include <winsock2.h>

/*Windows sock Library*/
#pragma comment (lib,"ws2_32.lib")

/*Global Variables*/
char recv_buff[2000];
const char *message;

int main()
{
    /*Only for windows*/
    WSADATA wsa;
    SOCKET s; // socket descriptor

    struct sockaddr_in server;

    printf("\nInitalizing Windows socket .... \n");
    if(WSAStartup(MAKEWORD(2,2) , &wsa) !=0)
    {
        printf("Failed . Error Code : %d",WSAGetLastError());
        return 1;
    }
     printf("Initialized successfully.\n");

     /* Description: Creat socket
      * Inputs     : Family(INET, UNIX)(IPv4 protocols, Internet addresses)
      *              Type of communication (SOCK_STREAM, SOCK_DGRAM)(TCP/IP, UDP)
      *              Protocol (usualy set 0 use default protocol
      * Outputs    : 0 if successful connect, -1 otherwise
     */
     if((s=socket(AF_INET , SOCK_STREAM,0))== INVALID_SOCKET){
         printf("Socket Can't be Created Successfully . we'll have another try .\n");
     }
     printf("Socket Created.\n");

     /*server from data tybe struct sockaddr_in*/
     server.sin_family = AF_INET;
     server.sin_port = htons(80);
     server.sin_addr.s_addr = inet_addr("184.106.153.149");

     /* Description: Connect the machine (client) to the server
      * Inputs     : socket id, address of passive participant (server struct), size of server struct
      * Outputs    : 0 if successful connect, -1 otherwise
     */
     if(connect(s,(struct sockaddr*)&server , sizeof(server)) < 0)
     {
         puts("\nConnection Failed");
     }
     puts("\nConnected!!\n");

     message = "GET /update?api_key=CHDGTB1D768XLFUW&field1=200\r\n\r\n";

     /* Description: Sending Data to server
      * Inputs     : socket id, ,msg, length of message in bytes, data tybe(usualy 0)
      * Outputs    : 0 if successful connect, -1 otherwise
     */
     if((send(s, message, strlen(message), 0)) < 0)
     {
        printf("Sending Failed\n");
     }
     printf("Message sent!!\n");

     /* Description: Receiving Data from server
      * Inputs     : socket id, receive buffer, Size of receive buffer
      * Outputs    : 0 if successful connect, -1 otherwise
     */
     if((recv(s, recv_buff, sizeof(recv_buff), 0)) < 0)
     {
         printf("\nReceived Failed\n");
     }
     puts(recv_buff);
     //printf("\n%d\n", recv_buff);

     /* Description: Clossing socket
      * Inputs     : socket id
      * Outputs    : 0 if successful connect, -1 otherwise
     */
     closesocket(s);

     return 0;
}
