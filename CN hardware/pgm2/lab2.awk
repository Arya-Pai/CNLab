BEGIN{
tcp=0
udp=0
}
{
if($1=="r"&&$3=="2"&&$4=="3"&&$5=="tcp")
tcp++;
if($1=="r"&&$3=="2"&&$4=="3"&&$5=="cbr")
udp++;
}
END{
printf("The total number of packets by tcp is %d\n",tcp);
printf("The total number of packets by udp is %d\n",udp);
}
