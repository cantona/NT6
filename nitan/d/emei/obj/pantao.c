#include <ansi.h>
inherit ITEM;

void create()
{
          set_name(HIR "蟠桃" NOR, ({"pan tao", "pan", "tao"}));
          set_weight(150);
          if (clonep())
                    set_default_object(__FILE__);
          else {
                    set("long", HIR "一個火紅色的大蟠桃，正散發著撲鼻的清香。\n" NOR);
                    set("value", 3000);
                set("only_do_effect", 1);
                    set("unit", "個");
          }
          setup();
}

int do_effect(object me)
{
        string force;
        int neili_limit;

        neili_limit = me->query_neili_limit();

        message_vision(HIR "\n$N" HIR "三兩口將手中的蟠桃嚼爛吞下，一張臉頓時脹"
                       "得通紅。\n\n" NOR, me);
        me->start_busy(random(5) + 5);

          if( query("max_neili", me)<neili_limit )
               {
                       addn("max_neili", 30+random(30), me);
                       if( query("max_neili", me)>neili_limit )
                               set("max_neili", neili_limit, me);
                       set("neili",query("max_neili",  me), me);
               }
        force = me->query_skill_mapped("force");
               if (me->can_improve_skill("force"))
                       me->improve_skill("force", 10000);
               if (stringp(force) && me->can_improve_skill(force))
                       me->improve_skill(force, 10000);

        destruct(this_object());
        return 1;
}
