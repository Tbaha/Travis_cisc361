#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <pwd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "sh.h"
#include <glob.h>
#include <fcntl.h>
#include <sys/stat.h>

int sh( int argc, char **argv, char **envp )
{
  char *prompt = calloc(PROMPTMAX, sizeof(char));
  char *commandline = calloc(MAX_CANON, sizeof(char));
  char *command, *arg, *commandpath, *p, *pwd, *owd;
  char **args = calloc(MAXARGS, sizeof(char*));
  int uid, i, status, argsct, go = 1;
  struct passwd *password_entry;
  char *homedir;
  struct pathelement *pathlist;

  int found; //Boolean to show if matches were found when user input a wildcard arg
  glob_t globs; //glob struct to get files matching the wild card pattern

  uid = getuid();
  password_entry = getpwuid(uid);               /* get passwd info */
  homedir = password_entry->pw_dir;		/* Home directory to start
						  out with*/
     
  if ( (pwd = getcwd(NULL, PATH_MAX+1)) == NULL )
  {
    perror("getcwd");
    exit(2);
  }
  owd = calloc(strlen(pwd) + 1, sizeof(char));
  memcpy(owd, pwd, strlen(pwd));
  prompt[0] = ' '; prompt[1] = '\0';

  /* Put PATH into a linked list */
  pathlist = get_path();

  while ( go )
  {
    /* print your prompt */
    printf("%s ~%s> ", prompt, pwd);

    /* get command line and process */
    if(fgets(commandline, MAX_CANON, stdin) == NULL)
    {  
      // If user hits "enter" with nothing written, clear stdin and continue the while loop 
      if(getchar() == EOF){
       fflush(stdin);
       continue;
      }
    }  

    // Ignore commandline input if newline
    if(!strcmp(commandline, "\n")) continue;

    // Get rid of the '\0'
    int len = strlen(commandline);
    commandline[len-1] = '\0';

    // Separate the user input by a space
    arg = strtok(commandline, " ");
    argsct = 0;
    while(arg != NULL)
    {
      args[argsct] = arg;
      argsct++;
      arg = strtok(NULL, " ");
    }

    // Handle wildcards
    found = 0;
    for(i=1;i<argsct;i++)
    {
      // If arg contains wildcard characters * or ?
      if(args[i] != NULL &&
        (strchr(args[i], '*') != NULL ||
         strchr(args[i], '?') != NULL))
      {
        int erro;
        // If error returned
        if((erro = glob(args[i], GLOB_ERR, 0, &globs)) != 0)
        {
          // Ignore NOMATCH error. Continue, leaving argument as is.
          if(erro == GLOB_NOMATCH)
          {
            printf("note: no matches for pattern %s\n", args[i]);
            continue;
          }
          perror("glob error\n");
          return 1;
        }

        // Set patternfound to true 
        found = 1;

        // Check if adding matching names will exceed MAXARGS
        if(globs.gl_pathc + argsct - 1 > MAXARGS)
        {
          printf("matches for pattern %s exceeds MAXARGS count\n", args[i]);
          continue;
        }

        // Offset other arguments
        for(int j=i+1; j<argsct; j++)
        {
          args[j+globs.gl_pathc] = args[j];
          args[j] = NULL;
        }

        // Set arguments to matching names
        for(int j=0; j<globs.gl_pathc; j++)
        {
          args[i+j] = globs.gl_pathv[j];
        }

        // Add to argsct
        argsct += globs.gl_pathc;

        break;
      }
    }
  

    /* check for each built in command and implement */

    command = args[0]; //first word the user input is a command

    if (!strcmp(command, "exit")){
      printf("exit\n");

      go = 0; // to exit the loop

      // free allocated memory
      free(prompt);
      free(commandline);
      free(command);
      free(arg);
      free(commandpath);
      free(p);
      free(pwd);
      free(owd);
      free(args);
      free(homedir);

      while(pathlist != NULL){
        struct pathelement *tmp = pathlist->next;
        pathlist->next = NULL;
        free(pathlist);
        pathlist = tmp;
      }

    }
    else if(!strcmp(command, "which")){
      if(argsct < 2){
        printf("which: requires more arguments\n");
      }
      else{
      //Searching for commands
        for(i = 1; i < argsct; i++){ 
          char *temp;
          if( (temp = which(args[1], pathlist)) != NULL){
          //Printing commands if found
          printf("[%s]\n", temp);
	        free(temp);
          }
	        else{
            printf("%s: Command does not exist\n", args[i]);
          }
        }
      }
    }
    else if(!strcmp(command, "where")){
      if(argsct < 2){
          printf("where: requires more arguments\n");
      }
      else{
      //Searching for commands
        for(i = 1; i < argsct; i++){
          where(args[i], pathlist);
        }
      }
    }
    else if(!strcmp(command, "cd")){
      if(argsct > 2)
      {
        printf("cd: has to many arguments\n");
      }
      else if(argsct == 2)
      {
        // If cd -
        if(!strcmp(args[1], "-"))
        {
          // copy of current working directory
          char *tmp = getcwd(NULL, PATH_MAX);

          //Go back to the previous working directory
          if(chdir(owd) < 0)
          {
            perror("No previous working directory\n");
            free(tmp);
          }
          else
          {
            // Change to original working directory
            free(owd);
            owd = tmp;
          }
        }
        else
        {
          // copy of current working directory
          char *tmp = getcwd(NULL, PATH_MAX);

          // Change to given directory
          if(chdir(args[1]) < 0)
          {
            perror("No such file or directory");
            free(tmp);
          }
          else
          {
            // Change to new orginal working directory
            free(owd);
            owd = tmp;
          }
        }
      }
      else
      {
        // Go to 
        free(owd);
        owd = getcwd(NULL, PATH_MAX);

        // Change to home directory
        if(chdir(homedir) < 0)
          perror("At home directory");
      }
    }
    else if(!strcmp(command, pwd)){
      // Prints current working directory
      pwd = getcwd(NULL, PATH_MAX);
      printf("%s\n", pwd);
      free(pwd);
    }
    else if(!strcmp(command, "list")){
      if(argsct == 2){
        list(args[1]);
      }
      else if(argsct > 2){
        for(i = 1; i < argsct; i++){
          list(args[i]);
        }
      }
      else{
        list(".");
      }
    }
    else if(!strcmp(command, "pid")){
      // Print process ID
      printf("%d\n", getpid());
    }
    else if(!strcmp(command, "kill")){
      // If only given pid
      if(argsct == 2){
        //Change string to int
        int kpid;
        kpid = strtol(args[1], NULL, 10);

        // Terminate process with given pid
        kill(kpid, SIGTERM);
      }
      // Else if given signal AND pid
      else if(argsct == 3 && args[1][0] == '-'){
        // Change string to in
        int kpid;
        kpid = strtol(args[2], NULL, 10);
        // Parse signal
        int sig;
        sig = strtol(args[1]+1, NULL, 10);

        // Send signal to pid
        kill(kpid, sig);
      }
    }
    else if(!strcmp(command, "prompt")){
      if(argsct > 2){
        printf("prompt: has to many arguments\n");
      }
      else if(argsct == 2){
        // Free current prompt, and set to given argument
        free(prompt);
        prompt = (char*)calloc(PROMPTMAX, sizeof(char));
        strcpy(prompt, args[1]);
      }
      else{
        // Get new prompt via input from command line. To be stored in promptBuf
        char *newPrompt = (char*)malloc(PROMPTMAX*sizeof(char));

        printf("input prompt prefix: ");
        if(fgets(newPrompt, PROMPTMAX, stdin) == NULL){
          perror("fgets error\n");
          return 1;
        }

        int buflen = strlen(newPrompt);
        newPrompt[buflen-1] = '\0';
        strcpy(prompt, newPrompt);

        free(newPrompt);
      }
    }
    else if(!strcmp(command, "printenv")){
      if(argsct == 1){
        //Print every environment variable
        i = 0;
        char *env;
        while((env = envp[i++]) != NULL)
          printf("%s\n", env);
      }
      else if(argsct == 2){
        // Search for the variable
        char *var = getenv(args[1]);
        if(var == NULL)
          printf("can not find environment variable: %s\n", args[1]);
        else
          printf("%s\n", var);
      }
      else{
        printf("printenv: has to many arguments\n");
      }
    }
    else if(!strcmp(command, "setenv")){
      if(argsct == 1){
        // If no arguments, iterate through environment list and print each
        int index = 0;
        char *env;
        while((env = envp[index++]) != NULL)
          printf("%s\n", env);
      }
      else if(argsct == 2)
      {
        // If given single argument, set as empty environment variable
        setenv(args[1], "", 1);
      }
      else if(argsct == 3){
        // If given two arguments, set 2nd as value of 1st
        setenv(args[1], args[2], 1);

        //If modifying PATH variable
        if(!strcmp(args[1], "PATH")){
          // Free old pathlist
          while(pathlist != NULL){
            struct pathelement *tmp = pathlist->next;
            pathlist->next = NULL;
            free(pathlist);
            pathlist = tmp;
            }

          // Get new pathlist
          pathlist = get_path();
        }
        // If modifying HOME variable
        else if(!strcmp(args[1], "HOME")){
          // Free old homedir, set to new one
          free(homedir);
          int homedirlen = strlen(args[2]) + 1;
          homedir = malloc(homedirlen * sizeof(char));
          strcpy(homedir, args[2]);
          homedir[homedirlen] = '\0';
        }
      }
      else if(argsct > 3){
        //If given more than two arguments, return error
        perror("has to many arguments\n");
      }
    }
     /*  else  program to exec */
    else
    {
       /* find it */
       /* do fork(), execve() and waitpid() */

      /* else */
        /* fprintf(stderr, "%s: Command not found.\n", args[0]); */

      char *path;
      // If command is absolute path or starts with ./ or ../
      if((strlen(command) > 0 && !strncmp(command, "/", 1)) ||
         (strlen(command) > 1 && !strncmp(command, "./", 2)) ||
         (strlen(command) > 2 && !strncmp(command, "../", 3)))
      {
        // Declare stat struct to determine if directory exist
        struct stat path_stat;
        stat(command, &path_stat);
        // If can execute it is not a directory
        if(!access(command, X_OK) && !S_ISDIR(path_stat.st_mode))
        {
          // Create new process
          int pid = fork();
          if(pid < 0)
          {
            fprintf(stderr, "fork failed.\n");
          }
          // If child...
          else if(pid == 0)
          {
            // Set signal behaviors to default
            signal(SIGINT, SIG_DFL);
            signal(SIGTSTP, SIG_DFL);
            signal(SIGTERM, SIG_DFL);

            // Execute command
            printf("Executing %s\n", command);
            execve(command, args, envp);

            exit(-1);
          }
          // If parent...
          else
          {
            // Wait for child to finish
            waitpid(pid, &status, 0);

            // If child returns with status other than 0, print the status
            if(WEXITSTATUS(status) != 0)
              printf("child process %d exited with status %d\n", pid, WEXITSTATUS(status));
          }
        }
        else
        {
          fprintf(stderr, "%s: No such file (or no permission to exec)\n", args[0]);
        }
      }
      // Else look for command in PATH
      else if((path = which(command, pathlist)) != NULL)
      {
        // Create new process
        int pid = fork();
        if(pid < 0)
        {
          fprintf(stderr, "fork failed.\n");
        }
        // If child...
        else if(pid == 0)
        {
          // Set signal behaviors to default
          signal(SIGINT, SIG_DFL);
          signal(SIGTSTP, SIG_DFL);
          signal(SIGTERM, SIG_DFL);

          // Set first (0) argument to obtained path, and execute command
          printf("Executing built-in %s\n", command);
          args[0] = path;
          execve(path, args, envp);

          exit(-1);
        }
        // If parent...
        else
        {
          // Wait for child to finish
          waitpid(pid, &status, 0);

          // If child returns with status other than 0, print the status
          if(WEXITSTATUS(status) != 0)
            printf("child process %d exited with status %d\n", pid, WEXITSTATUS(status));
        }
        free(path);
      }
      else
        fprintf(stderr, "%s: Command not found.\n", args[0]);
    }

    // Set args to NULL
    for(i=0;i<argsct;i++)
    {
      args[i] = NULL;
    }

    // free glob 
    if(found){
      globfree(&globs);
    }
  }
  return 0;
} /* sh() */

char *which(char *command, struct pathelement *pathlist )
{
  char cmd[64];
  struct pathelement *p;

  p = get_path();
  while (p) {         // WHICH
    sprintf(cmd, "%s/gcc", p->element);
    if (access(cmd, X_OK) == 0) {
      printf("[%s]\n", cmd);
      break;
    }
    p = p->next;
  }
   /* loop through pathlist until finding command and return it.  Return
   NULL when not found. */
} /* which() */

char *where(char *command, struct pathelement *pathlist )
{
  char cmd[64];
  struct pathelement *p;

  p = get_path();
  while (p) {         // WHERE
    sprintf(cmd, "%s/gcc", p->element);
    if (access(cmd, F_OK) == 0)
      printf("[%s]\n", cmd);
    p = p->next;
  }
  /* similarly loop through finding all locations of command */
} /* where() */

void list(char *dir)
{
  DIR *tmp;
  struct dirent	*dirp;

  if ((tmp = opendir(dir)) == NULL)
  {
		printf("can't open %s\n", dir);
    return;
  }
	while ((dirp = readdir(tmp)) != NULL)
  {
    if(!strcmp(dirp->d_name, ".") || !strcmp(dirp->d_name, ".."))
      continue;
      printf("%s\n", dirp->d_name);
  }

	closedir(tmp);
  /* see man page for opendir() and readdir() and print out filenames for
  the directory passed */
} /* list() */

