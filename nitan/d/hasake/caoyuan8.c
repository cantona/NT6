// caoyuan8.c 草原
inherit ROOM;
void create()
{
        set("short", "大草原");
        set("long", @LONG
你走進了這遍綿綿不絕的大草原，腳下是寸厚的青草，軟綿綿的還真
不好走，看來買匹馬來代步到是的好主意。
LONG);
        set("exits", ([
            "south" : __DIR__"caoyuan9",
            "west" : __DIR__"caoyuana",
            "east" : __DIR__"caoyuan7",
            "north" : __DIR__"room-che",
        ]));
        set("outdoors", "hasake");
        setup();
        replace_program(ROOM);
}