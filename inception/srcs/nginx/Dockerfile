FROM alpine:3.15

RUN apk update
RUN apk add nginx

RUN adduser -D -g 'www' www

RUN mkdir /www
RUN chown -R www:www /var/lib/nginx
RUN chown -R www:www /www

RUN ln -sf /dev/stdout /var/log/nginx/access.log \
 && ln -sf /dev/stderr /var/log/nginx/error.log

COPY nginx.conf /etc/nginx/nginx.conf
COPY index.html /www/index.html

COPY localhost.crt /etc/ssl/certs/localhost.crt
COPY localhost.key /etc/ssl/certs/localhost.key

CMD ["/usr/sbin/nginx", "-g",  "daemon off;error_log /dev/stdout debug;"]
