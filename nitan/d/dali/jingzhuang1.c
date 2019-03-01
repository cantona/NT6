//Room: /d/dali/jingzhuang1.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","第一層");
        set("long", @LONG
雕四大天王像，高約四尺，批甲戴胄，手持斧鉞，威嚴莊重。三
人足踏鬼奴。一鬼奴肌肉暴起，右手挽蛇，蛇嘴正觸鬼奴下□；另倆
鬼奴戴鐐。一天神足下三人，中間一人正以雙手各托天王一足。天王
之間遍刻梵文佛經。
LONG );
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "up"    : "/d/dali/jingzhuang2",
            "out"   : "/d/dali/jinzhihe",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19091);
	set("coor/y", -6871);
	set("coor/z", 9);
	setup();
        replace_program(ROOM);
}