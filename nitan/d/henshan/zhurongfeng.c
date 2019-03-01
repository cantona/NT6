#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "祝融峰");
        set("long",
"祝融峰之高為衡山大四絕之首。在此俯瞰群峰，盡收眼底。\n"
"東望湘江，南及五嶺，北瞰洞庭，西視雪山。唐朝杜甫望岳詩"
"\n中有「" HIW "祝融五峰尊，峰峰次低昂" NOR "」。著名詩人韓"
"癒亦以「" HIW "祝融\n萬丈拔地起，欲見不見輕煙裡" NOR "」"
"極言其高。\n");

        set("exits", ([
                "eastdown"   : __DIR__"shanlu004",
        ]));

        set("objects", ([
                CLASS_D("henshan") + "/mo" : 1,
        ]));    

        set("no_clean_up", 0);

	set("coor/x", -6960);
	set("coor/y", -5490);
	set("coor/z", 70);
	setup();
        replace_program(ROOM);
}