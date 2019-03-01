// caoyuan3.c 草原
inherit ROOM;
void create()
{
        set("short", "草原");
        set("long", @LONG
你走進了這遍綿綿不絕的大草原，腳下是寸厚的青草，軟綿綿的還真
不好走，看來買匹馬來代步到是的好主意。西邊可以看見哈薩克帳篷，往
東去就是沙漠了。
LONG);
        set("exits", ([
            "southwest" : __DIR__"caoyuan2",
            "northwest" : __DIR__"shop",
            "northup" : __DIR__"road1",
            "southdown" : __DIR__"caoyuan",
        ]));
        set("outdoors", "hasake");
        setup();
        replace_program(ROOM);
}