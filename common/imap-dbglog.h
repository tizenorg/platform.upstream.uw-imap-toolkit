/******************************************************************************
 * File: imap-dbglog.h
 * Desc:  Debug Header in IMAP toolkit for E-mail framework
 *
 * Auth:
 *
 * History:
 *    2009.12.16 : created
 *****************************************************************************/
#ifndef __IMAP_DEBUG_LOG_H__
#define __IMAP_DEBUG_LOG_H__

#ifdef  __cplusplus
extern "C"
{
#endif


#define true 1
#define false 0

#ifdef _DEBUG_LOG

#ifndef USE_LOG_FILE

#include <dlog.h>

#define LOG_TAG                              "UW_IMAP"

#define	IMAP_DEBUG_TRACE()                   SLOGV("[%s:%s():%d]\n", (rindex(__FILE__, '/')? rindex(__FILE__,'/')+1 : __FILE__ ), __FUNCTION__,  __LINE__)
#define	IMAP_DEBUG_LOG(format, arg...)       SLOGV("[%s:%s():%d] " format "\n", (rindex(__FILE__, '/')? rindex(__FILE__,'/')+1 : __FILE__ ), __FUNCTION__,  __LINE__, ##arg)
#define	IMAP_DEBUG_ASSERT(format, arg...)    SLOGE("[%s:%s():%d][EXCEPTION!!] " format "\n", (rindex(__FILE__, '/')? rindex(__FILE__,'/')+1 : __FILE__ ), __FUNCTION__,  __LINE__, ##arg)
#define	IMAP_DEBUG_EXCEPTION(format, arg...) SLOGE("[%s:%s():%d][EXCEPTION!!] " format "\n", (rindex(__FILE__, '/')? rindex(__FILE__,'/')+1 : __FILE__ ), __FUNCTION__,  __LINE__, ##arg)


#else	// USE_LOG_FILE

#include <strings.h>
#define strrchr rindex

EXPORT_API    void
    __log_func(const char* format, ...);
#define IMAP_DEBUG_LOG(fmt, args...)\
			do {\
				char* k = __FILE__;\
				char* x;\
				x = strrchr(k, '/');\
				__log_func("[%s:%d:%s]: " fmt, ++x, __LINE__, __func__, ##args);\
			} while(0)

#endif //USE_LOG_FILE
	
#else //_DEBUG_LOG
#ifdef FEATURE_NEW_DEBUG
#define IMAP_DEBUG_FUNC
#define IMAP_DEBUG_LINE
#define IMAP_DEBUG_LOG(format, arg...)	
#define IMAP_DEBUG_ASSERT(format, arg...)
#define IMAP_DEBUG_EXCEPTION(format, arg...)

#else //FEATURE_NEW_DEBUG
	
#define IMAP_DEBUG_LOG(format, arg...)	
#define	IMAP_DEBUG_LINE					
#define	IMAP_DEBUG_FUNC					
#define IMAP_DEBUG_RETURN_NULL			

#define IMAP_DEBUG_EXCEPTION		
#endif	
#define IMAP_DEBUG_RETURN_NULL	
#define IMAP_DEBUG_DB_EXEC(eval, expr, X)  if (eval) { IMAP_DEBUG_DB X; expr;} else {;}
#define	IMAP_DEBUG_DB						IMAP_DEBUG_LOG		
#define IMAP_PROFILE_BEGIN(pfid)
#define IMAP_PROFILE_END(pfid)
#endif //_DEBUG_LOG

#define	IMAP_DEBUG_FUNC_BEGIN(format, arg...) IMAP_DEBUG_LOG("BEGIN - "format, ##arg)
#define	IMAP_DEBUG_FUNC_END(format, arg...)   IMAP_DEBUG_LOG("END - "format, ##arg)
#define	IMAP_DEBUG_LINE                       IMAP_DEBUG_LOG("LINE[%s : %d]", __FUNCTION__, __LINE__)
#define	IMAP_DEBUG_DB                         IMAP_DEBUG_LOG	
#define IMAP_DEBUG_DB_EXEC(eval, expr, X)     if (eval) { IMAP_DEBUG_DB X; expr;} else {;}
#define	IMAP_DEBUG_DB                         IMAP_DEBUG_LOG	
#define IMAP_DEBUG_RETURN_NULL                IMAP_DEBUG_LOG("return NULL, Please check this point");
	
#define IMAP_PROFILE_BEGIN(pfid)\
	unsigned int __prf_l1_##pfid = __LINE__;\
	struct timeval __prf_1_##pfid;\
	struct timeval __prf_2_##pfid;\
	do {\
		gettimeofday(&__prf_1_##pfid, 0);\
	} while (0)


#define IMAP_PROFILE_END(pfid)\
	unsigned int __prf_l2_##pfid = __LINE__;\
	do {\
		gettimeofday(&__prf_2_##pfid, 0);\
		long __ds = __prf_2_##pfid.tv_sec - __prf_1_##pfid.tv_sec;\
		long __dm = __prf_2_##pfid.tv_usec - __prf_1_##pfid.tv_usec;\
		if ( __dm < 0 ) { __ds--; __dm = 1000000 + __dm; }\
		IMAP_DEBUG_LOG("**PROFILE BEGIN** [EMAILFW: %s: %s() %u ~ ] " #pfid\
		" -> Elapsed Time: %u.%06u seconds\n",\
		rindex(__FILE__, '/')+1,\
		__FUNCTION__,\
		__prf_l1_##pfid,\
		__prf_l2_##pfid,\
		(unsigned int)(__ds),\
		(unsigned int)(__dm));\
	} while (0)

#define EM_NULL_CHECK_FOR_VOID(expr)		{\
	if (!expr)\
	{\
		IMAP_DEBUG_LOG ("EM_NULL_CHECK_FOR_VOID: PARAM IS NULL\n");\
		return;\
	};				}

#define EM_IF_NULL_RETURN_VALUE(expr, val)		{\
	if (!expr )\
	{\
		IMAP_DEBUG_LOG ("EM_IF_NULL_RETURN_VALUE : PARAM IS NULL\n");\
		return val;\
	};				}


#define EM_SAFE_FREE(expr)		{\
	if (expr )\
	{\
		free(expr);\
		expr = NULL;\
	};			}
#define EM_SAFE_STRCPY(dest, src, ret)  {\
	if (!dest)\
	{\
		IMAP_DEBUG_EXCEPTION("Destinatin String NULL [%p]\n", dest);\
		ret = -1;\
	}\
	else if(!src)\
	{\
		IMAP_DEBUG_EXCEPTION("Source String NULL [%p]\n", src);\
		ret = -1;\
	}\
	else if(dest && src && strlen(src) > 0)\
	{\
		ret = strncpy(dest, src, strlen(src));\
	};		}


#define EM_SAFE_STRCMP(dest, src, ret)  {\
	if (!dest)\
	{\
		IMAP_DEBUG_EXCEPTION("Destinatin String NULL [%p]\n", dest);\
		ret = -1;\
	}\
	else if(!src)\
	{\
		IMAP_DEBUG_EXCEPTION("Source String NULL [%p]\n", src);\
		ret = -1;\
	}\
	else if(dest && src)\
	{\
		ret= strcmp(dest, src);\
	};		}

#define EM_SAFE_STRCAT(dest, src)  {\
	if (!dest)\
	{\
		IMAP_DEBUG_EXCEPTION("Destinatin String NULL [%p]\n", dest);\
	}\
	else if(!src)\
	{\
		IMAP_DEBUG_EXCEPTION("Source String NULL [%p]\n", src);\
	}\
	else if(dest && src)\
	{\
		strcat(dest, src);\
	};		}
#define EM_IF_ACCOUNT_ID_NULL(expr, ret) {\
	if (expr <= 0)\
	{\
		IMAP_DEBUG_LOG ("EM_IF_ACCOUNT_ID_NULL: Account ID [ %d ]\n", expr);\
		return ret;\
	};				}
	

#ifdef  __cplusplus
}
#endif	//__cplusplus

#endif	//__IMAP_DEBUG_LOG_H__