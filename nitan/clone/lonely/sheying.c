#include <ansi.h>
#include <armor.h>

inherit WAIST;

void create()
{
        set_name(NOR + CYN "含沙射影" NOR, ({ "hansha sheying", "han", "sha", "hansha", "sheying" }) );
        set_weight(500);
        if (clonep())
                destruct(this_object());
        else {
                set("long", CYN "這是五毒教的奇門暗器「含沙射影」，樣子象一條腰\n"
                                "帶，可以束在腰間。帶中間有一個扁扁的小鐵盒，只\n"
                                "要在腰間一按(shot)就可以發射出細如牛毛的毒針。\n" NOR) ;
                set("unit", "個");
                set("value", 800000);
                set("no_sell", "乖乖，這…這不是何…教主的……");
                set("zhen", 10);
                set("material", "iron");
                set("armor_prop/armor", 3);
                set("stable", 100);
        }
        setup();
}

void init()
{
        add_action("do_shot", "shot");
}

int do_shot(string arg)
{
        object me, ob, target;
        int myskill, tgskill;
        int mylev, damage;
        string fam;

        me = this_player();

        if( query("no_fight", environment(me)) )
                return notify_fail ("這裡不準戰鬥！\n");

        if( query_temp("armor/waist", me) != this_object() )
                return notify_fail("你首先得將含沙射影裝備在腰間。\n");

        if (! arg)
                return notify_fail("你想對誰發射含沙射影？\n");

        if (! objectp(target = present(arg, environment(me))))
                return notify_fail("這裡沒有這個人。\n");

        if( query("id", target) == query("id", me) )
                return notify_fail("你想殺自己嗎？\n");

        if (! me->is_fighting(target))
                return notify_fail("你只能射殺戰鬥中的對手。\n");

        if (! target->is_character() || target->is_corpse())
                return notify_fail("看清楚一點，那並不是活物。\n");

        if (me->is_busy())
                return notify_fail("你正忙著哪。\n");

        if( query("zhen", this_object())<1 )
                return notify_fail("鐵盒中的毒針已經射光了。\n");

        if (! objectp(ob = present("hansha sheying", me)))
                return notify_fail("你沒有這種東西。\n");

        myskill = me->query_skill("hansha-sheying", 1) + me->query_skill("dodge", 1);
        tgskill = target->query_skill("dodge");
        mylev = me->query_skill("hansha-sheying", 1);

        if (mylev <= 50)
                return notify_fail("你的含沙射影還不熟練，無法使用此物品！\n");

        addn("zhen", -1, this_object());
        message_vision(HIW "\n$N" HIW "一聲輕笑，左手不經意的在腰間一按。只聽"
                       "得一陣“嗤嗤嗤”的破空聲。\n" NOR, me, target);
        me->start_busy(2 + random(2)) ;

        if (random(myskill) < tgskill)
        {
                message_vision(HIY "$n" HIY "大叫一聲，猛的一個旱地拔蔥身行"
                        "沖起數丈來高，躲開了$N" HIY "的毒針！\n\n" NOR,
                        me, target);
        } else
        {
                message_vision(HIR "$n" HIR "躲閃不及，被無數細如牛毛的毒針"
                               "打了一身，不由慘嚎連連！\n\n" NOR, me, target);

                target->affect_by("sha_poison",
                               (["level":query("jiali", me)+random(query("jiali", me)),
                                  "id":query("id", me),
                                  "duration" : mylev / 50 + random(mylev / 20) ]));

                tell_object (target, HIB "你只覺得臉上、胸前一痛，而後是奇"
                                     "癢難熬。\n" NOR);

                damage=mylev*4-(query("max_neili", target)/10);
                if (damage < 100 ) damage = 100;
                if (damage > 800 ) damage = 800;
                target->receive_wound("qi", damage) ; 
                target->start_busy(4);
        }

        if (! target->is_killing(me))
                target->kill_ob(me);

        return 1;
}