// /d/gaoli/xuanwumen
// Room in 高麗
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "山路");
        set("long", @LONG
你走在一條山路上。再往南邊走不遠，就可以到高麗的玉龍門了。
這裡的道路有些崎嶇，你不禁小心起來。向北望去，隱約有一個巨大的
建築物。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "south" : __DIR__"shanlu7",
                "northeast":__DIR__"guangchang",
        ]));
       setup();
        
}

