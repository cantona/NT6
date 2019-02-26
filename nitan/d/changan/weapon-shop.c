//Room: weapon-shop.c

#include <ansi.h>

inherit ROOM;

void create ()
{
        set ("short", "兵器店");
        set("long", @LONG
這裏是兵器店。店裏到處銀光閃閃，讓人眼花繚亂。兵器架上擺
着各種兵器，十八般武器是應有盡有，樣樣俱全。兵器店老闆是慕容
世家的傳人。南牆上還寫了一首詩(poem)。
LONG );
        set("exits", 
        ([ //sizeof() == 1
                "north" : "/d/changan/qixiang6",
        ]));
        set("item_desc", ([
                "poem": HIR @TEXT
        易水蕭蕭西風冷，壯士一去不復還！
        拼死但憑三尺劍，深情唯有負紅顏！
TEXT NOR
        ]) );
        set("objects", 
        ([ //sizeof() == 1
                "/d/changan/npc/murong-hao" : 1,
        ]));

        set("no_clean_up", 0);
        set("coor/x", -10690);
	set("coor/y", 1960);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}