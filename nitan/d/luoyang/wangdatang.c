//  Room:  /d/luoyang/wangdatang.c

inherit  ROOM;

void  create  ()
{
        set("short",  "大堂");
        set("long",  @LONG
一進大堂門，只見樑上懸著一塊黑漆大匾，寫著“見義勇為”四個
金字，下面落款是河南省的巡撫某人。看來王家的勢力非只武功上的名
聲而來的。這裡也是王家迎賓歡宴的地方，檐下欄邊，均裝飾的十分華
貴。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "south"  :  __DIR__"wanghuating",
                "north"  :  __DIR__"wangdayuan",
                "west"   :  __DIR__"wangzhangfang",
        ]));
        set("objects",  ([  /*  sizeof()  ==  2  */
                __DIR__"npc/wang" : 1,
        ]));
	set("coor/x", -7021);
	set("coor/y", 2159);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}