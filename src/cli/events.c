#include "client/client.h"
#include "client/args.h"
#include "common.h"
#include "logging_client.h"
#include "server/events.h"
#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void event_team_created(client_t *client)
{
    team_content_t *team = team_parse_line(client->buffer, 1);
    client_event_team_created(team->uuid, team->name, team->description);
    team_content_free(team);
}

static void event_channel_created(client_t *client)
{
    channel_content_t *channel = channel_parse_line(client->buffer, 1);
    client_event_channel_created(channel->uuid, channel->name, channel->description);
    channel_content_free(channel);
}

static void event_thread_created(client_t *client)
{
    char *thread_uuid = get_arg(client->buffer, 1);
    char *user_uuid = get_arg(client->buffer, 2);
    char *timestamp = get_arg(client->buffer, 3);
    char *thread_title_len = get_arg(client->buffer, 4);
    char *thread_desc_len = get_arg(client->buffer, 5);
    char *thread_title = read_bytes_starting_arg(client->buffer, 6, atoi(thread_title_len));
    char *thread_desc = read_bytes_starting_arg(client->buffer, 6, atoi(thread_title_len) + 1 + atoi(thread_desc_len));
    client_event_thread_created(thread_uuid, user_uuid, atoi(timestamp), thread_title, thread_desc + 1 + atoi(thread_title_len));
    super_free(7, thread_uuid, user_uuid, timestamp, thread_title_len, thread_desc_len, thread_desc, thread_title);
}

static void event_reply_created(client_t *client)
{
    char *team_uuid = get_arg(client->buffer, 2);
    char *thread_uuid = get_arg(client->buffer, 3);
    char *user_uuid = get_arg(client->buffer, 4);
    char *reply_len = get_arg(client->buffer, 5);
    char *reply = read_bytes_starting_arg(client->buffer, 6, atoi(reply_len));
    client_event_thread_reply_received(team_uuid, thread_uuid, user_uuid, reply);
    super_free(5, team_uuid, thread_uuid, user_uuid, reply, reply_len);
}


void handle_server_events(client_t *client)
{
    if (strncmp(client->buffer, NEW_MESSAGE, strlen(NEW_MESSAGE)) == 0) {
        client_event_private_message_received(get_arg(client->buffer, 1), read_bytes_starting_arg(client->buffer, 3, atoi(get_arg(client->buffer, 2))));
    }
    if (strncmp(client->buffer, CLIENT_JOINED, strlen(CLIENT_JOINED)) == 0) {
        client_event_logged_in(get_arg(client->buffer, 1), get_arg(client->buffer, 2));
    }
    if (strncmp(client->buffer, CLIENT_LEFT, strlen(CLIENT_LEFT)) == 0) {
        client_event_logged_out(get_arg(client->buffer, 1), get_arg(client->buffer, 2));
    }
    if (strncmp(client->buffer, NEW_TEAM, strlen(NEW_TEAM)) == 0)
        event_team_created(client);
    if (strncmp(client->buffer, NEW_CHANNEL, strlen(NEW_CHANNEL)) == 0)
        event_channel_created(client);
    if (strncmp(client->buffer, NEW_THREAD, strlen(NEW_THREAD)) == 0)
        event_thread_created(client);
    if (strncmp(client->buffer, NEW_COMMENT, strlen(NEW_COMMENT)) == 0)
        event_reply_created(client);
}
