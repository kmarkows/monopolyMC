

read -p "Enter the number of loops: " n

cd ./build
make

rm ../logs/statistics/winningPlayers.txt
touch ../logs/statistics/winningPlayers.txt
rm ../logs/statistics/singleGameDuration.txt
touch ../logs/statistics/singleGameDuration.txt
rm ../logs/statistics/tilesVisitsCounter.txt
touch ../logs/statistics/tilesVisitsCounter.txt

for ((i = 1; i <= n; i++))
do
    rm ../logs/monopolyGameLogs.txt
    touch ../logs/monopolyGameLogs.txt
    ./monopoly.exe
done

rm ../logs/statistics/winningPlayersHistogram.png
python3 ../logs/statistics/winningPlayersHistogramGen.py

rm ../logs/statistics/singleGameDurationHistogram.png
python3 ../logs/statistics/singleGameDurationHistogramGen.py

rm ../logs/statistics/tilesVisitsCounterHistogram.png
python3 ../logs/statistics/tilesVisitsCounterHistogramGen.py