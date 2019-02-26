// Room: /wuliang/jianhugate.c
// Date: Oct.18 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "劍湖宮門");
        set("long", @LONG
這裏就是無量劍派的劍湖宮了。“無量劍”原分東、北、西三宗
，北宗近數十年來已趨式微，東西二宗卻均人才鼎盛。“無量劍”於
五代後唐年間在南詔無量山創派，掌門人居住無量山劍湖宮。
LONG );
        set("outdoors", "wuliang");
        set("exits", ([
                "enter"     : __DIR__"road1",
                "southdown" : __DIR__"shanlu9",
        ]));
        set("objects", ([
                __DIR__"npc/wuliangdizi" : 1,
        ]));
        set("coor/x", -71000);
        set("coor/y", -79960);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}