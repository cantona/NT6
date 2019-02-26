//Room: /d/dali/tusimentang.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","門堂");
        set("long", @LONG
門堂以及其他一些附屬建築，如穀倉，廚房，堅獄，外有二米多
高重修的圍牆。主體建築是規模最大的議事廳，三層大屋系三重蟾歇
山頂幹欄式建築，長六十尺，寬四十有五，高三十尺。二樓是宣撫召
集大小頭領議會地點，也是審判室。
LONG );
        set("exits",([ /* sizeof() == 1 */
            "north"  : "/d/dali/tusihouting",
            "up"     : "/d/dali/tusiyishi",
            "out"    : "/d/dali/tusifu",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19141);
	set("coor/y", -6891);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}