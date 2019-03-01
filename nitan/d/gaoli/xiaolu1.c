// Room in 高麗
inherit ROOM;
void create()        
{
        set("short", "小路");
        set("long", @LONG
你走在一條小路之上。東邊是一條青石大路，南邊就是海邊了，從
這裡可以聽到波濤洶湧的聲音，不時有幾只海鷗從你的頭上飛過。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "east" : __DIR__"dadao9",
                "southwest":__DIR__"xiaolu2",
        ]));
       setup();
        replace_program(ROOM);
}        
