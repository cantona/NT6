inherit NPC;
#include <ansi.h>

void create()
{

        set_name(HIR "朱雀" NOR,({"zhu que", "zhu", "que", "bird"}));

        set("race", "野獸");
        set("long", HIR "\n\n一只寬達丈許的浴火鳳凰，乃四神獸之一的朱雀。\n"
                        "它全身羽毛血紅似火，整個身體便如一團火燄。\n" NOR);
        set("age", 10000);
        set("attitude", "peaceful");

        set("limbs", ({ "頭部", "身體", "雙爪", "頸部", "翅膀" }) );
        set("verbs", ({ "bite" }) );
        set("title", HIY "神獸" NOR);

        set("combat_exp", 8000000);
        set("max_neili", 15000);
        set("neili", 15000);
        set("max_jing", 10000);
        set("jing", 10000);
        set("max_qi", 13000);
        set("qi", 13000);
        set("jingli", 10000);
        set("max_jingli", 10000);

        set("str", 30);
        set("int", 30);
        set("con", 20);
        set("dex", 80);

        set_skill("unarmed", 1000);
        set_skill("sword", 1000);
        set_skill("parry", 1000);
        set_skill("dodge", 1000);
        set_skill("force", 400);

        set("jiali", 150);

        set_temp("apply/attack", 300);
        set_temp("apply/unarmed_damage", 300);
        set_temp("apply/armor", 50);

        set_weight(500000000);

        setup();
}

void init()
{
        object me,ob;

        if (interactive(me = this_player()))
        {
                remove_call_out("kill_ob");
                call_out("kill_ob", 1, me);
        }
        ::init();
}

mixed hit_ob(object me, object ob, int damage_bouns)
{
        ob->receive_wound("qi", 200 + random(200), me);
        set("neili",query("max_neili",  me), me);
        return HIY "朱雀雙爪幻出兩道金光，剎那間霹靂電閃，紫雷"
               "轟鳴，千萬道閃電至九天而降，籠罩大地。\n" NOR;
}

void die()
{
        object me;
        object yumao;

        int exp, pot;

        exp = 3000 + random(200);
        pot = 500 + random(50);

        if( objectp(me = query_last_damage_from()) &&
            query("wang_get/朱羽", me) && 
            userp(me) )
        {
                message_vision(HIC "$N" HIC "從朱雀的屍體上拔下了一束羽毛。\n", me);
                yumao = new("/d/death/obj/yumao");
                yumao->move(me);
                delete("wang_get/朱羽", me);
                addn("combat_exp", exp, me);
                addn("potential", pot, me);

                tell_object(me, HIC "由于你斬殺神獸朱雀，你獲得了" + chinese_number(exp)
                                + "點經驗和" + chinese_number(pot) + "點潛能。\n" NOR);
        }
        ::die();
}
