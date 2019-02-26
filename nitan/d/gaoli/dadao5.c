// Room in 高麗
inherit ROOM;
void create()        
{
        set("short", "青石大道");
        set("long", @LONG
        
你走在一條青石大道上，因為戰爭的原因，越向前走行人越來越少，
不時有人騎着馬匆匆而過。大道往北進入新羅境內。南邊通向百濟,
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "north" : __DIR__"sanchalu",
                "south" : __DIR__"yuanmen",
        ]));
       setup();
        replace_program(ROOM);
}        
