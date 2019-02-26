// Room: /d/suzhou/road6.c
// Last Modified by Winder on May. 15 2001
inherit ROOM;

void create()
{
        set("short", "湖畔大道");
        set("long", @LONG
你走在一條青石大道上，往北遙看，靈巖山展現在你的面前。從這
裏向南遙看太湖景色，煙波浩森，氣象萬千。放棹太湖之上，聳嶂疊翠，
千頃一壁，倒影楚楚；黿頭眺望，羣山來去，島嶼浮水；蒼茫水面，魚
帆千張；湖中有湖，水天相接。若趕上傍晚彩霞滿天時，湖面金波頃流，
令人心曠神怡。
LONG);
        set("outdoors", "suzhou");
        set("exits",([
                "north" : __DIR__"road7",
                "south" : __DIR__"road5",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 1110);
	set("coor/y", -1160);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}