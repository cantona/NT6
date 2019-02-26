// Room: /d/chengdu/ruin2.c
// Last Modifyed by Winder on Jan. 4 2002

inherit ROOM;

void create()
{
        set("short", "丐幫分舵");
        set("long", @LONG
這裏是一棟破舊大宅的正廳，北面的牆壁跟屋頂已經整個坍塌了，
涼颼颼的冷風從北邊的缺口直灌進來，另你覺得意外的是，這裏清掃得
相當整潔，地上用乾草整整齊齊地鋪著一個牀(bed)。
LONG        );
        set("exits", ([
                "east": __DIR__"ruin1"
        ]));
        set("item_desc", ([
                "bed"  : "你低頭一看，發現牀鋪底下居然有個深幽的洞(dong)！\n",
                "dong" : "這是一個黑乎乎的洞口，不知道里面有多深。\n",
        ]));
        set("objects", ([
                CLASS_D("gaibang")+"/obj/jiaohuaji" : 1,
                FOOD_DIR"jitui" : 1,
                FOOD_DIR"jiudai": 1,
        ]));
        set("coor/x", -15260);
	set("coor/y", -1840);
	set("coor/z", 0);
	setup();
}

void init()
{
        add_action("do_enter", "enter");
        add_action("do_enter", "zuan");
}

int do_enter(string arg)
{
        object me = this_player();
        mapping fam;

        if( !arg || arg=="" ) return 0;
        if( arg=="dong" )
        {
                if( (fam=query("family", me)) && fam["family_name"] == "丐幫" )
                {
                        message("vision", me->name() + "運起丐幫縮骨功，一彎腰往洞裏鑽了進去。\n", environment(me), ({me}) );
                        me->move("/d/gaibang/undercd");
                        message("vision", me->name() + "從洞裏走了進來。\n", environment(me), ({me}) );
                        return 1;
                }
                else 
                        return notify_fail("這麼小的洞，你鑽得進去嗎？\n");
        }
}