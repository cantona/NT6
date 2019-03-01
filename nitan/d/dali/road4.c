//Room: /d/dali/road4.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","大路");
        set("long",@LONG
一條貫通南北的大路，是由大理城往南邊疆土的官道。沿路向南
叢林愈發茂密，大片雨林覆蓋山嶺，此間地勢較平坦，大路筆直地連
接着北邊的大理城和南邊的喜州等城鎮。
LONG);
        set("outdoors", "dalis");
        set("exits",([ /* sizeof() == 1 */
            "north"      : __DIR__"shuangheqiao",
            "south"      : __DIR__"tianweijing",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19130);
	set("coor/y", -6930);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}