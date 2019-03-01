// This program is a part of NITAN MudLIB

inherit ROOM;

void create()
{
        set("short", "碎石小路"); 
        set("long", @LONG
這是一條通往大廳的碎石小路，路上生滿了青苔，一不當心就會
跌倒，兩側不知名的野花開得倒也茂盛，淡淡的散發著一種清新的花
香。草窠中偶爾傳來一兩聲蟋蟀的叫聲。一抬頭，可以看見幾個或是
蜈蚣狀，或是老鷹狀的風箏高高飛舞在藍天白雲中。
LONG );
        set("outdoors", "wansong");
        set("type", "road");
        set("exits",([
                "out":__DIR__"damen",
                "north":__DIR__"fuguitin",
        ]) );
        
        set("objects" , ([
                __DIR__"obj/flower" : 1,
        ])); 
        set("coor/x",-590);
        set("coor/y",210);
        set("coor/z",80);
        
        setup();
        replace_program(ROOM);
}    
