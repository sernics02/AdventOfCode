data = {"Time": [46, 85, 75, 82], 
        "Distance": [208, 1412, 1257, 1410]}

def calculate(ms: int, record: int):
  possibilities = 0
  is_wining = False
  i = 0
  # Optimizacion, solo hace falta encontrar un numero del rango
  # ya que es cuadrático
  while (not is_wining):
    i += 1
    if i * (ms - i) >= record:
      is_wining = True
  lowest = i
  return ms - lowest - lowest + 1

def race():
  time = data["Time"]
  distance = data["Distance"]
  result = 1
  for i, j in zip(time, distance):
    result *= calculate(i, j)
  return result

def main():
  print("Parte uno", race())
  print("Parte dos", calculate(46857582, 208141212571410))

if __name__ == "__main__":
  main()