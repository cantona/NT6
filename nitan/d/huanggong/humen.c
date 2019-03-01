// Room: /d/huanggong/humen.c

inherit ROOM;

void create()
{
        set("short", "白虎門");
        set("long", @LONG
白虎門, 皇城西門. 由此西通狩場, 東往內城. 少有人來人往, 但
依舊森嚴戒備. 前些年正是在這發生民亂, 險些讓暴民闖進了內宮, 所
以, 這兒的守備之嚴較其他各城門有過之而無不及.
LONG
        );
        set("outdoors", "huanggong");
        set("exits", ([ /* sizeof() == 2 */
                "west" : __DIR__"dadao",
                "east" : __DIR__"xihuamen",
        ]));
        set("no_clean_up", 0);

        set("objects", ([
                __DIR__"npc/yulin" : 2,
        ]));
	set("coor/x", -2850);
	set("coor/y", 7721);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}