// /d/gaoli/xuanwumen
// Room in 高麗
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "山路");
        set("long", @LONG
你走在一條山路上。再往西邊走就是高麗的北城監獄了。西邊就是
北城監獄的大門了。有幾名官兵在那裏把守着，用嚴厲的眼神看着你。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "southeast" : __DIR__"shanlu15",
                       "west":__DIR__"jianju",
        ]));
       setup();
        
}

