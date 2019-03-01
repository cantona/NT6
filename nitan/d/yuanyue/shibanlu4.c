// This program is a part of NITAN MudLIB

inherit ROOM; 
void create()
{
        set("short", "碎石小路"); 
        set("long", @LONG
這條碎石小路往北就是圓月山莊的後院了，南面是富貴如意廳，
路上生滿了青苔，一不當心就會跌倒，兩側不知名的野花開得倒也茂
盛，淡淡的散發著一種清新的花香。草窠中偶爾傳來一兩聲蟋蟀的叫
聲。一抬頭，可以看見幾個或是蜈蚣狀，或是老鷹狀的風箏高高飛舞
在藍天白雲中。
LONG );
        set("type","road");
        set("outdoors", "wansong");
        set("exits",([
                "south":__DIR__"fuguitin",
                "northeast":__DIR__"grass3",
                "northwest":__DIR__"grass1",
        ]) );
        set("objects" , ([
                __DIR__"obj/flower" : 1,
        ]));    
        set("coor/x",-590);
        set("coor/y",230);
        set("coor/z",80);
        setup();
        replace_program(ROOM);
} 
