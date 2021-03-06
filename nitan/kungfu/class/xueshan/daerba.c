// This program is a part of NT MudLIB

#include <ansi.h>
#include "xueshan.h"

inherit NPC;
inherit F_MASTER;

mixed ask_skill1();
mixed ask_skill2();

void create()
{
        set_name("達爾巴", ({ "da erba", "da", "erba" }));
        set("long", @LONG
他是金輪法王座下的大弟子。深得法王的真傳。
身穿一件黃色袈裟，頭帶僧帽。
LONG);
        set("nickname", HIY "金剛佛" NOR);
        set("gender", "男性");
        set("class", "bonze");
        set("age", 38);
        set("attitude", "peaceful");
        set("shen_type", -1);

        set("str", 35);
        set("int", 20);
        set("con", 25);
        set("dex", 20);

        set("max_qi", 3500);
        set("max_jing", 2500);
        set("neili", 4000);
        set("max_neili", 4000);
        set("jiali", 150);
        set("level", 20);
        set("combat_exp", 800000);

        set_skill("force", 180);
        set_skill("mizong-neigong", 180);
        set_skill("unarmed", 180);
        set_skill("longxiang-gong", 180);
        set_skill("dodge", 160);
        set_skill("shenkong-xing", 160);
        set_skill("hammer", 180);
        set_skill("dali-chu", 160);
        set_skill("xiangmo-chu", 180);
        set_skill("hand", 160);
        set_skill("dashou-yin", 160);
        set_skill("cuff", 160);
        set_skill("yujiamu-quan", 160);
        set_skill("parry", 160);
        set_skill("lamaism", 180);
        set_skill("literate", 100);
        set_skill("sanscrit", 200);
        set_skill("martial-cognize", 160);

        map_skill("force", "mizong-neigong");
        map_skill("dodge", "shenkong-xing");
        map_skill("parry", "xiangmo-chu");
        map_skill("hammer", "xiangmo-chu");
        map_skill("hand", "dashou-yin");
        map_skill("cuff", "yujiamu-quan");

        prepare_skill("cuff", "yujiamu-quan");
        prepare_skill("hand", "dashou-yin");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "hammer.zhen" :),
                (: perform_action, "hand.yin" :),
                (: perform_action, "cuff.jiang" :),
                (: exert_function, "recover" :),
        }));

        create_family("雪山寺", 3, "活佛");

        set("inquiry", ([
                "轟雷萬鈞" : (: ask_skill1 :),
                "鎮魂舞"   : (: ask_skill2 :),
        ]));

        set("master_ob", 3);
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/xueshan/obj/y-jiasha")->wear();
        carry_object("/d/xueshan/obj/sengmao")->wear();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("gender", ob) != "男性" )
        {
                command("say 修習密宗內功需要純陽之體，你還是走吧。");
                return;
        }

        if( query("class", ob) != "bonze" )
        {
                command("say 我們雪山寺只收出家弟子，你還是請回吧。");
                return;
        }

        if( query("shen", ob)>-3000 )
        {
                command("say 我從來不和正派人士打交道，你還是走吧。");
                return;
        }

        if ((int)ob->query_skill("mizong-neigong", 1) < 50)
        {
                command("say 你內功這麼差，怎麼修行高深的武技？");
                return;
        }

        if ((int)ob->query_skill("lamaism", 1) < 30)
        {
                command("say 嗯，你有空還是多修修密宗心法吧。");
                return;
        }

        command("say 這個…那你以後就跟着我練武吧！");
        command("recruit "+query("id", ob));
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/dali-chu/hong", me) )
                return "你又來幹什麼？自己下去多練。";

        if( query("family/family_name", me) != query("family/family_name") )
                return "我又不認識你，打聽這個幹什麼？";

        if (me->query_skill("dali-chu", 1) < 1)
                return "你連無上大力杵都沒學，哪裏來絕招？";

        if( query("family/gongji", me)<100 )
                return "你為雪山寺效力不夠，這招暫時還不能傳你。";

        if( query("shen", me)>-3000 )
                return "你為人太過心軟，這招暫時還不能傳你。";

        if (me->query_skill("force") < 120)
                return "你的內功修為不足，還學不了這一招。";

        if( query("max_neili", me)<800 )
                return "你的內力修為不足，還是修煉高點再來吧。";

        if (me->query_skill("dali-chu", 1) < 80)
                return "等你把無上大力杵練熟了再來找我。";

        message_sort(HIY "\n$n" HIY "對$N" HIY "點了點頭，喝道：“瞧仔"
                     "細了。”話音剛落，只見$n" HIY "高舉手中的鋼杵，在"
                     "空中揮舞成盤，氣勢驚人！便在此時，那柄鋼杵已攜帶"
                     "着震天撞擊之聲猛然擊落。直把$N" HIY "看得目瞪口呆"
                     "。\n\n" NOR, me, this_object());

        command("nod");
        command("say 看明白了就自己下去練吧。");
        tell_object(me, HIC "你學會了「轟雷萬鈞」。\n" NOR);

        if (me->can_improve_skill("hammer"))
                me->improve_skill("hammer", 1500000);
        if (me->can_improve_skill("dali-chu"))
                me->improve_skill("dali-chu", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/dali-chu/hong", 1, me);
        addn("family/gongji", -100, me);

        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_perform/xiangmo-chu/zhen", me) )
                return "我不是讓你自己下去練嗎，怎麼又來了？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "我又不認識你，打聽這個幹什麼？";

        if (me->query_skill("xiangmo-chu", 1) < 1)
                return "你連金剛降魔杵都沒學，哪裏來絕招？";

        if( query("family/gongji", me)<200 )
                return "你為雪山寺效力不夠，這招暫時還不能傳你。";

        if( query("shen", me)>-6000 )
                return "你為人太過心軟，這招暫時還不能傳你。";

        if (me->query_skill("force") < 150)
                return "你的內功修為不足，還學不了這一招。";

        if( query("max_neili", me)<1500 )
                return "你的內力修為不足，還是修煉高點再來吧。";

        if (me->query_skill("xiangmo-chu", 1) < 100)
                return "等你把金剛降魔杵練熟了再來找我。";

        message_sort(HIY "\n$n" HIY "對$N" HIY "點了點頭，喝道：“看清"
                     "楚了。”話音剛落，只見$n" HIY "高舉手中的鋼杵，在"
                     "空中揮舞成盤，寶相莊嚴，氣度萬千。霎時間幻出重重"
                     "杵影，朝四面八方砸下。招式精奇，令人歎為觀止。\n"
                     "\n" NOR, me, this_object());

        command("nod");
        command("say 這招看似複雜，其實並不難，你下去體會吧。");
        tell_object(me, HIC "你學會了「鎮魂舞」。\n" NOR);

        if (me->can_improve_skill("hammer"))
                me->improve_skill("hammer", 1500000);
        if (me->can_improve_skill("xiangmo-chu"))
                me->improve_skill("xiangmo-chu", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/xiangmo-chu/zhen", 1, me);
        addn("family/gongji", -200, me);

        return 1;
}
