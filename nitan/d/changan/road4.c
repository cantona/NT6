//  Room:  /d/changan/road4.c

inherit  ROOM;

void  create  ()
{
        set("short",  "大官道");
        set("long",  @LONG
這是一條寬闊筆直的官道，足可容得下十馬並馳。往東南通向函谷
關，往西則直達長安城。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "north"      :  __DIR__"boshulin1",
                "west"      :  __DIR__"baqiao",
                "southeast" :  __DIR__"road3",
        ]));
        set("outdoors", "guanzhong");
        set("no_clean_up", 0);
        set("coor/x", -10650);
	set("coor/y", 1930);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}