//  Room:  /d/luoyang/wanggate.c

inherit  ROOM;

void  create  ()
{
        set("short",  "大門");
        set("long",  @LONG
這裏是大名鼎鼎的洛陽金刀王家。但見房舍十分高大，硃紅漆的大
門，門上兩個大銅環，擦得晶光雪亮，門楣上有朱漆塗就的“金刀”二
字，八名壯漢垂手在大門外侍候。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "enter"  :  __DIR__"wangdayuan",
                "north"  :  __DIR__"wroad3",
        ]));
        set("objects",  ([  /*  sizeof()  ==  2  */
                __DIR__"npc/zhuanghan" : 2,
        ]));
        set("outdoors", "luoyang");
	set("coor/x", -7020);
	set("coor/y", 2170);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        if ( objectp(present("zhuang han", environment(me))) && dir == "enter")
           return notify_fail("壯漢攔住你説：你來洛陽金刀門撒野？快出去！\n");
        return ::valid_leave(me, dir);
}