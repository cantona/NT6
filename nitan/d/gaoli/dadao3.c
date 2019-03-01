// Room in 高麗
inherit ROOM;
void create()        
{
        set("short", "青石大道");
        set("long", @LONG
        
你走在一條青石大道上，因為戰爭的原因，越向前走行人越來越少，
不時有人騎著馬匆匆而過。大道往東進入新羅境內。北邊通向高麗城,
西北有一條土路通向一座莊園。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "west" : __DIR__"dadao2",
                "east" : __DIR__"dadao4",
//              "northwest" : __DIR__"tulu1",
        ]));
       setup();
        replace_program(ROOM);
}        
