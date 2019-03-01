// Feb. 6, 1999 by Winder
inherit ROOM;
void create()
{
        set("short", "側房");
        set("long", @LONG
這裡就是溫家老三溫方義的住處，房間整潔，牆上掛著把帶鞘的
寶刀，桌子上面舖著一張圖，溫老三正在專心地看著圖上的內容，口
中念念有詞。
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