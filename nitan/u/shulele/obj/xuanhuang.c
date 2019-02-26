// xuanhuang.c 玄黃紫清丹

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIM "玄黃紫清丹" NOR, ({ "xuanhuang dan", "dan" }) );
	set_weight(300);
	if( clonep() )
		set_default_object(__FILE__);
	else {
                set("long", "一顆紫中泛黃的精緻奇丹，具有這神話般的功效，"
                            "是練武人夢寐以求的妙藥。\n");
                set("value", 2500000);
		set("unit", "粒");
		set("only_do_effect", 1);
	}
}

int do_effect(object me)
{
        int effect;
        int neili;

        log_file("static/using", sprintf("%s(%s) eat 玄黃紫清丹 at %s.\n",
                 me->name(1), me->query("id"), ctime(time())));

        effect = 0;
        message_vision(HIW "$N" HIW "一仰脖，吞下了一顆" +
                       this_object()->name() + HIW "，只見$N"
                       HIW "渾身一顫，七竅都冒出白煙來。\n" NOR, me);

        me->add("combat_exp", 100000 + random(50000));
        me->improve_skill("force", 250000);
        me->improve_skill("parry", 250000);
        me->improve_skill("dodge", 250000);
        neili = me->query("max_neili") + 500;
        if (neili > me->query_neili_limit())
                neili = me->query_neili_limit();
        me->set("max_neili", neili);

        destruct(this_object());
	return 1;
}

