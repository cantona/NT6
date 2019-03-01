// Code of ShenZhou
// Room: didao_n_2.c 地道北
// Zhangchi 7/00

inherit ROOM;
#include "didao.h"

void create()
{
        set("short", "地道");
        set("long", @LONG
這是一條剛剛挖成的地道，看樣子是往北延伸。
LONG );
        set("exits", ([
                "south": "/d/mingjiao/didao/didao_n_1",
]));
        
        set("cost", 1);
        set("valid_dig","north");

        setup();
//        replace_program(ROOM);
}

void init()
{
        int num=get_room("north");
        if (num >= 3)
                set("exits/north","/d/mingjiao/didao/didao_n_3");
        else
                delete("exits/north");

        add_action("do_dig","wa");
        add_action("do_dig","dig");
}
