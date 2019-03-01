// Room: /d/jiaxing/jnroad4.c
// Last Modified by winder on Nov. 17 2000

inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
你走在江南的一條山路上，到處鶯飛草長。時值春日，路旁的山坡
上開滿了金黃色的油菜花。北面是江南名城嘉興。向南則進入福建武夷
山區。東面有一個供路人休息的小茶亭。
LONG );
        set("exits", ([
                "north"   : __DIR__"jxnanmen",
                "west"    : __DIR__"jnroad3",
                "southup" : "/d/yanping/xianxialing",
                "east"    : __DIR__"chating",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "jiangnan");
	set("coor/x", 1190);
	set("coor/y", -1790);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}