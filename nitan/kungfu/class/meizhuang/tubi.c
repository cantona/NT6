#include <ansi.h>
#include "meizhuang.h"

inherit NPC;
inherit F_MASTER;

mixed ask_skill1();
mixed ask_skill2();

void create()
{
        set_name("禿筆翁", ({ "tubi weng", "tubi", "tu", "bi", "weng" }));
        set("long", @LONG
他就是梅莊四位莊主排行第三的禿筆翁。只見
他身穿一件乾乾淨淨的白色長袍。他已年愈五
旬，身材矮小，頂上光光，一看就知道是個極
易動怒的人。
LONG);
        set("title", "梅莊三莊主");
        set("nickname", HIR "梅莊四友" NOR);
        set("gender", "男性");
        set("attitude", "friendly");
        set("age", 52);
        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 25);
        set("max_qi", 4500);
        set("max_jing", 4000);
        set("neili", 5000);
        set("max_neili", 5000);
        set("jiali", 150);
        set("combat_exp", 2000000);

        set_skill("force", 220);
        set_skill("wuzheng-xinfa", 200);
        set_skill("xuantian-wujigong", 220);
        set_skill("dodge", 200);
        set_skill("meihua-zhuang", 200);
        set_skill("dagger", 220);
        set_skill("shigu-bifa", 220);
        set_skill("parry", 200);
        set_skill("strike", 200);
        set_skill("qingmang-zhang", 200);
        set_skill("calligraphy", 300);
        set_skill("literate", 300);
        set_skill("martial-cognize", 200);

        map_skill("force", "xuantian-wujigong");
        map_skill("dodge", "meihua-zhuang");
        map_skill("parry", "shigu-bifa");
        map_skill("dagger", "shigu-bifa");
        map_skill("strike", "qingmang-zhang");

        prepare_skill("strike", "qingmang-zhang");

        create_family("梅莊", 1, "莊主");

        set("inquiry", ([
                "絕招"        : "你要問什麼絕招？",
                "絕技"        : "你要問什麼絕技？",
                "任我行"      : "任我行乃日月神教上代教主，不過已經失蹤很久了。",
                "東方不敗"    : "東方教主武功深不可測，天下無敵。",
                "日月神教"    : "我們梅莊四友和日月神教已無瓜葛，你提它作甚？",
                "率意帖"      : "唐朝張旭的《率意帖》乃書中一絕，不過我卻無緣一見。",
                "神筆封穴"    : (: ask_skill1 :),
                "詩意縱橫"    : (: ask_skill2 :),
        ]));

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "dagger.feng" :),
                (: perform_action, "dagger.shiyi" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }) );

        set("master_ob",4);
        setup();
        carry_object("/d/city/npc/obj/cloth")->wear();
        carry_object("/d/meizhuang/obj/panguanbi")->wield();
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
                set("move_party/日月神教—梅莊", 1, me);
                return;
        }

        if( query("combat_exp", me)<50000 )
        {
                command("sigh");
                command("say 你的江湖經驗太淺，還是先多鍛鍊鍛鍊再説吧。");
                return;
        }

        if ((int)me->query_skill("wuzheng-xinfa", 1) < 80
           && (int)me->query_skill("xuantian-wujigong", 1) < 80)
        {
                command("say 你連本門的內功都沒學好，我收你做甚？");
                return;
        }

        command("say 好吧，既然你有心練武，我就收下你。");
        command("recruit "+query("id", me));
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/shigu-bifa/feng", me) )
                return "我已經教過你了，自己下去練，別老是跟我糾纏不休。";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本教素無瓜葛，何出此言？";

        if (me->query_skill("shigu-bifa", 1) < 1)
                return "你連石鼓打穴筆法都沒學，何談此言？";

        if( query("family/gongji", me)<300 )
                return "你對本莊所作出的貢獻不夠，這一招我暫時還不能傳你。";

        if (me->query_skill("calligraphy", 1) < 100)
                return "嘿，你連字都寫不好，還談什麼筆法？";

        if (me->query_skill("shigu-bifa", 1) < 100)
                return "你的石鼓打穴筆法還練得不到家，自己下去練練再來吧！";

        if (me->query_skill("force") < 150)
                return "你的內功火候尚不精純，學不了，學不了。";

        message_vision(HIY "$n" HIY "哈哈一笑，説道：不錯，不錯，孺子可"
                       "教也。今天我就傳你這招。\n$n" HIY "説完便將$N"
                       HIY "招至身前，嘀嘀咕咕説了半天。\n" NOR, me,
                       this_object());
        command("nod");
        command("say 剛才我所説的便是這神筆封穴的精要，懂了就下去練吧。");
        tell_object(me, HIC "你學會了「神筆封穴」。\n" NOR);

        if (me->can_improve_skill("dagger"))
                me->improve_skill("dagger", 1500000);
        if (me->can_improve_skill("shigu-bifa"))
                me->improve_skill("shigu-bifa", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/shigu-bifa/feng", 1, me);
        addn("family/gongji", -300, me);

        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_perform/shigu-bifa/shiyi", me) )
                return "我已經教過你了，自己下去練，別老是跟我糾纏不休。";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本教素無瓜葛，何出此言？";

        if (me->query_skill("shigu-bifa", 1) < 1)
                return "你連石鼓打穴筆法都沒學，何談此言？";

        if( query("family/gongji", me)<300 )
                return "你對本莊所作出的貢獻不夠，這一招我暫時還不能傳你。";

        if (me->query_skill("calligraphy", 1) < 100)
                return "嘿，你連字都寫不好，還談什麼筆法？";

        if (me->query_skill("shigu-bifa", 1) < 100)
                return "你的石鼓打穴筆法還練得不到家，自己下去練練再來吧！";

        if (me->query_skill("force") < 150)
                return "你的內功火候尚不精純，學不了，學不了。";

        message_vision(HIY "$n" HIY "點了點頭，説道：這一套筆法乃是從顏真"
                       "卿所書詩帖中變化出來\n的，一共二十三字，每字三招至"
                       "十六招不等，你可聽好了。只聽$n" HIY "\n搖頭晃腦的"
                       "念道：裴將軍！大君制六合，猛將清九垓。戰馬若龍虎，"
                       "騰\n陵何壯哉……\n" NOR, me, this_object());
        command("nod"+query("id", me));
        command("say 剛才我説的都記住了嗎？自己下去練吧。");
        tell_object(me, HIC "你學會了「詩意縱橫」。\n" NOR);

        if (me->can_improve_skill("dagger"))
                me->improve_skill("dagger", 1500000);
        if (me->can_improve_skill("shigu-bifa"))
                me->improve_skill("shigu-bifa", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/shigu-bifa/shiyi", 1, me);
        addn("family/gongji", -300, me);

        return 1;
}
