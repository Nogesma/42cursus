FROM alpine:3

RUN apk update

RUN apk add php8-fpm
RUN mkdir -p /usr/share/webapps/
WORKDIR /usr/share/webapps/
RUN wget http://wordpress.org/latest.tar.gz

RUN tar -xzvf latest.tar.gz && rm latest.tar.gz
