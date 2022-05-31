#!/bin/sh

wp core download
wp config create \
  --dbname="$MYSQL_DATABASE" \
  --dbuser="$MYSQL_USER" \
  --dbpass="$MYSQL_PASSWORD" \
  --dbhost=mariadb:3306 \
  --skip-check

if [ ! "$(wp core is-installed)" ]; then
  wp core install \
    --url="$WEBSITE_URL" \
    --title=Inception \
    --admin_user="$ADMIN_NAME" \
    --admin_password="$ADMIN_PASSWORD" \
    --admin_email="$ADMIN_EMAIL" \
    --skip-email
  wp user create "$USER_NAME" "$USER_EMAIL" --role=author --user_pass="$USER_PASSWORD"
fi

php-fpm8
