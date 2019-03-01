#include <ansi.h>
inherit NPC;

void create()
{
        set_name("猴王", ({ "hou wang", "hou", "wang", "monkey" }));
        set("race", "野獸");
        set("age", 23);
        set("long", "這是一只身材碩壯的大馬猴，眼神中透露出一股霸\n"
                    "氣，看起來極不好惹。\n");
        set("rank_info/rude", "孽畜");
        set("rank_info/respect", "大猴子");
        set("combat_exp", 3000000);
        set("attitude", "heroism");
        set("str", 80);
        set("int", 10);
        set("con", 80);
        set("dex", 80);

        set("max_neili", 5000);
        set("neili", 5000);
        set("max_jing", 4000);
        set("jing", 4000);
        set("max_qi", 6000);
        set("qi", 6000);
        set("jingli", 3000);
        set("max_jingli", 3000);
        set("jiali", 300);

        set_skill("cuff", 250);
        set_skill("mizong-houquan", 250);
        set_skill("parry", 250);
        set_skill("dodge", 250);
        set_skill("force", 250);

        map_skill("cuff", "mizong-houquan");
        prepare_skill("cuff", "mizong-houquan");

        set_temp("apply/attack",  200);
        set_temp("apply/defense", 300);
        set_temp("apply/damage",  300);
        set_temp("apply/unarmed_damage", 300);
        set_temp("apply/armor", 500);

        set("chat_chance", 30);
        set("chat_msg", ({
                (: random_move :)
        }));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "cuff.x" :),
        }));
        setup();

        if (random(10) == 1)
                set_temp("handing", carry_object("/d/emei/obj/pantao"));

}

int accept_object(object me, object ob)
{
        if( !query("food_supply", ob) )
        {
                message_vision(CYN "$N" CYN "擺了擺手，吱吱吱吱一陣"
                               "亂叫。\n" NOR, this_object());
                return 0;
        }

        if( query("food") >= max_food_capacity()-query("food_supply", ob) )
        {
                message_vision(CYN "$N" CYN "伸長脖子嗅嗅，擺了擺手"
                               "，打了一個飽嗝。\n" NOR, this_object());

                if (present("pan tao", this_object()))
                {
                        message_vision(CYN "\n$N" CYN "撓了撓頭，從身後摸出"
                                       "個水靈靈的大蟠桃，又嗅了嗅。\n" NOR,
                                       this_object());

                        command("give pan tao to "+query("id", me));
                        command("hehe");
                }
                return 0;
        }

        message_vision(CYN "$N" CYN "一把抓過$n" NOR + CYN "，使勁嗅了嗅。\n"
                       NOR, this_object(), ob);

        // 必須提前轉移物件，否則下面的指令無效
        ob->move(this_object());

        command("eat"+query("id", ob));
        command("stuff");
        command("shzi");
        return 1;
}

int accept_fight(object ob)
{
        message_vision(CYN "$N" CYN "朝著$n" CYN "吱吱吱吱一陣亂叫。"
                       "\n" NOR, this_object(), ob);
        return 0;
}

void fight_ob(object ob)
{
        if (is_fighting(ob))
                return;

        message_vision(HIW "$N" HIW "仰天一聲長哮，朝$n" HIW "猛撲了"
                       "上去。\n" NOR, this_object(), ob);

        ::fight_ob(ob);
        if( !is_killing(query("id", ob)) )
                kill_ob(ob);
}

int accept_kill(object ob)
{
        return 1;
}

int accept_hit(object ob)
{
        return 1;
}

mixed hit_ob(object me, object ob, int damage_bouns)
{
        ob->receive_wound("qi", 80 + random(50), me);
        set_temp("can_learn/houwang", 1, ob);
        return random(2) ? HIY "陡然間$N" HIY "招式一變，騰空躍起，雙"
                           "爪竟似幻作兩道金光，宛若星劃長空，颼的抓向"
                           "$n" HIY "而去。\n" NOR:

                           HIY "$N" HIY "驀地裡一聲清嘯，雙拳回圈斜揮"
                           "而出，招式煞為精奇。$n" HIY "登時只覺眼花"
                           "繚亂，難以招架。\n" NOR;
}

void unconcious()
{
        object ob;

        if (objectp(ob = query_last_damage_from())
           && ! ob->query_skill("mizong-houquan", 1)
            && query_temp("can_learn/houwang", ob)>30
            && query("combat_exp", ob)>100000
           && ob->query_skill("cuff", 1) > 100
           && ob->query_skill("force", 1) > 100
            && query("max_neili", ob)>1200
            && query("int", ob)>26
            && query("dex", ob)>24
           && random(10) == 1
           && userp(ob))
        {
                tell_object(ob, HIW "\n你通過和猴王格鬥，突然間靈光一"
                                "閃，領悟出了猴拳的真詣所在。\n\n" NOR +
                                HIC "恭喜你練成了「迷蹤猴拳」。\n" NOR);
                ob->set_skill("mizong-houquan", 49);
                ob->improve_skill("mizong-houquan", 1500000);
                ob->improve_skill("martial-cognize", 1500000);
        }
        ::die();
}
