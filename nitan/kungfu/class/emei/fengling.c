// This program is a part of NT MudLIB

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

#include <ansi.h>
#include "emei.h"

mixed ask_skill1();
mixed ask_skill2();

void create()
{
       set_name("風陵師太", ({"fengling shitai", "fengling", "shitai", "feng", "ling"}));
       set("long", "她就是峨嵋派第二代掌門人風陵師太。\n"
                   "她面目慈祥，便如尋常老尼一般，渾\n"
                   "不帶一絲塵俗之氣。\n");
        set("gender", "女性");
        set("age", 62);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("class", "bonze");

        set("str", 40);
        set("int", 40);
        set("con", 40);
        set("dex", 40);
        set("max_qi", 7000);
        set("max_jing", 6000);
        set("neili", 8000);
        set("max_neili", 8000);
        set("jiali", 250);
        set("level", 30);
        set("combat_exp", 5000000);

        set_skill("force", 700);
        set_skill("emei-jiuyang", 700);
        set_skill("emei-xinfa", 700);
        set_skill("linji-zhuang", 700);
        set_skill("dodge", 700);
        set_skill("zhutian-bu", 700);
        set_skill("finger", 700);
        set_skill("tiangang-zhi", 700);
        set_skill("hand", 700);
        set_skill("jieshou-jiushi", 700);
        set_skill("strike", 700);
        set_skill("jinding-zhang", 700);
        set_skill("piaoxue-zhang", 700);
        // set_skill("sixiang-zhang", 700);
        set_skill("sword", 700);
        set_skill("huifeng-jian", 700);
        set_skill("emei-jian", 700);
        set_skill("blade", 700);
        set_skill("yanxing-dao", 700);
        set_skill("parry", 700);
        set_skill("martial-cognize", 700);
        set_skill("literate", 700);
        set_skill("mahayana", 700);
        set_skill("buddhism", 700);

        set("no_teach", ([
                "emei-jiuyang" : "這峨嵋九陽功乃殘缺不全的九陽神功，臨濟十二莊"
                                 "勝之千倍，你還是學它好了。",
        ]));

        map_skill("force", "emei-jiuyang");
        map_skill("dodge", "zhutian-bu");
        map_skill("finger", "tiangang-zhi");
        map_skill("hand", "jieshou-jiushi");
        map_skill("strike", "piaoxue-zhang");
        map_skill("sword", "huifeng-jian");
        map_skill("blade", "yanxing-dao");
        map_skill("parry", "jinding-zhang");

        prepare_skill("strike", "piaoxue-zhang");

        create_family("峨嵋派", 2, "掌門人");

        set("inquiry",([
                "剃度"     : "要剃度找靜玄。",
                "出家"     : "要剃度找靜玄。",
                "雲海明燈" : (: ask_skill1 :),
                "佛光普照" : (: ask_skill2 :),
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "strike.yun" :),
                (: perform_action, "strike.zhao" :),
                (: exert_function, "recover" :),
                (: exert_function, "shield" :),
                (: exert_function, "powerup" :),
        }));

       set("master_ob", 5);
        setup();

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        carry_object(WEAPON_DIR"changjian")->wield();
        carry_object(CLOTH_DIR"ni-cloth")->wear();
        carry_object(CLOTH_DIR"ni-shoe")->wear();
}

void attempt_apprentice(object ob)
{
        string name, new_name;

        if (! permit_recruit(ob))
                return;

        if( query("shen", ob)<50000 )
        {
                command("say 你行俠仗義的事情還做得不夠，我暫時還不能收你。");
                return;
        }

        if( query("combat_exp", ob)<500000 )
        {
                command("sigh");
                command("say 你的江湖經驗太淺，還是先多鍛鍊鍛鍊再説吧。");
                return;
        }

        if ((int)ob->query_skill("mahayana", 1) < 150)
        {
                command("say 你大乘涅磐功的修為還不行，好好感悟感悟！");
                return;
        }

        if ((int)ob->query_skill("linji-zhuang", 1) < 150)
        {
                command("say 臨濟十二莊乃我峨嵋第一奇功，須得好好練習。");
                return;
        }

        name=query("name", ob);
        new_name = "滅" + name[2..3];
        NAME_D->remove_name(query("name", ob),query("id", ob));
        set("name", new_name, ob);
        NAME_D->map_name(query("name", ob),query("id", ob));

        command("say 不錯，不錯！");
        command("say 今日我便收你為徒，法號" + new_name + "。");
        command("recruit "+query("id", ob));
}

mixed ask_skill1()
{
        object me;

        me = this_player();
        if( query("can_perform/piaoxue-zhang/yun", me) )
                return "這一招我不是已經傳授予你了嗎？還有什麼不懂就自己下去練吧。";

        if( query("family/family_name", me) != query("family/family_name") )
                return "我與閣下素無來往，不知閣下打聽這個幹嘛？";

        if( query("family/master_id", me) != query("id") )
                return "只有我的弟子才能學習此招，你還是走吧。";

        if (me->query_skill("piaoxue-zhang", 1) < 1)
                return "你連飄雪穿雲掌都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<1800 )
                return "你對峨嵋派所作出的貢獻還不夠，這招我暫時不能傳你。";

        if (me->query_skill("force") < 200)
                return "你的內功修行太淺，尚且學不了這一招。";

        if( query("max_neili", me)<2000 )
                return "你的內力修行太淺，尚且學不了這一招。";

        if (me->query_skill("piaoxue-zhang", 1) < 150)
                return "你的飄雪穿雲掌火候未到，尚且學不了這一招。";

        if( query("shen", me)<40000 )
                return "你行俠仗義的事情還做得不夠，我暫時還不能傳你此招。";

        message_sort(HIY "\n$n" HIY "微微一笑，對$N" HIY "説道：“既然你內"
                     "外功均已達至如此境界，也不枉了我平時的一翻栽培。今日"
                     "我便傳你此招，希望日後能將我峨嵋派發揚光大。”説完，"
                     "$n" HIY "將$N" HIY "招至跟前，在$N" HIY "耳旁輕聲細説"
                     "良久。\n\n" NOR, me, this_object());

        command("nod");
        command("say 剛才我所説的你都記清了嗎？記清了就下去練吧。");
        tell_object(me, HIC "你學會了「雲海明燈」。\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("piaoxue-zhang"))
                me->improve_skill("piaoxue-zhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/piaoxue-zhang/yun", 1, me);
        addn("family/gongji", -1800, me);
        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();
        if( query("can_perform/piaoxue-zhang/zhao", me) )
                return "這一招我不是已經傳授予你了嗎？還有什麼不懂就自己下去練吧。";

        if( query("family/family_name", me) != query("family/family_name") )
                return "我與閣下素無來往，不知閣下打聽這個幹嘛？";

        if( query("family/master_id", me) != query("id") )
                return "只有我的弟子才能學習此招，你還是走吧。";

        if (me->query_skill("piaoxue-zhang", 1) < 1)
                return "你連飄雪穿雲掌都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<2200 )
                return "你對峨嵋派所作出的貢獻還不夠，這招我暫時不能傳你。";

        if (me->query_skill("force") < 700)
                return "你的內功修行太淺，尚且學不了這一招。";

        if( query("max_neili", me)<3500 )
                return "你的內力修行太淺，尚且學不了這一招。";

        if (me->query_skill("piaoxue-zhang", 1) < 180)
                return "你的飄雪穿雲掌火候未到，尚且學不了這一招。";

        if( query("shen", me)<40000 )
                return "你行俠仗義的事情還做得不夠，我暫時還不能傳你此招。";

        message_sort(HIY "\n$n" HIY "輕輕拍了拍$N" HIY "的頭，説道：“好"
                     "吧，難得你如此有心，今日我就將此招演示一遍，可得看"
                     "好了！”話音剛落，只見$n" HIY "狂提內勁，周身骨骼無"
                     "不噼啪作響，面赤如血，煞是驚人。隨即$n" HIY "一聲暴"
                     "喝，雙掌攜着隱隱風雷之勢猛力向前拍出，頓時只聽“喀"
                     "嚓”一聲巨響，前方崖邊一顆碗口粗的松樹應聲而斷，斷"
                     "枝仍是餘勢未盡，向前又飛出數丈，這才跌落至山谷之中"
                     "。須臾，便聞山谷下回聲四起，在峨嵋羣山中迴盪了好一"
                     "陣才消失殆盡。$n" HIY "微微一笑，長吁一口氣，緩緩收"
                     "回內勁，朝$N" HIY "望去，見$N" HIY "早已看得目瞪口"
                     "呆。\n\n" NOR, me, this_object());

        command("say 這招你下去後一定要勤加練習，才能發揮出它的威力。");
        tell_object(me, HIC "你學會了「佛光普照」。\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("piaoxue-zhang"))
                me->improve_skill("piaoxue-zhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/piaoxue-zhang/zhao", 1, me);
        addn("family/gongji", -2200, me);
        return 1;
}

int accept_ask(object me, string topic) 
{ 
        switch (topic) 
        { 
        case "涅磐" : 
        case "鳳凰涅磐" : 
               return MASTER_D->teach_pfm(me, this_object(), 
                             ([ "perform" : "can_exert/linji-zhuang/niepan", 
                                "name"    : "鳳凰涅磐",
                                "sk1"     : "linji-zhuang", 
                                "lv1"     : 1000, 
                                "sk2"     : "force", 
                                "lv2"     : 1000, 
                                "reborn"  : 1,
                                "gongxian": 3000, ])); 
                break; 
        default: 
                return 0; 
        } 
} 

