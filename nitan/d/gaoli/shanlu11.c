// /d/gaoli/xuanwumen
// Room in 高麗
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "山路");
        set("long", @LONG
你走在一條山路上。再往南邊走不遠就是高麗的玉龍門了。這裡的
行人不是很多。看來平時很少有人到這裡來。向北望去，隱約可以看到
高麗的烽火台。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "southeast" : __DIR__"shanlu10",
                "north":__DIR__"shanlu12",
        ]));
       setup();
        
}

