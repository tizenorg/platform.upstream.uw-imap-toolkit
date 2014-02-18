/* ========================================================================
 * Copyright (c) 2012 Samsung Electronics Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * 
 * ========================================================================
 */

/*
 * Program:	XOAUTH2 authenticator
 *
 * Author:	Kyuho Jo (kyuho.jo@samsung.com)
 *
 * Date:	18 May 2013
 */

long auth_xoauth2_client (authchallenge_t challenger,authrespond_t responder,
			char *service,NETMBX *mb,void *stream,
			unsigned long *trial,char *user);
char *auth_xoauth2_server (authresponse_t responder,int argc,char *argv[]);

AUTHENTICATOR auth_xoauth2 = {
  AU_AUTHUSER | AU_HIDE,	/* allow authuser, hidden */
  "XOAUTH2",			/* authenticator name */
  NIL,				/* always valid */
  auth_xoauth2_client,		/* client method */
  auth_xoauth2_server,		/* server method */
  NIL				/* next authenticator */
};

/* Client authenticator
 * Accepts: challenger function
 *	    responder function
 *	    SASL service name
 *	    parsed network mailbox structure
 *	    stream argument for functions
 *	    pointer to current trial count
 *	    returned user name
 * Returns: T if success, NIL otherwise, number of trials incremented if retry
 */

#define MAX_RESPONSE_LENGTH 1024
#define CHAR_SOH            0x01

long auth_xoauth2_client (authchallenge_t challenger,authrespond_t responder,
			char *service,NETMBX *mb,void *stream,
			unsigned long *trial,char *user)
{
	char *u, token[MAILTMPLEN] = { 0, };
	void *challenge;
	unsigned long clen;
	long ret = NIL;

	if (challenge = (*challenger) (stream,&clen)) {
		fs_give ((void **) &challenge);
		if (clen) { /* abort if challenge non-empty */
			mm_log ("auth_xoauth2_client : non-empty initial XOAUTH2 challenge",WARN);
			(*responder) (stream,NIL,0);
			ret = LONGT; /* will get a BAD response back */
		}
		token[0] = NIL;		/* prompt user if empty challenge */
		mm_login (mb, user, token, *trial);

		if (!token[0]) {		/* empty challenge or user requested abort */
			(*responder) (stream, NIL, 0);
			*trial = 0;		/* cancel subsequent attempts */
			ret = LONGT;		/* will get a BAD response back */
		}
		else {
			unsigned long formed_response_length = 0;
			char formed_response[MAX_RESPONSE_LENGTH] = { 0, };

			snprintf(formed_response, MAX_RESPONSE_LENGTH, "user=%s%cauth=Bearer %s%c%c", user, CHAR_SOH, token, CHAR_SOH, CHAR_SOH);

			mm_log(formed_response, TCPDEBUG);

			if ((*responder) (stream,formed_response,strlen(formed_response))) {
				if (challenge = (*challenger) (stream,&clen)) {
					/* print challenge with error code */
					mm_log(challenge, ERROR);
					/* and send CR */
					(*responder) (stream, "", 0);
					fs_give ((void **) &challenge);
					ret = LONGT;
				}
				else {
					++*trial;
					ret = LONGT;
				}
			}
		}
		memset(token,0,MAILTMPLEN);
	}
	return ret;
}

/* Server authenticator
 * Accepts: responder function
 *	    argument count
 *	    argument vector
 * Returns: authenticated user name or NIL
 */
char *auth_xoauth2_server (authresponse_t responder,int argc,char *argv[])
{
	char *ret = NIL;
	return NIL;
}
