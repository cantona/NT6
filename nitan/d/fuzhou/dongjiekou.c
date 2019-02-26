// Room: /d/fuzhou/dongjiekou.c
// may. 12 1998 Java

inherit ROOM;

void create()
{
        set("short", "東街口");
        set("long", @LONG
這裏是福州的中心。向東通往鼓山，向南經泉州出海可去台灣，北
去屏山，向西經延平府直達中原。街邊沉沉鬱鬱的都是榕樹，福州又稱
“榕城”即以其遍地植榕而名。
    街上幾個混混嬉皮笑臉地調戲過往行人。
LONG );

        set("exits", ([
                "south"   : __DIR__"nandajie",
                "north"   : __DIR__"beidajie",
                "east"    : __DIR__"dongdajie",
                "west"    : __DIR__"xidajie1",
        ]));
        set("objects", ([
                "/d/city/npc/liumangtou" : 1,
                "/d/city/npc/liumang" : 3,
        ]));
        set("outdoors", "fuzhou");
	set("coor/x", -80);
	set("coor/y", -6180);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}