//  Room:  /d/luoyang/wangxiaoyuan.c

inherit  ROOM;

void  create  ()
{
        set("short",  "小庭院");
        set("long",  @LONG
穿過掛著“幽徑天姿成獨秀，古園國色冠群芳”的角門，便是一個
十分秀巧的小園。園中小小的池塘中，淺淺的水裡，養著一些細細的遊
魚，也養護著池塘邊盛放的牡丹。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "east"   :  __DIR__"wangdayuan",
        ]));
        set("objects",  ([  /*  sizeof()  ==  2  */
                __DIR__"npc/obj/yaohuang" : random(2)+1,
                __DIR__"npc/obj/weizi" : random(2)+1,
        ]));
        set("outdoors", "luoyang");
	set("coor/x", -7031);
	set("coor/y", 2169);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}