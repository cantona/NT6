// /d/gaoli/xuanwumen
// Room in 高麗
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "山路");
        set("long", @LONG
你走在一條山路上。再往西邊走就是高麗的北城監獄了。那裏關押
着高麗的重要犯人，平時有很多官兵在那裏把守。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "east" : __DIR__"shanlu12",
                       "west":__DIR__"shanlu15",
        ]));
       setup();
        
}

