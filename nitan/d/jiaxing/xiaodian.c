// This program is a part of NT MudLIB

inherit ROOM;

int do_move(string);
int do_turn(string);

void create()
{
        set("short", "小酒店");
        set("long", @LONG
這是一家已經廢棄了的小酒店，櫃枱上積滿了灰，一個角落裏堆着
一大堆乾草，旁邊斜躺着一個大鐵叉；櫃枱後的櫥架上凌亂地放着幾摞
破舊的青花瓷碗(wan)。
LONG
        );

        set("item_desc", ([
                "wan"      : "一堆很凌亂地散放着的碗。\n",
                "bowl"     : "一堆很凌亂地散放着的碗。\n",
                "tiewan"   : "一隻奇怪的碗，好像是固定在了架子上。\n",
                "ironbowl" : "一隻奇怪的碗，好像是固定在了架子上。\n",
        ]) );

        set("exits", ([
                "north" : __DIR__"njroad1",
        ]));

        set("objects", ([
                //__DIR__"npc/shagu": 1,
                CLASS_D("taohua") + "/qusan" : 1
        ]));

	set("coor/x", 1250);
	set("coor/y", -1830);
	set("coor/z", 0);
	setup();
}

void init()
{
        add_action("do_move","move");
        add_action("do_move","yi");
        add_action("do_turn","turn");
        add_action("do_turn","zhuan");
}

int do_move(string arg)
{
        object me = this_player();

        if (me->is_busy() || me->is_fighting())
                return notify_fail("你正忙着呢！\n");
        if (arg == "wan" || arg == "bowl")
        {
                write( "你將架子上的碗使勁地摔到地上去，卻發現有一隻碗竟然拿不起來。仔細一看，才發現這是一隻鐵碗(tiewan)！\n");
                set_temp("mishi_temp", 1, me);
                return 1;
        }
        return notify_fail("你要搬動什麼？\n");
}

int do_turn(string arg)
{
        int temp;
        object me = this_player();

        if (me->is_busy() || me->is_fighting())
                return notify_fail("你正忙着呢！\n");
        if (arg == "tiewan left" || arg == "tiewan zuo")
        {
                temp=query_temp("mishi_temp", me);
                if (!temp) return 0;
                if (temp < 4) temp++;
                else temp = 1;
                write("你將鐵碗用勁地向左扳動，發出了“咯吱”的聲音。\n");
                set_temp("mishi_temp", temp, me);
                return 1;
        }
        if (arg == "tiewan right" || arg == "tiewan you")
        {
                temp=query_temp("mishi_temp", me);
                if (!temp) return 0;
                if (temp > 3) temp++;
                else temp = 1;
                write("你將鐵碗用勁地向右扳動，發出了“咯吱”的聲音。\n");
                if (temp == 7)
                {
                        write( "只聽“喀啦”一聲巨響，你的眼前出現了一道門。你毫不猶豫的走了進去。\n");
                        message("vision","櫥架後面忽然現出一道暗門，" + me->name() + "舉步走了進去，櫥架吱呀呀地又關上了。\n", this_object(), me);
                        delete_temp("mishi_temp", me);
                        me->move(__DIR__"mishi");
                        message("vision", me->name() + "打開暗門，走了進來。\n", environment(me), me);
                }
                else set_temp("mishi_temp", temp, me);
                return 1;
        }
        return notify_fail("你要做什麼？\n");
}