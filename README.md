# Dear Reader

https://dear-reader.herokuapp.com/

## How to Build

cd build
cmake ..
make

<!-- the next step may be necessary if the app is having trouble running correctly when running ./dear-reader -->

export PORT=8000

./dear-reader

Static files (js, css) need to be copied into the build directory after building.

# How to Push

NOTE: Build directory must be empty save for static files before doing this step.

heroku login
heroku container:push web -a dear-reader
heroku:container release web -a dear-reader
heroku open (to go straight to the web app from the terminal)
