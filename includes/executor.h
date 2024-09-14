
//redirections
int get_commandpath(char **cmd_path, char *cmd, char **env);
void redirect_input(const char *filename);
void redirect_output(const char *filename);
void append_redirect_output(const char *filename);
void here_doc(const char *delimiter);
