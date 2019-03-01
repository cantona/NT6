// /d/gaoli/xuanwumen
// Room in 高麗
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "山路");
        set("long", @LONG
你走在一條山路上。再往西邊走就是高麗的北城監獄了。這裡基本
上沒有什麼行人，兩旁是高高的圍牆，看起來有些陰森。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "east" : __DIR__"shanlu14",
                       "northwest":__DIR__"shanlu16",
        ]));
       setup();
        
}

