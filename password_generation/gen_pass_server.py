#!usr/bin/env python
import os

from random import *

# [START imports]

import cloudstorage 
from google.appengine.api import app_identity

import webapp2



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

  for s, line in enumerate(fp):
    if s == j:
      words = line.split()
      password = password + words[0] + str(num2)
      break 
  fp.seek(0)

  for s, line in enumerate(fp): 
    if s == k:
      words = line.split()
      password = password + words[0] + str(num3)
      break
  return password

#!/usr/bin/env python

"""A sample app that uses GCS client to operate on bucket and file."""


# [END imports]

# [START retries]
cloudstorage.set_default_retry_params(
    cloudstorage.RetryParams(
        initial_delay=0.2, max_delay=5.0, backoff_factor=2, max_retry_period=15
        ))


# [START read]
def read_file(self, filename, s):
  with cloudstorage.open(filename) as cloudstorage_file:
    self.response.write(genRand(cloudstorage_file, s))


class PassHandler(webapp2.RequestHandler):
  def get(self):
    hand = self.request.get('hand')
    self.response.headers['Content-Type'] = 'text/html'

    if hand == '':
      self.response.write('''<html>
<script
  src="https://code.jquery.com/jquery-3.3.1.min.js"
  integrity="sha256-FgpCb/KJQlLNfOu91ta32o/NMZxltwRo8QtmkMRdAu8="
  crossorigin="anonymous"></script>


  <div class="wrapper">
  <a href="http://directed-racer-218301.appspot.com/randompassword?hand=l" class="button">Left Hand</a>
  <a href="http://directed-racer-218301.appspot.com/randompassword?hand=r" class="button">Right Hand</a>
</div>

<style>

.wrapper {
    text-align: center;
}


.button {
  background-color: whitesmoke;
  border: none;
  color: black;
  padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
  margin: 4px 2px;
  cursor: pointer;
  align-self: center;
  position: relative;
}
.button:hover{
  background-color: #5F1414;
  color: white;

}
body {
  background-image: url("images/gradient_bg.png");
  background-repeat: repeat-x;
}
#central-test{  text-align: center;
  text-transform: uppercase;
  font-size: 18}
#passwould{font-weight: bold;
  text-align: center;
  font-size: 80}</style>
</html>''')
      return
    self.response.write('''<html>
<script
src="https://code.jquery.com/jquery-3.3.1.min.js"
integrity="sha256-FgpCb/KJQlLNfOu91ta32o/NMZxltwRo8QtmkMRdAu8="
crossorigin="anonymous"></script>
<h1 id='central-test'> YOUR PASSWORD IS: </h1>
<h1 id='passwould'>''')

    bucket_name = os.environ.get('BUCKET_NAME', app_identity.get_default_gcs_bucket_name())
    self.response.headers['Content-Type'] = 'text/html'
    # Create url for accessing the bucket
    bucket = '/' + bucket_name
    # Append filename to the bucket url
    file = 'blegh'
    leftorright = 1
    if hand == 'l':
      filename = bucket + '/' + 'lhand.txt'
      leftorright = 0
    elif hand == 'r':
      filename = bucket + '/' + 'rhand.txt'
      leftorright = 1
    read_file(self, filename,leftorright)

    self.response.write('''</h1>
<style>
body {
  background-image: url("www/images/gradient_bg.png");
  background-repeat: repeat-x;
}
#central-test{
  text-align: center;
  text-transform: uppercase;
  font-size: 18
}
#passwould{
  font-weight: bold;
  text-align: center;
  font-size: 80
}
</style>
</html>''')


app = webapp2.WSGIApplication([

    ('/randompassword', PassHandler),
    ('/', PassHandler)
    ], debug = True)