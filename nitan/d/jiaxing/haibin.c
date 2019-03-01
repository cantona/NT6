// Room: /d/jiaxing/haibin.c
// Last Modified by winder on Nov. 17 2000

inherit ROOM;

int do_jump(string arg);
int do_look(string arg);
int do_use(string arg);

void create()
{
        set("short", "海濱");
        set("long", @LONG
這裡是錢塘江的入海口。波濤洶湧，咆哮不息。海潮(tide)不斷地
撲面而來，拍在岸邊，濺起的水珠在半空飛舞，好象大雪紛紛一樣。
LONG
        );
        set("no_clean_up", 0);
        set("outdoors","jiaxing");

        set("exits", ([
                "west": __DIR__"jiangpan3.c",
        ]) );

        set("item_desc", ([
                "tide" : "海潮滾滾而來，似乎欲將天地吞沒。\n",
        ]) );

	set("coor/x", 1300);
	set("coor/y", -1860);
	set("coor/z", 0);
	setup();
}

/*
void init()
{
        add_action("do_jump", ({"jump", "tiao"}));
        add_action("do_use", "use");
        add_action("do_look", "look");
}
int do_use(string arg)
{
        object me = this_player();

        if (me->is_busy()) return notify_fail("你正忙著呢！\n");
        if( (arg == "boat" || arg == "chuan") && query_temp("thd_boat", me) )
        {
                delete_temp("thd_boat", me);
                write("你跳上小船，將船劃向桃花島。\n");
                write("海上正是順風，船借風勢，數日內便到達了。\n");
                me->move("/d/taohua/shore");
                return 1;
        }
        return 0;
}

int do_jump(string arg)
{
        object me = this_player();

        if (me->is_busy()) return notify_fail("你正忙著呢！\n");
        if (arg == "boat" || arg == "chuan")
                return do_use(arg);

        if (arg != "chao" && arg != "tide")
                return notify_fail("你要往哪裡跳？\n");

        if (me->query_dex() < 59)
                return notify_fail("你試圖跳進海潮裡，卻總覺得力不從心。\n");

        if (me->query_skill("dodge") < 80)
                return notify_fail("你試圖跳進海潮裡，卻發現自己的輕功修為還沒有達到這麼高的境界。\n");
        message_vision("$N聳身一躍，跳進了海潮中！\n", me);
        me->move("/d/taohua/tide");
        return 1;
}

int do_look(string arg)
{
        object me = this_player();

        if( query("family/master_name", me) != "黃藥師" || me->query_skill("count",1)<50 )
        {
                set("long", @LONG
這裡是錢塘江的入海口。波濤洶湧，咆哮不息。海潮(tide)不斷地
撲面而來，拍在岸邊，濺起的水珠在半空飛舞，好象大雪紛紛一樣。
LONG
);
                me->look(arg);
        }
        else
        {
                if (!arg)
                {
                        set("long", @LONG
這裡是錢塘江的入海口。波濤洶湧，咆哮不息。海潮(tide)不斷地
撲面而來，拍在岸邊，濺起的水珠在半空飛舞，好象大雪紛紛一樣。遠
處有一塊巨巖(rock)，後面似乎隱藏著什麼。
LONG
);
                        me->look(arg);
                }
                else if (arg == "rock" || arg == "yanshi" || arg == "juyan")
                {
                        write("一塊巨巖，後面隱約露出一條船(boat)的船首來。\n");
                        set_temp("thd_boat", 1, me);
                        return 1;
                }
                else if( (arg == "boat" || arg == "chuan") && query_temp("thd_boat", me) )
                {
                        write("一條藏著的小船，不精通陰陽八卦是很難發現的。\n");
                        return 1;
                }
        }
}
*/