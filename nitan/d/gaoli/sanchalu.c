// Room in 高麗
inherit ROOM;
void create()        
{
        set("short", "三岔路口");
        set("long", @LONG
        
這是一個三岔路口，向西走不遠就是高麗城了，向南就是百濟地界
了，東北就是新羅地界，因為打仗的原因來往的行人非常少。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "west" : __DIR__"dadao4",
                "south" : __DIR__"dadao5",
                "northeast" : __DIR__"shaoqia",
        ]));
       setup();
        replace_program(ROOM);
}        
