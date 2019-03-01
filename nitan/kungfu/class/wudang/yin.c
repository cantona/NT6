// This program is a part of NITAN MudLIB
// yin.c 殷梨亭

#include <ansi.h>
#include "wudang.h"

inherit NPC;
inherit F_MASTER;

mixed ask_me();
mixed ask_skill();

void create()
{
        set_name("殷梨亭", ({ "yin litin", "yin" }));
        set("nickname", "武當六俠");
        set("long",
                "他就是張三豐的六弟子殷梨亭。\n"
                "他今年三十歲，精明能幹，嫉惡如仇，性如烈火。\n");
        set("gender", "男性");
        set("age", 30);
        set("attitude", "heroism");
        set("shen_type", 1);
        set("str", 26);
        set("int", 30);
        set("con", 26);
        set("dex", 28);

        set("max_qi", 4200);
        set("max_jing", 2100);
        set("neili", 4800);
        set("max_neili", 4800);
        set("jiali", 100);
        set("combat_exp", 1250000);
        set("score", 45000);

        set_skill("force", 165);
        set_skill("yinyun-ziqi", 165);
        set_skill("taiji-shengong", 165);
        set_skill("dodge", 175);
        set_skill("tiyunzong", 175);
        set_skill("unarmed", 170);
        set_skill("taiji-quan", 170);
        set_skill("strike", 165);
        set_skill("wudang-zhang", 165);
        set_skill("hand", 180);
        set_skill("paiyun-shou", 180);
        set_skill("parry", 175);
        set_skill("sword", 160);
        set_skill("wudang-jian", 160);
        set_skill("raozhi-roujian", 180);
        set_skill("taiji-jian", 160);
        set_skill("taoism", 120);
        set_skill("literate", 100);

        set("no_teach", ([
                "taiji-shengong" : "要想學習太極神功請向張真人請教。",
                "taiji-jian"     : "太極劍必須張真人親傳。",
                "taiji-quan"     : "太極拳必須張真人親傳。",
        ]));

        map_skill("force", "yinyun-ziqi");
        map_skill("dodge", "tiyunzong");
        map_skill("unarmed", "taiji-quan");
        map_skill("parry", "wudang-jian");
        map_skill("sword", "raozhi-roujian");
        map_skill("strike", "wudang-zhang");

        prepare_skill("unarmed", "taiji-quan");
        prepare_skill("strike", "wudang-zhang");

        create_family("武當派", 2, "弟子");

        set("inquiry", ([
                "柔月穿空": (: ask_me :),
                "絕招"    : (: ask_me :),
                "天地同壽": (: ask_skill :),
        ]));

        set("chat_chance_combat", 40);
        set("chat_msg_combat", ({
                (: perform_action, "sword.chuankong" :),
                (: exert_function, "recover" :),
        }) );

        set("master_ob", 4);
        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/wudang/obj/whiterobe")->wear();
}

void init()
{
        ::init();
        remove_call_out("greeting");
        call_out("greeting", 1, this_player());
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("shen", ob)<8000 )
        {
                command("say 我武當乃是堂堂名門正派，對弟子要求極嚴。");
                command("say 在德行方面，" + RANK_D->query_respect(ob) +
                        "是否還做得不夠？");
                return;
        }

        if ((int)ob->query_skill("yinyun-ziqi",1) < 70)
        {
                command("say 我武當派最注重內功心法" + RANK_D->query_respect(ob)+
                        "是否應該在氤氳紫氣上多下點功夫啊?");
                return;
        }

        if ((int)ob->query_skill("taoism", 1) < 70)
        {
                command("say 習武是為了強身健體，一味的練武是不可取的。");
                command("say 我看你還需要在修身養性方面多鍛煉鍛煉，以提"
                        "高你的道德心法。");
                return;
        }

        command("say 好吧，我就收下你了。");
        command("say 希望你能好好用功，消滅邪魔外道！");
        command("recruit "+query("id", ob));
        if( query("class", ob) != "taoist" )
                set("class", "taoist", ob);
}

mixed ask_me()
{
        object me;

        me = this_player();
        if( query("can_perform/raozhi-roujian/chuankong", me) )
                return "自己好好多練習吧！";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "不是我們武當派的人，何出此言？";

        if (me->query_skill("raozhi-roujian", 1) < 1)
                return "你連繞指柔劍都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<250 )
                return "你為我武當派效力還不夠，這招我先不忙傳你。";

        if( query("shen", me)<15000 )
                return "你行俠仗義的事情做的還很不夠，我不能傳你絕招！";

        if (me->query_skill("force") < 150)
                return "你的內功的修為不夠，練高了再來吧。";

        if (me->query_skill("raozhi-roujian", 1) < 100)
                return "你的繞指柔劍還不到家，要多練練！";

        message_vision(HIY "$n" HIY "點了點頭，拔出腰間長劍突然向$N" HIY
                       HIY "刺來，途中劍法忽\n變，那柄長劍竟似成了一條軟"
                       "帶，輕柔曲折，飄忽不定，正\n是七十二招「繞指柔劍"
                       "」的最後一招「柔月穿空」。\n" NOR, me,
                       this_object());
        command("say 你可明白了？");
        tell_object(me, HIC "你學會了「柔月穿空」。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("raozhi-roujian"))
                me->improve_skill("raozhi-roujian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/raozhi-roujian/chuankong", 1, me);
        addn("family/gongji", -250, me);

        return 1;
}

mixed ask_skill()
{
        object me;

        me = this_player();
        if( query("can_perform/taiji-jian/tong", me) )
                return "自己好好多練習吧！";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "不是我們武當派的人，何出此言？";

        if (me->query_skill("taiji-jian", 1) < 1)
                return "你連太極劍都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<250 )
                return "你為我武當派效力還不夠，這招我先不忙傳你。";

        if( query("shen", me)<15000 )
                return "你行俠仗義的事情做的還很不夠，我不能傳你絕招！";

        if (me->query_skill("force") < 150)
                return "你的內功的修為不夠，練高了再來吧。";

        if (me->query_skill("taiji-jian", 1) < 100)
                return "你的太極劍還不到家，要多練練！";

        message_sort(HIY "$n" HIY "點了點頭道：既然$N" HIY "也是"
                     "我輩中人，那麼我就將自曉芙去後，我所參捂出"
                     "來的「天地同壽」傳于你，切記，非萬不得以時"
                     "千萬不要使用！緊接著，$n開始詳細講解其中奧"
                     "秘。\n" NOR, me, this_object());
        command("say 你可明白了？");
        tell_object(me, HIC "你學會了「天地同壽」。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("taiji-jian"))
                me->improve_skill("taiji-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/taiji-jian/tong", 1, me);
        addn("family/gongji", -250, me);

        return 1;
}


