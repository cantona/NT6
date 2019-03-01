//  Room:  /d/changan/road1.c

inherit  ROOM;

void  create  ()
{
        set("short",  "關洛道");
        set("long",  @LONG
這是一條寬闊筆直的官道，足可容得下十馬並馳。往東通向六朝古
都，天心之麓的洛陽城。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "east"  :  "/d/luoyang/guandaow1",
                "west"  :  __DIR__"hanguguan",
        ]));
        set("objects",  ([  /*  sizeof()  ==  2  */
                "/d/mingjiao/yuan/zhaomin" : 1,
                "/d/mingjiao/yuan/zhao1" : 1,
                "/d/mingjiao/yuan/qian2" : 1,
                "/d/mingjiao/yuan/sun3" : 1,
                "/d/mingjiao/yuan/li4" : 1,
        ]));
        set("outdoors", "guanzhong");
        set("coor/x", -10600);
	set("coor/y", 1920);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}