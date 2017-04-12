#!/bin/sh
echo "Access-Control-Allow-Origin: *"
echo "Content-type: application/json"
echo ""

echo "{"
echo "\"timestamp\": $(date +%s),"
echo -n "\"data\": "
jys
echo "}"

