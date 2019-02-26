//Room: /d/dali/southgate.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","南門");
        set("long", @LONG
此間是大理國都大理城的南門，大理城實名陽苜咩城，南詔於初
建來，經歷代而至當今的段氏的『大理國』，皆以此城為都。城牆由
石塊和土壘成，高二丈五，厚達二丈。城下三兩個盔甲鮮明的軍士瞪
大了眼睛觀察着來來往往的行人，偶爾盤問幾個形跡可疑份子。
LONG );
        set("objects", ([
           "/d/dali/npc/jiang": 1,
           "/d/dali/npc/bing": 3,
                "/clone/npc/walker"  : 1,
        ]));
        set("outdoors", "dali");
        set("exits",([ /* sizeof() == 1 */
            "north"      : "/d/dali/shizilukou",
            "east"       : "/d/dali/xiaodao2",
            "south"      : "/d/dali/shuangheqiao",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19130);
	set("coor/y", -6910);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}