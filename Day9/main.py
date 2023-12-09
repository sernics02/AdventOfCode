# Start by making a new sequence from the difference at each step of your history

# If that sequence is not all zeroes, repeat this process, using the sequence you
# just generated at the input sequence.

# Once all of the values in your latest sequence are zeroes, you can extrapolate 
# what the next value of the original history should be.

#  0  3  6  9 12 15
#  1  3  6 10 15 21
# 10 13 16 21 30 45

def extrapolate(array):
  if all(x == 0 for x in array):
    return 0

  deltas = [y - x for x, y in zip(array, array[1:])]
  return array[-1] + extrapolate(deltas)


def extrapolateBackwards(array):
  if all(x == 0 for x in array):
    return 0
  
  deltas = [y - x for x, y in zip(array, array[1:])]
  return array[0] - extrapolateBackwards(deltas)


def main():
  total = 0
  totalPart2 = 0
  for line in open("input.txt"):
    nums = list(map(int, line.split()))
    total += extrapolate(nums)
    totalPart2 += extrapolateBackwards(nums)
  print(total)
  print(totalPart2)

if __name__ == "__main__":
  main() 