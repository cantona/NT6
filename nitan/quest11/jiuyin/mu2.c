// mu2.c
// 墓

inherit ROOM;
#include <ansi.h>
void create()
{
	set("short", "墓室");
	set("long",@long
這裡是郭襄墓下的墓室。墓室不大，正面是一具白玉石棺，旁邊放著一盞
長明燈。石棺一塵不染，看來經常有人進來打掃。
long);
	set("exits", ([
		"up" : __DIR__"mu",
	]));
	setup();
	set("count", 1);
}

void init()
{
	add_action("do_na", "na");
	add_action("do_move", "move");
	add_action("do_move", "open");
}

int do_move(string arg)
{
	object me, tmp;
	int dex;
	me = this_player();

	if (arg != "coffin" || !arg) 
		return notify_fail("你要幹什麼？\n");

	if (me->is_busy() || me->is_fighting()) 
		return notify_fail("你正忙著哪！\n");

	if ( me->query("combat_exp") < 1000000 ) return 0;
	if ( !me->query("quest/jiuyin2/emeijump")) return 0;

	message_vision("$N運足氣，雙手用力去搬白玉石棺蓋。\n", me);
	message_vision(HIR"忽然間幾支短箭從棺後一個機關裡射出來，直射向$N的面門！\n"NOR, me);

	dex = me->query_dex(1) + me->query("kar");

	if( random(dex) < 18 && !me->query("hanshui_food") && random(2) ) {
		message_vision(HIW"$N連忙躲閃，結果沒能躲過去。\n"NOR, me);
		me->add("quest/jiuyin2/fail", 1);
		me->set("quest/jiuyin2/time", time());
		log_file("quest/jiuyin",sprintf("%-18s想從郭襄墓中掀開棺蓋，娥眉九陰部分失敗%s次。\n",
       			me->name(1)+"("+capitalize(getuid(me))+")",chinese_number(me->query("quest/jiuyin2/fail"))), me);
		me->unconcious(); 
		me->set_temp("last_damage_from","身中巨毒毒發");
       		me->die();
		if (tmp = present("corpse", this_object())) {
			object *ob = deep_inventory(tmp);
			int i = sizeof(ob);
			while (i--) if (userp(ob[i])) ob[i]->move(this_object());
			destruct(tmp);
			if (me) tell_room(this_object(), me->name()+"的屍骨都找不到了。\n");
		}
		return 1;
	}
	else {
		message_vision(HIW"$N頭一低，避開短箭，掀開棺蓋。\n"NOR, me);
		me->set_temp("marks/掀", 1);
		log_file("quest/jiuyin",sprintf("%-18s在娥眉九陰部分失敗%s次後成功在郭襄墓中掀開棺蓋，身：%d，福：%d。\n",
       			me->name(1)+"("+capitalize(getuid(me))+")",chinese_number(me->query("quest/jiuyin2/fail")),
       			me->query_dex(), me->query("kar")), me);
		return 1;
	}
}

int do_na(string arg)
{
	object me, ob;

	me = this_player();
	ob = this_object();

	if (me->is_busy() || me->is_fighting()) return notify_fail("你正忙著哪！\n");


	if (arg != "all from coffin") return notify_fail("你要幹什麼？\n");

	if (!me->query_temp("marks/掀")) 
		return notify_fail("你不打開石棺的蓋子，怎麼能拿裡面的東西？\n");

	if( random(30) > 5 ) {
		write("你在石棺裡摸了半天，什麼也沒有拿到。\n", me);
		write("只聽見啪的一聲，棺蓋不知怎麼又合上了。\n", me);
		log_file("quest/jiuyin",sprintf("%-18s在失敗%s次後，在郭襄墓中掀開棺蓋，但未得到任何東西。\n",
       			me->name(1)+"("+capitalize(getuid(me))+")",chinese_number(me->query("quest/jiuyin2/fail"))), me);
		me->delete_temp("marks/掀");
		return 1;
	}
	if (ob->query("count") > 0) {
		switch(random(2)) {
			case 0: { 
				new("/d/emei/obj/yangpi")->move(me);
				me->set("quest/jiuyin2/emei", 1);
				log_file("quest/jiuyin",sprintf("%-18s在娥眉九陰部分失敗%s次後成功在郭襄墓中得到山羊皮。\n",
       					me->name(1)+"("+capitalize(getuid(me))+")",chinese_number(me->query("quest/jiuyin2/fail"))), me);
				write("你從石棺中拿出一塊山羊皮。\n", me);
				break;
			}
			case 1: {
				new("/d/emei/obj/yuzhuo")->move(me);
				write("你從石棺拿出支黑玉鐲。\n", me);
				log_file("quest/jiuyin",sprintf("%-18s在娥眉九陰部分失敗%s次後，在郭襄墓中掀開棺蓋，但未得到山羊皮。\n",
       					me->name(1)+"("+capitalize(getuid(me))+")",chinese_number(me->query("quest/jiuyin2/fail"))), me);
				break;
			}
		}
		write("只聽見啪的一聲，棺蓋不知怎麼又合上了。\n", me);
		me->delete_temp("marks/掀");
		ob->add("count", -1);
	}
	return 1;
}
