// -----------------------------------
// CSCI 340 - Operating Systems
// Fall 2016
// server.h header file
// Homework 1
//
// -----------------------------------

#define OK 0
#define FAIL -1
#define DEBUG 1
#define REQUEST_SIZE 1048576

// ------------------------------------
// Function prototype that creates a socket and 
// then binds it to the specified port_number 
// for incoming client connections
// 
//
// Arguments:	port_number = port number the server 
//				socket will be bound to.
//
// Return:      Socket file descriptor (or -1 on failure)
//

int bind_port( unsigned int port_number );

// ------------------------------------
// Function prototype that accepts a client
// socket connection
// 
//
// Arguments:	server file descriptor
//
// Return:      Termination status of client
//				( 0 = No Errors, -1 = Error )
//

void accept_client( int server_socket_fd );

void* processing_thread(void* arg);

struct thread_start_arg {    /* Used as argument to thread_start() */
           char* request;        /* ID returned by pthread_create() */
           int       client_socket_fd;       /* Application-defined thread # */
			int server_socket_fd;
       };

char* readable_fs(double size/*in bytes*/, char *buf);