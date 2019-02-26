// zhaixing.c 摘星子

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_GUARDER;

#include "xingxiu.h"
#include <ansi.h>

string ask_me();
string ask_book();
string ask_job();

void create()
{
        set_name("摘星子", ({ "zhaixing zi", "zhaixing", "zi" }));
        set("nickname", HIR "星宿派大師兄" NOR);
        set("long",
                "他就是丁春秋的大弟子、星宿派大師兄摘星子。\n"
                "他三十多歲，臉龐瘦削，眼光中透出一絲乖戾之氣。\n");
        set("gender", "男性");
        set("age", 35);
        set("attitude", "peaceful");
        set("class", "fighter");
        set("str", 26);
        set("int", 28);
        set("con", 26);
        set("dex", 26);

        set("max_qi", 3400);
        set("max_jing", 1800);
        set("neili", 5800);
        set("max_neili", 5800);
        set("jiali", 80);
        set("combat_exp", 420000);
        set("shen_type", -1);

        set_skill("force", 140);
        set_skill("huagong-dafa", 140);
        set_skill("guixi-gong", 140);
        set_skill("throwing", 120);
        set_skill("feixing-shu", 120);
        set_skill("dodge", 120);
        set_skill("zhaixing-gong", 120);
        set_skill("whip", 120);
        set_skill("chanhun-suo", 120);
        set_skill("strike", 120);
        set_skill("chousui-zhang", 120);
        set_skill("claw", 120);
        set_skill("sanyin-zhua", 120);
        set_skill("parry", 120);
        set_skill("poison", 140);
        set_skill("medical", 120);
        set_skill("xingxiu-qishu", 140);
        set_skill("literate", 140);

        set("no_teach", ([
                "huagong-dafa" : "化功大法要老仙親自傳授。",
        ]));

        map_skill("force", "huagong-dafa");
        map_skill("dodge", "zhaixing-gong");
        map_skill("strike", "chousui-zhang");
        map_skill("claw", "sanyin-zhua");
        map_skill("parry", "chousui-zhang");
        map_skill("throwing", "feixing-shu");
        map_skill("whip", "chanhun-suo");

        prepare_skill("strike", "chousui-zhang");
        prepare_skill("claw", "sanyin-zhua");

        set("coagents", ({
                ([ "startroom" : "/d/xingxiu/riyuedong",
                   "id"        : "ding chunqiu", ]),
        }));

        set("inquiry", ([
                "煉心彈"    : (: ask_me :),
                "祕籍"      : (: ask_book :),
                "天山器法"  : (: ask_book :),
                "job"       : (: ask_job :),
        ]));
        set("dan_count", 1);
        set("book_count", 1);

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "claw.zhua" :),
                (: perform_action, "strike.tao" :),
                (: perform_action, "strike.shi" :),
                (: perform_action, "strike.dan" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }) );

        set_temp("apply/attack", 150);
        set_temp("apply/defense", 150);
        set_temp("apply/damage", 150);
        set_temp("apply/unarmed_damage", 150);

        create_family("星宿派", 2, "弟子");

        set("master_ob", 4);
        setup();
        carry_object("/clone/weapon/lianzi")->wield();
}

void attempt_apprentice(object ob)
{
        if( query("shen", ob)>0 )
        {
             command("heng");
             command("say 老仙最討厭你們這些正道中人，你還是回去吧！");
             return;
        }
        command("say 好吧，我就收下你了。");
        welcome(ob);
        command("recruit "+query("id", ob));
}

string ask_me()
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player())) || fam["family_name"] != "星宿派" )
                return RANK_D->query_respect(this_player()) + "與本派素無來往，不知此話從何談起？\n";

        if (query("dan_count") < 1)
                return "你來晚了，沒有煉心彈了。\n";

        addn("dan_count", -1);
        ob = new("/d/xingxiu/obj/lianxindan");
        ob->move(this_player());
        return "這些練心彈夠你用的了吧。\n";
}

string ask_book()
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player())) || fam["family_name"] != "星宿派" )
                return RANK_D->query_respect(this_player()) + "與本派素無來往，不知此話從何談起？\n";

        if (query("book_count") < 1)
                return "你來晚了，現在沒什麼剩的了。\n";

        addn("book_count", -1);
        ob = new("/clone/book/throw_book");
        ob->move(this_player());
        return "好吧，這本書你拿回去好好看看吧。\n";
}

int accept_ask(object me, string topic)
{
        switch(topic)
        {
             case "歷練" :
             case "歷煉" :
             case "鍛鍊" :
                return QUEST_D->accept_ask(this_object(), me, topic);
                break;

             case "如蛆附骨":
                 return MASTER_D->teach_pfm(me, this_object(),
                               (["perform"  :  "can_perform/tianshan-zhang/fugu",
                                 "name"     :  "如蛆附骨",
                                 "sk1"      :  "tianshan-zhang",
                                 "lv1"      :  60,
                                 "shen"     :  -2200,
                                 "family/gongji" :  80,
                                 "force"    :  80 ]));
                  break;

             case "冰雪紛飛":
                 return MASTER_D->teach_pfm(me, this_object(),
                               (["perform"  :  "can_perform/tianshan-zhang/xue",
                                 "name"     :  "冰雪紛飛",
                                 "sk1"      :  "tianshan-zhang",
                                 "lv1"      :  60,
                                 "shen"     :  -22000,
                                 "family/gongji" :  80,
                                 "force"    :  80 ]));
                  break;

             case "滿天花雨":
                 return MASTER_D->teach_pfm(me, this_object(),
                               (["perform"  :  "can_perform/feixing-shu/hua",
                                 "name"     :  "滿天花雨",
                                 "sk1"      :  "feixing-shu",
                                 "lv1"      :  100,
                                 "sk2"      :  "force",
                                 "lv2"      :  120,
                                 "shen"     :  -5500,
                                 "family/gongji" :  400 ]));
                  break;

             case "火牆":
                 return MASTER_D->teach_pfm(me, this_object(),
                               (["perform"  :  "can_perform/chousui-zhang/huo",
                                 "name"     :  "火牆",
                                 "sk1"      :  "chousui-zhang",
                                 "lv1"      :  150,
                                 "sk2"      :  "huagong-dafa",
                                 "lv2"      :  150,
                                 "sk3"      :  "poison",
                                 "lv3"      :  120,
                                 "shen"     :  -6000,
                                 "family/gongji" :  600 ]));
                  break;

             case "鎖魂勢":
                 return MASTER_D->teach_pfm(me, this_object(),
                               (["perform"  :  "can_perform/chanhun-suo/suo",
                                 "name"     :  "鎖魂勢",
                                 "sk1"      :  "chanhun-suo",
                                 "lv1"      :  70,
                                 "sk2"      :  "force",
                                 "lv2"      :  120,
                                 "shen"     :  -6500,
                                 "family/gongji" :  400 ]));
                  break;

             case "三陰毒爪":
                 return MASTER_D->teach_pfm(me, this_object(),
                               (["perform"  :  "can_perform/sanyin-zhua/zhua",
                                 "name"     :  "三陰毒爪",
                                 "sk1"      :  "sanyin-zhua",
                                 "lv1"      :  100,
                                 "sk2"      :  "force",
                                 "lv2"      :  100,
                                 "shen"     :  -7000,
                                 "family/gongji" :  500 ]));
                  break;

             case "追魂爪":
                 return MASTER_D->teach_pfm(me, this_object(),
                               (["perform"  :  "can_perform/sanyin-zhua/zhui",
                                 "name"     :  "追魂爪",
                                 "sk1"      :  "sanyin-zhua",
                                 "lv1"      :  100,
                                 "sk2"      :  "force",
                                 "lv2"      :  100,
                                 "shen"     :  -7000,
                                 "family/gongji" :  500 ]));
                  break;

             case "腐屍毒":
                 return MASTER_D->teach_pfm(me, this_object(),
                               (["perform"  :  "can_perform/chousui-zhang/shi",
                                 "name"     :  "腐屍毒",
                                 "sk1"      :  "chousui-zhang",
                                 "lv1"      :  140,
                                 "sk2"      :  "force",
                                 "lv2"      :  120,
                                 "sk3"      :  "poison",
                                 "lv3"      :  150,
                                 "sk4"      :  "throwing",
                                 "lv4"      :  120,
                                 "shen"     :  -10000,
                                 "neili"    :  1200,
                                 "family/gongji" :  500 ]));
                  break;

             default :
                  return 0;

        }
}

/*
void unconcious()
{
        die();
}
*/

string ask_job()
{
        object me, ob;
        mapping fam;
        int shen, exp;
        me = this_player();
        fam=query("family", me);
        shen=query("shen", me);
        exp=query("combat_exp", me);

        if(!fam) return "看得出你對老仙態度恭敬，何不加入我星宿派呢？";
        if( fam["family_name"] != "星宿派" && !query_temp("ding_flatter", me) )
                return "你對老仙的態度看上去不太恭敬啊！";
        if(exp<500000)
                return "哈哈哈，你再加把力練功吧。";
        if(exp>=750000)
                return "老仙最近的情況我不太清楚，你自己去問問他老人家吧。";
        if(me->query_condition("wait_xx_task"))
                return "上次搞砸了，這次你就等等吧。";
        if( interactive(me) && query_temp("xx_job", me) )
                return "你怎麼還在這裏發呆？";
        if(interactive(me) && me->query_condition("wait_xx_task"))
                return "老仙現在心情還好，不用你來為他分憂。";
        if(query("di_count") < 1)
                return "老仙現在心情還好，你別再來煩我了。";
        ob = new(__DIR__"obj/di");
        addn("di_count", -1);
        ob->move(me);
        set("name", MAG"紫玉短笛"NOR, ob);
        set("long", MAG"這玉笛短得出奇，只不來七寸來長、通體紫紅，晶瑩可愛。\n"NOR, ob);
        set("xx_user", getuid(me), ob);
        if(fam["family_name"] != "星宿派")
                set_temp("apply/short", ({MAG"星宿派門客"NOR+me->name()+"("+query("id", me)+")"}), me);
        set_temp("xx_job", 1, me);
        message_vision("\n$N拿出一隻玉製短笛，交給$n。\n", this_object(), me);
        return "老仙最近心情不佳，你可要多多為他老人家分憂才是！\n";
}
