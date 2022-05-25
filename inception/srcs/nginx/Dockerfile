FROM alpine:3

RUN apk update
RUN apk upgrade

RUN apk add --no-cache nginx

RUN adduser -D -g 'www' www

RUN mkdir /www
RUN chown -R www:www /var/lib/nginx
RUN chown -R www:www /www

COPY nginx.conf /etc/nginx/nginx.conf
COPY localhost.crt /etc/ssl/certs/localhost.crt
COPY localhost.key /etc/ssl/private/localhost.key

VOLUME /var/www/html/wordpress

CMD ["/usr/sbin/nginx", "-g",  "daemon off;error_log /dev/stdout debug;"]
