#include <ansi.h>
#include "meizhuang.h"

#define QIPAN    "/clone/lonely/qipan"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_COAGENT;

mixed ask_skill1();
mixed ask_skill2();
mixed ask_skill3();
mixed ask_qipan();

void create()
{
        object ob;
        set_name("黑白子", ({ "heibai zi", "hei", "bai", "heibai", "zi" }));
        set("long", @LONG
這是一位極高極瘦的黑衣老者，這就是梅莊四
位莊主排行第二的黑白子。這人眉清目秀，只
是臉色泛白，似乎是一具僵屍模樣，令人一見
之下，心中便感到一陣涼意。他頭發極黑而皮
膚極白，果然是黑白分明。
LONG);
        set("title", "梅莊二莊主");
        set("nickname", HIR "梅莊四友" NOR);
        set("gender", "男性");
        set("age", 58);
        set("attitude", "peaceful");
        set("str", 35);
        set("int", 35);
        set("con", 35);
        set("dex", 35);

        set("max_qi", 5000);
        set("max_jing", 4500);
        set("neili", 5500);
        set("max_neili", 5500);
        set("jiali", 200);
        set("combat_exp", 2500000);

        set_skill("force", 220);
        set_skill("wuzheng-xinfa", 200);
        set_skill("xuantian-wujigong", 220);
        set_skill("dodge", 220);
        set_skill("meihua-zhuang", 220);
        set_skill("parry", 220);
        set_skill("hammer", 240);
        set_skill("finger", 240);
        set_skill("xuantian-zhi", 240);
        set_skill("fenglei-panfa", 240);
        set_skill("strike", 200);
        set_skill("qingmang-zhang", 200);
        set_skill("literate", 200);
        set_skill("fenglei-zifa", 240);
        set_skill("throwing", 240);
        set_skill("chess", 280);
        set_skill("martial-cognize", 220);

        map_skill("force", "xuantian-wujigong");
        map_skill("dodge", "meihua-zhuang");
        map_skill("parry", "fenglei-panfa");
        map_skill("hammer", "fenglei-panfa");
        map_skill("strike", "qingmang-zhang");
        map_skill("throwing", "fenglei-zifa");
        map_skill("finger", "xuantian-zhi");

        prepare_skill("finger", "xuantian-zhi");

        create_family("梅莊", 1, "莊主");

        set("inquiry", ([
                "絕招"        : "你要問什麼絕招？",
                "絕技"        : "你要問什麼絕技？",
                "任我行"      : "任我行乃日月神教上代教主，不過已經失蹤很久了。",
                "東方不敗"    : "東方教主武功深不可測，天下無敵。",
                "日月神教"    : "我們梅莊四友和日月神教已無瓜葛，你提它作甚？",
                "嘔血譜"      : "那是傳說中的東西，根本不存在。",
                "射日訣"      : (: ask_skill1 :),
                "風雷四擊"    : (: ask_skill2 :),
                "冰堅地獄"    : (: ask_skill3 :),
                "玄鐵棋盤"    : (: ask_qipan :),
        ]));

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "hammer.fenglei" :),
                (: perform_action, "throwing.she" :),
                (: perform_action, "finger.bing" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),

        }));

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob",4);
        setup();

        if (clonep())
        {
                ob = find_object(QIPAN);
                if (! ob) ob = load_object(QIPAN);
                if (! environment(ob))
                {
                        ob->move(this_object());
                        ob->wield();
                } else
                {
                        ob = new("/d/meizhuang/obj/qipan");
                        ob->move(this_object());
                        ob->wield();
                }
        }
        carry_object("clone/misc/cloth")->wear();
        set_temp("handing", carry_object("/d/meizhuang/obj/qizi"));
}

void attempt_apprentice(object me)
{
        string purename, name, new_name;

        if (! permit_recruit(me))
                return;

        if( query("family/family_name", me) && 
             query("family/family_name", me) == "日月神教" && 
             query("family/master_name", me) == "東方不敗" )
        {
                command("ah");
                command("say 原來是東方教主的弟子，收你…這個倒沒什麼問題。");
                command("say 但是在收你之前，我得先考察一下你的能力。");
                set("move_party/日月神教─梅莊", 1, me);
        }

        if( query("combat_exp", me)<200000 )
        {
                command("sigh");
                command("say 你的江湖經驗太淺，還是先多鍛煉鍛煉再說吧。");
                return;
        }

        if ((int)me->query_skill("force") < 120)
        {
                command("say 你內功火候太差，就算收下你，也不會有什麼出息。");
                return;
        }

        command("say 不錯，不錯！");
        command("say 我就收下你了，不過千萬別招惹是非，給我梅莊添亂。");
        command("recruit "+query("id", me));

        if( query("move_party/日月神教─梅莊", me) )
        {
                delete("move_party/日月神教─梅莊", me);
                command("say 現在你成為我梅莊中人，望你專心練武，別再去過問教中事物。");
        }
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/fenglei-zifa/she", me) )
                return "我已經教過你了，自己下去練，別老是跟我糾纏不休。";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本教素無瓜葛，何出此言？";

        if (me->query_skill("fenglei-zifa", 1) < 1)
                return "你連風雷子法都沒學，何談此言？";

        if( query("family/gongji", me)<300 )
                return "你對本莊所作出的貢獻不夠，這一招我暫時還不能傳你。";

        if (me->query_skill("fenglei-zifa", 1) < 100)
                return "你的風雷子法還練得不到家，自己下去練練再來吧！";

        message_vision(HIY "$n" HIY "微微一笑，隨手拈起一顆棋子，“颼”的"
                       "彈射了出去。$N" HIY "只覺眼前一花，那顆棋子正好打"
                       "\n在自己腳跟前的青磚上，沒入半尺之深。\n" NOR, me,
                       this_object());
        command("nod");
        command("say 這一招便是風雷子法的射日，你看明白了多少？");
        tell_object(me, HIC "你學會了「射日訣」。\n" NOR);

        if (me->can_improve_skill("throwing"))
                me->improve_skill("throwing", 1500000);
        if (me->can_improve_skill("fenglei-zifa"))
                me->improve_skill("fenglei-zifa", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/fenglei-zifa/she", 1, me);
        addn("family/gongji", -300, me);

        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_perform/fenglei-panfa/fenglei", me) )
                return "我已經教過你了，自己下去練，別老是跟我糾纏不休。";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本教素無瓜葛，何出此言？";

        if (me->query_skill("fenglei-panfa", 1) < 1)
                return "你連風雷盤法都沒學，何談此言？";

        if( query("family/gongji", me)<1000 )
                return "你對本莊所作出的貢獻不夠，這一招我暫時還不能傳你。";

        if (me->query_skill("force") < 200)
                return "你的內功火候尚不精純，學不了這一招。";

        if (me->query_skill("fenglei-panfa", 1) < 150)
                return "你的風雷盤法還練得不到家，自己下去練練再來吧！";

        message_vision(HIY "$n" HIY "點了點頭，將$N" HIY "招至"
                       "身邊，在耳旁低聲細說良久，$N" HIY "聽了"
                       "半天，忽然說道：“我明白了，所謂四\n擊"
                       "便是抬手似疾風、起勢如驟雨、出招若雷鳴"
                       "、收勢如電閃。”\n" NOR, me, this_object());

        command("haha");
        command("say 不錯，不錯。這就是風雷四擊的奧秘，你自己下去練吧。");
        tell_object(me, HIC "你學會了「風雷四擊」。\n" NOR);

        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("hammer"))
                me->improve_skill("hammer", 1500000);
        if (me->can_improve_skill("fenglei-panfa"))
                me->improve_skill("fenglei-panfa", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/fenglei-panfa/fenglei", 1, me);
        addn("family/gongji", -1000, me);

        return 1;
}

mixed ask_skill3()
{
        object me;

        me = this_player();

        if( query("can_perform/xuantian-zhi/bing", me) )
                return "我已經教過你了，自己下去練，別老是跟我糾纏不休。";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本教素無瓜葛，何出此言？";

        if (me->query_skill("xuantian-zhi", 1) < 1)
                return "你連玄天指都沒學，何談此言？";

        if( query("family/gongji", me)<1500 )
                return "你對本莊所作出的貢獻不夠，這一招我暫時還不能傳你。";

        if (me->query_skill("xuantian-wujigong", 1) < 180)
                return "你的玄天無極功火候不夠，學不了這一招。";

        if (me->query_skill("xuantian-zhi", 1) < 180)
                return "你的玄天指還練得不到家，自己下去練練再來吧！";

        message_vision( HIW "$n" HIW "點了點頭，默運玄天無極功，伸出右手"
                       "食指，插入桌上的花瓶\n中。片刻間花瓶水面便浮起一"
                       "絲絲白氣，過不多時，瓶口上起了一層\n白箱，跟著水"
                       "面結成一片片薄冰，冰越結越厚，只一盞茶時分，整個"
                       "\n花瓶內的清水都化成了寒冰。\n" NOR, me,
                       this_object());
        command("nod");
        command("say 這就是玄天指絕技冰堅地獄的運功竅門，你自己下去練吧。");
        tell_object(me, HIC "你學會了「冰堅地獄」這一招。\n" NOR);

        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("xuantian-wujigong"))
                me->improve_skill("xuantian-wujigong", 1500000);
        if (me->can_improve_skill("finger"))
                me->improve_skill("finger", 1500000);
        if (me->can_improve_skill("xuantian-zhi"))
                me->improve_skill("xuantian-zhi", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/xuantian-zhi/bing", 1, me);
        addn("family/gongji", -1500, me);

        return 1;
}

mixed ask_qipan()
{
        object me;
        object ob;

        me = this_player();

        if( query("family/family_name", me) != "梅莊" )
                return "你和本莊素無淵源，打聽它幹什麼？";

        if( query("family/master_id", me) != query("id") )
                return "只有我的弟子才配使用這玄鐵棋盤。";

        if (me->query_skill("fenglei-panfa", 1) < 150)
                return "你還是下去將你的風雷盤法練練再來吧。";

        if (me->query_skill("chess", 1) < 100)
                return "你連奕棋都不會，用我這寶貝幹嘛？";

        if (present("xuantie qipan", me))
                return "現在玄鐵棋盤不就在你身上嗎，怎麼老是跟我糾纏不休？";

        ob = present("xuantie qipan", this_object());

        if (! objectp(ob))
                return "現在玄鐵棋盤已經不在我這裡了。";

        ob->move(this_object());
        command("givexuantieqipanto"+query("id", me));

        ob = new("/d/meizhuang/obj/qipan");
        ob->move(this_object());
        ob->wield();

        return "很好，既然這樣，我這玄鐵棋盤你就暫時拿去用吧。";
}

int accept_object(object me, object ob)
{
        int r;
        if (r = ::accept_object(me, ob))
                return r;

        if (base_name(ob) != QIPAN)
        {
                command("say 你給我這種東西幹什麼？");
                return 0;
        }

        if( query("family/master_id", me) != query("id") )
                command("say 多謝這位" + RANK_D->query_respect(me) +
                        "將我的寶貝交回。");
        else
                command("say 很好，很好！");
        destruct(ob);
        return 1;
}

/*
void unconcious()
{
        die();
}
*/
