// Room: /d/jiaxing/tieqiang.c
// Last Modified by winder on Nov. 17 2000

inherit ROOM;

void create()
{
        set("short", "鐵槍廟");
        set("long", @LONG
這鐵槍廟祀奉的是五代時名將鐵槍王彥章。廟旁有座高塔，塔頂羣
鴉世代為巢，當地鄉民傳説鐵槍廟的烏鴉是神兵神將，向來不敢侵犯，
以致生養繁殖，越來越多。案桌下有個小洞(dong)。
LONG );
        set("exits", ([
                "west"  : __DIR__"jxnanmen",
                "north" : __DIR__"nanhu",
        ]));
        set("item_desc", ([
            "dong" : "一個在案桌下隱藏得很好的土洞。\n",
        ]));
        set("objects", ([
                __DIR__"npc/wuya": 4
        ]));
//        set("no_clean_up", 0);
        set("outdoors", "jiaxing");
	set("coor/x", 1200);
	set("coor/y", -1780);
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
        object me;
        mapping fam;

        me = this_player();
        if( !arg || arg=="" ) return 0;
        if( arg=="dong" )
        {
                if( (fam=query("family", me)) && fam["family_name"] == "丐幫" )
                {
                        message("vision",
                                me->name() + "運起丐幫縮骨功，一彎腰往洞裏鑽了進去。\n",
                                environment(me), ({me}) );
                        me->move("/d/gaibang/underqz");
                        message("vision",
                                me->name() + "從洞裏走了進來。\n",
                                environment(me), ({me}) );
                        return 1;
                }
                else 
                        return notify_fail("這麼小的洞，你鑽得進去嗎？\n");
        }
}