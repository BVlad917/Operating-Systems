BEGIN {
    sum = 0	
    cnt = 0
}

{
    sum += $2	
    cnt += 1
}

END {
    print sum / cnt	
}
