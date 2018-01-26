
# network-dropbox

A small HTTP web server in C that offers a web interface for uploading & managing files on a network location.

![Demo](https://media.giphy.com/media/xThta5C2cb4y2dMdOw/giphy.gif)

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. This project is not ready for live deployment yet for security reasons.

### Prerequisites

You will need:

 - C compiler
 - pthreads
 - standard library

### Building

Building is usually hassle free.

```
git clone 
cd network-dropbox
make
```

And to run

```
make run
```

Then visit ```localhost:8888```

## Built With

* [Bootstrap](https://github.com/twbs/bootstrap) - The web framework used
* [Dropzone.js](http://www.dropzonejs.com/) - Drag'n'drop file uploads
* [jQuery](https://jquery.com//) - Used to generate RSS Feeds

## Authors

* **Claudio Spiess** - *Server, front-end, misc.*
* **Chris Stolarski** - *HTTP entity parser*

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Mark Bayazit for readable file sizes
* Dr. Brent Munsell for the base of the project