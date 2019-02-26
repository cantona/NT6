// Room: /d/suzhou/xuanmiao.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "玄妙觀");
        set("long", @LONG
你一走進玄妙觀，看到觀中香火繚繞，香客眾多。大殿是重檐歇山
式，屋脊高十幾米，內有高大殿柱四十根。屋面坡度平緩，出檐較深，
斗拱疏朗宏大，殿內正中有磚砌須彌座，座上供奉着的三尊高十幾米的
泥塑三清金身像，法像莊嚴，神采奕奕，不失為道教雕塑中的精品。
LONG );
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "north"  : __DIR__"xidajie2",
        ]));
	set("coor/x", 1090);
	set("coor/y", -1070);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}