# Bank

## Requirements
Apache server - CGI module actived is required 

## Instructions
  * Install apache server
  * Execute the following commands to active CGI module
  	- sudo a2enmod cgi
  	- sudo service apache2 restart

## Apache config
  * Create a virtual host or use default config file with the following options

```
	ServerName bank.com
	DocumentRoot /var/www/cgi-bin

	<Directory "/var/www/cgi-bin">
        Options +ExecCGI -MultiViews +SymLinksIfOwnerMatch
        Order allow,deny
        Allow from all
		AddHandler cgi-script .cgi
		RewriteEngine on
		RewriteCond %{REQUEST_FILENAME} !-f
		RewriteCond %{REQUEST_URI} !^.*\.(jpg|css|js|gif|png)$ [NC]
		RewriteRule ^(.*)$ /index.cgi?path=$1 [NC,L,QSA]
	</Directory>
```
  * A simbolic link to public/ must be placed inside DocumentRoot directory (/var/www/cgi-bin)