// caoyuan1.c 草原

inherit ROOM;

void create()
{
        set("short", "草原");
        set("long", @LONG
你走進了這遍綿綿不絕的大草原，腳下是寸厚的青草，軟綿綿的還真
不好走，看來買匹馬來代步到是的好主意。南邊和西邊都有好多帳篷，往
東可以看見沙漠的邊緣。
LONG);
        set("exits", ([
            "northeast" : __DIR__"caoyuan",
            "west" : __DIR__"caochang",
            "south" : __DIR__"majiu",
            "north" : __DIR__"caoyuan2",
        ]));
        set("objects", ([
                    __DIR__"npc/hasake" : 1,
                    __DIR__"npc/yang" : 2
        ]));
        set("outdoors", "hasake");
        setup();
        replace_program(ROOM);
}