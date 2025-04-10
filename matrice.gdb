set $i = 0

printf "Matrice augmentée (format : matrice | résultat)\n\n"

while $i < 3
  set $j = 0
  while $j < 4
    if ($j < 3) 
      printf "%6.2f ", matrix[$i][$j]
    else 
      printf "| %6.2f\n", matrix[$i][$j]
    end
    set $j = $j + 1
  end
  set $i = $i + 1
end
