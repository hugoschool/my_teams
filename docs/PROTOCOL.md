%%%
Title = "MAICHE Protocol"
area = "Internet"
workgroup = "Network Working Group"
date = 2026-03-30T00:00:00Z

[seriesInfo]
name = "Internet-Draft"
value = "draft-maiche-00"
stream = "IETF"
status = "informational"

[[author]]
initials="M."
surname="MAICHE"
fullname="MAICHE FAN CLUB"
%%%

.# Abstract

This document describes the protocol that will be in use for the `my_teams` project.

{mainmatter}

# Introduction

The goal of the `my_teams` project is to create our CLI (client) and a server.

For this, we must also create a protocol to handle the events between the client and the server.

# Context

According to the subject:

> A collaborative communication application is a service able to manage several communication teams, where discussion are organised like following:
>
> - threads (initial post and additional comments) in a specific channel
> - discussion (personal messages)
>
> Here are the features intended to be implemented:
>
> - Creating/Joining/Leaving a team
> - Creating a user
> - Creating a channel in a team
> - Creating a thread in a channel
> - Creating a comment in a thread
> - Saving & restoring users, teams, channels, threads & associated comments
> - Personal discussion (from a user to an other)
> - Saving & restoring personal discussion

# Ending sequence

All communications from the client and from the server must end with an ending sequence.

In our case, the chosen ending sequence is CRLF, Carriage Return Line Feed (`\r\n`).

# Client input

A client must send the message with a valid command and an ending sequence.

An input from the client must be formatted as such (without the brackets, of course):

> [Command] [Args...] [Ending sequence]

# Server response

The server should always respond to the client, whether the input is valid or not.

All responses from the server must be formatted as such (without the brackets, of course):

> [Status code] [Message] [Ending sequence]

## Status codes

All status codes, classed by category:

Success:

- 200 Success.
- 250 User logged in.
- 251 User logged out.

User failure:

- 430 User already logged in.
- 435 User isn't logged in.

Server failure:

- 500 Server failure.

# User-related events

## Connection of a user

On the client, connecting as a user is done via the `/login` command and does not require authentication using a password.

Citing the subject:

> There is no password authentication required for this subject but you should always develop with security in mind.

Connecting as a user should be done using the `LOGIN username` command.

A user can only be logged in once. You cannot login as the same user in another window.

If the username doesn't exist on the server, the server must add the user to its database and associate it with a newly created UUID.

Example:
> LOGIN username
>
> 250 User logged in.
>
> In case user is already logged in:
>
> LOGIN username
>
> 430 User already logged in.

Resume:
> LOGIN username ->
>
> <- 250
>
> <- 430

## Disconnection of a user

A user can disconnect from the server using the `/logout` command on the client.

On the server, disconnecting from the server is done using the `LOGOUT` command.

This command can error out in case the user isn't logged in.

Example:
> LOGOUT
>
> 251 User logged out.
>
> In case user isn't logged in:
>
> LOGOUT
>
> 435 User isn't logged in.

Resume:
> LOGOUT ->
>
> <- 251
>
> <- 435

## Retrieve a list of all users

A user can request a list of all the user with their usernames and matching UUIDs.

On the client, this is the `/users` command.

This is done using the `USERS` command.

What is returned is a list of all the users with their usernames, their UUIDs and their status.

Their status is 0 if logged out and 1 if logged in.

This command can error out in case the user isn't logged in.

Example:
> USERS
>
> 200 Success. [Ending sequence]
>
> USERNAME uuid 0 [newline]
>
> USERNAME uuid 1 [newline]
>
> USERNAME uuid 0 [newline]
>
> In case user isn't logged in:
>
> USERS
>
> 435 User isn't logged in.

## Retrieve information about a specific user

A user can request information about a specific user given its UUID.

On the client, this is the `/user [uuid]` command.

This is done using the `USER uuid` command.

What is returned is the users username, uuid and status.

Their status is 0 if logged out and 1 if logged in.

This command can error out in case the user isn't logged in.

Example:
> USER [uuid]
>
> 200 Success. [Ending sequence]
>
> USERNAME uuid 0 [newline]
>
> In case user isn't logged in:
>
> USER [UUID]
>
> 435 User isn't logged in.

<!-- TODO: rest of the docs -->
