def rhand(word):
  x = len(word)
  count = x
  for index in range(0,x):
    if word[index] == 'y' or 'u' or 'i' or 'o' or 'p' or 'l' or 'k' or 'j' or 'h' or 'b' or 'n' or 'm':
      count = count - 1
    continue

  print(count)
  if count == 0:
    Wmr.emit(word, 1)

def mapper(key, value):
  words = key.split()
  for word in words:
    rhand(word)