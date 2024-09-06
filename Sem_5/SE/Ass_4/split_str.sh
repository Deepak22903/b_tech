string="apple,banana,cherry"
IFS=',' read -r -a array <<< "$string"
for element in "${array[@]}"; do
  echo "$element"
done
