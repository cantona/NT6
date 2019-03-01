// This program is a part of NT MudLIB

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_COAGENT;

#include <ansi.h>
#include "emei.h"

string ask_me();
string ask_for_quit();

mixed ask_skill1();
mixed ask_skill2();
mixed ask_skill3();
mixed ask_skill4();
mixed ask_skill5();
mixed ask_skill6();
mixed ask_skill7();
mixed ask_skill8();
mixed ask_skill9();
mixed ask_skill10();
mixed ask_skill11();
mixed ask_skill8();
mixed ask_skill9();
mixed ask_skill12();

void create()
{
        set_name("滅絕師太", ({ "miejue shitai", "miejue", "shitai", "mie", "jue"}));
        set("long", "她是峨嵋派的第三代弟子，現任峨嵋派掌門人。\n");
        set("gender", "女性");
        set("age", 62);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("class", "bonze");

        set("inquiry",([
                "剃度"     : "要剃度找靜玄。",
                "出家"     : "要剃度找靜玄。",
                // "雲海明燈" : "自張無忌應我三掌之約，而我敗于他後，我已發誓不用飄雪穿雲掌了。",
                // "佛光普照" : "哼，自從光明頂一戰後，我早已將這招封存，你找別人吧。",
                "絕招"     : "我峨眉派絕學如此之多，你到底要問什麼絕招？",
                "絕技"     : "我峨眉派絕學如此之多，你到底要問什麼絕技？",
                "秘籍"     :  (: ask_me :),
                "還俗"     : (: ask_for_quit :),
                "滅劍"     : (: ask_skill1 :),
                "絕劍"     : (: ask_skill2 :),
                "星羅棋布" : (: ask_skill3 :),
                "八式合一" : (: ask_skill4 :),
                "截筋斷脈" : (: ask_skill5 :),
                "凌空指穴" : (: ask_skill6 :),
                "無形幻影" : (: ask_skill7 :),
                "佛光初現" : (: ask_skill8 :),
                "伏魔劍訣" : (: ask_skill9 :),
                "倚天劍訣" : (: ask_skill12 :),
                "雲海明燈" : (: ask_skill10 :),
                "佛光普照" : (: ask_skill11 :),
        ]));

        set("str", 35);
        set("int", 35);
        set("con", 35);
        set("dex", 35);

        set("max_qi", 4500);
        set("max_jing", 3000);
        set("neili", 6000);
        set("max_neili", 6000);
        set("jingli", 1200);
        set("max_jingli", 1200);
        set("jiali", 200);
        set("level", 50);
        set("combat_exp", 2500000);
        set("score", 50000);
        set("book_count", 1);

        set_skill("force", 600);
        set_skill("emei-xinfa", 600);
        set_skill("emei-jiuyang", 600);
        set_skill("linji-zhuang", 600);
        set_skill("dodge", 600);
        set_skill("zhutian-bu", 600);
        set_skill("finger", 600);
        set_skill("tiangang-zhi", 600);
        set_skill("hand", 600);
        set_skill("jieshou-jiushi", 600);
        set_skill("strike", 600);
        set_skill("jinding-zhang", 600);
        set_skill("piaoxue-zhang", 600);
        // set_skill("sixiang-zhang", 460);
        set_skill("sword", 600);
        set_skill("huifeng-jian", 600);
        set_skill("emei-xinfa", 600);
        set_skill("emei-jian", 600);
        set_skill("yitian-jian", 600);
        set_skill("blade", 600);
        set_skill("yanxing-dao", 600);
        set_skill("parry", 600);
        set_skill("martial-cognize", 600);
        set_skill("literate", 600);
        set_skill("mahayana", 600);
        set_skill("buddhism", 600);

        set("no_teach", ([
                "emei-jiuyang" : "這峨嵋九陽功乃殘缺不全的九陽神功，臨濟十二莊"
                "勝之千倍，你還是學它好了。",
        ]));

        map_skill("force", "linji-zhuang");
        map_skill("dodge", "zhutian-bu");
        map_skill("finger", "tiangang-zhi");
        map_skill("hand", "jieshou-jiushi");
        map_skill("strike", "jinding-zhang");
        map_skill("sword", "yitian-jian");
        map_skill("blade", "yanxing-dao");
        map_skill("parry", "yitian-jian");

        prepare_skill("strike", "jinding-zhang");
        prepare_skill("hand", "jieshou-jiushi");

        create_family("峨嵋派", 3, "掌門人");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.yitian" :),
                (: perform_action, "sword.fumo" :),
                (: perform_action, "finger.ling" :),
                (: perform_action, "strike.bashi" :),
                (: perform_action, "hand.jie" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set("master_ob", 5);
        setup();

        carry_object(WEAPON_DIR"changjian")->wield();
        carry_object(CLOTH_DIR"ni-cloth")->wear();
        carry_object(CLOTH_DIR"ni-shoe")->wear();
}

void attempt_apprentice(object ob)
{
        string name, new_name;

        if (! permit_recruit(ob))
                return;

        if( query("shen", ob)<30000 )
        {
                command("say 你行俠仗義之事做的太少！實在是太少！");
                return;
        }

        if( query("combat_exp", ob)<300000 )
        {
                command("sigh");
                command("say 你的江湖經驗太淺，還是先多鍛煉鍛煉再說吧。");
                return;
        }

        if ((int)ob->query_skill("mahayana", 1) < 100)
        {
                command("say 你大乘涅磐功修為還不行，好好感悟感悟！");
                return;
        }

        if ((int)ob->query_skill("linji-zhuang",1) < 100)
        {
                command("say 怎麼回事？本門內功心法你怎麼學的？好好給我練功去！");
                return;
        }

        name=query("name", ob);
        new_name = "靜" + name[2..3];
        NAME_D->remove_name(query("name", ob),query("id", ob));
        set("name", new_name, ob);
        NAME_D->map_name(query("name", ob),query("id", ob));

        command("say 好吧，我就收下你了。");
        command("say 以後你就叫作" + new_name + "，要像為師一樣，把天下的惡人統統殺光！");
        command("recruit "+query("id", ob));
}

string ask_for_quit()
{
        object me;
        me = this_player();

        if( query("family/family_name", me) != "峨嵋派" )
                return "你是什麼人？跑到這裡來搗亂？\n";

        if( query("class", me) != "bonze" )
                return "阿彌陀佛！你本是俗家人，何談還俗？\n";

        set_temp("pending/quit_bonze", 1, me);
        command("heng");
        command ("say 還俗？好！你滾出我們峨嵋派，找別人替你還俗去吧！\n");
        return "你好好的給我安心修煉，以後降妖除魔，別天天滿腦子不正經。\n";
}

mixed ask_skill1()
{
        object me;

        me = this_player();
        if( query("can_perform/huifeng-jian/mie", me) )
                return "這招我不是已經教過你了嗎？自己下去多練吧！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是哪裡來的？快給我滾開！";

        if (me->query_skill("huifeng-jian", 1) < 1)
                return "你連回風拂柳劍法都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<1000 )
                return "哼，你在本派中無所作為，這一招我暫時還不能傳你。";

        if (me->query_skill("force") < 180)
                return "你的內功修行太淺，怎能使出這回風拂柳劍法中的精妙之處？";

        if (me->query_skill("huifeng-jian", 1) < 120)
                return "你回風拂柳劍法尚未修煉得精深，哪裡能領會其中的微妙之處？";

        if( query("shen", me)<30000 )
                return "哼！你行俠仗義的事情還做得不夠！做得不夠！";

        message_sort(HIY "\n$n" HIY "微微點了點頭，不露半點聲色，將$N" HIY
                     "招至跟前，在耳邊秘密的說了些什麼。$N" HIY "聽後會心的"
                     "一笑，似乎明白了什麼。\n\n" NOR, me, this_object());

        command("say 以後對那些妖人不要手軟，一上來就用這招！");
        tell_object(me, HIC "你學會了「滅劍」。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("huifeng-jian"))
                me->improve_skill("huifeng-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/huifeng-jian/mie", 1, me);
        addn("family/gongji", -1000, me);
        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();
        if( query("can_perform/huifeng-jian/jue", me) )
                return "你自己多練練，降妖除魔就靠你們這些人了！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是哪裡來的？快給我滾開！";

        if (me->query_skill("huifeng-jian", 1) < 1)
                return "你連回風拂柳劍法都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<1800 )
                return "哼，你在本派中無所作為，這一招我暫時還不能傳你。";

        if (me->query_skill("force") < 300)
                return "你的內功修行太淺，怎能使出這回風拂柳劍法中的精妙之處？";

        if (me->query_skill("huifeng-jian", 1) < 180)
                return "你回風拂柳劍法尚未修煉得精深，哪裡能領會其中的微妙之處？";

        if( query("shen", me)<30000 )
                return "哼！你行俠仗義的事情還做得不夠！做得不夠！";

        message_sort(HIY "\n$n" HIY "呆呆的望著天空，激動萬分，口中喃喃道"
                     "：“我峨嵋派真是後繼有人啊。”過了半晌，$n" HIY "才"
                     "回過神來，在$N" HIY "耳邊秘密的說了些什麼。\n\n" NOR,
                     me, this_object());

        command("say 聽好了！以後對那些妖人不要手軟，見一個殺一個，"
                "見兩個殺一雙！");
        tell_object(me, HIC "你學會了「絕劍」。\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("huifeng-jian"))
                me->improve_skill("huifeng-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/huifeng-jian/jue", 1, me);
        addn("family/gongji", -1800, me);
        return 1;
}

mixed ask_skill3()
{
        object me;

        me = this_player();
        if( query("can_perform/sixiang-zhang/xing", me) )
                return "你自己多練練，降妖除魔就靠你們這些人了！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是哪裡來的？快給我滾開！";

        if (me->query_skill("sixiang-zhang", 1) < 1)
                return "你連四象掌法都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<80 )
                return "哼，你在本派中無所作為，這一招我暫時還不能傳你。";

        if (me->query_skill("force") < 100)
                return "你的內功修行太淺，尚且學不了這一招。";

        if (me->query_skill("sixiang-zhang", 1) < 70)
                return "你的四象掌法火候未到，尚且學不了這一招。";

        if( query("shen", me)<5000 )
                return "哼！你行俠仗義的事情還做得不夠！做得不夠！";

        message_sort(HIY "\n$n" HIY "略微點了點頭，說道：“看好了！”隨即"
                     "一聲清嘯，雙掌紛飛貫出，掌影重重疊疊，虛實難辨，全全"
                     "籠罩$N" HIY "全身。\n\n" NOR, me, this_object());

        command("say 剛才我所施展的便是這式星羅棋布，你自己下去練習吧。");
        tell_object(me, HIC "你學會了「星羅棋布」。\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("sixiang-zhang"))
                me->improve_skill("sixiang-zhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/sixiang-zhang/xing", 1, me);
        addn("family/gongji", -80, me);
        return 1;
}

mixed ask_skill4()
{
        object me;

        me = this_player();
        if( query("can_perform/jinding-zhang/bashi", me) )
                return "你自己多練練，降妖除魔就靠你們這些人了！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是哪裡來的？快給我滾開！";

        if (me->query_skill("jinding-zhang", 1) < 1)
                return "你連金頂綿掌都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<250 )
                return "哼，你在本派中無所作為，這一招我暫時還不能傳你。";

        if (me->query_skill("force") < 120)
                return "你的內功修行太淺，尚且學不了這一招。";

        if (me->query_skill("jinding-zhang", 1) < 100)
                return "你的金頂綿掌火候未到，尚且學不了這一招。";

        if( query("shen", me)<8000 )
                return "哼！你行俠仗義的事情還做得不夠！做得不夠！";

        message_sort(HIY "\n$n" HIY "朝著$N" HIY "讚許的點了點頭，說道：“"
                     "既然如此，今日我便傳授你此招！”說完$n" HIY "深深吸"
                     "了一口氣，站起身來，提于全身功力于雙掌猛力拍出，頓時"
                     "只聽“砰”的一聲巨響，$N" HIY "面前那張青石桌案應聲"
                     "而碎，塵沙四起，石屑飛濺。直看得$N" HIY "目瞪口呆。"
                     "\n\n" NOR, me, this_object());

        command("say 這招並不復雜，只須下去後勤加練習便可。");
        tell_object(me, HIC "你學會了「八式合一」。\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("jinding-zhang"))
                me->improve_skill("jinding-zhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/jinding-zhang/bashi", 1, me);
        addn("family/gongji", -250, me);
        return 1;
}

mixed ask_skill5()
{
        object me;

        me = this_player();
        if( query("can_perform/jieshou-jiushi/jie", me) )
                return "這招我不是已經教過你了嗎？自己下去多練吧！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是哪裡來的？快給我滾開！";

        if (me->query_skill("jieshou-jiushi", 1) < 1)
                return "你連截手九式都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<300 )
                return "哼，你在本派中碌碌無為，這一招我暫時還不能傳你。";

        if( query("max_neili", me)<850 )
                return "你的內力修行太淺，尚且學不了這一招。";

        if (me->query_skill("force") < 120)
                return "你的內功修行太淺，尚且學不了這一招。";

        if (me->query_skill("jieshou-jiushi", 1) < 100)
                return "你的截手九式火候未到，尚且學不了這一招。";

        if( query("shen", me)<12000 )
                return "哼！你行俠仗義的事情還做得不夠！做得不夠！";

        message_sort(HIY "\n$n" HIY "甚喜，對$N" HIY "點頭道：“不錯，不"
                     "錯。你這孩子，真不虧了我平時的教誨。”說完將$N" HIY
                     "招至跟前，細說良久。\n\n" NOR, me, this_object());

        command("say 這招用來對付妖人再合適不過。你自己下去練吧。");
        tell_object(me, HIC "你學會了「截筋斷脈」。\n" NOR);

        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 1500000);
        if (me->can_improve_skill("jieshou-jiushi"))
                me->improve_skill("jieshou-jiushi", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/jieshou-jiushi/jie", 1, me);
        addn("family/gongji", -300, me);
        return 1;
}

mixed ask_skill6()
{
        object me;

        me = this_player();
        if( query("can_perform/tiangang-zhi/ling", me) )
                return "這招我不是已經教過你了嗎？自己下去多練吧！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是哪裡來的？快給我滾開！";

        if (me->query_skill("tiangang-zhi", 1) < 1)
                return "你連天罡指穴法都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<250 )
                return "哼，你在本派中碌碌無為，這一招我暫時還不能傳你。";

        if( query("max_neili", me)<800 )
                return "你的內力修行太淺，尚且學不了這一招。";

        if (me->query_skill("force") < 100)
                return "你的內功修行太淺，尚且學不了這一招。";

        if (me->query_skill("tiangang-zhi", 1) < 100)
                return "你的天罡指穴法火候未到，尚且學不了這一招。";

        if( query("shen", me)<10000 )
                return "哼！你行俠仗義的事情還做得不夠！做得不夠！";

        message_sort(HIY "\n$n" HIY "甚喜，對$N" HIY "點頭道：“不錯，不"
                     "錯。你這孩子，真不虧了我平時的教誨。”說完將$N" HIY
                     "招至跟前，細說良久。\n\n" NOR, me, this_object());

        command("say 剛才我所說的你都記住了嗎？自己下去練吧。");
        tell_object(me, HIC "你學會了「凌空指穴」。\n" NOR);

        if (me->can_improve_skill("finger"))
                me->improve_skill("finger", 1500000);
        if (me->can_improve_skill("tiangang-zhi"))
                me->improve_skill("tiangang-zhi", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/tiangang-zhi/ling", 1, me);
        addn("family/gongji", -250, me);
        return 1;
}

mixed ask_skill7()
{
        object me;

        me = this_player();
        if( query("can_perform/yanxing-dao/huan", me) )
                return "這招我不是已經教過你了嗎？自己下去多練吧！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是哪裡來的？快給我滾開！";

        if (me->query_skill("yanxing-dao", 1) < 1)
                return "你連雁行刀法都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<300 )
                return "哼，你在本派中碌碌無為，這一招我暫時還不能傳你。";

        if( query("max_neili", me)<800 )
                return "你的內力修行太淺，尚且學不了這一招。";

        if (me->query_skill("force") < 120)
                return "你的內功修行太淺，尚且學不了這一招。";

        if (me->query_skill("yanxing-dao", 1) < 80)
                return "你的雁行刀法火候未到，尚且學不了這一招。";

        if( query("shen", me)<15000 )
                return "哼！你行俠仗義的事情還做得不夠！做得不夠！";

        message_sort(HIY "\n$n" HIY "微微一笑，沉聲道：“要修成這一招，須"
                     "得通曉四象八卦之學。”$N" HIY "點了點頭，朗聲說道："
                     "“陽分太陽、少陰，陰分少陽、太陰，是為四象。太陽為乾"
                     "兌，少陰為離震，少陽為巽坎，太陰為艮坤。乾南、坤北、"
                     "離東、坎西、震東北、兌東南、巽西南、艮西北。自震至乾"
                     "為順，自巽至坤為逆。正如師父所教：天地定位，山澤通氣"
                     "，雷風相薄，水火不相射，八卦相錯。數往者順，知來者逆"
                     "。”$n" HIY "聽後大喜，說道：“不錯，不錯。我果然沒"
                     "看錯你，這便傳授你此招！”$n" HIY "在$N" HIY "耳畔低"
                     "聲細說良久，$N" HIY "聽後會心的一笑，似乎領悟到了什"
                     "麼。\n\n" NOR, me, this_object());

        command("say 剛才我所說的須記牢了，自己下去練吧。");
        tell_object(me, HIC "你學會了「無形幻影」。\n" NOR);

        if (me->can_improve_skill("blade"))
                me->improve_skill("blade", 1500000);
        if (me->can_improve_skill("yanxing-dao"))
                me->improve_skill("yanxing-dao", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/yanxing-dao/huan", 1, me);
        addn("family/gongji", -300, me);
        return 1;
}

mixed ask_skill8()
{
        object me;

        me = this_player();
        if( query("can_perform/emei-jian/xian", me) )
                return "這招我不是已經教過你了嗎？自己下去多練吧！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是哪裡來的？快給我滾開！";

        if (me->query_skill("emei-jian", 1) < 1)
                return "你連峨嵋劍法都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<50 )
                return "哼，你在本派中無所作為，這一招我暫時還不能傳你。";

        if (me->query_skill("force") < 80)
                return "你的內功修行太淺，用不了這一招！";

        if (me->query_skill("emei-jian", 1) < 60)
                return "你峨嵋劍法尚未修煉得精深，沒法用這招。";

        if( query("shen", me)<3000 )
                return "哼！你行俠仗義的事情還做得不夠！做得不夠！";

        message_sort(HIY "\n$n" HIY "微微點了點頭，不露半點聲色，將$N" HIY
                     "招至跟前，在耳邊輕聲的說了些什麼。$N" HIY "聽後會心"
                     "的一笑，似乎明白了什麼。\n\n" NOR, me, this_object());

        command("say 這招很簡單，下去後稍加練習便成。");
        tell_object(me, HIC "你學會了「佛光初現」。\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("emei-jian"))
                me->improve_skill("emei-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/emei-jian/xian", 1, me);
        addn("family/gongji", -50, me);
        return 1;
}

mixed ask_skill9()
{
        object me;

        me = this_player();
        if( query("can_perform/yitian-jian/fumo", me) )
                return "這招我不是已經教過你了嗎？自己下去多練吧！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是哪裡來的？快給我滾開！";

        if (me->query_skill("yitian-jian", 1) < 1)
                return "你連倚天劍法都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<500 )
                return "哼，你在本派中無所作為，這一招我暫時還不能傳你。";

        if (me->query_skill("force") < 180)
                return "你的內功修行太淺，用不了這一招！";

        if (me->query_skill("yitian-jian", 1) < 120)
                return "你倚天劍法尚未修煉得精深，沒法用這招。";

        if( query("shen", me)<20000 )
                return "哼！你行俠仗義的事情還做得不夠！做得不夠！";

        message_sort(HIY "\n$n" HIY "微微點了點頭，不露半點聲色，將$N" HIY
                     "招至跟前，在耳邊輕聲的說了些什麼。$N" HIY "聽後會心"
                     "的一笑，似乎明白了什麼。\n\n" NOR, me, this_object());

        command("sigh");
        command("say 如果那柄倚天劍還在的話，用這招最爽快不過。");
        tell_object(me, HIC "你學會了「伏魔劍訣」。\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("yitian-jian"))
                me->improve_skill("yitian-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/yitian-jian/fumo", 1, me);
        addn("family/gongji", -500, me);
        return 1;
}

mixed ask_skill12()
{
        object me;

        me = this_player();
        if( query("can_perform/yitian-jian/yitian", me) )
                return "這招我不是已經教過你了嗎？自己下去多練吧！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是哪裡來的？快給我滾開！";

        if (me->query_skill("yitian-jian", 1) < 1)
                return "你連倚天劍法都沒學，還談什麼絕招可言？";

       if (me->query_skill("force") < 200)
               return "你的內功修行太淺，用不了這一招！";

       if (me->query_skill("yitian-jian", 1) < 150)
               return "你倚天劍法尚未修煉得精深，沒法用這招。";

       if( query("shen", me)<40000 )
               return "哼！你行俠仗義的事情還做得不夠！做得不夠！";

       message_sort(HIY "\n$n" HIY "微微點了點頭，不露半點聲色，將$N" HIY
                    "招至跟前，在耳邊輕聲的說了些什麼。$N" HIY "聽後會心"
                    "的一笑，似乎明白了什麼。\n\n" NOR, me, this_object());

       command("sigh");
       command("say 如果那柄倚天劍還在的話，用這招最厲害不過。");
       tell_object(me, HIC "你學會了「倚天劍訣」。\n" NOR);

       if (me->can_improve_skill("sword"))
               me->improve_skill("sword", 1500000);
       if (me->can_improve_skill("yitian-jian"))
               me->improve_skill("yitian-jian", 1500000);
       me->improve_skill("martial-cognize", 1500000);
       set("can_perform/yitian-jian/yitian", 1, me);
       return 1;
}

string ask_me()
{
         object ob;
        if( query("family/family_name", this_player()) != "峨嵋派" )
                 return RANK_D->query_respect(this_player()) +
                  "非我弟子，不知此話從何談起？";
         if (query("book_count") < 1)
                 return "你來晚了，本派的秘籍不在此處。";
         addn("book_count", -1);
         ob = new("/d/emei/obj/fojing");
         ob->move(this_player());
         return "好吧，這本「"+ob->name()+"」你拿回去好好鑽研。";
}

mixed ask_skill10()
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

        message_sort(HIY "\n$n" HIY "微微一笑，對$N" HIY "說道：“既然你內"
                     "外功均已達至如此境界，也不枉了我平時的一翻栽培。今日"
                     "我便傳你此招，希望日後能將我峨嵋派發揚光大。”說完，"
                     "$n" HIY "將$N" HIY "招至跟前，在$N" HIY "耳旁輕聲細說"
                     "良久。\n\n" NOR, me, this_object());

        command("nod");
        command("say 剛才我所說的你都記清了嗎？記清了就下去練吧。");
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

mixed ask_skill11()
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

        if (me->query_skill("force") < 300)
                return "你的內功修行太淺，尚且學不了這一招。";

        if( query("max_neili", me)<3500 )
                return "你的內力修行太淺，尚且學不了這一招。";

        if (me->query_skill("piaoxue-zhang", 1) < 180)
                return "你的飄雪穿雲掌火候未到，尚且學不了這一招。";

        if( query("shen", me)<40000 )
                return "你行俠仗義的事情還做得不夠，我暫時還不能傳你此招。";

        message_sort(HIY "\n$n" HIY "輕輕拍了拍$N" HIY "的頭，說道：“好"
                     "吧，難得你如此有心，今日我就將此招演示一遍，可得看"
                     "好了！”話音剛落，只見$n" HIY "狂提內勁，周身骨骼無"
                     "不□啪作響，面赤如血，煞是驚人。隨即$n" HIY "一聲暴"
                     "喝，雙掌攜著隱隱風雷之勢猛力向前拍出，頓時只聽“喀"
                     "嚓”一聲巨響，前方崖邊一顆碗口粗的鬆樹應聲而斷，斷"
                     "枝仍是余勢未盡，向前又飛出數丈，這才跌落至山谷之中"
                     "。須臾，便聞山谷下回聲四起，在峨嵋群山中回盪了好一"
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

void reset()
{
        set("book_count",1);
}

/*
void unconcious()
{
        die();
}
*/
