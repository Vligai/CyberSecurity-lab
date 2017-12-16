#include <stdio.h>
#include <pcap.h>
#include <stdlib.h>
#include <iostream>
#include <netinet/ip.h>
#include <arpa/inet.h>

#define ETHER_TYPE_IP (0x0800)
#define ETHER_TYPE_8021Q (0x8100)

int main(int argc, char **argv) 
{ 
  unsigned int pkt_counter=0;   
  unsigned long byte_counter=0; 
  unsigned long cur_counter=0; 
  unsigned long max_volume = 0; 
  unsigned long current_ts=0; 
  unsigned int udp_counter =0;
  unsigned int ip_counter =0;
  unsigned int tcp_counter =0; 

  struct pcap_pkthdr header;  
  const u_char *packet;
  
  if (argc < 2) { 
    fprintf(stderr, "Usage: %s [input pcaps]\n", argv[0]); 
    exit(1); 
  } 
  
  std::cout << "Counting UDP, TCP, IP packets..." << std::endl;
  for (int fnum=1; fnum < argc; fnum++) {  
 
    
    pcap_t *handle; 
    char errbuf[PCAP_ERRBUF_SIZE]; 
    handle = pcap_open_offline(argv[fnum], errbuf);   
 
    if (handle == NULL) { 
      fprintf(stderr,"Couldn't open pcap file %s: %s\n", argv[fnum], errbuf); 
      return(2); 
    } 
 
   
    while (packet = pcap_next(handle,&header)) { 
      
      u_char *pkt_ptr = (u_char *)packet; 
       
      int ether_type = ((int)(pkt_ptr[12]) << 8) | (int)pkt_ptr[13]; 
      int ether_offset = 0; 
 
      if (ether_type == ETHER_TYPE_IP)  
        ether_offset = 14; 
      else if (ether_type == ETHER_TYPE_8021Q) 
         ether_offset = 18; 
/*
      else 
         fprintf(stderr, "Unknown ethernet type, %04X, skipping...\n", ether_type); 
 */
      pkt_ptr += ether_offset;  
      struct iphdr *ip_hdr = (struct iphdr *)pkt_ptr; 
 
      if(ip_hdr->protocol == IPPROTO_IP)
	ip_counter++;
      if(ip_hdr->protocol == IPPROTO_UDP)
	udp_counter++;
      if(ip_hdr->protocol == IPPROTO_TCP)
	tcp_counter++;
      else
	pkt_counter++;
    }

      std::cout << "Number of IP packets: "<< ip_counter << std::endl;
      std::cout << "Number of UDP packets: "<< udp_counter << std::endl;
      std::cout << "Number of TCP packets: "<<tcp_counter << std::endl;
      std::cout << "Number of total packets: "<<pkt_counter << std::endl;
 
    pcap_close(handle); 
 
  } 
  
  return 0; 
} 