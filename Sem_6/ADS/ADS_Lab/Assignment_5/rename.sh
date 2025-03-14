files=($(ls 20*))

num=1
for ((i = 0; i < ${#files[@]}; i++)); do
  # echo "${files[i]}"
  mv ${files[i]} sc${num}.png
  ((num++))
  # echo ${num}
done
