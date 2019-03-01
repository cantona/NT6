// Room: /qingcheng/qcroad2.c
// Date: Frb.20 1998 by Java

inherit ROOM;
void create()
{
        set("short", "青泥小道");
        set("long", @LONG
你走在青泥小道上。左邊不遠傳來陣陣水響，原來那裡就是天
下知名都江堰。攔河分流，使岷江之水分注到無數小小溪流中，才
免了連年的水禍，灌溉出了這富饒的成都平原。
LONG );
        set("outdoors","qingcheng");
        set("exits", ([
                "north" : __DIR__"qcroad3",
                "east"  : __DIR__"qcroad1",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -8060);
        set("coor/y", -950);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}