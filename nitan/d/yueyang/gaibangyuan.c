// Room: /d/yueyang/gaibangyuan.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "大院");
        set("long", @LONG
院子裏很是破敗，鋪地的青磚處處開裂，圍牆的瓦片也是殘缺不全
的。丐幫威鎮天下，總舵卻如此不起眼，也正是丐兒本色。南面是一扇
大門，北邊的大屋黑咕隆咚的。東西兩廂的房間窗户盡是蜘蛛網，地上
鋪着一把把的茅草，看來是丐幫人眾休息場所。院子中央是一眼井台長
滿青苔的古井(jing)，井壁倒是很光滑，似乎常有人在井中出入。
LONG );
        set("outdoors", "yueyang");
        set("exits", ([
                "north" : __DIR__"gaibangtang",
                "south" : __DIR__"gaibanggate",
        ]));
        set("item_desc", ([
                "jing"  : "一口滿是水光的深井。\n",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -6210);
	set("coor/y", -2990);
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

        if( arg=="jing" )
        {
                if( (fam=query("family", me)) && fam["family_name"] == "丐幫" )
                {
                        message("vision", me->name() + "運起丐幫縮骨功，一彎腰往井裏跳了下去。\n", environment(me), ({me}) );
                        me->move("/d/gaibang/underyy");
                        message("vision", me->name() + "從井裏走了進來。\n", environment(me), ({me}) );
                        return 1;
                }
                else return notify_fail("這麼小的井，你鑽得進去嗎？\n");
        }
}        