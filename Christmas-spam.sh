
for i in {0..25..1}
do
    echo "Merry Christmas : $i" > Christmas-spam.txt
    git add .
    git commit -m "Merry Christmas : $i"
    git push

done
