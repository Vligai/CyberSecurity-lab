Vladislav Ligai

For this assignment We are going to use the following file: http://download.netresec.com/pcap/maccdc-2012/maccdc2012_00016.pcap.gz, from http://www.netresec.com/?page=MACCDC

building the system: make re

running the basesniffer.cpp: ./basesniffer [pcap_file]

running the searchmod.cpp: ./searchmod [pcap_file] [what_to_search]

running the flowmod.cpp: ./flowmod [pcap_file]

Concept in base sniffer:
Open and process a pcap file, printing packet statistics.

Concept in Context search module:
This module receives a third argument, which specifies a sequence of bytes that should be searched in the logged packets. E.g., sniffer data.pcap search “0A EB FF 00” When processing finishes, it prints out how many packets matched the given byte string, along with the connections they belong. For example:

[~](TCP|UDP) source_ip:source_tcp_port dest_ip:dest_tcp_port packets_number 
Example output:
TCP 192.168.24.152:69 192.168.24.152:10240 32067
TCP 192.168.24.152:69 192.168.24.152:10240 32323
TCP 192.168.24.152:69 192.168.24.152:35845 45379
TCP 192.168.24.152:69 192.168.24.152:35845 5444
or 
[~]IP source_ip dest_ip packets number for other protocols.

Concept in Encrypted flows module
This module locates all TCP connections/flows that are using SSL or TLS in the captured file. When processing finishes it prints out all the TCP flows that were found using the following format: [~]source_ip:source_tcp_port dest_ip:dest_tcp_port packets_number.

Sources:
http://stackoverflow.com/questions/5403103/hex-to-ascii-string-conversion
