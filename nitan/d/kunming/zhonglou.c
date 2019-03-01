#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",  "鐘樓" );
        set("long", @LONG
這是一座鐘樓，中間懸有有一巨鐘，上面刻的有銘文。永
樂大鐘鐘身足有兩人那麼高，看起來足有上千斤，不知道當初
是怎麼掛上去的，鐘的兩側懸有一巨木，看來是用來敲鐘用的。 
LONG);
        
        set("exits", ([
                "down"    :__DIR__"jinrilou",
        ]));
        set("objects", ([
                "/d/hangzhou/npc/seng" : 1,
        ]));                       

	set("coor/x", -16840);
	set("coor/y", -7210);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);       
}