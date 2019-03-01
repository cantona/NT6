// Code of ShenZhou
// Room: didao_e.c 地道東
// Zhangchi 7/00

inherit ROOM;
#include "didao.h"

void create()
{
        set("short", "地道");
        set("long", @LONG
這是一條剛剛挖成的地道，看樣子是往東延伸。
LONG );
        set("exits", ([
                "west": "/d/mingjiao/didao/didao1",
]));
        
        set("cost", 1);
        set("valid_dig","east");

        setup();
//        replace_program(ROOM);
}

void init()
{
        int num=get_room("east");
        if (num >= 1)
                set("exits/east","/d/mingjiao/didao/didao_e_1");
        else
                delete("exits/east");

        add_action("do_dig","wa");
        add_action("do_dig","dig");
}