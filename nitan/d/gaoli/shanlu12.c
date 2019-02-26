// /d/gaoli/xuanwumen
// Room in 高麗
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "山路");
        set("long", @LONG
你走在一條山路上。再往南邊走不遠就是高麗的玉龍門了。幾乎沒
有什麼人，冷冷清清的。這裏已經是高麗的北郊了。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "south" : __DIR__"shanlu11",
                "north":__DIR__"shanlu13",
                "west":__DIR__"shanlu14",
        ]));
       setup();
        
}

