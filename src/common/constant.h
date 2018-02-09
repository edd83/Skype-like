#pragma once

#define TCP_MAGIC_A				(1)
#define TCP_MAGIC_B				(1)
#define TCP_MAGIC_C				(7)

#define MIN_COMMAND_ID			(1)
#define MAX_COMMAND_ID			(19)

#define MIN_USERNAME_SIZE		(2)
#define MAX_USERNAME_SIZE		(20)

#define MIN_PASSWORD_SIZE		(2)
#define MAX_PASSWORD_SIZE		(30)

#define USERNAME_CHAR_SET		"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_"
#define PASSWORD_CHAR_SET		"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_ ,:;@"

#define BUFFER_SIZE				(4096)
#define MAX_FRIENDS				(20)
#define SEC_IN_USEC				(1000000)
#define AUTH_TIMEOUT			(10 * SEC_IN_USEC)

#define	TCP_HEADER_SIZE			(4 * sizeof(char) + sizeof(unsigned int))
#define	UDP_HEADER_SIZE			(4 * sizeof(char) + sizeof(unsigned int))

#define DEBUG_ENABLED			true

#define DEFAULT_PORT			"27015"

#define DEFAULT_SERVER_PORT		(4340)
#define DEFAULT_SERVER_BACKLOG	(10)
#define DEFAULT_SERVER_DB_FILE	"babel_users.db"

#define DEFAULT_CLIENT_UDP_PORT (5989)
#define UDP_MAGIC_A             (13)
#define UDP_MAGIC_B             (21)
#define UDP_MAGIC_C             (34)
