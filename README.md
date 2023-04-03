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

<p>
   <img src="https://emoji.slack-edge.com/T039P7U66/the-federation/cf19b04ff8baa385.png" width="25px"/><img src="https://img.shields.io/badge/cjung--mo(Jungmoo Cheon) : Server Config -000000?style=for-the-badge&logoColor=white"/> <a href="https://profile.intra.42.fr/users/cjung-mo"><img src="https://img.shields.io/badge/Intra-000000?style=for-the-badge&logo=42&logoColor=white"/></a> <a href="https://github.com/jmcheon"><img src="https://img.shields.io/badge/Github-181717?style=for-the-badge&logo=Github&logoColor=white"/></a>
  <br>
   <img src="https://emoji.slack-edge.com/T039P7U66/the-federation/cf19b04ff8baa385.png" width="25px"/><img src="https://img.shields.io/badge/eyoo(Eunmi Yoo) : Resoponse Parsing -000000?style=for-the-badge&logoColor=white"/> <a href="https://profile.intra.42.fr/users/eyoo"><img src="https://img.shields.io/badge/Intra-000000?style=for-the-badge&logo=42&logoColor=white"/></a> <a href="https://github.com/EunmiYoo"><img src="https://img.shields.io/badge/Github-181717?style=for-the-badge&logo=Github&logoColor=white"/></a>
   <br>
   <img src="https://emoji.slack-edge.com/T039P7U66/the-assembly/157ba128c687991d.png" width="25px"/><img src="https://img.shields.io/badge/hyungyoo (Hyungjun Yoo) : Server Config -000000?style=for-the-badge&logoColor=white"/> <a href="https://profile.intra.42.fr/users/hyungyoo"><img src="https://img.shields.io/badge/Intra-000000?style=for-the-badge&logo=42&logoColor=white"/></a> <a href="https://github.com/hyungyoo"><img src="https://img.shields.io/badge/Github-181717?style=for-the-badge&logo=Github&logoColor=white"/></a>
  <br>
   <img src="https://emoji.slack-edge.com/T039P7U66/the-order/bc19034a94c85e26.png" width="25px"/><img src="https://img.shields.io/badge/seyun (Seokchan Yun) : SocketI/O -000000?style=for-the-badge&logoColor=white"/> <a href="https://profile.intra.42.fr/users/seyun"><img src="https://img.shields.io/badge/Intra-000000?style=for-the-badge&logo=42&logoColor=white"/></a> <a href="https://github.com/zeroet"><img src="https://img.shields.io/badge/Github-181717?style=for-the-badge&logo=Github&logoColor=white"/></a>
  <br>
   <img src="https://emoji.slack-edge.com/T039P7U66/the-order/bc19034a94c85e26.png" width="25px"/><img src="https://img.shields.io/badge/keulee (Keungeun Lee) : Request Parsing -000000?style=for-the-badge&logoColor=white"/> <a href="https://profile.intra.42.fr/users/keulee"><img src="https://img.shields.io/badge/Intra-000000?style=for-the-badge&logo=42&logoColor=white"/></a> <a href="https://github.com/keulee"><img src="https://img.shields.io/badge/Github-181717?style=for-the-badge&logo=Github&logoColor=white"/></a>
  <br>
</p>
