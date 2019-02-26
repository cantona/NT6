// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit NPC;
inherit F_MASTER;

#define MOON_BLADE    "/clone/lonely/moonblade"

mixed ask_blade();

void create()
{
        set_name("青青", ({"qing qing", "qing"}));
        set("gender", "女性");
        set("age", 21);
        set("shen_type", -1);
        set("long", "
穿着一身淡青色的衣服，就像是春天晴朗的天空，
晴空下清澈的湖水，湖水中倒映着的遠山，美得
神祕而朦朧。笑容清新，甜柔，純潔，高貴。腰
上掛着一柄彎刀，彎刀是用純銀作刀鞘，刀柄上
鑲着一粒光澤圓潤的明珠。");

        set("attitude", "peaceful");

        set("per", 21);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("qi", 20000);
        set("max_qi", 20000);
        set("jing", 10000);
        set("max_jing", 10000);
        set("neili", 130000);
        set("max_neili", 130000);
        set("jiali", 3000);

        set("combat_exp", 150000000);
        set("score", 0);

        set_skill("force", 600);
        set_skill("moshen-xinfa", 600);
        set_skill("chiyou-kuangzhanjue", 600);
        set_skill("dodge", 600);
        set_skill("moshen-bufa", 600);
        set_skill("jiutian-xiaoyaobu", 600);
        set_skill("strike", 600);
        set_skill("moshen-zhangfa", 600);
        set_skill("cuff", 600);
        set_skill("moshen-quanfa", 600);
        set_skill("sword", 600);
        set_skill("moshen-jianfa", 600);
        set_skill("blade", 600);
        set_skill("moshen-daofa", 600);
        set_skill("moon-blade", 600);
        set_skill("parry", 600);
        set_skill("literate", 600);
        set_skill("medical", 600);
        set_skill("mojiao-medical", 600);
        set_skill("motun-tianxia", 600);
        set_skill("martial-cognize", 600);

        map_skill("force", "chiyou-kuangzhanjue");
        map_skill("dodge", "jiutian-xiaoyaobu");
        map_skill("strike", "moshen-zhangfa");
        map_skill("cuff", "moshen-quanfa");
        map_skill("sword", "moshen-jianfa");
        map_skill("blade", "moon-blade");
        map_skill("parry", "moon-blade");

        prepare_skill("strike", "moshen-zhangfa");

        create_family("魔教", 40, "弟子");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "blade.ting" :),
                (: perform_action, "blade.yue" :),
                (: exert_function, "recover" :),
        }) );

        set("inquiry", ([
                "圓月彎刀"      : (: ask_blade :),
                "圓月魔刀"      : (: ask_blade :),
        ]));

        set_temp("apply/attack", 280);
        set_temp("apply/damage", 280);
        set_temp("apply/unarmed_damage", 280);
        set_temp("apply/armor", 280);

        set("master_ob", 5);
        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/blade")->wield();
        add_money("silver",70);
}

void attempt_apprentice(object ob)
{
        command("say 我不收徒，你還是另找他人吧！");
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "當時明月在" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/moon-blade/yue",
                           "name"    : "當時明月在",
                           "sk1"     : "moon-blade",
                           "lv1"     : 300,
                           "dodge"   : 300,
                           "gongxian": 1000,
                           "shen"    : -50000, ]));
                break;

        case "小樓一夜聽春雨" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/moon-blade/ting",
                           "name"    : "小樓一夜聽春雨",
                           "sk1"     : "moon-blade",
                           "lv1"     : 300,
                           "dodge"   : 300,
                           "gongxian": 1000,
                           "shen"    : -50000, ]));
                break;

        case "刀至上，至上刀" :
                  return MASTER_D->teach_pfm(me, this_object(),
                          ([ "perform" : "can_perform/moon-blade/dao",
                             "name"    : "刀至上，至上刀",
                             "sk1"     : "moon-blade",
                             "lv1"     : 400,
                             "dodge"   : 400,
                             "gongxian": 1000,
                             "shen"    : -50000, ]));
                  break;
        default:
                return 0;
        }
}

int recognize_apprentice(object ob, string skill)
{
        object blade, owner;

        blade = find_object(MOON_BLADE);
        if (! blade) blade = load_object(MOON_BLADE);
        owner = environment(blade);

        if (owner != ob)
        {
                command("say 你還是先拿到圓月彎刀後再來找我學習圓月刀法吧！");
                return -1;
        }

        if (ob->query_skill(skill, 1) >= 600)
        {
                command("say 夠了！我就教你到這裏吧，武功還是"
                        "要靠自己多研究才是！");
                return -1;
        }

        if( query_temp("can_learn/qingqing/moon-blade", ob) && 
            skill == "blade")
                return 1;

        if( query_temp("can_learn/qingqing/moon-blade", ob) && 
            skill == "moon-blade")
                return 1;

        if (skill == "moon-blade")
        {
                if( query("family/family_name", ob) != "魔教" )
                {
                        command("say 你和我素無淵源，我為什麼要教你武功？");
                        return -1;
                }

                message_vision("$N看了看$n，點點頭道：圓月刀法也沒有什麼難學的。\n",
                               this_object(), ob);
                set_temp("can_learn/qingqing/moon-blade", 1, ob);
                return 1;
        }

        command("say 我只懂得一點圓月刀法，你可不要為難我。");
        return -1;
}

mixed ask_blade()
{
        object ob,owner;
        object gift;
        object me;

   int cost;
        me = this_player();
        if( query("family/family_name", me) != query("family/family_name") )
                return "你找死啊？";

        if( query("combat_exp", me)<2000000 )
                return "你武功太差了，就別給我魔教丟臉了。";

   if( query("family/first", me) ) cost = 250; 
             else cost = 500; 
             if( query("family/gongji", me) < cost ) 
                     return "你為我魔教效力還不夠，等你擁有足夠的師門功績再來兑換圓月彎刀使用時間吧。";

        call_other(MOON_BLADE, "???");
        ob = find_object(MOON_BLADE);
        if (! objectp(ob))
                return "刀沒了！";

        if (objectp(owner = environment(ob)))
        {
                if(owner == me)
                {
                        destruct(ob);
                        return "你什麼意思？不要就拿回來嘛。\n";
                }
                if(owner->is_character())
                {
                        return "刀已經被" + owner->name(1) + "拿走了。等歸還後你再來取吧。\n";
                }
                return "刀已經被人借走了。現在不知道在什麼地方。\n";
        }
        ob->move(me, 1);
        ob->start_borrowing();
    addn("family/gongji", -cost, me); 
        message_vision("$N掏出一把象月芽兒樣的彎刀，遞給$n，"
                       "道：“你可要拿好了！切勿被他人拿走”。\n", this_object(), me);
        return 1;
}
