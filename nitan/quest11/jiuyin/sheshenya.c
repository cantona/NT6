// sheshenya.c
// 捨身崖

// Modified by mxzhao 2004/04/11 for do_jump function

inherit ROOM;
#include <ansi.h>
void create()
{
	set("short",MAG "睹光台捨身崖" NOR);
	set("long",@long
從卧雲庵出來，這裏是看日出、雲海、佛光、神燈之地。台下深崖萬丈，
陡徹無底，雲遮霧掩。極目四望，數百里外的大小雪山皆歷歷在目。因為這裏
至高至潔，至險至奇，又至美至幻，常有人在這裏投身雲海，舍此肉身塵世。
long);
	set("outdoors", "峨嵋山");
	set("exits",([
		"east" : __DIR__"duguangtai",
	]));
	
	setup();
}

void init()
{

	add_action("do_jump", "tiao");	// 修改 命令 jump
	add_action("do_look", "look");
}

int do_look()
{
	object me = this_player();
	mixed *local;
	local = localtime(time() * 60);
	if(local[2] < 4 || local[2] >= 21)
	{
		write(BLU"初見金頂下黑黝黝一片，忽而閃現出一點、兩點帶藍色的亮光，這種亮點\n"
			"越來越多，轉眼便佈滿山谷，有的如流螢飄飛，有的如繁星閃爍。\n"NOR, me);
	}
	if(local[2] >= 4 && local[2] < 8)
	{
		write(HIR"啟明星剛剛升起，一道道微白的光在東方雲層閃現，一輪紅日托地跳出，\n"
			"大千世界頓時在彩陽映照下呈現出無限生機。\n"NOR, me);
	}
	if(local[2] >= 8 && local[2] <= 13)
	{
		write(HIC"金頂雲海，迷迷茫茫，籠罩四野，遠接天際。雲海輕蕩時，你在金頂，腳\n"
			"踏白雲，大有飄飄欲仙之感；當雲濤迅猛湧來時，整個金頂都似在向前浮動，\n"
			"令人有乘舟欲風之意。\n"NOR, me);
	}
	if(local[2] > 13 && local[2] < 16)
	{
		write(YEL"日麗風靜，雲海平鋪，美麗以極。陽光從你背面斜射下來，在捨身崖下形\n"
			"成彩色光環，你見到自己的身影清晰地出現在銀色世界上。『光環隨人動，\n"
			"人影在環中』，這就是奇妙的　※※※※※※※佛光※※※※※※※　。\n"
			"這裏有一種使人獻身的超人力量，令你不禁想要在此投身雲海，擺脱人世\n"
			"的俗累，與天相接。\n"NOR, me);
	}
	if(local[2] >= 16 && local[2] < 21)
	{
		write(HIC"金頂雲海，迷迷茫茫，籠罩四野，遠接天際。雲海輕蕩時，你在金頂，腳\n"
			"踏白雲，大有飄飄欲仙之感；當雲濤迅猛湧來時，整個金頂都似在向前浮動，\n"
			"令人有乘舟欲風之意。\n"NOR, me);
	}
}

int do_jump(string arg)
{
	object me = this_player();

	mixed *local = localtime(time() * 60);
	
	if (me->is_busy() || me->is_fighting())
	{
		return notify_fail("你正忙着哪！\n");
	}
	
	if(arg != "cliff")
	{
		return notify_fail("你要往哪裏跳？\n");
	}
	
	if (me->query("quest/jiuyin2/fail") >= 3 
		&& me->query("registered") < 3)
	{
		return notify_fail("你再也不敢拿生命開玩笑了。\n");
	}
	
	if ( me->query("quest/jiuyin2/fail") 
                >= (int)((me->query("combat_exp") - 1000000)/100000) 
		|| (time() - me->query("quest/jiuyin2/time")) < 86400)
	{
		return notify_fail("你猶豫了半天，想想還是算了吧。\n");
	}
	
	{
		object *ob = deep_inventory(me);
		int i = sizeof(ob);

		while (i--)
		{
			if (userp(ob[i]))
			{
				ob[i]->move(this_object());
			}
		}

		message_vision(HIR"$N縱身跳下捨身崖。\n"NOR, me);
		me->move(__DIR__"bankong");

		if(local[2] > 13 && local[2] < 15 )
		{
			if (random(me->query("kar")) > 15
				&& (int)me->query_dex(1) > 32 )
			{
				call_out("do_wait", 2, me);
			}
			else if ( me->query("hanshui_food") && random(3) == 1  )
			{
				call_out("do_wait", 2, me);
			}
			else 
			{
				call_out("do_wait1", 2, me);
			}

			return 1;
		}

		call_out("do_wait2", 2, me);
		return 1;
	}
}

void do_wait(object me)
{
	tell_object(me, HIR"你只覺得耳邊呼呼風聲作響，身體飛快的象下綴去....\n"NOR);
	tell_object(me, "突然你被什麼東西阻擋了一下........\n");
        me->move(__DIR__"wanniansong");
	me->set("quest/jiuyin2/emeijump", 1);
	log_file("quest/jiuyin",sprintf("%-18s娥眉九陰部分失敗%s次後從捨身崖成功跳下，福：%d。\n",
		me->name(1)+"("+capitalize(getuid(me))+")",
		chinese_number(me->query("quest/jiuyin2/fail")), me->query("kar")), me);
//	me->unconcious();
}

void do_wait1(object me)
{
	object *ob, *inv;
	int i, j;
	ob = all_inventory(environment(me));
	tell_object(me, HIR"你只覺得耳邊呼呼風聲作響，身體飛快的象下綴去....\n"NOR);
        me->move(__DIR__"shuitan");
	me->set("water", 666); 
	me->add("quest/jiuyin2/fail",1);
	me->set("quest/jiuyin2/time", time());
	log_file("quest/jiuyin",sprintf("%-18s從捨身崖往下跳失敗，娥眉九陰部分失敗%s次。\n",
		me->name(1)+"("+capitalize(getuid(me))+")",chinese_number(me->query("quest/jiuyin2/fail"))), me);
	tell_object(me, HIC"只聽得撲通一聲，你掉進了一個大水潭中，咕嘟咕嘟喝了好幾口水....\n"NOR);
        for(i=0; i<sizeof(ob); i++) {
		inv = all_inventory(ob[i]);
		for (j = 0; j < sizeof(inv); j++)
		if (!inv[j]->query_autoload()) destruct(inv[j]);
		ob[i]->unconcious();
	}
}

void do_wait2(object me)
{
        object tmp;
        object *ob;
        int i;
	tell_object(me, HIR"你只覺得耳邊呼呼風聲作響，身體飛快的象下綴去....\n"NOR);
	tell_object(me, HIW"你只覺得世界正在離你遠去........\n"NOR);
        me->move(__DIR__"shuitan");
        me->set_temp("last_damage_from","摔下山崖跌");
        me->add("quest/jiuyin2/fail", 1);
        me->set("quest/jiuyin2/time", time());
	log_file("quest/jiuyin",sprintf("%-18s從捨身崖往下跳失敗，死，娥眉九陰部分失敗%s次。\n",
		me->name(1)+"("+capitalize(getuid(me))+")",chinese_number(me->query("quest/jiuyin2/fail"))), me);
        me->unconcious();
        me->die();
        if (tmp = present("corpse", this_object())) {
		ob = deep_inventory(tmp);
		i = sizeof(ob);
		while (i--) if (userp(ob[i])){
			ob[i]->move(this_object());
			ob[i]->set_temp("last_damage_from","摔下山崖跌");
			ob[i]->die();
		}
		destruct(tmp);
		if (me) tell_room(this_object(), me->name()+"的屍骨都找不到了。\n");
	}
}
