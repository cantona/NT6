// liangong.c

inherit ROOM;

void create()
{
        set("short", "練武場");
        set("long", @LONG
這裏是一個不太的院子，是鍛鍊武功的地方。段家雖然世代皇族，
但是和江湖卻有着割不斷的聯繫。因此段家子孫有無數武道高手，這
裏就是他們練功的場地。東南就是王府內院，北面則通往另一個練武
場。
LONG );
        set("exits", ([
                "north" : "/d/dali/liangong2",
                "southeast" : "/d/dali/yongdao1",
        ]));
        set("objects", ([
                "/clone/npc/mu-ren": 4,
        ]));
	set("coor/x", -19111);
	set("coor/y", -6821);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}