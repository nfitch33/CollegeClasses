#!/bin/bash

FILE="cslab-hosts"

while read -r HOST _; do
    SHORTHOST=${HOST%%.cs.ohio.edu}

    echo "=== $HOST / $SHORTHOST"

    ssh -o ConnectTimeout=3 -q "$HOST" uptime \
        || echo "OOPS: ssh $HOST failed"

    ssh -o ConnectTimeout=3 -q "$SHORTHOST" uptime \
        || echo "OOPS: ssh $SHORTHOST failed"

done < "$FILE"

exit 0