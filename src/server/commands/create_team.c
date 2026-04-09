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
        dprintf(*CLIENT_I(i)->fd, NEW_TEAM" %s %ld %ld %s %s"CRLF,
            team->uuid, strlen(team->name), strlen(team->description),
            team->name, team->description);
    }
}

void command_create_team(server_t *server)
{
    char *name_len_text = get_arg(server->buffer, 1);
    int name_len = 0;
    char *description_len_text = NULL;
    int description_len = 0;
    char *name = NULL;
    char *description = NULL;
    team_data_t *team = NULL;

    if (name_len_text == NULL) {
        WRITE_STATUS(*CLIENT->fd, 499);
        return;
    }
    name_len = atoi(name_len_text);
    free(name_len_text);

    description_len_text = get_arg(server->buffer, 2);
    if (description_len_text == NULL) {
        WRITE_STATUS(*CLIENT->fd, 499);
        return;
    }
    description_len = atoi(description_len_text);
    free(description_len_text);

    name = read_bytes_starting_arg(server->buffer, 3, name_len);
    description = read_bytes_starting_arg(server->buffer, 3, name_len + 1 + description_len);
    team = teams_get_from_name(server->teams, name);
    if (team != NULL) {
        free(name);
        WRITE_STATUS(*CLIENT->fd, 440);
        return;
    }
    team = teams_add(server->teams, name, description + name_len + 1);
    free(name);
    free(description);
    WRITE_STATUS(*CLIENT->fd, 200);
    server_event_team_created(team->uuid, team->name, CLIENT->user->uuid);
    send_event_all_clients(server, team);
    dprintf(*CLIENT->fd, "%s %ld %ld %s %s\n", team->uuid,
        strlen(team->name), strlen(team->description), team->name,
        team->description);
}
