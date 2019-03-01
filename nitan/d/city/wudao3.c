// Room: /city/wudao3.c

#include <ansi.h>

inherit "/d/city/underlt";

void create()
{
        set("short", "武道場");
        set("long", @LONG
這裡是三面環山，只有北面有條出口的一坪山間平地。山坡山陣
陣鬆濤嘩嘩作響，山腳下的平地綠草如茵，中間架起了個擂台，四周
一溜過去搭著涼棚，棚中桌椅杯盆俱全。這裡是成年組的比武場地！
LONG );
        set("outdoors", "city");
        set("exits", ([
                "leitai"      : "/d/city/leitai3",
                "north"       : "/d/city/wudao4",        
        ]));
        set("no_fight", 1);
        setup();

        init_here();
        replace_program("/d/city/underlt");
}
