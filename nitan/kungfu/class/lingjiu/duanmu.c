#include <ansi.h>;
#include "etc.h"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

mixed ask_me();

void create()
{
        set_name("端木元", ({ "duanmu yuan", "duanmu", "yuan"}));
        set("gender", "男性");
        set("title", "海南島赤焰洞洞主");
        set("nickname", HIR "歸去來兮" NOR);
        set("age", 54);
        set("long", @LONG
這大頭老者就是海南島五指山赤焰洞洞主端木
元。只見他一顆大腦袋光禿禿地，半根頭髮也
無，臉上巽血，遠遠望去，便如大血球般。
LONG );
        set("attitude", "peaceful");
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
    
        set("qi", 4000);
        set("max_qi", 4000);
        set("jing", 1800);
        set("max_jing", 1800);
        set("neili", 4200);
        set("max_neili", 4200);
        set("jiali", 120);
        set("combat_exp", 2200000);

        set_skill("force", 200);
        set_skill("wudoumi-shengong", 200);
        set_skill("dodge", 180);
        set_skill("feiyan-zoubi", 180);
        set_skill("unarmed", 200);
        set_skill("parry", 200);
        set_skill("martial-cognize", 180);
        set_skill("literate", 140);

        map_skill("dodge", "feiyan-zoubi");
        map_skill("force", "wudoumi-shengong");
        map_skill("parry", "wudoumi-shengong");
        map_skill("unarmed", "wudoumi-shengong");

        prepare_skill("unarmed", "wudoumi-shengong");

        set("inquiry", ([
                "歸去來兮"   : (: ask_me :),
                "五斗米神功" : "這…這個……這是由地火功演化而來的一門功夫。",
                "地火功"     : "地火功是我海南島五指山赤焰洞一派的基本功夫。",
                "虛竹子"     : "他是我們靈鷲宮新的主公，我們全部聽他號令。",
                "虛竹"       : "他是我們靈鷲宮新的主公，我們全部聽他號令。",
        ]));

        create_family("赤焰洞", 14, "洞主");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "unarmed.gui" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }) );

        set("master_ob",3);
        setup();
        carry_object("/clone/cloth/cloth")->wear();
}

int recognize_apprentice(object ob, string skill)
{
        if( query("family/family_name", ob) != "靈鷲宮" )
        {
                command("?");
                command("say 你是哪裏鑽來的鬼東西？");
                return -1;
        }

        if( query("family/master_id", ob) != "xuzhu zi" )
        {
                command("grin");
                command("say 恐怕這靈鷲宮裏，還輪不到你説話吧？");
                return -1; 

        }

        if (skill != "wudoumi-shengong" && skill != "unarmed")
        {
                command("say 我只傳授你五斗米神功和一些拳腳知識，不學就算了。");
                return -1;
        }

        if (skill == "unarmed" && ob->query_skill("unarmed", 1) > 179)
        {
                command("sweat");
                command("say 夠了，夠了！累死我了，剩下的你自己去研究。");
                return -1;
        }

        if( !query_temp("can_learn/duanmuyuan", ob) )
        {
                command("sigh");
                command("say 這個…既然你是主公派來的，我也只有教你好了。");
                set_temp("can_learn/duanmuyuan", 1, ob);
        }
        return 1;
}

mixed ask_me()
{
        object me;

        me = this_player();
        if( query("can_perform/wudoumi-shengong/gui", me) )
                return "本洞主已經説得夠多了，自己下去練吧。";

        if( query("family/family_name", me) != "靈鷲宮" && 
           query("family/family_name", me) != "赤焰洞" )
                return "哪裏鑽來的鬼東西，快給本洞主滾開！";

        if (me->query_skill("wudoumi-shengong", 1) < 1)
                return "嘿！你學過本洞主的五斗米神功嗎？";

        if( query("family/family_name", me) == "靈鷲宮" && 
           query("family/gongji", me)<1500 )
                return "嗯，主公説過了，不得傳功給無功勞的弟子。";

        if (me->query_skill("force") < 200)
                return "你看你，內功練成這樣，像什麼話！";

        if( query("max_neili", me)<2000 )
                return "你的內力弱成這樣，怎麼學習歸去來兮？";

        if (me->query_skill("wudoumi-shengong", 1) < 140)
                return "你的五斗米神功火候還差得遠，再回去練練！";

        message_vision(HIY "$n" HIY "點了點頭，一聲咳嗽，朝着$N" HIY "吐出"
                       "一口濃痰，$N" HIY "不明\n其理，當即側身躲過。可霎時"
                       "卻見那口濃痰在$N" HIY "身後轉了個\n彎，又飛了回來，"
                       "正直打在$N" HIY "的後腦上。\n" NOR, me,
                       this_object());
        command("haha");
        command("say 看懂了嗎？這東西難練得緊，可要多花些功夫。");
        command("say 還有就是，施功前要將全身功力盡數提起，這樣才得心應手。");
        tell_object(me, HIC "你學會了「歸去來兮」。\n" NOR);
        tell_object(me, HIC "你學會了如何將五斗米神功作為拳腳施展。\n" NOR);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1500000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1500000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1500000);
        if (me->can_improve_skill("wudoumi-shengong"))
                me->improve_skill("wudoumi-shengong", 1500000);
        if (me->can_improve_skill("wudoumi-shengong"))
                me->improve_skill("wudoumi-shengong", 1500000);
        if (me->can_improve_skill("wudoumi-shengong"))
                me->improve_skill("wudoumi-shengong", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/wudoumi-shengong/gui", 1, me);
        if( query("family/family_name", me) == "靈鷲宮" )
                addn("family/gongji", -1500, me);
        return 1;
}

/* 
void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        command("@@");
        command("say 你…你沒搞錯吧？既然這樣，那你跟着我好了。");
        command("recruit "+query("id", ob));
}

void unconcious()
{
        die();
}
*/
