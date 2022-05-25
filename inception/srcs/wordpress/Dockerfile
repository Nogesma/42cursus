FROM alpine:3

RUN apk update
RUN apk upgrade

RUN apk add --no-cache php-fpm php-mysqli

VOLUME /var/www/html/wordpress

RUN mkdir -p /var/www/html
WORKDIR /var/www/html

RUN wget http://wordpress.org/latest.tar.gz
RUN mkdir wp
RUN tar -xzvf latest.tar.gz --directory=wp && rm latest.tar.gz

COPY www.conf /etc/php8/php-fpm.d/www.conf
COPY php.ini /etc/php8/php.ini
COPY wp-config.php .
COPY run.sh run.sh

CMD ["./run.sh"]
