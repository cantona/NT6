// Room: /d/village/smithy2.c

inherit ROOM;

void create()
{
        set("short", "小房間");
        set("long", @LONG
這是鐵匠的住宅，屋子裏十分簡單，靠牆有一張木牀，牆角擺着
個小桌子，桌上胡亂的擺着幾個酒杯、茶碗，桌上靠牆放着一把長劍
(sword)。西邊有個小門，門上掛著個破布簾，出去就是鐵匠的鋪子了。
LONG );
        set("exits", ([ /* sizeof() == 1 */
            "west" :"/d/village/smithy1",
        ]));
        set("item_desc", ([
        "sword" : 
"這是一把看起來挺普通的劍，連劍鞘都沒有，大概新出爐不久。\n"
"你一撩布簾，正要出去，在外間爐火映照下，一眼瞥見劍身上仿\n"
"佛有些花紋。你伸手想把劍拿起來看個究竟，可一恍惚間，居然\n"
"抓了個空。你不信邪的再要拿，又是抓了個空。你注意到桌上酒\n"
"杯、茶碗的位置似乎有些怪。\n",
])) ;

        setup();
        replace_program(ROOM);
}
