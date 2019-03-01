// Room: /qingcheng/qcroad2.c
// Date: Frb.20 1998 by Java

inherit ROOM;
void create()
{
        set("short", "青石大道");
        set("long", @LONG
你走在青石大道上。遠遠傳來細細的水聲，掩蓋在路邊密密樹
林的風聲中。望北可以看到一座大山了，蒼蒼翠翠，象一塊清清純
純的碧玉。
LONG );
        set("outdoors","qingcheng");
        set("exits", ([
                "south"  : __DIR__"qcroad2",
                "north"  : __DIR__"xiaoqiao",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -8060);
        set("coor/y", -940);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}