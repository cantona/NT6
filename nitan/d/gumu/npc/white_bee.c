// white_bee.c        玉蜂羣
// by April 01.09.01

#include <ansi.h>

inherit NPC;

void create()
{
        set_name(WHT"玉蜂羣"NOR, ({ "yufeng qun","bees" }) );
        set("race", "昆蟲");
        set("subrace", "飛蟲");
        set("age", 1);
        set("long", "這是古墓派馴養的一羣玉蜂，嗡嗡的，不知有多少。\n");
        set("str", 60);
        set("dex", 80);

        set("limbs", ({ "密集處", "稀薄處", "核心", "外圍" }) );

        set("max_jing",1000);
        set("jing",1000);
        set("qi",1000);
        set("max_qi",1000);
        set("jingli",1000);
        set("max_jingli",1000);

        set_skill("dodge", 100);
        set_skill("parry", 100);
        set_skill("unarmed", 100);

        setup();
}

void init()
{
        add_action("do_attack", "attack");
}

void die()
{
        object ob;

        message_vision("\n$N終於都死了，地上白茫茫一片。\n", this_object());
        destruct(this_object());
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        object owner;
        object here = environment(me);

        if( (owner=present(query("owner", me),here))){
                addn("combat_exp", 2+random(3), owner);
                addn("potential", 1+random(3), owner);

                owner->improve_skill("qufeng", 20+random(20), 0);
        }

        victim->apply_condition("yufengdu", 5 + random(5) 
                + victim->query_condition("yufengdu"));
}

int do_attack(string arg)
{
        object env, obj, ob, me = this_player(),bees;
        string target_dir, dir, dest, victim;
        mapping exit;

        if (!arg) return 0;

        victim = arg;
        if( victim == query("id", me))return notify_fail("玉蜂羣不知所措，只是圍着你打轉。\n");

        ob = present(victim, environment(me));
        bees = present("yufeng qun", environment(me));

        if (!ob) return notify_fail("這裏並無此人！\n");

        message_vision(HIR "$N嘴裏嗡嗡作聲，指揮玉蜂羣向$n攻去。\n" NOR, me, ob);

        if( query("owner") != me || query("race", ob) != "人類"
                 || query("family/family_name", ob) == "古墓派"){
                message_vision( "$N不知所措，只是圍着你打轉。\n" NOR, bees );
                return 1;
        }

        if( random(20) ){
                message_vision( HIW"只見$N發瘋般向$n撲了過去。\n" NOR, bees, ob );
                bees->kill_ob(ob);
                me->want_kill(ob);
                ob->kill_ob(me);
        }
        else
                message_vision( "$N不知所措，只是圍着你打轉。\n" NOR, bees );

        return 1;
}
