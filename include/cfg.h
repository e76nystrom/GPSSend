#if !defined(CFG_H)
#define CFG_H

#if defined(RTK_SEND)
inline char CLIENT_NAME[] = "cli2";
#define HOST_NAME CLIENT_NAME
#endif	/* RTK_SEND */

inline char SERVER_NAME[] = "srv2";

#if defined(RTK_RECV)
#define HOST_NAME SERVER_NAME
#endif	/* RTK_RECV */

#endif
