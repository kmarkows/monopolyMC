

read -p "Enter the number of loops: " n

cd ./build
make

for ((i = 1; i <= n; i++))
do
    rm ../logs/monopolyGameLogs.txt
    touch ../logs/monopolyGameLogs.txt
    ./monopoly.exe
done