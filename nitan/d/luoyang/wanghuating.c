//  Room:  /d/luoyang/wanghuating.c

inherit  ROOM;

void  create  ()
{
        set("short",  "花廳");
        set("long",  @LONG
你走進王家花廳，才領會到在洛陽，怎樣才叫□紫嫣紅，什麼樣才
叫春色無邊。花廳中，小小花徑縱橫蜿蜒，草色連壁。花廳中央是個石
亭，那裡就是王家閒來講經論武之所。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "north"  :  __DIR__"wangdatang",
                "south"  :  __DIR__"wanglianwu",
                "west"   :  __DIR__"wangxiangfang",
        ]));
        set("objects",  ([  /*  sizeof()  ==  2  */
                __DIR__"npc/wangzhongqiang" : 1,
        ]));
        set("outdoors", "luoyang");
	set("coor/x", -7021);
	set("coor/y", 2149);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}