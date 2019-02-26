// Room: /yangzhou/ouxiangqiao.c
// Last Modified by Winder on Jul. 20 2000

inherit ROOM;

void create()
{
        set("short","藕香橋");
        set("long",@LONG
藕香橋舊名法海橋，位於蓮性寺東南側，東西跨瘦西湖，支流湖道
栽種荷花。開蓮花埂新河，建蓮花橋後，湖上畫舫皆過蓮花橋，不復過
法海橋。
LONG );
        set("outdoors", "shouxihu");

        set("exits", ([
                "northwest" : __DIR__"lianxingsi",
                "southeast" : __DIR__"taohuawu",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -10);
        set("coor/y", 50);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}