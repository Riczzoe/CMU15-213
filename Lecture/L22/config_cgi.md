I want do something cool like textbook:
```
telnet kittyhawk.cmcl.cs.emu.edu 8000
****
***
GET /cgi-bin/adder?15000&213 HTTP/ 1.0

HTTP/1.1 200 OK
Date: Tue, 23 May 2023 03:01:01 GMT
Server: Apache/2.4.41 (Ubuntu)
Connection: close
Content-length: 115
Vary: Accept-Encoding
Content-Type: text/html

Welcome to add.com: The Internet addition portal.
<p>The answer is: 15000 + 213 = 15213
<p>Thanks for wisiting!
Connection closed by foreign host.
```

so I use apache2 to build a server and write a cgi program to do 
the addition.

1. config telnet server

In most linux system, telnet server are usually run through xinetd
or inted. So we need check whether the xinetd service is installed.
``` bash
systemctl status xinetd   # check xinetd service

# if not installed, install it
sudo apt update
sudo apt install xinetd
```
If the service is successfully installed and running, you should be 
able to see output similar to the following:
``` bash
● xinetd.service - LSB: Starts or stops the xinetd daemon.
  Loaded: loaded (/etc/init.d/xinetd; generated)
  Active: active (running) since [timestamp]
```
now, configure the telnet server: Open the `/etc/xinetd.d` directory.
Find the file named `telnet` (create a new one if it doesn't exist).
Open the file with a text editor and copy the following content to the file:
``` 
service telnet
{
    disable = no
    flags = REUSE
    socket_type = stream
    wait = no
    user = root
    server = /usr/sbin/in.telnetd
    log_on_failure += USERID
}
```
Save the file and restart the xinetd service:
``` bash
sudo systemctl restart xinetd
```
Now, the telnet server is running on port 23. You can use telnet with
```
telnet localhost 23
```

2. config apache2

First, make sure that CGI-supporting Web server software, such as 
Apache HTTP Server or Nginx, is installed and configured on the 
remote server. In this case, I use apache2.

so download apache2
``` bash
sudo apt update
sudo apt install apache2
```
enable the CGI module
``` bash
sudo a2enmod cgi

# I get something like this
# Your MPM seems to be threaded. Selecting cgid instead of cgi.
# Module cgid already enabled
#
# In this case, you can continue to follow the steps above since 
# the cgid module also supports CGI. This means that the CGI module 
# has been enabled on your Apache HTTP server. So just continue.
```
Create a directory for our adder program, I create a directory named
`/var/www/cgi-bin`, and you can create a directory named and located
anywhere you want.

After you create the directory, and move the program to the directory,
or create a new one. whatever. you just need to make sure that the
program you want to run is located in the directory.
and then, check the permission of the program, make sure that the
program is executable.
``` bash
# you can use chmod to change the permission
# In my case, I use 755
sudo chmod +x /var/www/cgi-bin/adder
```
Now, we need to configure the Apache HTTP server to run CGI programs.
Open the `/etc/apache2/sites-enabled/000-default.conf` file 

Add the following lines to the file:
```bash
<Directory /var/www/cgi-bin>
    Options +ExecCGI
    AddHandler cgi-script .cgi .pl
</Directory>
```

But sometimes, In file `/etc/apache2/apache2.conf`, you can find
```bash
<VirtualHost *:80>
 ********

 ServerAdmin webmaster@local
 # This is the default directory index for this server. It maybe
 # make some trouble, 
 DocumentRoot /var/www/html 
 # so you can add the following line to the <VirtualHost> section 
 # of your configuration file:
 # That you can access the cgi-bin directory correctly.
 ScriptAlias /cgi-bin/ /var/www/cgi-bin/

 *******
</VirtualHost>
```
After you finish the configuration, restart the apache2 service
``` bash
sudo service apache2 restart
```

Now, you can use telnet to access the server, and run the program
``` bash
Linux> telnet localhost 80
Trying 127.0.0.1...
Connected to localhost.
Escape character is '^]'.
GET /cgi-bin/adder?15000&213 HTTP/1.0

*****
```


