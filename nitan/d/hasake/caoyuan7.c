// caoyuan7.c 草原
inherit ROOM;
void create()
{
        set("short", "大草原");
        set("long", @LONG
你走進了這遍綿綿不絕的大草原，腳下是寸厚的青草，軟綿綿的還真
不好走，看來買匹馬來代步到是的好主意。
LONG);
        set("exits", ([
            "south" : __DIR__"caoyuana",
            "west" : __DIR__"caoyuan9",
            "east" : __DIR__"caoyuan8",
            "north" : __DIR__"room-su",
        ]));
        set("outdoors", "hasake");
        setup();
        replace_program(ROOM);
}