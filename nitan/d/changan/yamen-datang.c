//Room: yamen-datang.c

inherit ROOM;

void create ()
{
        set ("short", "長安府大堂");
        set("long", @LONG
長安府大堂之上有一種威嚴之勢，不由讓你心驚膽顫。前方一張
紅木大桌，後面坐著知府大人。上有一幅大匾，寫著"廉明清正"四個
燙金大字。桌旁站立著一位老師爺。
LONG );
        set("exits", 
        ([ //sizeof() == 1
                "north" : "/d/changan/yamen",
        ]));
        set("objects", 
        ([ //sizeof() == 2
                "/d/changan/npc/zhifu" : 1,
                "/d/changan/npc/shiye" : 1,
        ]));

        set("coor/x", -10710);
	set("coor/y", 1890);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}