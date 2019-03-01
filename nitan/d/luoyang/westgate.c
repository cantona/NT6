//  Room:  /d/luoyang/westgate.c

inherit  ROOM;

void  create  ()
{
        set("short",  "西門");
        set("long",  @LONG
出了此門，就不在洛陽城的管轄范圍，進入長安的轄地，登上城樓
已可以隱隱看見函谷關的城樓了。西面是通往長安城的大官道，而東面
則是通向洛陽城中心的主要通道。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "west"  :  "/d/changan/road1",
                "east"  :  __DIR__"westroad",
        ]));
        set("objects",  ([  /*  sizeof()  ==  2  */
                "/d/city/npc/bing" : 2,
        ]));
        set("outdoors", "luoyang");
        set("coor/x", -700);
        set("coor/y", -10);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}

