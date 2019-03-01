#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW "腦白金" NOR, ({ "nao baijin", "nao", "baijin" }) );
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "上面寫著「" HIY "今年我家不收禮，收禮只"
                            "收腦白金" HIW "」看樣子是高級貨。\n" NOR);
                set("value", 500000);
                set("no_sell", 1);
                set("unit", "盒");
                set("only_do_effect", 1);
        }
}

int do_effect(object me)
{
        string mapsk;
        int effect;
        int neili;

        log_file("static/using", sprintf("%s(%s) eat 腦白金 at %s.\n",
                 me->name(1),query("id", me),ctime(time())));

        effect = 0;

               message_vision(HIW "$N" HIW "哈哈一笑，將一整盒腦白金連同"
                       "盒子一塊吞下肚去。\n" NOR, me);

               //addn("combat_exp", 100000, me);
               addn("potential", 10000, me);

               mapsk = me->query_skill_mapped("force");

               if (me->can_improve_skill("force"))
                       me->improve_skill("force", 1500000);
               if (stringp(mapsk) && me->can_improve_skill(mapsk))
                       me->improve_skill(mapsk, 1500000);

               mapsk = me->query_skill_mapped("parry");

               if (me->can_improve_skill("parry"))
                       me->improve_skill("parry", 1500000);
               if (stringp(mapsk) && me->can_improve_skill(mapsk))
                       me->improve_skill(mapsk, 1500000);

               mapsk = me->query_skill_mapped("dodge");

               if (me->can_improve_skill("dodge"))
                       me->improve_skill("dodge", 1500000);
               if (stringp(mapsk) && me->can_improve_skill(mapsk))
                       me->improve_skill(mapsk, 1500000);

               me->improve_neili(300);
               me->improve_jingli(300);
        addn("magic_points", 500, me);
        destruct(this_object());
        return 1;
}
