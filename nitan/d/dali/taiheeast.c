//Room: /d/dali/taiheeast.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","太和東街");
        set("long", @LONG
太和街連貫陽苜咩城南北門，延伸三裡，是城內主要街道。街面
是由碗口大的彩色石塊舖成，青蘭紫綠，煞是好看。城內居民族裔繁
雜，習俗各異，飲食穿著無不異于中原。北面是薛氏成衣舖，南面是
藥舖。
LONG );
        set("outdoors", "dali");
        set("exits",([ /* sizeof() == 1 */
            "west"   : "/d/dali/taihejiekou",
            "east"   : "/d/dali/stoneshop",
            "north"  : "/d/dali/garments",
            "south"  : "/d/dali/yaoshop",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19120);
	set("coor/y", -6880);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}