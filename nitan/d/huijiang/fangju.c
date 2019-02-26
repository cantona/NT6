// Room: /d/huijiang/fangju.c
// Last Modified by winder on Sep. 12 2001

inherit ROOM;

void create()
{
        set("short", "防具庫");
        set("long",@LONG
這裏是紅花會的防具庫。紅花會為了反清復明，做了很多物質上的
準備。看看這裏，你大概就能有所體會。整間倉庫堆到頂，都是滿滿當
當的，所有防具真是應有盡有。
LONG );
        set("objects", ([
                ARMOR_DIR"beixin"  : random(2)+1,
                ARMOR_DIR"tengjia" : random(2)+1,
                ARMOR_DIR"tiejia"  : random(2)+1,
                ARMOR_DIR"niupi"   : random(2)+1,
        ]));
        set("exits", ([
                "south" : __DIR__"wuchang",
        ]));
        set("coor/x", -50040);
        set("coor/y", 9150);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}