//Room: /d/dali/dalinorth.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","大理城北");
        set("long", @LONG
這裏是個岔路口。南邊就是大理城的北門了，道路從這裏分岔，
北去可到太和城，西北通向下關城，也通蒼山，是去遊蒼山和崇聖寺
的必經之路。
LONG );
        set("outdoors", "dalin");
        set("exits",([ /* sizeof() == 1 */
            "north"      : "/d/dali/taihecheng",
            "south"      : "/d/dali/northgate",
            "northwest"  : "/d/dali/ershuiqiao",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19160);
	set("coor/y", -6850);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}