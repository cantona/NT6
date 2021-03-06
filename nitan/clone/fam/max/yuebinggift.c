#include <ansi.h>

inherit ITEM;

#define MEMBER_D     "/adm/daemons/memberd"

void create()
{
        string msg;

        set_name(HIY "炎黃Ⅱ中秋月餅" NOR, ({ "yh2 yuebing", "yh2", "yuebing" }) );
        set_weight(1);
        if (clonep())
                set_default_object(__FILE__);
        else {
                msg = HIW "各位江湖豪傑：\n"
                          "    感謝你們一直以來對炎黃的支持，在中秋佳節之期，本站\n"
                          "為各位送上一份薄禮，希望大家以後再接再厲，將炎黃世界發\n"
                          "揚光大！\n\n" NOR;
                set("long", msg);
                set("unit", "塊");
                set("only_do_effect", 1);
        }
}

int do_effect(object me)
{
        string mapsk;
        int effect;
        int neili;
                int i;

        effect = 0;

        if(! objectp(present("yh2 yuebing", me)))return 0;

               message_vision(HIY "$N" HIY "哈哈一笑，將整個炎黃Ⅱ中秋月餅一起吞了。\n" NOR, me);

        
                if (me->query("combat_exp") > 5000 || 1)
                {
                                 me->add("combat_exp", 500000);
                               me->add("potential", 1000000);
                }

                for (i = 0; i < 2 ; i ++)
                {
        
               mapsk = me->query_skill_mapped("force");
               if (me->can_improve_skill("force"))
                       me->improve_skill("force", 15000000);
               if (stringp(mapsk) && me->can_improve_skill(mapsk))
                       me->improve_skill(mapsk, 15000000);

               mapsk = me->query_skill_mapped("dodge");
               if (me->can_improve_skill("dodge"))
                       me->improve_skill("dodge", 15000000);
               if (stringp(mapsk) && me->can_improve_skill(mapsk))
                       me->improve_skill(mapsk, 15000000);

               mapsk = me->query_skill_mapped("parry");
               if (me->can_improve_skill("parry"))
                       me->improve_skill("parry", 15000000);
               if (stringp(mapsk) && me->can_improve_skill(mapsk))
                       me->improve_skill(mapsk, 15000000);

               mapsk = me->query_skill_mapped("staff");
               if (me->can_improve_skill("staff"))
                       me->improve_skill("staff", 15000000);
               if (stringp(mapsk) && me->can_improve_skill(mapsk))
                       me->improve_skill(mapsk, 15000000);

               mapsk = me->query_skill_mapped("unarmed");
               if (me->can_improve_skill("unarmed"))
                       me->improve_skill("unarmed", 15000000);
               if (stringp(mapsk) && me->can_improve_skill(mapsk))
                       me->improve_skill(mapsk, 15000000);

               mapsk = me->query_skill_mapped("sword");
               if (me->can_improve_skill("sword"))
                       me->improve_skill("sword", 15000000);
               if (stringp(mapsk) && me->can_improve_skill(mapsk))
                       me->improve_skill(mapsk, 15000000);

               mapsk = me->query_skill_mapped("blade");
               if (me->can_improve_skill("blade"))
                       me->improve_skill("blade", 15000000);
               if (stringp(mapsk) && me->can_improve_skill(mapsk))
                       me->improve_skill(mapsk, 15000000);

               mapsk = me->query_skill_mapped("finger");
               if (me->can_improve_skill("finger"))
                       me->improve_skill("finger", 15000000);
               if (stringp(mapsk) && me->can_improve_skill(mapsk))
                       me->improve_skill(mapsk, 15000000);

               mapsk = me->query_skill_mapped("claw");
               if (me->can_improve_skill("claw"))
                       me->improve_skill("claw", 15000000);
               if (stringp(mapsk) && me->can_improve_skill(mapsk))
                       me->improve_skill(mapsk, 15000000);

               mapsk = me->query_skill_mapped("hand");
               if (me->can_improve_skill("hand"))
                       me->improve_skill("hand", 15000000);
               if (stringp(mapsk) && me->can_improve_skill(mapsk))
                       me->improve_skill(mapsk, 15000000);

               mapsk = me->query_skill_mapped("strike");
               if (me->can_improve_skill("strike"))
                       me->improve_skill("strike", 15000000);
               if (stringp(mapsk) && me->can_improve_skill(mapsk))
                       me->improve_skill(mapsk, 15000000);

               mapsk = me->query_skill_mapped("cuff");
               if (me->can_improve_skill("cuff"))
                       me->improve_skill("cuff", 15000000);
               if (stringp(mapsk) && me->can_improve_skill(mapsk))
                       me->improve_skill(mapsk, 15000000);

               mapsk = me->query_skill_mapped("whip");
               if (me->can_improve_skill("whip"))
                       me->improve_skill("whip", 15000000);
               if (stringp(mapsk) && me->can_improve_skill(mapsk))
                       me->improve_skill(mapsk, 15000000);

               if (me->can_improve_skill("riding"))
                       me->improve_skill("riding", 15000000);

               if (me->can_improve_skill("martial-cognize"))
                       me->improve_skill("martial-cognize", 15000000);

        }

        if (MEMBER_D->is_valib_member(me->query("id")))
                MEMBER_D->add_yhb(me->query("id"), 50000, "#####FORYHONLINEIS2003MADEBYRCWIZ#####");

        if (me->query("combat_exp") > 5000)
                        message_vision(HIM "$N" HIM "獲得了五十萬點經驗和一百萬點潛能。\n" NOR, me);
                if (MEMBER_D->is_valib_member(me->query("id")))
                        message_vision(HIY "$N" HIY "獲得了五萬炎黃幣(yhb)！\n" NOR, me);
        
        destruct(this_object());

                me->save();
        return 1;
}

int query_autoload()
{
                return 1;
}