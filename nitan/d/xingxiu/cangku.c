// Room: /d/xingxiu/cangku.c
// Last Modified by winder on Feb. 28 2001

inherit ROOM;

void create()
{
        object fen1,fen2,fen3,fen4;
        
        set("short", "儲藏室");
        set("long", @LONG
這裡原來是一個長在山壁上的天然溶洞，是星宿派老巢的儲藏處。
從外面看只是一個開在石山上的普通天然石洞，然因地點隱秘而且洞中
空氣十分幹燥，星宿派弟子將這裡改造成了一個絕佳的儲藏庫。
LONG );
        set("exits", ([
            "out" : __DIR__"xxroad5",
        ]));
        set("objects", ([
                __DIR__"obj/yanwu" : 1,
                __DIR__"obj/hulu" : 2,
                __DIR__"obj/menghan_yao" : 1 + random(2),
                __DIR__"obj/xxqingxin-san" : 1,
                __DIR__"obj/shoutao" : 1 + random(2),
                "/clone/misc/muding" : 2 + random(2),
                "/clone/book/dujing_1"  : random(2),
        ]));

        set("coor/x", -50900);
        set("coor/y", 20120);
        set("coor/z", 30);
        setup();
        seteuid(getuid());
        fen1 = new("/clone/medicine/poison/duchongfen");
        fen2 = new("/clone/medicine/poison/bingpofen");
        fen3 = new("/clone/medicine/poison/honglinfen");
        fen4 = new("/clone/medicine/poison/yinlinfen");
        if (fen1->violate_unique()) destruct(fen1);
        else fen1->move(this_object());
        if (fen2->violate_unique()) destruct(fen2);
        else fen2->move(this_object());
        if (fen3->violate_unique()) destruct(fen3);
        else fen3->move(this_object());
        if (fen4->violate_unique()) destruct(fen4);
        else fen4->move(this_object());
        replace_program(ROOM);
}
