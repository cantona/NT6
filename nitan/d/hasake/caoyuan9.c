// caoyuan9.c 草原
inherit ROOM;
void create()
{
        set("short", "大草原");
        set("long", @LONG
你走進了這遍綿綿不絕的大草原，腳下是寸厚的青草，軟綿綿的還真
不好走，看來買匹馬來代步到是的好主意。
LONG);
        set("exits", ([
            "south" : __DIR__"caoyuan",
            "west" : __DIR__"caoyuan7",
            "east" : __DIR__"caoyuan8",
            "north" : __DIR__"caoyuana",
        ]));
        set("objects", ([
                    __DIR__"npc/hasake" : 1,
                    __DIR__"npc/yang" : 2
        ]));
        set("outdoors", "hasake");
        setup();
        replace_program(ROOM);
}