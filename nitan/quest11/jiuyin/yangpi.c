// yangpi.c
// Modified by Lane@SJ

inherit ITEM;
#include <ansi.h>

void create()
{
	set_name(HIW"山羊皮"NOR, ({ "shanyang pi", "yangpi", "pi" }));
	set_weight(250);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "張");
		set("long","這是一張山羊皮，上面寫滿了許多希奇古怪的字。\n");
		set("treasure", 1);
		set("value", 200000);
		set("material", "skin");
		set("no_drop", 1);
		set("no_give", 1);
		set("no_get", 1);
		set("no_steal", 1);
		set("skill", ([
/*                        "name": "jiuyin-baiguzhua",     // name of the skill
			"exp_required":	300000,	// minimum combat experience required
                        "jing_cost":    30,     // jing cost every time study this
			"difficulty":	20,	// the base int to learn this skill
                        "max_skill":    62      // the maximum level you can learn
*/
		]) );
	}
}

void init()
{
	add_action("do_du", "read");
}

int do_du(string arg)
{
	object me = this_player();
	int level;

	if( !id(arg) ) return 0;

	if( me->is_busy() )
		return notify_fail("你現在正忙著呢。\n");

	if( me->is_fighting() )
		return notify_fail("你無法在戰鬥中專心下來研讀新知！\n");

	if( !me->query("quest/jiuyin2/emei") )
		return notify_fail("你根本無法理解山羊皮上希奇古怪的字！\n");

	if( !me->query_skill("literate", 1) )
		return notify_fail("你是個文盲，先學點文化(literate)吧。\n");        

	if( me->query("jing") < 30 )
		return notify_fail("你現在過于疲倦，無法專心下來研讀新知。\n");

	if( me->query_int() < 32 )
		return notify_fail("由于你的悟性不夠，無法研習山羊皮。\n");

	if( me->query("combat_exp") < 1500000 )
		return notify_fail("你的實戰經驗不夠，無法領會山羊皮上的文字。\n");

	level = me->query_skill("jiuyin-baiguzhua", 1);

	if( level >= 62 )
		return notify_fail("山羊皮上的文字對你而言已經太淺了。\n");

	me->receive_damage("jing", 30);
	write("你研讀「山羊皮」上的文字，頗有心得。\n");
	me->improve_skill("jiuyin-baiguzhua", me->query_skill("literate", 1)+level);
	if( !random(9) ) message("vision", me->name() + "正在鑽研一張山羊皮。\n", environment(me), ({me}));
	return 1;
}
