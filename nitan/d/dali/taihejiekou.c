//Room: /d/dali/taihejiekou.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","太和街口");
        set("long", @LONG
太和街連貫陽苜咩城南北門，延伸三裡，是城內主要街道。街面
是由碗口大的彩色石塊舖成，青蘭紫綠，煞是好看。街上行人絡繹不
絕。大道兩邊遍植鬆柏，滿目蒼翠。城內居民族裔繁雜，習俗各異，
飲食穿著無不異于中原。太學生們的朗朗之聲透室可聞。北面出城門
有官道通中原。
LONG );
        set("outdoors", "dali");
        set("exits",([ /* sizeof() == 1 */
            "north"   : "/d/dali/paifang",
            "south"   : "/d/dali/center",
            "east"    : "/d/dali/taiheeast",
            "west"    : "/d/dali/sheguta",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19130);
	set("coor/y", -6880);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}