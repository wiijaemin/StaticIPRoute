// IPLayer.h: interface for the CEthernetLayer class.
//
//////////////////////////////////////////////////////////////////////

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseLayer.h"
#include <list>

#define FLAG_UP				(1 << 4)
#define FLAG_GATEWAY		(1 << 3)
#define FLAG_HOST_SPECIFIT	(1 << 2)
#define FLAG_D				(1 << 1)
#define FLAG_M				1
#define IS_FLAG_UP(X)		(((X) & (FLAG_UP)) >> 4)
#define IS_FLAG_GATEWAY(X)	(((X) & (FLAG_GATEWAY)) >> 3)
#define IS_FLAG_HOST(X)		(((X) & (FLAG_HOST_SPECIFIT)) >> 2)
#define IS_FLAG_D(X)		(((X) & (FLAG_D)) >> 1)
#define IS_FLAG_M(X)		(((X) & (FLAG_M)))

class CIPLayer 
: public CBaseLayer  
{
private:
	inline void		ResetHeader( );
	unsigned char srcip[4];
	unsigned char destip[4];

public:
	CIPLayer( char* pName );
	virtual ~CIPLayer();
	void SetSrcIPAddress(unsigned char* src_ip);
	void SetDstIPAddress(unsigned char* dst_ip);
	void SetFragOff(unsigned short fragoff);

	BOOL Send(unsigned char* ppayload, int nlength);
	BOOL Receive(unsigned char* ppayload);

	typedef struct _IPLayer_HEADER {
		unsigned char ip_verlen;	// ip version		(1byte)
		unsigned char ip_tos;		// type of service	(1byte)
		unsigned short ip_len;		// total packet length	(2byte)
		unsigned short ip_id;		// datagram id			(2byte)
		unsigned short ip_fragoff;	// fragment offset		(2byte)
		unsigned char ip_ttl;		// time to live in gateway hops (1byte)
		unsigned char ip_proto;		// IP protocol			(1byte)
		unsigned short ip_cksum;	// header checksum		(2byte)
		unsigned char ip_src[4];	// IP address of source	(4byte)
		unsigned char ip_dst[4];	// IP address of destination	(4byte)
		unsigned char ip_data[IP_DATA_SIZE]; // variable length data
		
	} IPLayer_HEADER, *PIPLayer_HEADER ;

	typedef struct _STATIC_IP_ROUTING_RECORD{
		unsigned char		destination_ip[4];
		unsigned char		own_ip[4];
		unsigned char		netmask_ip[4];
		unsigned char		gateway_ip[4];
		unsigned char		flag;
		unsigned char		netmask_length;
		CString				flag_string;
		CString				interface_info;
		CString				metric;

		virtual bool operator < (const _STATIC_IP_ROUTING_RECORD& rhs) const {
			return ( netmask_length > rhs.netmask_length );
		}
	}STATIC_IP_ROUTING_RECORD, *PSTATIC_IP_ROUTING_RECORD;

	list<STATIC_IP_ROUTING_RECORD>	routingTable;
	
protected:
	IPLayer_HEADER					m_sHeader ;
};




