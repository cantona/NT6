// Room: /d/guiyun/qianting.c
// Last Modified by winder on Jul. 9 2001

inherit ROOM;

void create()
{
        set("short","前廳");
        set("long",@LONG
這是歸雲莊的前廳。平常招待客人都在這裡進行。廳中陳設華美，
雕樑畫棟，極窮巧思。
LONG
);
        set("objects",([
                __DIR__"npc/zhuangding1" : 2,
        ]));  
        set("exits",([
                "east" : __DIR__"dayuan",
                "west" : __DIR__"zhongting",
        ]) );
        set("no_clean_up",0);
        set("coor/x", 270);
        set("coor/y", -830);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}