inherit NPC;
#include <ansi.h>

void create()
{

        set_name(WHT "玄武" NOR,({"xuan wu", "xuan", "wu"}));

        set("race", "野獸");
        set("long", WHT "\n\n一隻龍頭龜身的龐然大物，乃四神獸之一的玄武。\n"
                        "它全身被厚厚的甲殼保護着。\n" NOR);
        set("age", 10000);
        set("attitude", "peaceful");

        set("limbs", ({ "頭部", "身體", "雙爪", "頸部", "翅膀" }) );
        set("verbs", ({ "bite" }) );
        set("title", HIY "神獸" NOR);

        set("combat_exp", 8000000);
        set("max_neili", 25000);
        set("neili", 25000);
        set("max_jing", 20000);
        set("jing", 20000);
        set("max_qi", 30000);
        set("qi", 30000);
        set("jingli", 15000);
        set("max_jingli", 15000);

        set("str", 40);
        set("int", 40);
        set("con", 80);
        set("dex", 20);

        set_skill("unarmed", 600);
        set_skill("sword", 600);
        set_skill("parry", 600);
        set_skill("dodge", 600);
        set_skill("force", 1200);

        set("jiali", 100);

        set_temp("apply/attack", 50);
        set_temp("apply/unarmed_damage", 50);
        set_temp("apply/armor", 1000);

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
        return WHT "玄武雙足猛踏地面，頓時地動山搖，山崩地裂，"
               "四處飛沙走石，彷彿天地都要崩潰了一般。\n" NOR;
}

void die()
{
        object me;
        object jiake;

        int exp, pot;

        exp = 3000 + random(200);
        pot = 500 + random(50);

        if( objectp(me = query_last_damage_from()) &&
            query("wang_get/武甲", me) && 
            userp(me) )
        {
                message_vision(HIC "$N" HIC "從玄武的屍體上除下了一塊玄武甲殼。\n", me);
                jiake = new("/d/death/obj/jiake");
                jiake->move(me);
                delete("wang_get/武甲", me);
//                me->delete("wang_get/虎骨", 1);
//                me->delete("wang_get/虎皮", 1);
                addn("combat_exp", exp, me);
                addn("potential", pot, me);

                tell_object(me, HIC "由於你斬殺神獸玄武，你獲得了" + chinese_number(exp)
                                + "點經驗和" + chinese_number(pot) + "點潛能。\n" NOR);
        }
        ::die();
}
