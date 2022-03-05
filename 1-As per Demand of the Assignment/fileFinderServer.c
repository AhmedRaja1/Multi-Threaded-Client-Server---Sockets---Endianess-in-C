/*-------------------------------------------------------------------------*
*--- ---*
*--- fileFinderServer.c ---*
*--- ---*
*--- This file defines a C program that gets a file name from ---*
*--- client via a socket, tries to find that file in the current ---*
*--- directory, and sends the directory and beginning portion of ---*
*--- file back if it is found within the current directory or ---*
*--- subdirectory. ---*
*--- ---*
*--- ---- ---- ---- ---- ---- ---- ---- ---- ---*
*--- ---*
*--- Version 1.0 Joseph Phillips ---*
*--- ---*
*-------------------------------------------------------------------------*/

// Compile with:
// $ gcc fileFinderServer.c -o fileFinderServer -lpthread -g

//--- Header file inclusion ---//
#include "fileFinder.h"
#include <errno.h> // For perror()
#include <pthread.h> // For pthread_create()


//--- Definition of constants: ---//
const int ERROR_FD = -1;

//--- Definition of global vars: ---//
// PURPOSE: To be non-zero for as long as this program should run, or '0'
// otherwise.

//--- Definition of functions: ---//
// PURPOSE: To recursively look for a _file_ named 'filenameCPtr' in the
// directory named 'dirnameCPtr'. If it is found then the full path is
// placed in 'filepathBuffer' of length 'filepathBufferLen', and the
// _integer_ '1' is returned. Returns the integer '0' otherwise.

int didFindFile (char* filepathBuffer,
size_t filepathBufferLen,
const char* dirnameCPtr,
const char* filenameCPtr
)
{
// I. Application validity check:
// II. Look in 'dirnameCPtr' for 'filenameCPtr':
DIR* dirPtr;
struct dirent* entryPtr;
char tempBuffer[BUFFER_LEN];
struct stat statBuffer;

// II.A. Base case, look for file itself in 'dirnameCPtr':


void printdir(char dirnameCPtr, int depth)
{	
	// Check if the directory exists & can be opened
    DIR dirnameCPtr;
    struct dirent *entry;
    struct stat statbuf;
    if((dp = opendir(dir)) == NULL) {
        fprintf(stderr,"cannot open directory: %s\n", dir);
        return;
    }
    chdir(dir);
	// Reading the directory
    while((entry = readdir(dirnameCPtr)) != NULL) {
        lstat(entry->d_name,&statbuf);
        if(S_ISDIR(statbuf.st_mode)) {
            /* Found a directory, but ignore . and .. */
            if(strcmp(".",entry->d_name) == 0 ||
                strcmp("..",entry->d_name) == 0)
                continue;
            printf("%*s%s/\n",depth,"",entry->d_name);
            /* Recurse at a new indent level */
            printdir(entry->d_name,depth+4);
        }
        else printf("%*s%s\n",depth,"",entry->d_name);
    }
    chdir("..");
    closedir(dirnameCPtr);
}

int main()
{
    printf("Directory scan of /home:\n");
    printdir("/home",0);
    printf("done.\n");
    exit(0);
}


// II.B. Recursive case: look in subdirectories of 'dirnameCPtr':


static int listDir_helper(char* path) {
  char slash = '\\';  // or maybe slash = '/'
  DIR* dirnameCPtr;
  struct dirent *ent;
  char *NulPosition = &path[strlen(path)];
  if ((dir = opendir(path)) != NULL) {

    while ((ent = readdir(dir)) != NULL) {
      printf("%s%c%s\n", path, slash, ent->d_name);
      if (ent->d_type == DT_DIR) {
        if ((strcmp(ent->d_name, ".") != 0) && (strcmp(ent->d_name, "..") != 0)) {
          sprintf(NulPosition, "%c%s", slash, ent->d_name);
          if (listDir_helper(path)) {
            closedir(dir);
            return 1;
          }
          *NulPosition = '\0';
        }
      }
    }

  }
  closedir(dir);
  return 0;
}

int listDir(const char* path){
  struct dirent *ent;
  char pathmax[MAXPATHLEN+1+sizeof(ent->d_name)+1];
  if (strlen(path) > MAXPATHLEN) {
    return 1;
  }
  strcpy(pathmax, path);
  return listDir_helper(pathmax);
}

int main() {
  listDir2("dirnameCPtr");
  return 0;
}


// III. Finished:
return(0);
}
// PURPOSE: To handle the client being communicated with socket file
// descriptor '*(int*)vPtr'. Returns 'NULL'.
void* handleClient (void* vPtr
)
{

// B-Part Do --- (Implementing doServer(int listenFd))
//Here is a code for doserver

void doServer (int listenFd)
{

//I.  Application validity check:
//II.  Server clients:
pthread_t threadId; 
pthread_attr_t threadAttr;
int threadCount = 0;

//1.Malloc use
int *a; while(1) {
a = malloc(sizeof(int) * 2);
// if not satisied then use &a[0]
accept(getServerFileDescriptor(), NULL, NULL);

// 2.
a[0] = getServerFileDescriptor();

// 3.
a[1] = threadCount++;

//4
pthread_attr_init(&threadAttr);
pthread_attr_setdetachstate(&threadAttr, PTHREAD_CREATE_DETACHED); 
pthread_create(&threadId, &threadAttr, handleClient, &a[0]);
pthread_join(threadId, NULL);
pthread_attr_destroy(&threadAttr);
	}
}


// Here's my handle Client method:

void* handleClient(void* vPtr) {
// Use another pointer to cast back to int
// Save the file descriptor and thread number in local vars
// free() the memory

printf("&a=%p\n", (void *) &a);
printf("castMe=%p\n", (void *) castMe);
int * const numbers = vPtr;
free(vPtr);

/  II.B.  Read command:
char  buﬀer[BUFFER_LEN]; char  command;
int fileNum;

int fd = castMe[0];
int threadNum = castMe[1];

char  text[BUFFER_LEN]; int   shouldContinue  = 1;

while  (shouldContinue)
{
	text[0] = '\0';
read(fd,buﬀer,BUFFER_LEN);
printf("Thread %d received: %s\n",threadNum,buﬀer); 
sscanf(buﬀer,"%c %d \"%[^\"]\"",&command,&fileNum,text);
/printf("Thread %d quitting.\n",threadNum); return(NULL);

}





}
// PURPOSE: To decide a port number, either from the command line arguments
// 'argc' and 'argv[]', or by asking the user. Returns port number.
int getPortNum (int argc,
char* argv[]
)
{

// I. Application validity check:
// II. Get listening socket:
int portNum;
if (argc >= 2)
portNum = strtol(argv[1],NULL,0);
else
{
char buffer[BUFFER_LEN];
printf("Port number to monopolize? ");
fgets(buffer,BUFFER_LEN,stdin);
portNum = strtol(buffer,NULL,0);
}

// III. Finished:
return(portNum);
}

// PURPOSE: To attempt to create and return a file-descriptor for listening
// to the OS telling this server when a client process has connect()-ed
// to 'port'. Returns that file-descriptor, or 'ERROR_FD' on failure.
int getServerFileDescriptor
(int port
)
{

// I. Application validity check:
// II. Attempt to get socket file descriptor and bind it to 'port':
// II.A. Create a socket
int socketDescriptor = socket(AF_INET, // AF_INET domain
SOCK_STREAM, // Reliable TCP
0);
if (socketDescriptor < 0)
{
perror("socket");
return(ERROR_FD);
}

// II.B. Attempt to bind 'socketDescriptor' to 'port':
// II.B.1. We'll fill in this datastruct
struct sockaddr_in socketInfo;

// II.B.2. Fill socketInfo with 0's
memset(&socketInfo,'\0',sizeof(socketInfo));

// II.B.3. Use TCP/IP:
socketInfo.sin_family = AF_INET;

// II.B.4. Tell port in network endian with htons()
socketInfo.sin_port = htons(port);

// II.B.5. Allow machine to connect to this service
socketInfo.sin_addr.s_addr = INADDR_ANY;

// II.B.6. Try to bind socket with port and other specifications
int status = bind(socketDescriptor, // from socket()
(struct sockaddr*)&socketInfo,
sizeof(socketInfo)
);
if (status < 0)
{
perror("bind");
return(ERROR_FD);
}

// II.B.6. Set OS queue length:
listen(socketDescriptor,5);

// III. Finished:
return(socketDescriptor);
}
int main (int argc,
char* argv[]
)
{

// I. Application validity check:
// II. Do server:
int port = getPortNum(argc,argv);
int listenFd = getServerFileDescriptor(port);
int status = EXIT_FAILURE;
if (listenFd >= 0)
{
doServer(listenFd);
close(listenFd);
status = EXIT_SUCCESS;
}


// III. Finished:
return(status);
}