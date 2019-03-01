//Room: /d/dali/jingzhuang5.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","第五層");
        set("long", @LONG
球狀，無人像，四角掛有黃銅鑄靈鷲。四只靈鷲，口角噙有一枚
兩頭有孔的銅管，管內有金屬簧片，鷲口、鷲頸、鷲腹皆是空心。每
當勁風吹來，經鷲嘴內銅管，在鷲腹內空氣回旋盪揚，便發出悅耳的
鳴叫。不但憑增靈鷲的神密氣氛，亦可想見能工巧匠們的精湛技藝。
LONG );
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "up"    : "/d/dali/jingzhuang6",
            "down"  : "/d/dali/jingzhuang4",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19091);
	set("coor/y", -6871);
	set("coor/z", 49);
	setup();
        replace_program(ROOM);
}