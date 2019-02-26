// hua4.c

inherit ITEM;

#include <ansi.h>

void create()
{
	set_name(HIC "翡翠蘭" NOR, ({"feicui lan", "feicui", "lan"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
        	set("unit", "朵");
		set("long", "這是一朵千年難得一見的翡翠蘭，據説能解百毒。\n");
        	set("value", 1000000);
		set("only_do_effect", 1);
	}
        setup();
}

int do_effect(object me)
{
        if( time()-query_temp("last_eat/feicui", me)<300 ) 
        {
                write("你剛服用過藥，需藥性發揮完效用以後才能繼續服用。\n"); 
                return 1; 
        }

        set_temp("last_eat/feicui", time(), me); 
set_temp("nopoison", 3, 	me);
set("eff_jing",query("max_jing",  me), 	me);
set("jing",query("max_jing",  me), 	me);
set("eff_qi",query("max_qi",  me), 	me);
set("qi",query("max_qi",  me), 	me);
        message_vision("$N把" + name() + "扔進嘴裏，幾下就吞了下去。\n", me);
	tell_object(me, HIG "\n你只覺一股清香沁入心肺，頓時靈台一片"
		        "空明，神意清爽！\n" NOR);
	destruct(this_object());
	return 1;
}
