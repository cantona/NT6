// This program is a part of NITAN MudLIB

inherit ROOM;
#include <room.h>

void create()
{
        set("short", "橋上");
        set("long", @LONG
小橋上，朱欄低垂，垂柳下，少女輕笑。小溪緩緩流過，幾尾金
色鯉魚越水而出。
LONG );
        set("exits", ([ /* sizeof() == 4 */
                "east" : __DIR__"gu1",
                "westdown" : __DIR__"gu3",
 
        ]));
        set("outdoors","wansong");       
        set("coor/x",110);
        set("coor/y",10);
        set("coor/z",10);
        setup();
        replace_program(ROOM);
}    
