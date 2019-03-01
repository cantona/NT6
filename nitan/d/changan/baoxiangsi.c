//Room: baoxiangsi.c

inherit ROOM;

void create ()
{
        set ("short", "寶象寺");
        set("long", @LONG
寶象寺規模宏大，房舍近千，別院處處。放眼所見，這裡盡是高
閣石壁，佛彩龍像，繞不一會，已然分不清來時的道路。但見那一尊
尊的石刻似乎都裂著嘴在向你嘿嘿而笑。
LONG );
        set("exits", 
        ([ //sizeof() == 2
                "north" : "/d/changan/qinglong1",
                "south" : "/d/changan/baodian",
        ]));
        set("objects", 
        ([ //sizeof() == 2
                "/d/changan/npc/monk" : 2,
        ]));

        set("coor/x", -10730);
	set("coor/y", 1900);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}