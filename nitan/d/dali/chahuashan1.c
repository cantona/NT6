//Room: /d/dali/chahuashan1.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","茶花山");
        set("long", @LONG
你站在一座小山西面腳下，大理盛產茶花，好品種的茶花遍地生
長，東面的這片小山林也長滿了好茶。西邊不遠就是大理城的北門了。
LONG );
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "west"      : "/d/dali/northgate",
            "eastup"    : "/d/dali/chahuashan2",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19150);
	set("coor/y", -6860);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}