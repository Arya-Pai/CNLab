BEGIN{
count=0
}
{
if($1=="d")
count++;
}
END{
printf("\ntotal number of packet dropped is %d\n",count);
}
