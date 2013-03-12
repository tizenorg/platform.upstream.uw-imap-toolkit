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
 
#ifndef __LINUX_INC_H__
#define __LINUX_INC_H__

#include "c-client.h"

#ifndef WIN32
#include "tcp_unix.h"
#endif

/* Server protocol level and capabilities */

typedef struct imap_cap {
  unsigned int rfc1176 : 1;	/* server is RFC-1176 IMAP2 */
  unsigned int imap2bis : 1;	/* server is IMAP2bis */
  unsigned int imap4 : 1;	/* server is IMAP4 (RFC 1730) */
  unsigned int imap4rev1 : 1;	/* server is IMAP4rev1 */
  unsigned int acl : 1;		/* server has ACL (RFC 2086) */
  unsigned int quota : 1;	/* server has QUOTA (RFC 2087) */
  unsigned int litplus : 1;	/* server has LITERAL+ (RFC 2088) */
  unsigned int idle : 1;	/* server has IDLE (RFC 2177) */
  unsigned int mbx_ref : 1;	/* server has mailbox referrals (RFC 2193) */
  unsigned int log_ref : 1;	/* server has login referrals (RFC 2221) */
  unsigned int authanon : 1;	/* server has anonymous SASL (RFC 2245) */
  unsigned int namespace :1;	/* server has NAMESPACE (RFC 2342) */
  unsigned int uidplus : 1;	/* server has UIDPLUS (RFC 2359) */
  unsigned int starttls : 1;	/* server has STARTTLS (RFC 2595) */
				/* server disallows LOGIN command (RFC 2595) */
  unsigned int logindisabled : 1;
  unsigned int id : 1;		/* server has ID (RFC 2971) */
  unsigned int children : 1;	/* server has CHILDREN (RFC 3348) */
  unsigned int multiappend : 1;	/* server has multi-APPEND (RFC 3502) ;*/
  unsigned int binary : 1;	/* server has BINARY (RFC 3516) */
  unsigned int unselect : 1;	/* server has UNSELECT */
  unsigned int sasl_ir : 1;	/* server has SASL-IR initial response */
  unsigned int sort : 1;	/* server has SORT */
  unsigned int scan : 1;	/* server has SCAN */
  unsigned int extlevel;	/* extension data level supported by server */
				/* supported authenticators */
  unsigned int auth : MAXAUTHENTICATORS;
  THREADER *threader;		/* list of threaders */
} IMAPCAP;

typedef struct imap_argument {
  int type;			/* argument type */
  void *text;			/* argument text */
} IMAPARG;

typedef struct imap_parsed_reply {
  unsigned char *line;		/* original reply string pointer */
  unsigned char *tag;		/* command tag this reply is for */
  unsigned char *key;		/* reply keyword */
  unsigned char *text;		/* subsequent text */
} IMAPPARSEDREPLY;

#define IMAPTMPLEN 16*MAILTMPLEN

typedef struct imap_local {
  NETSTREAM *netstream;		/* TCP I/O stream */
  IMAPPARSEDREPLY reply;	/* last parsed reply */
  MAILSTATUS *stat;		/* status to fill in */
  IMAPCAP cap;			/* server capabilities */
  unsigned int uidsearch : 1;	/* UID searching */
  unsigned int byeseen : 1;	/* saw a BYE response */
				/* got implicit capabilities */
  unsigned int gotcapability : 1;
  unsigned int sensitive : 1;	/* sensitive data in progress */
  unsigned int tlsflag : 1;	/* TLS session */
  unsigned int notlsflag : 1;	/* TLS not used in session */
  unsigned int sslflag : 1;	/* SSL session */
  unsigned int novalidate : 1;	/* certificate not validated */
  unsigned int filter : 1;	/* filter SEARCH/SORT/THREAD results */
  unsigned int loser : 1;	/* server is a loser */
  unsigned int saslcancel : 1;	/* SASL cancelled by protocol */
  long authflags;		/* required flags for authenticators */
  unsigned long sortsize;	/* sort return data size */
  unsigned long *sortdata;	/* sort return data */
  struct {
    unsigned long uid;		/* last UID returned */
    unsigned long msgno;	/* last msgno returned */
  } lastuid;
  NAMESPACE **namespace;	/* namespace return data */
  THREADNODE *threaddata;	/* thread return data */
  char *referral;		/* last referral */
  char *prefix;			/* find prefix */
  char *user;			/* logged-in user */
  char *reform;			/* reformed sequence */
  char tmp[IMAPTMPLEN];		/* temporary buffer */
  SEARCHSET *lookahead;		/* fetch lookahead */
} IMAPLOCAL;

typedef struct pop3_local {
  NETSTREAM *netstream;		/* TCP I/O stream */
  char *response;		/* last server reply */
  char *reply;			/* text of last server reply */
  unsigned long cached;		/* current cached message uid */
  unsigned long hdrsize;	/* current cached header size */
  FILE *txt;			/* current cached file descriptor */
  struct {
    unsigned int capa : 1;	/* server has CAPA, definitely new */
    unsigned int expire : 1;	/* server has EXPIRE */
    unsigned int logindelay : 1;/* server has LOGIN-DELAY */
    unsigned int stls : 1;	/* server has STLS */
    unsigned int pipelining : 1;/* server has PIPELINING */
    unsigned int respcodes : 1;	/* server has RESP-CODES */
    unsigned int top : 1;	/* server has TOP */
    unsigned int uidl : 1;	/* server has UIDL */
    unsigned int user : 1;	/* server has USER */
    char *implementation;	/* server implementation string */
    long delaysecs;		/* minimum time between login (neg variable) */
    long expiredays;		/* server-guaranteed minimum retention days */
				/* supported authenticators */
    unsigned int sasl : MAXAUTHENTICATORS;
  } cap;
  unsigned int sensitive : 1;	/* sensitive data in progress */
  unsigned int loser : 1;	/* server is a loser */
  unsigned int saslcancel : 1;	/* SASL cancelled by protocol */
} POP3LOCAL;

long tcp_abort (TCPSTREAM *stream);

#endif
