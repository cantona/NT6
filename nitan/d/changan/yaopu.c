//Room: yaopu.c

#include <ansi.h>

inherit ROOM;

void create ()
{
        set ("short", "回春堂藥鋪");
        set("long", @LONG
這是長安城一家剛剛開張不久的藥鋪，相傳原來的老闆是江湖中
最神祕的醫谷中的神醫，手段可知一二。藥鋪中的擺設也十分考究，
桌椅被勤快的夥計擦的乾乾淨淨。牆上掛滿了別人送來的謝匾(bian)。
LONG );
        set("item_desc", (["bian" : HIW" 妙手回春 \n\n"NOR, ]));
        set("exits", 
        ([ //sizeof() == 1
                "south" : "/d/changan/qixiang6",
        ]));
        set("objects", 
        ([ //sizeof() == 1
                "/d/changan/npc/doctor" : 1,
        ]));

        set("no_clean_up", 0);
        set("coor/x", -10690);
	set("coor/y", 1980);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}