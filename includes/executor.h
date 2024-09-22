#define PARENT 0
#define CHILD 1
#define IGNORE 2

//redirections
void handle_signals(int mode);
int get_commandpath(char **cmd_path, char *cmd, char **env);
int redirect_input(const char *filename);
int redirect_output(const char *filename);
int append_redirect_output(const char *filename);
void here_doc(char **delimiter);
int check_error_type(char *cmd_path);
int specify_error(int status, char *cmd_path);
int tiny_check();
