//  Room:  /d/lanzhou/southgate.c

inherit  ROOM;

void  create  ()
{
        set("short",  "南門");
        set("long",  @LONG
這是蘭州南門，城牆剛修整過顯得氣勢雄偉。由於蘭州是軍事重鎮，
因此官兵們都打起十二分精神檢查來往行人。一條筆直的官道向南北兩
邊延伸。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "north" : __DIR__"road2",
                "south" : __DIR__"road1",
        ]));
        set("objects",  ([  /*  sizeof()  ==  2  */
                "/d/city/npc/wujiang": 1,
                "/d/city/npc/bing": 2,
                "/clone/npc/walker"  : 1,
        ]));
        set("outdoors", "lanzhou");
	set("coor/x", -15750);
	set("coor/y", 3790);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}