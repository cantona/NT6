// shishi1.c
// Modified by Winder June.25 2000

inherit ROOM;

void create()
{
        set("short", "石室");
        set("long", @LONG
這是一個石頭砌成的房間，因為好久沒有人來過，散發着一些很難
聞的氣味，房間中到處可以看到蛛絲和蟲跡。
LONG );
        set("exits", ([
                "east" : __DIR__"shiji1",
        ]));
        set("objects",([
                __DIR__"obj/putuan" : 1,
        ]));
//        set("no_clean_up", 0);
        set("coor/x", -50040);
        set("coor/y", -21040);
        set("coor/z", -40);
        setup();
        replace_program(ROOM);
}