# Webserv

- 42 Project with C++(98). This project implements a simple web server based on HTTP/1.1 protocol. We tried to implement a web server similar to nginx as much as possible. You can test GET, POST, and DELETE methods. The server provoides static web page and dynamic pages with CGI(PHP). The Configuration file is inspired by Nginx format and the server contorls event management with Epoll Socket I/O.
 
### 📝 PDF
[Webserv 42 Project PDF (2022, EN)](https://github.com/keulee/Webserv/en.subject.pdf)

### ⚙️ How to build

You can run on Linux OS (used Epoll)
```
$> cd Webserv && make
$> ./webserv [configuration file]

ex) ./webserv config/conf/sample.conf
```

* You have the option to run without a configuration file, which will automatically set the default configuration file.

After building, you can check a local demo page on **http://localhost:8080**

### 🚩Team

Server Config : cjung-mo, hyungyoo.   
SocketI/O : seyun.  
Request Parsing: keulee.   
Resoponse Parsing: eyoo.   
