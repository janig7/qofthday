#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>


int main( int argc, char const *argv[])
{
    char *advice[] = {
        "Think before you speak. Read before you think.\r\n",
        "Keep your face always toward the sunshine - and shadows will fall behind you\r\n",
        "Write it on your heart that every day is the best day in the year.\r\n",
        "Do not pray for an easy life, pray for the strength to endure a difficult one.\r\n",
        "Everything in moderation, including moderation.\r\n",
    };
   int listener_d = socket(PF_INET, SOCK_STREAM, 0); //creating socket

   struct sockaddr_in name;

   name.sin_family = PF_INET;
   name.sin_port = (in_port_t)htons(30000);
   name.sin_addr.s_addr = htonl(INADDR_ANY);

   if(bind(listener_d, (struct sockaddr *) &name, sizeof(name)) == -1)// tying socket with port
   {
       perror("Can not connect with socket");
   } 
 
    int reuse = 1;

    if(setsockopt(listener_d, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(int)) == -1)
        perror("Can not reuse socket");

   listen(listener_d, 10); // setting que length on 10
   puts("Waiting for connection....");

   while(1){
       struct sockaddr_storage client_addr;
       unsigned int address_size = sizeof(client_addr);
       int connect_d = accept(listener_d, (struct sockaddr *)&client_addr, &address_size);
       char *msg = advice[rand() % 6];

       send(connect_d,msg,strlen(msg),0);
       close(connect_d);
   }

    return 0;
    
    
}