#include <stdio.h>
#include <pcap.h>
#include <stdlib.h>
#include <iostream>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <string.h>

#define ETHER_TYPE_IP (0x0800)
#define ETHER_TYPE_8021Q (0x8100)

int hex_to_int(char c){
        int first = c / 16 - 3;
        int second = c % 16;
        int result = first*10 + second;
        if(result > 9) result--;
        return result;
}

int hex_to_ascii(char c, char d){
        int high = hex_to_int(c) * 16;
        int low = hex_to_int(d);
        return high+low;
}

int main(int argc, char **argv) 
{ 
  char* argg = "1603001603"
	       "011603021"
 		"603031403"
		"00140301"
		"1403021403"
		"03170300"
		"170301170"
   		"302170303";

  unsigned int pkt_counter=0;
  unsigned int id_counter =0;
  unsigned int pack_counter = 0;
  unsigned long byte_counter=0; 
  unsigned long cur_counter=0; 
  unsigned long max_volume = 0; 
  unsigned long current_ts=0; 
  unsigned int udp_counter =0;
  unsigned int ip_counter =0;
  unsigned int tcp_counter =0; 
  unsigned int hex_len = 0;
  std::string hexstr;
  char **newString;
  struct pcap_pkthdr header;  
  const u_char *packet;
  
  if (argc < 2) { 
    std::cerr << "Usage: ./searchmod .pcap_file string_to_search [hex-optional]" << std::endl; 
    exit(1); 
  } 
  
   
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
      /*else 
         fprintf(stderr, "Unknown ethernet type, %04X, skipping...\n", ether_type); 
 	*/

      pkt_ptr += ether_offset;
   struct iphdr *ip_hdr = (struct iphdr *)(pkt_ptr);
    size_t needle_len;

    
  //size_t needle_len2;
  void *c;

    //size_t needle_len2 = strlen(argv[3]);
    //void *needle = argv[2];
    //void *hstack = packet;
    
    size_t count = 0;
    
    char *pos = argv[3];
    size_t hstack_len = ip_hdr->tot_len;

    char *newstr;
    //newstr = tobytes(argv[2]);

  //  std::cout << newstr << std::endl;

    

    //std::cout << "HI" << std::endl;
	const char* st = argg;
	char str[50];
        int length = strlen(st);
        int i;
	int n;
	int j = 0;
        char buf = 0;

        for(i = 0; i < length; i++){
                if(i % 2 != 0){
                        sprintf(&str[j], "%c", hex_to_ascii(buf, st[i]));
			//str2[j] += str[0];
			j++;
                }else{
                        buf = st[i];
                }
        }

	//fflush(stdout);
 	str[j] = '\0';
	//printf("%s", str);
	needle_len = strlen(str);
	
    c = memmem(packet, hstack_len, str, needle_len);

   if (c!=NULL){
	
      struct iphdr *ip_hdr = (struct iphdr *)pkt_ptr; 
      pack_counter++;
      if(ip_hdr->protocol == IPPROTO_IP)
	{
           std::cout << "IP "<< inet_ntoa(*(struct in_addr *) &ip_hdr->saddr) << " "<< inet_ntoa(*(struct in_addr *) &ip_hdr->daddr) << " "<< ip_hdr->id << std::endl;
           ip_counter++;
	}	
      if(ip_hdr->protocol == IPPROTO_UDP)
	{
	   struct udphdr *udph = (struct udphdr *)(ip_hdr);
	   std::cout << "UDP "<< inet_ntoa(*(struct in_addr *) &ip_hdr->saddr) << ":" << udph->source <<" "<< inet_ntoa(*(struct in_addr *) &ip_hdr->daddr) << ":" << udph->dest <<" "<< ip_hdr->id << std::endl;
	   udp_counter++;
	}      
      if(ip_hdr->protocol == IPPROTO_TCP)
	{
	   struct tcphdr *tcp_hdr = (struct tcphdr *)(ip_hdr);
	   std::cout << "TCP "<< inet_ntoa(*(struct in_addr *) &ip_hdr->saddr) << ":" << tcp_hdr->source << " "<< inet_ntoa(*(struct in_addr *) &ip_hdr->daddr) << ":" << tcp_hdr->dest<< " " << ip_hdr->id << std::endl;
	   tcp_counter++;
	}
      else
	pkt_counter++;
    }


}	
      std::cout << "Number of IP packets: "<< ip_counter << std::endl;
      std::cout << "Number of UDP packets: "<< udp_counter << std::endl;
      std::cout << "Number of TCP packets: "<<tcp_counter << std::endl;
      std::cout << "Number of total packets: "<<pkt_counter << std::endl;
      std::cout << "Number of packets with "<< argv[2] << ": "<< pack_counter<< std::endl;
 
    pcap_close(handle); 
 
  } 
  
  return 0; 
} 
