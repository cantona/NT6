// This program is a part of NITAN MudLIB

inherit ROOM;
#include <room.h> 
void create()
{
        set("short", "山隙中");
        set("long", @LONG
這是山壁間一條一尺多寬的山隙，被附生在壁上的蔓草藤蘿遮掩，
不加仔細探查很難發現。
LONG );
        set("exits", ([ /* sizeof() == 2 */
                "east" : __DIR__"shandong",
                "westdown" : __DIR__"dong1",
 
        ]));
         
        set("coor/x",150);
        set("coor/y",0);
        set("coor/z",20);
        setup();
        replace_program(ROOM); 
} 
