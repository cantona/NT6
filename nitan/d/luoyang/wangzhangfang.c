//  Room:  /d/luoyang/wangzhangfang.c

inherit  ROOM;

void  create  ()
{
        set("short",  "帳房");
        set("long",  @LONG
這裏是王家的賬房。滿四壁都是帳簿架，堆滿了陳年老帳，更有一
些帳簿堆在地下。一個師爺一臉酒氣，正在收拾破爛帳。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "south"  :  __DIR__"wangxiangfang",
                "east"   :  __DIR__"wangdatang",
        ]));
        set("objects",  ([  /*  sizeof()  ==  2  */
                __DIR__"npc/yi" : 1,
        ]));
	set("coor/x", -7031);
	set("coor/y", 2159);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}