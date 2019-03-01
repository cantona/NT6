//Room: /d/dali/bijishan.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","碧雞山頂");
        set("long", @LONG
碧雞山坐在滇池的西岸上，與拓東城隔水相望。山勢高聳入雲，
山形有如公雞，漫山樹木蒼翠欲滴。此處乃是極頂，已達雲端，東眺
滇池一片汪洋，美不勝收。山下屬大理國的昆州。東西皆有下山之路。
LONG );
        set("objects", ([
           "/d/dali/npc/youke": 1,
        ]));
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "westdown"  : "/d/dali/qingxi",
            "eastdown"  : "/d/dali/yanan2",
        ]));
	set("coor/x", -19100);
	set("coor/y", -6880);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}