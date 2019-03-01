// liangong.c

inherit ROOM;

void create()
{
        set("short", "練武場");
        set("long", @LONG
這裡是一個不太的院子，是鍛煉武功的地方。段家雖然世代皇族，
但是和江湖卻有著割不斷的聯系。因此段家子孫有無數武道高手，這
裡就是他們練功的場地。東南就是王府內院，北面則通往另一個練武
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