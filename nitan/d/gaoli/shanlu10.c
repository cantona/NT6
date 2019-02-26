// /d/gaoli/xuanwumen
// Room in 高麗
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "山路");
        set("long", @LONG
你走在一條山路上。南邊就是高麗的玉龍門了。這裏的行人不是很
多。看來平時很少有人到這裏來。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "southeast" : __DIR__"shanlu9",
                "northwest":__DIR__"shanlu11",
        ]));
       setup();
        
}

