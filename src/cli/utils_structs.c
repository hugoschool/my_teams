#include "client/client.h"
#include <stdlib.h>

// offset is an arg offset, in case it's not starting at 0 but 1
team_content_t *team_parse_line(char *line, int offset)
{
    char *team_uuid = get_arg(line, offset + 0);
    char *team_name_len = get_arg(line, offset + 1);
    char *team_desc_len = get_arg(line, offset + 2);

    team_content_t *content = malloc(sizeof(team_content_t));
    strncpy(content->uuid, team_uuid, UUID_STR_LEN);
    content->name_len = atoi(team_name_len);
    content->description_len = atoi(team_desc_len);
    content->_initial_desc = read_bytes_starting_arg(line, offset + 3, content->name_len + 1 + content->description_len);
    content->name = read_bytes_starting_arg(line, offset + 3, content->name_len);
    content->description = content->_initial_desc + content->name_len + 1;

    free(team_uuid);
    free(team_name_len);
    free(team_desc_len);
    return content;
}

void team_content_free(team_content_t *content)
{
    if (content == NULL)
        return;
    free(content->_initial_desc);
    free(content->name);
    free(content);
}
