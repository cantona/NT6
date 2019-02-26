//Room: /d/dali/dalangan1.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","大杆欄");
        set("long",@LONG
依着一棵大榕樹，擺夷人在此建了一座相當大的杆欄。下層這裏
有一滿圈的十幾頭牛羊。旁邊的樓梯修得頗寬。看來這裏是本地的體
麪人家。
LONG);
        set("objects", ([
           __DIR__"npc/shanyang": 3,
           __DIR__"npc/cow": 2,
        ]));
        set("outdoors", "dalie");
        set("exits",([ /* sizeof() == 1 */
            "west"  : __DIR__"nongtian4",
            "up"    : __DIR__"dalangan2",
        ]));
	set("coor/x", -19000);
	set("coor/y", -6870);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}