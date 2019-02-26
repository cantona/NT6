//Room: /d/dali/xiaodao.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","林蔭小道");
        set("long", @LONG
沿林蔭小道曲折前行約四十公尺，只見古樹林立，濃廕庇天，一
方清泉嵌於其間，底鋪青石，泉水明澈，常有人擲錢幣於池中，觀其
緩緩旋落，陽光從樹頂篩下，池底銀光閃爍，倍感泉水清冽。池邊距
地面約二三尺的地方有一粗可合抱的樹幹，伸過泉上，池旁建有小亭，
小坐生涼，十分清幽。 
LONG );
        set("objects", ([
           "/d/dali/npc/maque": 1,
                "/clone/npc/walker"  : 1,
        ]));
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "northup"  : "/d/dali/qingxi",
            "south"    : "/d/dali/heilongling",
            "west"     : "/d/dali/hudiequan",
        ]));
	set("coor/x", -19110);
	set("coor/y", -6890);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}