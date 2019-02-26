// Room: /city/wudao2.c

#include <ansi.h>
inherit "/d/city/underlt";

void create()
{
        set("short", "武道場");
        set("long", @LONG
這裏是三面環山，只有北面有條出口的一坪山間平地。山坡山陣
陣松濤嘩嘩作響，山腳下的平地綠草如茵，中間架起了個擂台，四周
一溜過去搭着涼棚，棚中桌椅杯盆俱全。這裏是青年組的比武場地！
LONG );
        set("outdoors", "city");
        set("exits", ([
                "leitai"      : "/d/city/leitai2",
                "west"        : "/d/city/wudao4",
        ]));
        set("no_fight", 1);
        setup();

        init_here();
        replace_program("/d/city/underlt");
}
