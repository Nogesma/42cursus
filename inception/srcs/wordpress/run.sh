#!/bin/sh

if [ ! -f "wordpress/index.php" ]; then
  mv wp/wordpress/* wordpress
  mv wp-config.php wordpress
fi

php-fpm8
