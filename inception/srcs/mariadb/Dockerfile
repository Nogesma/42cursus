FROM alpine:3

RUN apk update
RUN apk upgrade
RUN apk add --no-cache mariadb mariadb-client

COPY run.sh .

CMD ["./run.sh"]
