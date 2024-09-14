
//redirections
int get_commandpath(char **cmd_path, char *cmd, char **env);
int redirect_input(const char *filename);
int redirect_output(const char *filename);
int append_redirect_output(const char *filename);
void here_doc(const char *delimiter);
