BEGIN{
}
{
if($6=="cwnd_")
printf("%f\t\t%f\n",$1,$7);
}
END{
}
