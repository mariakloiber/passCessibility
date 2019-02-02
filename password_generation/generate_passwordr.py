from random import *

def genRand(fp, t):
  num1 = 0
  num2 = 0
  num3 = 0

  max_num_words = 0
  if t ==1:
    max_num_words = 1200
    num1 = randint(6,9)
    num2 = randint(6,9)
    num3 = randint(6,9)
  if t == 0:
    max_num_words = 7000  
    num1 = randint(1,5)
    num2 = randint(1,5)
    num3 = randint(1,5)
  i = randint(1, max_num_words)
  j = randint(1,max_num_words)
  k = randint(1,max_num_words)




  password = ""

  for s, line in enumerate(fp):
    if s==i:
      words = line.split()
      password = password + words[0] + str(num1)
      break
  fp.seek(0)
  for w, line in enumerate(fp):
    if w == j:
      words = line.split()
      password = password + words[0] + str(num2)
      break 
  fp.seek(0)

  for r, line in enumerate(fp): 
    if r == k:
      words = line.split()
      password = password + words[0] + str(num3)
      break
  print(password)
  return password


file = open("rhand.txt")
genRand(file,0)
file.close()