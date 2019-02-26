// Feb. 6, 1999 by Winder
inherit ROOM;
void create()
{
        set("short", "側房");
        set("long", @LONG
這裏就是温家老三温方義的住處，房間整潔，牆上掛着把帶鞘的
寶刀，桌子上面鋪着一張圖，温老三正在專心地看着圖上的內容，口
中唸唸有詞。
LONG
        );
        set("exits", ([ 
                "east" : __DIR__"zoulang2",
        ]));
        set("objects", ([
                __DIR__"npc/wenfangshan" : 1,
        ]));
        set("coor/x", 1590);
        set("coor/y", -1930);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}