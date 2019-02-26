// This program is a part of NITAN MudLIB

inherit ROOM;
#include <room.h>

void create()
{
        set("short", "山谷口");
        set("long", @LONG
一片遼闊的山谷，四山合抱，蒼峯滴翠，一道清溪橫流過，水波
溶溶，游魚可數。沿溪一帶，綠柳垂揚，如絲如縷，清溪對岸，半坡
繁花間，隱隱現出一棟精舍，四外花枝環繞，燦若雲錦。
LONG );
        set("exits", ([ /* sizeof() == 4 */
                "east" : __DIR__"gu",
                "north" : __DIR__"gu1",
 
        ]));
     
        set("outdoors","wansong");          
        set("coor/x",120);
        set("coor/y",0);
        set("coor/z",5);
        setup();
        replace_program(ROOM); 
}       
