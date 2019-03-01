// Room: /d/yanziwu/xunfeng.c
// Date: Jan.28 2000 by Winder

inherit ROOM;

void create()
{
        set("short", "熏風軒");
        set("long", @LONG
一個精美的小軒，建在水邊，一半橫臥萬頃太湖波濤中。湖面風勢
徐來，帶動軒角風鈴一陣陣低吟。遠望萬千波濤，如少女的碧綠長裙輕
舞，漸行漸近，終于消失在軒下，真是無邊景致，全在心情。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                "southwest"   : __DIR__"path13",
        ]));
        set("coor/x", 1270);
        set("coor/y", -1210);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}