#include <ctype.h>
#include <stdlib.h>
#include <string.h>

char *capitalize_cmd(char *cmd)
{
    char temp[strlen(cmd)];

    memset(temp, '\0', strlen(cmd));
    strncpy(temp, &cmd[1], strlen(cmd));
    for (int i = 0; temp[i] != '\0' && temp[i] != ' '; i++)
        temp[i] = toupper(temp[i]);
    free(cmd);
    cmd = strdup(temp);
    return cmd;
}
