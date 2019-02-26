//Room: xiaojiadt.c

inherit ROOM;

void create()
{
        set("short", "蕭家大廳");
        set("long", @LONG
這間大廳很樸素，房中除了一個鐵箱之外，竟是既無傢俱，又無
擺設，只是牆上掛着一幅巨大的工筆畫，畫中一座大城，山環水繞，
還點綴有亭台樓閣、園林人物，看來是江南的一處名城。
LONG );
        set("exits", ([ /* sizeof() == 3 */
                "west" : "/d/changan/xiaojia-qianyuan",
                "north" : "/d/changan/xiaojia-pianting",
                "south" : "/d/changan/xiaojia-sleep"
        ]));
        set("objects", ([
                "/d/changan/npc/yuanwai" : 1,
        ]) );

        set("NONPC",1);
        set("coor/x", -10660);
	set("coor/y", 1910);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}