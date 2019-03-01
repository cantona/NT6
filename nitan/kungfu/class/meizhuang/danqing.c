#include <ansi.h>
#include "meizhuang.h"

inherit NPC;
inherit F_MASTER;

mixed ask_skill1();

void create()
{
        set_name("丹青生", ({ "danqing sheng", "danqing", "dan", "qing", "sheng" }));
        set("long", @LONG
只見這人髯長及腹，左手拿著一只酒杯，臉上
醺醺然大有醉意，這就是梅莊四位莊主排行第
四的丹青生。他好酒、好畫、好劍，人稱三絕。
三絕之中，以酒為首，丹青次之，劍道居末。
LONG);
        set("title", "梅莊四莊主");
        set("nickname", HIR "梅莊四友" NOR);
        set("gender", "男性");
        set("age", 54);
        set("attitude", "peaceful");
        set("str", 35);
        set("int", 35);
        set("con", 35);
        set("dex", 35);

        set("max_qi", 3500);
        set("max_jing", 3000);
        set("neili", 4000);
        set("max_neili", 4000);
        set("jiali", 140);
        set("combat_exp", 1000000);

        set_skill("force", 180);
        set_skill("wuzheng-xinfa", 180);
        set_skill("xuantian-wujigong", 180);
        set_skill("dodge", 180);
        set_skill("zuixian-bu", 180);
        set_skill("parry", 180);
        set_skill("sword", 200);
        set_skill("unarmed", 180);
        set_skill("zuiquan-sanda", 180);
        set_skill("pomopima-jian", 200);
        set_skill("strike", 180);
        set_skill("qingmang-zhang", 180);
        set_skill("literate", 180);
        set_skill("drawing", 220);
        set_skill("liquor", 240);
        set_skill("martial-cognize", 180);

        map_skill("force", "xuantian-wujigong");
        map_skill("dodge", "zuixian-bu");
        map_skill("parry", "pomopima-jian");
        map_skill("sword", "pomopima-jian");
        map_skill("strike", "qingmang-zhang");
        map_skill("unarmed", "zuiquan-sanda");

        prepare_skill("unarmed", "zuiquan-sanda");

        create_family("梅莊", 1, "莊主");

        set("inquiry", ([
                "絕招"        : "你要問什麼絕招？",
                "絕技"        : "你要問什麼絕技？",
                "任我行"      : "任我行乃日月神教上代教主，不過已經失蹤很久了。",
                "東方不敗"    : "東方教主武功深不可測，天下無敵。",
                "日月神教"    : "我們梅莊四友和日月神教已無瓜葛，你提它作甚？",
                "溪山行旅圖"  : "我一直想看看北宋范中立《溪山行旅圖》究竟是怎樣的。",
                "醉裡乾坤"    : (: ask_skill1 :),
        ]));

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "sword.zui" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),

        }) );

        set("master_ob",4);
        setup();
                
        carry_object("clone/misc/cloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
}

void attempt_apprentice(object me)
{
        if (! permit_recruit(me))
                return;

        if( query("family/family_name", me) && 
             query("family/family_name", me) == "日月神教" && 
             query("family/master_name", me) == "東方不敗" )
        {
                command("yi");
                command("say 我道是誰，原來是東方教主的弟子。");
                command("say 這件事我不便插手，你去找我大哥、二哥好了。");
                set("move_party/日月神教─梅莊", 1, me);
                return;
        }

        if( query("combat_exp", me)<50000 )
        {
                command("sigh");
                command("say 你的江湖經驗太淺，還是先多鍛煉鍛煉再說吧。");
                return;
        }

        if ((int)me->query_skill("wuzheng-xinfa", 1) < 80
           && (int)me->query_skill("xuantian-wujigong", 1) < 80)
        {
                command("say 你連本門的內功都沒學好，我收你做甚？");
                return;
        }

        command("en");
        command("say 那你以後就跟著我吧。");
        command("recruit "+query("id", me));
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/pomopima-jian/zui", me) )
                return "我已經教過你了，自己下去練，別老是跟我糾纏不休。";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本教素無瓜葛，何出此言？";

        if (me->query_skill("pomopima-jian", 1) < 1)
                return "你連潑墨披麻劍都沒學，何談此言？";

        if( query("family/gongji", me)<300 )
                return "你對本莊所作出的貢獻不夠，這一招我暫時還不能傳你。";

        if (me->query_skill("pomopima-jian", 1) < 120)
                return "你的潑墨披麻劍還練得不到家，自己下去練練再來吧！";

        if (me->query_skill("force") < 150)
                return "你的內功火候尚不精純，學不了這一招。";

        message_vision(HIY "$n" HIY "哈哈一笑，舉起手中酒杯一口飲"
                       "幹，說道：好，今日老夫便傳你這招！\n$n" HIY
                       "說完左掌猛力拍落，一股掌力擊在地下，“蓬”"
                       "的一聲響，身子向後\n躍起，已在丈許之外。只"
                       "見他尚未站定，長劍已在身前連劃三個圓圈，幻"
                       "作\n三個光圈。三個光圈便如是有形之物，凝在"
                       "空中停得片刻，緩緩向$N" HIY "身前移\n去。"
                       "這幾個劍氣化成的光圈驟視之似不及一字電劍的"
                       "凌厲，但劍氣滿室，寒\n風襲體。直看得$N" HIY
                       "目瞪口呆。\n" NOR, me, this_object());
        command("haha");
        command("say 精要便是如此，自己下去練吧。");
        tell_object(me, HIC "你學會了「醉裡乾坤」。\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("pomopima-jian"))
                me->improve_skill("pomopima-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/pomopima-jian/zui", 1, me);
        addn("family/gongji", -300, me);

        return 1;
}
