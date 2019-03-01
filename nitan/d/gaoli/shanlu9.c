// /d/gaoli/xuanwumen
// Room in 高麗
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "山路");
        set("long", @LONG
你走在一條山路上。南邊就是高麗的玉龍門了。有很多行人從你的
身旁走過，說著你聽不懂的高麗語。往北邊去，可以到高麗的北烽火台。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "southeast" : __DIR__"xuanwumen",
                "northwest":__DIR__"shanlu10",
        ]));
       setup();
        
}

