The PassCessability project is an password generation service designed entirely
for use with a single hand. 

Words.txt source: https://github.com/dwyl/english-words

The word lists were generated using Hadoop to create files lhand.txt and rhand.txt

They contain words able to be typed entirely with a left or right hand respectively.

The project also contain a GUI that's capable of running OpenGL as well as on OpenGL supported machines.
The application GUI requires GLUT in order to operate.

The password_generation folder is a full application deployed to the Google Cloud Platform. 
If you have the gcloud sdk installed, it can be deployed ot your project using 
'gcloud app deploy password_generation/app.yaml' on Windows Powershell. Ensure to deploy a dispatch.yaml
with a routing rule

- url: randompassword.*
  service: randompassword

At the time of writing, a sample of this applcation is running At
http://directed-racer-218301.appspot.com/randompassword


