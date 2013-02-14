/* ========================================================================
 * Copyright 1988-2006 University of Washington
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * 
 * ========================================================================
 */

#ifndef WIN32
#define tcp_getline   tcp_getline_lnx
#define tcp_getbuffer tcp_getbuffer_lnx
#define tcp_soutr     tcp_soutr_lnx
#define tcp_sout      tcp_sout_lnx
#endif

#define mail_lookup_auth_name      mail_lookup_auth_name_unused


#include "mail.c"
//#include "em-core-utils.h"
#include <errno.h>
#include <sys/time.h>
#include <unistd.h>

#include "imap-dbglog.h"

#ifndef WIN32
#undef tcp_getline
#undef tcp_getbuffer
#undef tcp_soutr
#undef tcp_sout
#endif

#undef mail_lookup_auth_name


#ifndef WIN32

#include "tcp_unix.h"


long 
tcp_getdata_lnx(TCPSTREAM* stream)
{
	struct timeval tmout;
	fd_set readfds;
	int nread, sret, sockid, maxfd;
	int max_timeout = 0;
	
	sockid = stream->tcpsi;
	maxfd = sockid + 1;
	
	if (sockid < 0) return false;
	
	while (stream->ictr < 1) 
	{
		tmout.tv_usec = 0;//1000*10;
		tmout.tv_sec = 1;
		
		FD_ZERO(&readfds);
		FD_SET(sockid, &readfds);
		
		sret = select(maxfd, &readfds, NULL, NULL, &tmout);
		
		if (sret < 0) {
			tcp_abort(stream);
			return false;
		}
		else if (!sret) {
			if (max_timeout >= 50) {
				IMAP_DEBUG_EXCEPTION("max select timeout %d", max_timeout);
				
				//em_core_set_network_error(EMF_ERROR_NO_RESPONSE);
				return false;
			}
			
			IMAP_DEBUG_EXCEPTION("%d select timeout", max_timeout);
			
			++max_timeout;
			continue;
		}
		
		if ((nread = read(sockid, stream->ibuf, BUFLEN)) < 0) {
			IMAP_DEBUG_EXCEPTION("\t socket read failed...\n");
			tcp_abort(stream);
			return false;
		}
		
		if (!nread) {
			IMAP_DEBUG_EXCEPTION("\t socket read no data...\n");
			tcp_abort(stream);
			return false;
		}
		
		stream->ictr = nread;
		stream->iptr = stream->ibuf;
	}

	return true;
}

/* TCP/IP receive line
 * Accepts: TCP/IP stream
 * Returns: text line string or NIL if failure
 */

char *tcp_getline_lnx (void *vstream)
{
	TCPSTREAM *stream = (TCPSTREAM*)vstream;
	int n,m;
	char *st,*ret,*stp;
	char c = '\0';
	char d;
	/* make sure have data */
	if (!tcp_getdata_lnx (stream)) return NIL;
	st = stream->iptr;		/* save start of string */
	n = 0;			/* init string count */
	while (stream->ictr--) {	/* look for end of line */
		d = *stream->iptr++;	/* slurp another character */
		if ((c == '\015') && (d == '\012')) {
			ret = (char *) fs_get (n--);
			memcpy (ret,st,n);	/* copy into a free storage string */
			ret[n] = '\0';		/* tie off string with null */
			return ret;
		}
		n++;			/* count another character searched */
		c = d;			/* remember previous character */
	}
	/* copy partial string from buffer */
	memcpy ((ret = stp = (char *) fs_get (n)),st,n);
	/* get more data from the net */
	if (!tcp_getdata_lnx (stream)) fs_give ((void **) &ret);
	/* special case of newline broken by buffer */
	else if ((c == '\015') && (*stream->iptr == '\012')) {
		stream->iptr++;		/* eat the line feed */
		stream->ictr--;
		ret[n - 1] = '\0';		/* tie off string with null */
	}
	/* else recurse to get remainder */
	else if (st = tcp_getline_lnx (stream)) {
		ret = (char *) fs_get (n + 1 + (m = strlen (st)));
		memcpy (ret,stp,n);		/* copy first part */
		memcpy (ret + n,st,m);	/* and second part */
		fs_give ((void **) &stp);	/* flush first part */
		fs_give ((void **) &st);	/* flush second part */
		ret[n + m] = '\0';		/* tie off string with null */
	}
	return ret;
}
#endif


int try_auth = 0;
unsigned int mail_lookup_auth_name (char *mechanism,long flags)
{
  int i;
  AUTHENTICATOR *auth;

  if(!try_auth) return 0;

  for (i = 1, auth = mailauthenticators; auth; i++, auth = auth->next)
    if (auth->client && !(flags & ~auth->flags) &&
	!compare_cstring (auth->name,mechanism))
      return i;
  return 0;
}

// 22-Mar-2010 added
int try_auth_smtp = 0;
unsigned int mail_lookup_auth_name_smtp (char *mechanism,long flags)
{
  int i;
  AUTHENTICATOR *auth;

  if(!try_auth_smtp) return 0;

  for (i = 1, auth = mailauthenticators; auth; i++, auth = auth->next)
    if (auth->client && !(flags & ~auth->flags) &&
	!compare_cstring (auth->name,mechanism))
      return i;
  return 0;
}

