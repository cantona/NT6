//Room: /d/dali/wuding.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","武定鎮");
        set("long",@LONG
這裡是台夷分支盧鹿族羅蝥部的治府，羅蝥部除了這武定州外還
轄元謀、祿定兩鎮。此鎮不大，正處山中竹林深處，顯得格外清幽。
盧鹿族人的竹樓四散分布在竹林中。
LONG);
        set("objects", ([
           __DIR__"npc/guniang": 1,
                "/clone/npc/walker"  : 1,
        ]));
        set("outdoors", "dalis");
        set("exits",([ /* sizeof() == 1 */
            "north"      : __DIR__"zhulou1",
            "northeast"  : __DIR__"zhulin",
            "west"       : __DIR__"qingzhulin",
            "south"      : __DIR__"nongtian1",
        ]));
	set("coor/x", -19150);
	set("coor/y", -6970);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}