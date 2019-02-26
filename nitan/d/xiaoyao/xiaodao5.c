// xiaodao5.c
// Modified by Winder June.25 2000

inherit ROOM;

void create()
{
        set("short", "林間小道");
        set("long", @LONG
這是一條從南到北的林間小道，沿途風景極之清幽，參天古樹，拔
地而起，兩旁百花爭豔。令人留連忘返。
LONG );
        set("exits", ([
                "south" : __DIR__"muwu1",
                "north" : __DIR__"qingcaop",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "xiaoyao");
        set("coor/x", 80);
        set("coor/y", -510);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}