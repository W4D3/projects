// chat_server.c
// Mitchell Wade
// April 17, 2015
// This program is the API for a chat server in C.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "sockettome.h"
#include "jrb.h"
#include "dllist.h"

JRB t;

typedef struct client {
    char* name;
    struct chatroom* r;
    int fd;
    FILE *fin, *fout;
} client;

typedef struct chatroom {
    Dllist clients;
    Dllist messages;
    char* name;
    pthread_mutex_t *lock;
    pthread_cond_t *cv;
} chatroom;

void *client_thread(void *v) {

    int i;
    char command[1000], buf[1000];
    client *clientp, *tmpclientp;
    chatroom *chatp;
    JRB jtmp;
    Dllist dlltmp, dllrm;

    // Grab the client struct
    clientp = (void *)v;

    // Connect input/ouput to stdin/out for each client
    clientp->fin = fdopen(clientp->fd, "r");
    if (clientp->fin == NULL) { perror("making fin"); exit(1); }
    clientp->fout = fdopen(clientp->fd, "w");
    if (clientp->fout == NULL) { perror("making fout"); exit(1); }

    // Print out the label for chatrooms
    if (fputs("Chat Rooms:\n\n", clientp->fout) == EOF) {
        fclose(clientp->fin);
        fclose(clientp->fout);
        pthread_exit(NULL);
    }

    if (fflush(clientp->fout) == EOF) {
        fclose(clientp->fin);
        fclose(clientp->fout);
        pthread_exit(NULL);
    }

    // Print out each chat room name
    jrb_traverse(jtmp, t) {

        // Grab each chatroom ptr
        chatp = (chatroom *) jtmp->val.v;

        if (fputs(chatp->name, clientp->fout) == EOF) {
            fclose(clientp->fin);
            fclose(clientp->fout);
            pthread_exit(NULL);
        }

        if (fflush(clientp->fout) == EOF) {
            fclose(clientp->fin);
            fclose(clientp->fout);
            pthread_exit(NULL);
        }

        if (fputs(":", clientp->fout) == EOF) {
            fclose(clientp->fin);
            fclose(clientp->fout);
            pthread_exit(NULL);
        }

        if (fflush(clientp->fout) == EOF) {
            fclose(clientp->fin);
            fclose(clientp->fout);
            pthread_exit(NULL);
        }

        // Print all clients from each chatroom
        dll_traverse(dlltmp, chatp->clients) {
            if (fputs(" ", clientp->fout) == EOF) {
                fclose(clientp->fin);
                fclose(clientp->fout);
                pthread_exit(NULL);
            }

            if (fflush(clientp->fout) == EOF) {
                fclose(clientp->fin);
                fclose(clientp->fout);
                pthread_exit(NULL);
            }

            tmpclientp = (client *) dlltmp->val.v;

            if (fputs(tmpclientp->name, clientp->fout) == EOF) {
                fclose(clientp->fin);
                fclose(clientp->fout);
                pthread_exit(NULL);
            }

            if (fflush(clientp->fout) == EOF) {
                fclose(clientp->fin);
                fclose(clientp->fout);
                pthread_exit(NULL);
            }
        }
    }

    // Prompt client for name
    if (fputs("Enter your chat name (no spaces):\n", clientp->fout) == EOF) {
        fclose(clientp->fin);
        fclose(clientp->fout);
        pthread_exit(NULL);
    }

    if (fflush(clientp->fout) == EOF) {
        fclose(clientp->fin);
        fclose(clientp->fout);
        pthread_exit(NULL);
    }

    if (fgets(command, sizeof(command), clientp->fin) == NULL) {
        fclose(clientp->fin);
        fclose(clientp->fout);
        pthread_exit(NULL);
    } 
    chatp->name = command;    

    // Prompt client for a chat room
    if (fputs("Enter chat room:\n", clientp->fout) == EOF) {
        fclose(clientp->fin);
        fclose(clientp->fout);
        pthread_exit(NULL);
    } 

    if (fflush(clientp->fout) == EOF) {
        fclose(clientp->fin);
        fclose(clientp->fout);
        pthread_exit(NULL);
    } 

    if (fgets(command, sizeof(command), clientp->fin) == NULL) {
        fclose(clientp->fin);
        fclose(clientp->fout);
        pthread_exit(NULL);
    }

    //HERE

    // Find the chatroom that was specified
    jtmp = jrb_find_str(t, command);

    if (jtmp != NULL) {
        chatp = (chatroom *) jtmp->val.v;
        clientp->r = chatp;

        // Lock the chatroom thread
        pthread_mutex_lock(chatp->lock);

        dll_append(chatp->clients, new_jval_v((void *) clientp));
        strcpy(command, clientp->name);
        strcat(command, " has joined\n\0");
        dll_append(chatp->messages, new_jval_s(strdup(command)));

        // Signal and unlock the chatroom
        pthread_cond_signal(chatp->cv);
        pthread_mutex_unlock(chatp->lock);
    } else {
        printf("Chatroom %s called by %s does not exist\n", command, clientp->name);
        exit(1);
    }

    // Connect to chat room
    while (1) {
        
        strcpy(buf, clientp->name);
        strcat(buf, ": ");

        // Read in the clients message
        if (fgets(command, sizeof(command), clientp->fin) == NULL) {
            fclose(clientp->fin);

            // Print out client has left
            strcpy(buf, clientp->name);
            strcat(buf, " has left\n");
            pthread_mutex_lock(chatp->lock);
            dll_append(chatp->messages, new_jval_s(strdup(buf)));

            // Remove client from chatroom dllist
            if(clientp->fout != 0){ 
                fclose(clientp->fout);
                dllrm = NULL;
                dll_traverse(dlltmp, chatp->clients){
                    tmpclientp = (client *) dlltmp->val.v;
                    if(strcmp(clientp->name, tmpclientp->name) == 0) {
                        dllrm = dlltmp;
                    }
                }
                if(dllrm != NULL) dll_delete_node(dllrm);
            }

            /* Signal the chatroom, get rid of client's pthread */
            pthread_cond_signal(chatp->cv);
            pthread_mutex_unlock(chatp->lock);
            pthread_exit(NULL);
        }
        else{
            strcat(buf, command);

            /* Obtain lock, add message to the chatroom's message list */
            pthread_mutex_lock(chatp->lock);
            dll_append(chatp->messages, new_jval_s(strdup(buf)));

            /* Signal the chatroom, then unlock the mutex */
            pthread_cond_signal(chatp->cv);
            pthread_mutex_unlock(chatp->lock);
        }
    }

    return NULL;
}


void *chat_thread(void *v) {

    chatroom *chatp;
    client *clientp;
    Dllist msg_dlltmp, client_dlltmp;

    // Grab the chatroom struct
    chatp = (chatroom *)v;

    // Grab the chatroom's lock
    pthread_mutex_lock(chatp->lock);
    while (1) {

        // Blocks until signaled to print messages
        pthread_cond_wait(chatp->cv, chatp->lock);

        // Print message to all clients in chatroom
        dll_traverse(msg_dlltmp, chatp->messages) {
            if (!dll_empty(chatp->clients)) {
                dll_traverse(client_dlltmp, chatp->clients) {
                    clientp = (client *) client_dlltmp->val.v;

                    if(fputs(msg_dlltmp->val.s, clientp->fout) == EOF) {
                        dll_delete_node(client_dlltmp);
                        fclose(clientp->fout);
                    }

                    if (fflush(clientp->fout) == EOF) {
                        dll_delete_node(client_dlltmp);
                        fclose(clientp->fout);
                    }
                }
            }
        }
    }

    // Delete old message log and create a new log
    free_dllist(chatp->messages);
    chatp->messages = new_dllist();

    return NULL;
}

int main(int argc, char** argv) {

    int i, fd, sock;
    chatroom *chatp;
    client *clientp;
    pthread_t *tidp;

    printf("Initialize Server\n");

    if (argc < 3) {
        fprintf(stderr, "usage: chat_server host port [chatrooms]\n");
        exit(1);
    }

    // Make a tree to hold all threads
    t = make_jrb();

    // Create a thread for each chatroom 
    for (i = 2; i < argc; i++) {
        chatp = (chatroom *) malloc(sizeof(chatroom));
        chatp->clients = new_dllist();
        chatp->messages = new_dllist();
        chatp->lock = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
        pthread_mutex_init(chatp->lock, NULL);
        chatp->cv = (pthread_cond_t *) malloc(sizeof(pthread_cond_t));
        pthread_cond_init(chatp->cv, NULL);
        chatp->name = (char *) malloc(sizeof(char)*strlen(argv[i]));
        chatp->name = strdup(argv[i]); 

        // Create a chatroom thread
        tidp = (pthread_t *) malloc(sizeof(pthread_t));    
        if (pthread_create(tidp, NULL, chat_thread, chatp) != 0) {
            perror("pthread_create");
            exit(1);
        }
        pthread_detach(*tidp);

        // Store the new chatroom in a tree
        jrb_insert_str(t, chatp->name, new_jval_v((void *)chatp));
    }
    
    printf("Chatrooms made\n");

    // Creates a link for anyone else to join the server
    sock = serve_socket(atoi(argv[1]));

    // Wait for and create new clients
    while (1) {
        fd = accept_connection(sock);
        clientp = (client *) malloc(sizeof(client));
        clientp->name = NULL;
        clientp->r = NULL;
        clientp->fd = fd;
        clientp->fin = NULL;
        clientp->fout = NULL;

        // Create a client thread
        tidp = (pthread_t *) malloc(sizeof(pthread_t));     
        if (pthread_create(tidp, NULL, client_thread, clientp) != 0) {
            perror("pthread_create");
            exit(1);
        }
        printf("Added client\n");
        pthread_detach(*tidp);
    }

    return 0;
}
