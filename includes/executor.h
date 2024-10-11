#define PARENT 0
#define CHILD 1
#define IGNORE 2
#define HDOC 3
#define SAVE 0
#define RECOVER 1

//redirections
void handle_signals(int mode);
int get_commandpath(char **cmd_path, char *cmd);
int redirect_input(char *filename);
int redirect_output(char *filename);
int append_redirect_output(char *filename);
int here_doc(char **delimiter, int flag, t_token **toklst);
int check_error_type(char *cmd_path);
int specify_error(int status, char *cmd_path);
int tiny_check();
int echo(char **args);
int pre_exec_errors(char *cmd, char *cmd_path);
int is_built_in(char *str);
int has_slash(char *str);
int is_dir0(char *pwd);
