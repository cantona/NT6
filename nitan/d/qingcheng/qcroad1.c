// Room: /qingcheng/qcroad1.c
// Date: Frb.20 1998 by Java

inherit ROOM;
void create()
{
        set("short", "青石大道");
        set("long", @LONG
你走在青石大道上。兩邊是稀硫的樹林和連片的田野。一條條
小溪和路平行，溪流清澈見底，水流甚急。
LONG );
        set("outdoors","qingcheng");
        set("exits", ([
                "south" : "/d/chengdu/fuheqiaon",
                "west"  : __DIR__"qcroad2",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -8050);
        set("coor/y", -950);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}