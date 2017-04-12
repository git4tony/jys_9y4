#!/bin/sh

putnum() {
        echo "\"$1\": $(eval echo \${$1})$2"
}

REG=jys

reg32() {
        echo $(expr $(($($REG $1) << 16)) + $($REG $(expr $1 + 1)))
}

calc() {
        awk "BEGIN{print $*}";
}

id=1
timestamp=$(date +%s)
Ua=$(calc $($REG 128)/100)
Ub=$(calc $($REG 129)/100)
Uc=$(calc $($REG 130)/100)
Ia=$(calc $($REG 134)/100)
Ib=$(calc $($REG 135)/100)
Ic=$(calc $($REG 136)/100)
Pa=$($REG 137)
Pb=$($REG 138)
Pc=$($REG 139)
PFa=$(calc $($REG 149)/1000)
PFb=$(calc $($REG 150)/1000)
PFc=$(calc $($REG 151)/1000)
PFS=$(calc $($REG 152)/1000)
HZ=$(calc $($REG 153)/100)
SIGN1=$($REG 154)
SIGN2=$($REG 155)
SIGN3=$($REG 156)
WPP=$(calc $(reg32 160)/1000)
WPN=$(calc $(reg32 162)/1000)
WQP=$(calc $(reg32 164)/1000)
WQN=$(calc $(reg32 166)/1000)

echo "Access-Control-Allow-Origin: *"
echo "Content-type: application/json"
echo ""
echo "{"
putnum id ,
putnum timestamp ,
putnum Ua ,
putnum Ub ,
putnum Uc ,
putnum Ia ,
putnum Ib ,
putnum Ic ,
putnum Pa ,
putnum Pb ,
putnum Pc ,
putnum PFa ,
putnum PFb ,
putnum PFc ,
putnum PFS ,
putnum SIGN1 ,
putnum SIGN2 ,
putnum SIGN3 ,
putnum HZ ,
putnum WPP ,
putnum WPN ,
putnum WQP ,
putnum WQN
echo "}"
