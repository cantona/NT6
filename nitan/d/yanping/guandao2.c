// Room: /d/yanping/guandao2.c
// Date: Sep 28, 2002  Winder

inherit ROOM;

void create()
{
        set("short", "官道");
        set("long", @LONG
你走在閩江北岸大官道上。福建境內無山不青，無水不翠，山陡林
深少行人，官道在羣峯邊下延伸，山林裏面時常有尖利的啼叫聲起，不
禁讓你惴惴。
LONG );
        set("exits", ([
                "eastdown"  : __DIR__"guandao1",
                "northwest" : __DIR__"milin",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "yanping");
        set("coor/x", 1700);
        set("coor/y", -6300);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}