// This program is a part of NITAN MudLIB
// yu.c 俞蓮舟

#include <ansi.h>
#include "wudang.h"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;

mixed ask_me();

void create()
{
        set_name("俞蓮舟", ({ "yu lianzhou", "yu" }));
        set("nickname", "武當二俠");
        set("long",
                "他就是張三豐的二弟子俞蓮舟。\n"
                "他今年五十歲，身材魁梧，氣度凝重。\n"
                "雖在武當七俠中排名第二，功夫卻是最精。\n");
        set("gender", "男性");
        set("age", 50);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 30);
        set("int", 30);
        set("con", 32);
        set("dex", 32);

        set("max_qi", 4800);
        set("max_jing", 2400);
        set("neili", 5500);
        set("max_neili", 5500);
        set("jiali", 100);
        set("combat_exp", 1600000);
        set("score", 50000);

        set_skill("force", 195);
        set_skill("yinyun-ziqi", 195);
        set_skill("taiji-shengong", 195);
        set_skill("dodge", 170);
        set_skill("tiyunzong", 170);
        set_skill("unarmed", 180);
        set_skill("taiji-quan", 180);
        set_skill("strike", 180);
        set_skill("wudang-zhang", 180);
        set_skill("hand", 180);
        set_skill("paiyun-shou", 180);
        set_skill("claw", 180);
        set_skill("huzhua-shou", 180);
        set_skill("parry", 180);
        set_skill("sword", 185);
        set_skill("wudang-jian", 185);
        set_skill("taiji-jian", 185);
        set_skill("taoism", 160);
        set_skill("literate", 100);
        set_skill("medical", 160);
        set_skill("liandan-shu", 160);

        set("no_teach", ([
                "taiji-shengong" : "要想學習太極神功請向張真人請教。",
                "taiji-jian"     : "太極劍必須張真人親傳。",
                "taiji-quan"     : "太極拳必須張真人親傳。",
        ]));

        map_skill("force", "taiji-shengong");
        map_skill("dodge", "tiyunzong");
        map_skill("unarmed", "taiji-quan");
        map_skill("hand", "paiyun-shou");
        map_skill("claw", "huzhua-shou");
        map_skill("parry", "taiji-quan");
        map_skill("sword", "taiji-jian");
        map_skill("strike", "wudang-zhang");

        prepare_skill("unarmed", "taiji-quan");
        prepare_skill("strike", "wudang-zhang");

        create_family("武當派", 2, "弟子");

        set("inquiry", ([
                "虎爪絕戶手": (: ask_me :),
                "絕戶": (: ask_me :),
                "絕招"  : (: ask_me :),
        ]));

        set("chat_chance_combat", 40);
        set("chat_msg_combat", ({
                (: perform_action, "sword.chan" :),
                (: perform_action, "sword.lian" :),
                (: perform_action, "sword.sui" :),
                (: exert_function, "recover" :),
        }) );

        set("master_ob", 4);
        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/wudang/obj/whiterobe")->wear();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("shen", ob)<15000 )
        {
                command("say 我武當乃是堂堂名門正派，對弟子要求極嚴。");
                command("say 在德行方面，" + RANK_D->query_respect(ob) +
                        "是否還做得不夠？");
                return;
        }

        if ((int)ob->query_skill("yinyun-ziqi",1) < 80)
        {
                command("say 我武當派最注重內功心法" + RANK_D->query_respect(ob)+
                        "是否應該在武當心法上多下點功夫啊?");
                return;
        }

        if ((int)ob->query_skill("taoism", 1) < 80)
        {
                command("say 習武是為了強身健體，一味的練武是不可取的。");
                command("say 我看你還需要在修身養性方面多鍛煉鍛煉，以提高"
                        "你的道德心法。");
                return;
        }

        command("say 好吧，我就收下你了。");
        command("say 希望你能好好用功，發揚我武當精神！");
        command("recruit "+query("id", ob));
        if( query("class", ob) != "taoist" )
                set("class", "taoist", ob);
}

mixed ask_me()
{
        object me;

        me = this_player();
        if( query("can_perform/huzhua-shou/juehu", me) )
                return "這一招你不是已經會了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "不是我們武當派的人，何出此言？";

        if (me->query_skill("huzhua-shou", 1) < 1)
                return "你連虎爪絕戶手都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<400 )
                return "你為我武當派效力還不夠，這招我先不忙傳你。";

        if( query("shen", me)<100000 )
                return "這一招太過陰恨，如果被你用去我恐怕不放心！";

        if (me->query_skill("force") < 180)
                return "你的內功的修為不夠，練高了再來吧。";

        if (me->query_skill("huzhua-shou", 1) < 120)
                return "你的虎爪絕戶手還不到家，還是自己先下去多多練習吧。";

        message_vision(HIY "$n" HIY "嘆了口氣，在$N" HIY "耳邊輕"
                       "聲說了幾句虎爪絕戶手\n的精要，隔了良久，"
                       "又嘆了一口氣。\n" NOR, me, this_object());
        command("sigh");
        command("say 這便是絕戶手的精要所在，你懂了多少？");
        command("say 絕戶手太易使人重殘，因而使用前一定要慎重考慮。");
        tell_object(me, HIC "你學會了「絕戶神抓」。\n" NOR);
        if (me->can_improve_skill("claw"))
                me->improve_skill("claw", 1500000);
        if (me->can_improve_skill("huzhua-shou"))
                me->improve_skill("huzhua-shou", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/huzhua-shou/juehu", 1, me);
        addn("family/gongji", -400, me);

        return 1;
}
