// Room in 高麗
inherit ROOM;
void create()        
{
        set("short", "轅門");
        set("long", @LONG
        
這是百濟駐軍所在的兵營的轅門，兩邊有數丈高的旗桿，旗桿上的
刁鬥上，轅門的兩旁百濟士兵嚴陣以待，再向前走就是兵營的中軍大帳
了。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "north" : __DIR__"dadao5",
                "south" : __DIR__"dazhang",
        ]));
       setup();
        replace_program(ROOM);
}        
