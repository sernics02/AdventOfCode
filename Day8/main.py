from math import gcd

def run(steps, options):
  # Inicializa la posición actual en "AAA"
  current_position = "AAA"
  i = 0

  # Repite el bucle hasta que la posición actual sea "ZZZ"
  while current_position != "ZZZ":
    i += 1
    # Determina el siguiente paso según el primer carácter de la cadena 'steps'
    # Si el primer carácter es "R", el siguiente paso es 1, de lo contrario, es 0
    step = int(steps[0] == "R")

    # Actualiza la posición actual según las opciones y el paso determinado
    current_position = options[current_position][step]
    # Rotación circular de la cadena 'steps' para el próximo ciclo
    steps = steps[1:] + steps[0]
  print("Parte 1:", i)

def ghosts(steps, options):
  # Encuentra los puntos de inicio que terminan en "A"
  starts = [key for key in options if key[2] == "A"]
  cycles = []

  # Para cada punto de inicio
  for current in starts:
    cycle = []
    current_steps = steps
    step_count = 0
    first_z = None

    # Repetir hasta que se complete un ciclo
    while True:
      # Mientras no se haya dado ningún paso o no se haya llegado a "Z"
      while step_count == 0 or not current.endswith("Z"):
        # Realizar un paso
        step_count += 1
        step = 0 if current_steps[0] == "L" else 1
        current = options[current][step]
        current_steps = current_steps[1:] + current_steps[0]

      # Agregar la cantidad de pasos al ciclo
      cycle.append(step_count)

      # Si es el primer "Z" encontrado, guarda el estado actual
      if first_z is None:
        first_z = current
        step_count = 0
      # Si se ha vuelto al estado inicial, termina el ciclo
      elif current == first_z:
        break
    
    # Agregar el ciclo completo a la lista de ciclos
    cycles.append(cycle)

  # Calcular el mínimo común múltiplo (LCM) de las longitudes de los ciclos
  lcm = cycles[0][0]

  for cycle in cycles[1:]:
    lcm = lcm * cycle[0] // gcd(lcm, cycle[0])

  print("Parte 2:", lcm)
  
def main():
  steps, _, *data = open('Day8/input.txt').read().splitlines()

  options = {}

  for line in data:
    pos, targets = line.split(" = ")
    options[pos] = targets[1:-1].split(", ")
  run(steps, options)
  ghosts(steps, options)

if __name__ == "__main__":
  main()