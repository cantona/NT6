//Room: /d/dali/zhulou3.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","大竹樓");
        set("long",@LONG
這是一座普通樣式的台夷竹樓，建在魯望鎮中心，與四周其它竹
樓比佔地廣大得多，也特別高大，似有三層，正是普麼部的祭祀大屋。
此處下層也不養牲畜，打掃得乾乾淨淨。寬大的竹梯直通上層。
LONG);
        set("exits",([ /* sizeof() == 1 */
            "south"  : __DIR__"luwang",
            "up"     : __DIR__"zhulou4",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19120);
	set("coor/y", -6950);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}