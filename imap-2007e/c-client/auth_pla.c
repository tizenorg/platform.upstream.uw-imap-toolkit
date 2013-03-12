/* ========================================================================
 * Copyright 1988-2006 University of Washington
 * Copyright (c) 2000 - 2011 Samsung Electronics Co., Ltd.
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
 * Program:	Plain authenticator
 *
 * Author:	Mark Crispin
 *		Networks and Distributed Computing
 *		Computing & Communications
 *		University of Washington
 *		Administration Building, AG-44
 *		Seattle, WA  98195
 *		Internet: MRC@CAC.Washington.EDU
 *
 * Date:	22 September 1998
 * Last Edited:	30 August 2006
 */

long auth_plain_client (authchallenge_t challenger,authrespond_t responder,
			char *service,NETMBX *mb,void *stream,
			unsigned long *trial,char *user);
char *auth_plain_server (authresponse_t responder,int argc,char *argv[]);

AUTHENTICATOR auth_pla = {
  AU_AUTHUSER | AU_HIDE,	/* allow authuser, hidden */
  "PLAIN",			/* authenticator name */
  NIL,				/* always valid */
  auth_plain_client,		/* client method */
  auth_plain_server,		/* server method */
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

long auth_plain_client (authchallenge_t challenger,authrespond_t responder,
			char *service,NETMBX *mb,void *stream,
			unsigned long *trial,char *user)
{
  char *u,pwd[MAILTMPLEN];
  void *challenge;
  unsigned long clen;
  long ret = NIL;
				/* snarl if not SSL/TLS session */
  if (!mb->sslflag && !mb->tlsflag)
    mm_log ("SECURITY PROBLEM: insecure server advertised AUTH=PLAIN",WARN);
				/* get initial (empty) challenge */
  if (challenge = (*challenger) (stream,&clen)) {
    fs_give ((void **) &challenge);
    if (clen) {			/* abort if challenge non-empty */
      mm_log ("auth_plain_client : Server bug: non-empty initial PLAIN challenge 1",WARN);
      (*responder) (stream,NIL,0);
      ret = LONGT;		/* will get a BAD response back */
    }
    pwd[0] = NIL;		/* prompt user if empty challenge */
    mm_login (mb,user,pwd,*trial);

    if (!pwd[0]) {		/* empty challenge or user requested abort */
      (*responder) (stream,NIL,0);
      *trial = 0;		/* cancel subsequent attempts */
      ret = LONGT;		/* will get a BAD response back */
    }
    else {
      unsigned long rlen = 
	strlen (mb->authuser) + strlen (user) + strlen (pwd) + 2;
      char *response = (char *) fs_get (rlen);
      char *t = response;	/* copy authorization id */

	memset(response, 0x00, rlen);

      if (mb->authuser[0]) for (u = user; *u; *t++ = *u++);
      *t++ = '\0';		/* delimiting NUL */

				/* copy authentication id */
      for (u = mb->authuser[0] ? mb->authuser : user; *u; *t++ = *u++);
      *t++ = '\0';		/* delimiting NUL */

				/* copy password */
      for (u = pwd; *u; *t++ = *u++);
				/* send credentials */
	
      if ((*responder) (stream,response,rlen)) {
	if (challenge = (*challenger) (stream,&clen))
	{
	  fs_give ((void **) &challenge);
	}
	else {
	  ++*trial;		/* can try again if necessary */
	  ret = LONGT;		/* check the authentication */
	}
      }
      memset (response,0,rlen);	/* erase credentials */
      fs_give ((void **) &response);
    }
  }
  else // [ Written by Kyuho Jo for AOL 2010/02/16
  {
  	mm_log ("Enter section for handling emtpy challenge",WARN);
    if (clen) 
	{			/* abort if challenge non-empty */
      mm_log ("auth_plain_client : Server bug: non-empty initial PLAIN challenge 2",WARN);
      (*responder) (stream,NIL,0);
      ret = LONGT;		/* will get a BAD response back */
    }
    pwd[0] = NIL;		/* prompt user if empty challenge */

	mm_login (mb,user,pwd,*trial);

	if (pwd[0] == NULL) 
    { /* empty challenge or user requested abort */
      mm_log ("empty challenge or user requested abort",WARN);
      (*responder) (stream,NIL,0);
      *trial = 0;		/* cancel subsequent attempts */
      ret = LONGT;		/* will get a BAD response back */
    }
    else 
	{
      unsigned long rlen = strlen (mb->authuser) + strlen (user) + strlen (pwd) + 2;
      char *response = (char *) fs_get (rlen);
      char *t = response;	/* copy authorization id */

	  mm_log ("copy authorization id ",WARN);

	  if (mb->authuser[0]) 
	  	for (u = user; *u; *t++ = *u++);
	  *t++ = '\0';		/* delimiting NUL */
				        /* copy authentication id */
      for (u = mb->authuser[0] ? mb->authuser : user; *u; *t++ = *u++);
      *t++ = '\0';		/* delimiting NUL */
				        /* copy password */
      for (u = pwd; *u; *t++ = *u++); /* send credentials */

	  if ((*responder)(stream,response,rlen)) 
	  {
	    mm_log ("response ",WARN);
	    if (challenge = (*challenger) (stream,&clen))
	      fs_give ((void **) &challenge);
	    else 
	    {
	      mm_log ("Second emtpy challege  ",WARN);
	      ++*trial;		/* can try again if necessary */
	      ret = LONGT;		/* check the authentication */
	    }
      }
      memset (response,0,rlen);	/* erase credentials */
      fs_give ((void **) &response);
    }
	
  }    // ] Written by Kyuho Jo for AOL 2010/02/16

  memset (pwd,0,MAILTMPLEN);	/* erase password */
  if (!ret) *trial = 65535;	/* don't retry if bad protocol */
  return ret;
}

/* Server authenticator
 * Accepts: responder function
 *	    argument count
 *	    argument vector
 * Returns: authenticated user name or NIL
 */

char *auth_plain_server (authresponse_t responder,int argc,char *argv[])
{
  char *ret = NIL;
  char *user,*aid,*pass;
  unsigned long len;
				/* get user name */
  if (aid = (*responder) ("",0,&len)) {
				/* note: responders null-terminate */
    if ((((unsigned long) ((user = aid + strlen (aid) + 1) - aid)) < len) &&
	(((unsigned long) ((pass = user + strlen (user) + 1) - aid)) < len) &&
	(((unsigned long) ((pass + strlen (pass)) - aid)) == len) &&
	(*aid ? server_login (aid,pass,user,argc,argv) :
	 server_login (user,pass,NIL,argc,argv))) ret = myusername ();
    fs_give ((void **) &aid);
  }
  return ret;
}
