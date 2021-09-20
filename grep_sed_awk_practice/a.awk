BEGIN {
    a=10	
    b=0
}

$0 ~ /ana/ {
    a++	
}

NF == 3 {
    b++	
}

END {
    print a, b
}
