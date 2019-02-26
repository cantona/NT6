// Room in 高麗
inherit ROOM;
void create()        
{
        set("short", "青石大道");
        set("long", @LONG
你走在一條青石大道上，人來人往地非常繁忙，不時地有人騎着馬
匆匆而過。北邊通向高麗城。南面是海邊了，在這裏你可以聽見海浪的
聲音。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "north" : __DIR__"dadao6",
                "west":__DIR__"xiaolu1",
                "southwest":__DIR__"suishilu1",
                "southeast":__DIR__"shatan1",
        ]));
       setup();
        replace_program(ROOM);
}        
