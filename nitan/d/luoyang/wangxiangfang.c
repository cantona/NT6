//  Room:  /d/luoyang/wangxiangfang.c

inherit  ROOM;

void  create  ()
{
        set("short",  "廂房");
        set("long",  @LONG
這裏是王家的廂房。進門處是一扇雕花門，門扇上鏤空雕着三國故
事：一邊是千里走單騎，正合王家絕技。一邊是定軍山老黃忠，也是個
刀顯威風的場面。房內一張大牀，堆着枕蓆，甚是精潔。房角小几上擺
着茶具，壁上掛着一口單刀。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "north"  :  __DIR__"wangzhangfang",
                "east"   :  __DIR__"wanghuating",
        ]));
        set("objects",  ([  /*  sizeof()  ==  2  */
                __DIR__"npc/wangjiajun" : 1,
        ]));
	set("coor/x", -7031);
	set("coor/y", 2149);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}