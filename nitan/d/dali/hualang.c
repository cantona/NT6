//Room: /d/dali/hualang.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","花廊");
        set("long", @LONG
這裏是大理國皇宮的花廊，走廊下到處是奇花異草，往北是正殿，
往南是御花園，往西是御膳房，往東是偏殿。
LONG );
        set("objects", ([
           "/d/dali/npc/gongnu": 1,
        ]));
        set("outdoors", "daligong");
        set("exits",([ /* sizeof() == 1 */
            "south"  : "/d/dali/yuhuayuan",
            "north"  : "/d/dali/zhengdian",
            "east"   : "/d/dali/piandian",
            "west"   : "/d/dali/yushanfang",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19140);
	set("coor/y", -6830);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}