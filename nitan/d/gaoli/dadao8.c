// Room in 高麗
inherit ROOM;
void create()        
{
        set("short", "青石大道");
        set("long", @LONG
你走在一條青石大道上，人來人往地非常繁忙，不時地有人騎着馬
匆匆而過。南邊通向高麗城。西北面是一條通向較軍場的大道。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "southwest" : __DIR__"jiaojunchang",
                "northeast" : __DIR__"dadao1",
        ]));
       setup();
        replace_program(ROOM);
}        
