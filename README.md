<div id="top"></div>

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

Project parses [NASA's logs](https://drive.google.com/file/d/1jjzMocc0Rn9TqkK_51Oo93Fy78KYnm2i/view). Every log is given in the format `$remote_addr - - [$local_time] “$request” $status $bytes_send` where
* $remote_addr - source of a request
* $local_time - time of the request
* $request - request
* $status - status
* $bytes_send - number of bytes in the answer to the request

Ex.: `198.112.92.15 - - [03/Jul/1995:10:50:02 -0400] "GET /shuttle/countdown/HTTP/1.0" 200 3985`

The program will
* output the number of logs with status 5xx and the list of such logs
* for the given time interval in seconds find maximum number of requests to the server



<!-- GETTING STARTED -->
## Getting Started

Clone the repo with `git clone https://github.com/MariaMozgunova/parse_server_logs.git`



<!-- USAGE EXAMPLES -->
## Usage

To run the program type `process_logs.exe <time_interval_in_seconds> <path_to_logs_file>` in the terminal



<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE.txt` for more information.



<!-- CONTACT -->
## Contact

Maria Mozgunova - [@mariamozgunova](https://t.me/mariamozgunova) - maria.mozgunova@inbox.ru

Project Link: [https://github.com/MariaMozgunova/parse_server_logs](https://github.com/MariaMozgunova/parse_server_logs)

<p align="right">(<a href="#top">back to top</a>)</p>
