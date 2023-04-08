START=$(date +%s.%N)
./bin/read /dev/ttyS2 115200 5
END=$(date +%s.%N)
DIFF=$(echo "$END - $START" | bc)
echo "Used "$DIFF"s for reading meter"
