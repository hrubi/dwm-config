#!/bin/bash

#
# Copyright (c) 2009 Brian Tarricone <brian@tarricone.org>
#
# Released under the terms of the GNU General Public License, version 2.
#

[ ${1} ] || exit 1
[ ${2} ] || exit 1


#CARD="0"
#MIXER="Master"
CARD="${1}"
CMD="${2}"
VAL="${3}"
MIXER="Speaker"

if [ $CARD = "0" ];then
    MIXER="Speaker"
elif [ $CARD = "1" ]; then
    MIXER="Master"
fi

case $CMD in
    up)
        [ "$VAL" ] || exit 1
        amixer -c "$CARD" set $MIXER ${VAL}%+ &>/dev/null
        ;;
    down)
        [ "$VAL" ] || exit 1
        amixer -c "$CARD" set $MIXER ${VAL}%- &>/dev/null
        ;;
    toggle)
        amixer -c "$CARD" set $MIXER toggle &>/dev/null
        ;;
    *)
        exit 1
        ;;
esac
