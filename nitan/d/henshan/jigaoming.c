#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "極高明台");
        set("long", @LONG
這裡是福嚴寺最高處。唐鄴侯李泌手書「[1；37m極高明[2；37；0m」三個大字于此，
意即佛相極高(高無見頂相)，佛光極明(明不借他光)，佛是至高無上
的，故曰極高明台。
LONG );
        set("exits", ([ 
               "northdown"  : __DIR__"sansheng",
        ]));

        set("objects", ([
                __DIR__"npc/youke" : 4,
        ]));    

        set("outdoors", "henshan");

        set("no_clean_up", 0);

	set("coor/x", -6950);
	set("coor/y", -5580);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}