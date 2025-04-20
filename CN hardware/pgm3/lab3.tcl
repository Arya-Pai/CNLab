set ns [new Simulator]
set tf [open lab1.tr w]
$ns trace-all $tf
set nf [open lab1.nam w]
$ns namtrace-all $nf

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]

$n0 label "Ping0"
$n1 label "Ping1"
$n4 label "Ping4"
$n5 label "Ping5"

$ns duplex-link $n0 $n2 0.5Mb 10ms DropTail
$ns duplex-link $n1 $n2 0.5Mb 10ms DropTail
$ns duplex-link $n2 $n3 0.5Mb 10ms DropTail
$ns duplex-link $n3 $n4 0.5Mb 10ms DropTail
$ns duplex-link $n3 $n5 0.5Mb 10ms DropTail

set ping0 [new Agent/Ping]
$ns attach-agent $n0 $ping0
set ping1 [new Agent/Ping]
$ns attach-agent $n1 $ping1
set ping4 [new Agent/Ping]
$ns attach-agent $n4 $ping4
set ping5 [new Agent/Ping]
$ns attach-agent $n5 $ping5

$ping0 set packetSize_ 500
$ping0 set interval_ 0.001
$ping1 set packetSize_ 500
$ping1 set interval_ 0.001
$ping4 set packetSize_ 500
$ping4 set interval_ 0.001
$ping5 set packetSize_ 500
$ping5 set interval_ 0.001

$ns connect $ping0 $ping4
$ns connect $ping1 $ping5

set udp0 [new Agent/UDP]
$ns attach-agent $n0 $udp0
set cbr0 [new Application/Traffic/CBR]
$cbr0 attach-agent $udp0
set null4 [new Agent/Null]
$ns attach-agent $n4 $null4
$ns connect $udp0 $null4

$cbr0 set packetSize_ 512
$cbr0 set interval_ 0.001

Agent/Ping instproc recv {from rtt} {
    set node_id [$self set node_]
    puts "The node $node_id received reply from $from at time $rtt"
}


proc finish { } {
global ns nf tf
$ns flush-trace 
exec nam lab3.nam &
close $tf
close $nf
exit 0
}

$ns at 0.1 "$ping0 send"
$ns at 0.2 "$ping0 send"
$ns at 0.3 "$ping0 send"
$ns at 0.4 "$ping0 send"
$ns at 0.5 "$ping0 send"
$ns at 0.6 "$ping0 send"
$ns at 0.7 "$ping0 send"
$ns at 0.8 "$ping0 send"
$ns at 0.9 "$ping0 send"
$ns at 1.0 "$ping0 send"
$ns at 0.2 "$cbr0 start"
$ns at 4.0 "$cbr0 stop"
$ns at 0.1 "$ping1 send"
$ns at 0.2 "$ping1 send"
$ns at 0.3 "$ping1 send"
$ns at 0.4 "$ping1 send"
$ns at 0.5 "$ping1 send"
$ns at 0.6 "$ping1 send"
$ns at 0.7 "$ping1 send"
$ns at 0.8 "$ping1 send"
$ns at 0.9 "$ping1 send"
$ns at 1.0 "$ping1 send"
$ns run
