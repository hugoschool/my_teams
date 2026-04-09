/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** team.c
*/

#include "server/commands.h"
#include "server/server.h"
#include "server/status.h"
#include "utils.h"
#include <stdlib.h>

void command_team(server_t *server)
{
    char *uuid = NULL;
    team_data_t *team = NULL;

    uuid = get_arg(server->buffer, 1);
    if (uuid == NULL)
        return;
    team = teams_get_from_uuid(server->teams, uuid);
    free(uuid);
    if (team == NULL) {
        WRITE_STATUS(*CLIENT->fd, 460);
        return;
    }
    WRITE_STATUS(*CLIENT->fd, 200);
    team_print(*CLIENT->fd, team);
}
