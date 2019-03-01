// Room: /guiyun/ship.c
// Date: Nov.18 1998 by Winder

inherit ROOM;

void create()
{
        set("short", "戰船");
        set("long", @LONG
這是一艘大漁船，船上的人白天打魚，晚上就幹些沒本錢的買賣，
接濟沿湖的百姓。
LONG );
        set("outdoors", "guiyun");
        set("no_clean_up", 0);
        set("objects", ([
                __DIR__"npc/haojie" : 1,
        ]));
        set("coor/x", 300);
        set("coor/y", -610);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}