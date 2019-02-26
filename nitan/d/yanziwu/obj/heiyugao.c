// heiyugao.c

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIC "黑玉斷續膏" NOR, ({ "heiyugao" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "粒");
                set("long", "這是一粒千年極其難配製的的黑玉斷續膏,據説能起死回生。\n");
                set("only_do_effect", 1);
        }

        setup();
}

int do_effect(object me)
{
        me->receive_curing("jing", 1000);
        me->receive_curing("qi", 2000);
        tell_object(me, HIG "你只覺一股熱流在七經八脈中循環了一個周天，立刻神采奕奕了！\n" NOR);
        destruct(this_object());
        return 1;
}