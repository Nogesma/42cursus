FROM alpine:3.16

VOLUME /var/www/html

RUN apk update
RUN apk upgrade

RUN apk add --no-cache php8 php8-fpm php8-mysqli php8-mysqlnd php8-phar php8-iconv

RUN wget https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
RUN chmod +x wp-cli.phar
RUN mv wp-cli.phar /usr/local/bin/wp

COPY www.conf /etc/php8/php-fpm.d/www.conf
COPY php.ini /etc/php8/php.ini

COPY run.sh run.sh
COPY wait-for-it.sh wait-for-it.sh

WORKDIR /var/www/html

CMD ["/wait-for-it.sh", "mariadb:3306", "--", "./run.sh"]
