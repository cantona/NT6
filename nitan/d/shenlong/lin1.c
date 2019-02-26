inherit DEMONROOM;

void create()
{
        set("short", "灌木林");
        set("long",@LONG
這是一片灌木林。你沒有想到這樣一個孤島上竟有這樣大一片灌
木林(bush)，不由感到非常吃驚。前面根本沒有路，四周的密林中長
滿了雜草。
LONG);

	set("exits", ([
	    "south" : __DIR__"haitan",
		"east"  : __DIR__"lin1.1", 
	]));

	set("item_desc", ([
	    "bush" : "這片灌木林太深了,要想過去恐怕只有砍出一條路了(kan)。\n",
	]));
		
		set("n_time", 30); 
		set("n_npc", 1); 
                set("n_max_npc", 10);
		set("s_npc", "/clone/dream_npc/shenlongdao/snake/snake");

        set("outdoors", "shenlong");
        setup();
}

void init()
{
        add_action("do_kan", "kan");
}

int do_kan(string arg)
{
        object weapon;
        object me;

        if (arg != "bush")
                return notify_fail("你要砍什麼？\n" ) ;

        me = this_player();
	if( !objectp(weapon=query_temp("weapon", me)) )
		return notify_fail("不用武器恐怕不行吧！\n");

        if( query("skill_type", weapon) != "blade" && 
            query("skill_type", weapon) != "sword" )
                return notify_fail(weapon->name() + "也能用來砍東西？\n");

	message_vision("$N抽出兵刃，對着灌木叢就是一陣亂砍。\n", me);

        if( query("neili", me)>100 )
        {
                set("exits/north", __DIR__"lin2");
                message_vision("$N累得氣喘吁吁,終於砍出一條小路。\n", me);
                addn("neili", -50, me);
                remove_call_out("close");
                call_out("close", 20);
	} else	
	{
                message_vision("$N累得氣喘吁吁,也沒砍開一條路來。\n", me);
                set("neili", 0, me);
	}
        return 1;
}

void close()
{
        message("vision", "灌木叢漸漸合攏起來,終於又恢復了原狀。\n",
                this_object());
        delete("exits/north");
}
