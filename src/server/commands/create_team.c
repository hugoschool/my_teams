/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** create_team.c
*/

#include "logging_server.h"
#include "server/events.h"
#include "server/server.h"
#include "server/status.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

static void send_event_all_clients(server_t *server, team_data_t *team)
{
    for (unsigned int i = INITIAL_AMOUNT; i < server->clients->amount; i++) {
        if (i == server->index || CLIENT_I(i)->login_step == LOGGED_OUT)
            continue;
        dprintf(*CLIENT_I(i)->fd, NEW_TEAM" %s %s %s"CRLF,
            team->uuid, team->name, team->description);
    }
}

// TODO: not respecting protocol here
// Same as LOGIN
void command_create_team(server_t *server)
{
    char *name = get_arg(server->buffer, 1);
    char *description = NULL;
    team_data_t *team = teams_get_from_name(server->teams, name);

    if (team != NULL) {
        free(name);
        WRITE_STATUS(*CLIENT->fd, 440);
        return;
    }
    description = get_arg(server->buffer, 2);
    team = teams_add(server->teams, name, description);
    free(name);
    free(description);
    WRITE_STATUS(*CLIENT->fd, 200);
    server_event_team_created(team->uuid, team->name, team->uuid);
    send_event_all_clients(server, team);
}
