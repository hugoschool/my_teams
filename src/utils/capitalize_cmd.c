#include <ctype.h>

char *capitalize_cmd(char *cmd)
{
    cmd = &cmd[1];

    for (int i = 0; cmd[i] != '\0' && cmd[i] != ' '; i++)
        cmd[i] = toupper(cmd[i]);
    return cmd;
}
