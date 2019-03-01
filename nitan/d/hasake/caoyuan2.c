// caoyuan1.c 草原
inherit ROOM;
void create()
{
        set("short", "草原");
        set("long", @LONG
你走進了這遍綿綿不絕的大草原，腳下是寸厚的青草，軟綿綿的還真
不好走，看來買匹馬來代步到是的好主意。北邊和西邊都有好多帳篷，往
東可以看見沙漠的邊緣。
LONG);
        set("exits", ([
            "southeast" : __DIR__"caoyuan",
            "west" : __DIR__"pmchang",
            "south" : __DIR__"caoyuan1",
            "northeast" : __DIR__"caoyuan3",
        ]));
        set("outdoors", "hasake");
        setup();
        replace_program(ROOM);
}