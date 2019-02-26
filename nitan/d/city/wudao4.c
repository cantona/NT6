// Room: /city/wudao4.c
// Date: Feb.28 1998 by Java

#include <ansi.h>

inherit "/d/city/underlt";

void create()
{
        set("short", "武道場");
        set("long", @LONG
這裏是三面環山，只有北面有條出口的一坪山間平地。山坡山陣
陣松濤嘩嘩作響，山腳下的平地綠草如茵，中間架起了個擂台，四周
一溜過去搭着涼棚，棚中桌椅杯盆俱全。西面是少年組的比武場，東
面是青年組的比武場，南面是成年組的比武場。
LONG );
        set("outdoors", "city");
        set("exits", ([
                "north"       : "/d/city/ximenroad",
                "west"        : "/d/city/wudao1",
//                "east"        : "/d/city/wudao2",
//                "south"       : "/d/city/wudao3",
//               "up"  : "/d/sjszhuang/gate",
        ]));
        set("no_fight", 1);
	set("coor/x", -50);
	set("coor/y", -10);
	set("coor/z", 0);
	setup();
        "/clone/board/wudao_b"->foo();
        init_here();
        replace_program("/d/city/underlt");
}
