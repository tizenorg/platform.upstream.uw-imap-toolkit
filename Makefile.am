AUTOMAKE_OPTIONS = subdir-objects

lib_LTLIBRARIES = libuw-imap-toolkit.la

libuw_imap_toolkit_la_SOURCES= 	imap-2007e/c-client/lnx_osdep.c \
			   imap-2007e/c-client/lnx_mail.c \
			   imap-2007e/c-client/dummy.c \
			   imap-2007e/c-client/fdstring.c \
			   imap-2007e/c-client/flstring.c \
			   imap-2007e/c-client/imap4r1.c \
			   imap-2007e/c-client/misc.c \
			   imap-2007e/c-client/mx.c \
			   imap-2007e/c-client/netmsg.c \
			   imap-2007e/c-client/phile.c \
			   imap-2007e/c-client/pop3.c \
			   imap-2007e/c-client/pseudo.c \
			   imap-2007e/c-client/rfc822.c \
			   imap-2007e/c-client/siglocal.c \
			   imap-2007e/c-client/smanager.c \
			   imap-2007e/c-client/smtp.c \
			   imap-2007e/c-client/unix.c \
			   imap-2007e/c-client/utf8.c \
			   imap-2007e/c-client/utf8aux.c 


libuw_imap_toolkit_la_CPPFLAGS= -I. \
                -I$(includedir)/openssl \
			    -I$(srcdir)/imap-2007e/c-client \
			    -I./common \
			    $(DLOG_CFLAGS) \
			    $(SSL_CFLAGS) \
			    -D_DEBUG_LOG \
			    -D__FEATURE_HEADER_OPTIMIZATION__ \
			    -D__FEATURE_SEND_OPTMIZATION__ \
			    -D__FEATURE_XLIST_SUPPORT__ \
			    -D__FEATURE_SUPPORT_IMAP_ID__ \
			    -DCREATEPROTO=unixproto -DEMPTYPROTO=unixproto \
			    -DMAILSPOOL=\"/var/spool/mail\" \
			    -DANONYMOUSHOME=\"/var/spool/mail/anonymous\" \
			    -DACTIVEFILE=\"/var/lib/news/active\" \
			    -DNEWSSPOOL=\"/var/spool/news\" \
			    -DRSHPATH=\"/usr/bin/rsh\" \
			    -DMD5ENABLE=\"/etc/cram-md5.pwd\" \
			    -DSSL_CERT_DIRECTORY=\"/opt/etc/ssl/certs\" \
			    -DSSL_KEY_DIRECTORY=\"/opt/etc/ssl/certs\" \
			    -DCHUNKSIZE=65536 \
			    -DLOCKPGM=\"\" \
			    -DLOCKPGM1=\"/usr/libexec/mlock\" \
			    -DLOCKPGM2=\"/usr/sbin/mlock\" \
			    -DLOCKPGM3=\"/usr/etc/mlock\" \
			    -DDATA_PATH=\"/opt/.email/res\" \
			    -DEXPORT_API="__attribute__((visibility(\"default\")))"
 
#-DFEATURE_CORE_DEBUG 
#-D__NON_BLOCKING_SSL_WRITE__ 
#-D__FEATURE_METADATA_SUPPORT__
			    
libuw_imap_toolkit_la_LIBADD = -L$(prefix)/lib \
			       $(SSL_LIBS) 

includelibuw_imap_toolkitdir = $(includedir)/uw-imap-toolkit

includelibuw_imap_toolkit_HEADERS = imap-2007e/c-client/*.h
			    

pcfiles = uw-imap-toolkit.pc

all: 
all-local: $(pcfiles)

.pc: .pc
	cp $< $@

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = $(pcfiles)

EXTRA_DIST = uw-imap-toolkit.pc.in

CLEANFILES = $(pcfiles)

