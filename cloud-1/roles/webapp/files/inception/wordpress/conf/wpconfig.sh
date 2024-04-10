#!/bin/bash
set -e

WP_PATH="/var/www/html"
CONFIG_FILE="$WP_PATH/wp-config.php"

if ! command -v wp &>/dev/null; then
	echo "WP-CLI not found!"
	exit 1
fi

if [ ! -f "$CONFIG_FILE" ]; then
	wp config create \
		--dbname="$DATABASE_NAME" \
		--dbhost=mariadb \
		--dbuser="$DATABASE_USER" \
		--dbpass="$DATABASE_PW" \
		--path="$WP_PATH" \
		--allow-root \
		--skip-check

	until wp db check --path="$WP_PATH" --allow-root; do
		echo "Waiting for MariaDB..."
		sleep 1
	done

	wp core install \
		--url="$WP_URL" \
		--title="$WP_SITE_TITLE" \
		--admin_user="$WP_ADMIN_USER" \
		--admin_password="$WP_ADMIN_PW" \
		--admin_email="$WP_ADMIN_EMAIL" \
		--path="$WP_PATH" \
		--allow-root

	wp theme install twentytwentyfour --activate --allow-root

	default_post_id=$(wp post list --post_type='post' --posts_per_page=1 --post_status=publish --format=ids --allow-root)
	if [ -n "$default_post_id" ]; then
		wp post delete "$default_post_id" --force --allow-root
	fi

	wp post create \
		--post_type=post \
		--post_status=publish \
		--post_title="Exploring the Cloud 1 Concept" \
		--post_content="The journey into the cloud begins with understanding the intricate layers that make up cloud computing. Inspired by the complex narrative of Inception, our exploration of Cloud 1 delves into the foundational aspects of deploying and managing cloud-based infrastructures. Just as Inception navigates through multiple layers of the subconscious, Cloud 1 represents the initial layer of our cloud journey—setting the stage for deeper exploration and understanding." \
		--allow-root

	wp config set WP_REDIS_HOST "redis" --allow-root
	wp config set WP_REDIS_PORT 6379 --raw --allow-root
	wp config set WP_CACHE_KEY_SALT "$WP_URL" --allow-root
	wp config set ALLOW_UNFILTERED_UPLOADS true --raw --allow-root
	wp config set WP_REDIS_CLIENT "phpredis" --allow-root
	wp config set WP_DEBUG true --raw --allow-root
	wp config set WP_DEBUG_LOG true --raw --allow-root
	wp config set WP_DEBUG_DISPLAY false --raw --allow-root

	wp plugin install redis-cache --activate --allow-root
	wp plugin update --all --allow-root
	wp redis enable --allow-root

	#echo '<!-- Server IP Address Display --><div class="server-ip-address" style="text-align: center; margin-top: 20px;"><p>Server IP Address: <?php echo $_SERVER['SERVER_ADDR']; ?></p></div>' >>"$WP_PATH/wp-content/themes/twentytwentyfour/patterns/footer.php"
	chown -R nobody:nobody /var/www/html # a verifier
fi

exec /usr/sbin/php-fpm83 -F
