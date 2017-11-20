
// -----------------------------------
// CSCI 340 - Operating Systems
// Fall 2017
// server.h header file
// Homework 1
//
// -----------------------------------

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <unistd.h>
#include "server.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>        
#include <sys/time.h>      
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <string.h> 
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

// ------------------------------------
// Function prototype that creates a socket and
// then binds it to the specified port_number
// for incoming client connections
//
//
// Arguments:   port_number = port number the server
//              socket will be bound to.
//
// Return:      Socket file descriptor (or -1 on failure)
//



int bind_port(unsigned int port_number)
{

    // -------------------------------------
    // NOTHING TODO HERE :)
    // -------------------------------------
    // Please do not modify

    int socket_fd;
    int set_option = 1;

    struct sockaddr_in server_address;

    socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, (char*)&set_option, sizeof(set_option));

    if (socket_fd < 0)
        return FAIL;

    bzero((char*)&server_address, sizeof(server_address));

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(port_number);

    if (bind(socket_fd, (struct sockaddr*)&server_address, sizeof(server_address)) == 0) {

        return socket_fd;
    }
    else {

        return FAIL;
    }

} // end bind_port function

// ------------------------------------
// Function prototype that accepts a client
// socket connection
//
//
// Arguments:   server file descriptor
//
// Return:      Termination status of client
//              ( 0 = No Errors, -1 = Error )
//
int accept_client(int server_socket_fd)
{

    int exit_status = OK;

    int client_socket_fd = -1;

    socklen_t client_length;

    struct sockaddr_in client_address;

    char request[REQUEST_SIZE];

    client_length = sizeof(client_address);

    client_socket_fd = accept(server_socket_fd, (struct sockaddr*)&client_address, &client_length);

    // TODO: you add your implementation here
    pthread_t processing_thread_t;
    
    //status variable
    struct thread_start_arg *args = malloc(sizeof(struct thread_start_arg));
    args->client_socket_fd = client_socket_fd;
    args->request = request;

    if (client_socket_fd >= 0) {
        int pthread_status = pthread_create(&processing_thread_t, NULL, processing_thread, (void*) args);
    }
    else {

        exit_status = FAIL;
    }

    if (DEBUG)
        printf("Exit status = %d\n", exit_status);

    return exit_status;

} // end accept_client function

char* find_entities(char* request)
{
    char* search_ptr = request;
                    char* result_ptr = request;


                    size_t str_len = strlen(request);
                    unsigned long int i = 0;

                    for (i = 0; i < str_len; i++) {

                        if ((*search_ptr) == '?') {
                            result_ptr = ++search_ptr;
                        }
                        else if ((*search_ptr) == ' ') {
                            (*search_ptr) = '\0';
                        }
                        else {
                            search_ptr++;
                        }
                    }
                    return result_ptr;
}

void* processing_thread(void* arg)
{
    struct thread_start_arg *args = arg;
    int client_socket_fd = args->client_socket_fd;

    char* request = args->request;

    char content_type[64] = "text/html";

    bzero(request, REQUEST_SIZE);

            read(client_socket_fd, request, REQUEST_SIZE-1);

            if (DEBUG)
                printf("\nHere is the http message:\n%s\n\n", request);

            char entity_body[REQUEST_SIZE];
            char* upload_file = "/upload";

            if (strncmp(request, "GET ", 4) == 0) {
                char* url_offset = request + 4;

                //routes
                char* file_list = "/ ";
                char* delete_file = "/delete/";
                char* get_file = "/get/";
                //use function pointers for more elegance
                if (strncmp(url_offset, delete_file, strlen(delete_file)) == 0) {
                    char* file_name_deletion = url_offset+strlen(delete_file);
                    *(strstr(file_name_deletion, " ")) = '\0';
                    
                    if (remove(file_name_deletion) == 0)
      strcat(entity_body, "Deleted successfully");
   else
      strcat(entity_body, "Unable to delete the file");
      
                }
                else if (strncmp(url_offset, get_file, strlen(get_file)) == 0) {
                    char* file_name_get = url_offset+strlen(get_file);
                    *(strstr(file_name_get, " ")) = '\0';

                    FILE *fptr;
                
                    
                    /*  open the file for reading */
                    fptr = fopen(file_name_get, "r");
                    if (fptr == NULL)
                    {
                        printf("Cannot open file \n");
                    }
                    char chs[2];
                    chs[1] = '\0';
                    chs[0] = fgetc(fptr);
                    while (chs[0] != EOF)
                    {
                        strcat (entity_body, chs);
                        chs[0] = fgetc(fptr);
                    }
                    fclose(fptr);
                    strcpy(content_type, "application/octet-stream");
                }else if (strncmp(url_offset, file_list, strlen(file_list)) == 0) {
                    //This code is from the class c example 1
                    FILE* fhnd;

                    fhnd = fopen("header.html", "r");

                    char line[500];

                    if (fhnd != NULL) {

                        while (fgets(line, sizeof(line), fhnd) != NULL) {

                            strcat(entity_body, line);
                        }
                    }

                    fclose(fhnd);

                    DIR *dir;
                    struct dirent *ent;
                    if ((dir = opendir (".")) != NULL) {
                      /* print all the files and directories within directory */
                      while ((ent = readdir (dir)) != NULL) {
                        if (!(strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0))
                        {
                            
                        struct stat attrib;
                        stat(ent->d_name, &attrib);
                        char date[10];
                        strftime(date, 20, "%d/%m/%y", localtime(&(attrib.st_ctime)));
                        char filesize[10];
                        readable_fs(attrib.st_size, filesize);

                        char table_row_template[512] = "<tr>\n \
      <td><a href=\"/get/%s\">%s</a> \
      <a href=\"/delete/%s\" class=\"btn btn-danger float-right btn-sm\"> \
      <span class=\"oi\" data-glyph=\"trash\"></span></a></td>\n \
      <td>%s</td>\n \
      <td>%s</td>\n \
    </tr>\n";
    char table_row[512];
                        sprintf(table_row, table_row_template, ent->d_name, ent->d_name, ent->d_name, filesize, date);
                        strcat(entity_body, table_row);
                    }
                      }
                      closedir (dir);
                    } else {
                      /* could not open directory */
                      
                    }

                    

                    fhnd = fopen("footer.html", "r");

                    if (fhnd != NULL) {

                        while (fgets(line, sizeof(line), fhnd) != NULL) {

                            strcat(entity_body, line);
                        }
                    }

                    fclose(fhnd);

                }
                else {
                    char entities[1024];

                    strcpy(entity_body, "Error 404");
                    
                    //parse get variables
                    /*char* entities_ptr = find_entities(request);
                    strcpy(entities, entities_ptr);

                    char table_buffer[1024];
                    char* table_content = parse_print_entities(entities, table_buffer);

                    strcat(entity_body, table_content);

                    strcat(entity_body, "<table></body></html>");*/
                }
            }
            else if (strncmp(request, "POST ", 5) == 0) {
                char entities[1024];
                char* search_ptr;
                char* found_ptr;

                strcpy(entity_body, "<html><body><h1>POST Operation</h1><table cellpadding=5 cellspacing=5 border=1>");

                size_t req_len = strlen(request);

                search_ptr = request;

                unsigned long int i = 0;

                for (i = 0; i < req_len; i++) {

                    if (strncmp(search_ptr, "\r\n\r\n ", 4) == 0) {
                        search_ptr = search_ptr + 4;
                        found_ptr = search_ptr;
                    }
                    else {
                        search_ptr++;
                    }
                }

                


                /*char* entities_ptr = find_entities(found_ptr);

                strcpy(entities, entities_ptr);
                char table_buffer[1024];
                    char* table_content = parse_print_entities(entities, table_buffer);

                    strcat(entity_body, table_content);

                strcat(entity_body, "<table></body></html>");*/
                //printf("%s", found_ptr);

                FILE * fp = fopen ("test.txt","w");
                
                
                fprintf (fp, found_ptr);
                

                fclose (fp);
 
   /* close the file*/  
            }
            else {
                //error, http function not supported!
                strcpy(entity_body, "Only GET and POST operations are supported on this webserver.");
                char response[512];
                sprintf(response, "HTTP/1.1 501 Not Implemented\r\nContent-Length: %d\r\n\r\n%s", (int)strlen(entity_body), entity_body);

                //if (DEBUG)
                //    printf("%s\n", response);

                write(client_socket_fd, response, strlen(response));

                close(client_socket_fd);
                return;
            }

            char response[512];
            sprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: %s\r\nContent-Length: %d\r\n\r\n%s", content_type, (int)strlen(entity_body), entity_body);

            //if (DEBUG)
            //    printf("%s\n", response);

            write(client_socket_fd, response, strlen(response));

            close(client_socket_fd);
}

char* parse_print_entities(char* entities, char* buff)
{
    size_t entity_length = strlen(entities);
    unsigned int j = 0;
                    char* entity_start = entities;
                    char* entity_end = entities;
                    char entity_buffer[1024];
                    
                    for (j = 0; j <= entity_length; j++) {
                        if ((*entity_end) == '=') {
                            (*entity_end) = '\0';
                            sprintf(entity_buffer, "<tr><td><b>%s</b></td>", entity_start);
                            entity_start = ++entity_end;
                            strcat(buff, entity_buffer);
                        }
                        else if ((*entity_end) == '&') {
                            (*entity_end) = '\0';
                            sprintf(entity_buffer, "<td>%s</td></tr>\n", entity_start);
                            entity_start = ++entity_end;
                            strcat(buff, entity_buffer);
                        }
                        else if ((*entity_end) == ' ' || (*entity_end) == '\0') {
                            sprintf(entity_buffer, "<td>%s</td></tr>\n", entity_start);
                            strcat(buff, entity_buffer);
                        }
                        else {
                            entity_end++;
                        }
                    }

                    return buff;
}

char* readable_fs(double size/*in bytes*/, char *buf) {
    int i = 0;
    const char* units[] = {"B", "kB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB"};
    while (size > 1024) {
        size /= 1024;
        i++;
    }
    sprintf(buf, "%.*f %s", i, size, units[i]);
    return buf;
}