// Room: /d/quanzhou/enyuanxiang.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "恩怨巷");
        set("long", @LONG
走進巷中，就感到一股肅殺之氣瀰漫四周。巷旁一碑聳立，上書「
恩怨分明」四個大字，仔細一看，乃用指力刻劃而成！北面就是聞名天
下的擂台了。
LONG );
        set("outdoors", "quanzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "south" : __DIR__"eastroad2",
        ]));
	set("coor/x", -880);
	set("coor/y", -7660);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}