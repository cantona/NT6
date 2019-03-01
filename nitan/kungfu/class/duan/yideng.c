#include <ansi.h>
#include "duan.h"

inherit NPC;
inherit F_MASTER;

string ask_me();
mixed ask_skill1();
mixed ask_skill2();
string ask_recover();
int do_answer(string arg);

void create()
{
            set_name("一燈大師", ({ "yideng dashi", "yideng", "dashi" }));
            set("long", @LONG
一燈大師乃江湖中人稱“東邪西毒，南帝北丐”中
的南帝段皇爺，當年憑著段氏“一陽指”而獨步武
林，罕逢敵手。但卻在中年時因一段悲情而出家為
僧，之後大徹大悟，成為一位得道高僧。
LONG );
            set("title", "大理國退位皇帝");
            set("nickname", HIY "南帝" NOR);
            set("gender", "男性");
            set("age", 71);
            set("shen_type", 1);
            set("attitude", "friendly");

            set("str", 33);
            set("int", 35);
            set("con", 38);
            set("dex", 33);

            set("qi", 6500);
            set("max_qi", 6500);
            set("jing", 5000);
            set("max_jing", 5000);
            set("neili", 8000);
            set("max_neili", 8000);
            set("jiali", 200);
            set("combat_exp", 4000000);
            set("score", 500000);

        set_skill("force", 640);
        set_skill("xiantian-gong", 600);
        set_skill("duanshi-xinfa", 640);
        set_skill("kurong-changong", 640);
        set_skill("dodge", 640);
        set_skill("tiannan-bu", 640);
        set_skill("cuff", 600);
        set_skill("jinyu-quan", 600);
        set_skill("strike", 600);
        set_skill("wuluo-zhang", 600);
        set_skill("sword", 600);
        set_skill("staff", 600);
        set_skill("duanjia-jian", 600);
        set_skill("finger", 640);
        set_skill("qiantian-zhi", 640);
        set_skill("sun-finger", 640);
        set_skill("parry", 600);
        set_skill("jingluo-xue", 600);
        set_skill("buddhism", 640);
        set_skill("literate", 600);
        set_skill("sanscrit", 600);
        set_skill("qimai-liuzhuan", 700);
        set_skill("martial-cognize", 640);

        map_skill("force", "xiantian-gong");
        map_skill("dodge", "tiannan-bu");
        map_skill("finger", "sun-finger");
        map_skill("cuff", "jinyu-quan");
        map_skill("strike", "wuluo-zhang");
        map_skill("parry", "sun-finger");
        map_skill("sword", "duanjia-jian");
        map_skill("staff", "sun-finger");

        prepare_skill("finger", "sun-finger");

        create_family("段氏皇族", 11, "傳人");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "finger.jian" :),
                (: perform_action, "finger.qian" :),
                (: perform_action, "finger.dian" :),
                (: perform_action, "finger.die" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

            set("inquiry",([
                  "王重陽"   : "中神通王重陽名動江湖，老衲很是佩服。",
                  "瑛姑"     : "那是老衲出家前的一段孽緣，不提也罷。",
                  "老頑童"   : "呵呵，那人武功高強，可是心機卻如頑童一般。",
                  "周伯通"   : "呵呵，那人武功高強，可是心機卻如頑童一般。",
                  "郭靖"     : "哦，那個憨小子心地善良，忠厚老實，沒黃蓉一定要吃虧。",
                 "黃蓉"     : "是郭靖那憨小子的伴侶吧，人倒很是機靈。",
                  "知識"     : "我可以傳授你禪宗心法和梵文，其它的找你的師父學習吧。",
                  "傳授"     : "我可以傳授你禪宗心法和梵文，其它的找你的師父學習吧。",
                  "陽關三疊" : (: ask_skill1 :),
                "一陽指"   : (: ask_me :),
                "乾陽劍氣" : (: ask_skill2 :),
                "療傷"     : (: ask_recover :),
                "治療"     : (: ask_recover :),
            ]));

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

            set("master_ob", 5);
        setup();
            carry_object("/clone/cloth/seng-cloth")->wear();
}

void init()
{
        object ob;
        ::init();
        add_action("do_answer","answer");

                 if (interactive(ob = this_player()) && ! is_fighting())
                 {
                   remove_call_out("greeting");
                   call_out("greeting", 1, ob);
                   }
}

void greeting(object ob)
{
        if (! ob || environment(ob) != environment()) return;

        if( query("shen", ob)<-50000 )
                command("say 這位施主眼中戾氣深重，勸施主好自為知。");

        else
        if( query("shen", ob)<-5000 )
                command("say 這位施主，切記魔從心起，其道必誅。");

        else
        if( query("shen", ob)<0 )
                command("say 這位施主，人行江湖，言行當正，切務走進邪魔歪道。");

        else
        if( query("shen", ob)>50000 )
                command("say 施主行事光明磊落，日後必為武林翹楚。");

        else
                command("say 這位施主，光明正道任人走，望施主多加保重。");

        return;
}

int recognize_apprentice(object me, string skill)
{
        if( query("shen", me)<0 )
        {
                command("say 施主眼中戾氣深重，多行善事之後老衲自會傳授給你。");
                return -1;
        }

        if (skill != "sanscrit" && skill != "buddhism" && skill != "jingluo-xue")
        {
                command("say 這些還是向你的師父學吧，老衲只能傳授些知識給你。");
                return -1;
        }

        if (skill == "buddhism" && me->query_skill("buddhism", 1) > 5000)
        {
                command("haha");
                command("say 你的佛法造詣已經非同凡響了，剩下的自己去研究吧。");
                return -1;
        }

        if( !query_temp("can_learn/yideng", me) )
        {
                command("say 南無阿弭佗佛。");
                command("say 既然施主有心面佛，老衲自當竭力傳授。");
                set_temp("can_learn/yideng", 1, me);
        }

        return 1;
}
string ask_me()
{
        object me;

        me = this_player();

        if( query("shen", me)<0 )
                return "施主眼中戾氣深重，多行善之後老衲自會傳授給你。";

        if (me->query_skill("sun-finger", 1) > 600)
               return "你的一陽指練到了這種境界，老衲已沒什麼可教的了。";

        if( query("family/family_name", me) != query("family/family_name") )
               return "不是老衲吝嗇，你不是我段家之人，若由老衲之手將這絕學傳于它處，恐怕不妥。";

        if( query("combat_exp", me)<500000 )
               return "武功最注重根基，切莫貪圖捷徑，你把基本功練好後老衲自會傳授給你。";

        addn_temp("can_learn/yideng/sun-finger", 1, me);
               return "好吧！老衲就傳授一陽指絕技給你，但切記人行江湖，言行當正，不要走進邪魔歪道！";
}
mixed ask_skill1()
{
        object me;

        me = this_player();
        if( query("can_perform/sun-finger/die", me) )
                return "你一陽指練到這種境界，老衲已沒什麼可教的了。";

        if( query("family/family_name", me) != query("family/family_name") )
                return "施主與老衲素不相識，不知施主此話從何說起？";

        if (me->query_skill("sun-finger", 1) < 1)
                return "你連一陽指訣都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<2500 )
                return "你為段氏所作出的貢獻還不夠，這招老衲暫時還不能傳你。";

        if( query("shen", me)<50000 )
                return "你的俠義正事還做得不夠，這招老衲暫時還不能傳你。";

        if (me->query_skill("force") < 300)
                return "你內功的修為還不夠，練高了再來吧。";

        if( query("max_neili", me)<5000 )
                return "你的內力修為還不夠，練高點再來吧。";

        if (me->query_skill("jingluo-xue", 1) < 200)
                return "你對經絡學的了解還不透徹，研究透了再來找我吧。";

        if (me->query_skill("sun-finger", 1) < 200)
                return "你的一陽指訣功力還不夠，練高了再說吧。";

        message_sort(HIY "\n$n" HIY "凝視了$N" HIY "好一會兒，隨即點了點"
                     "頭，將$N" HIY "招至身邊，在耳旁低聲細說良久，$N" HIY
                     "聽後會心的一笑，看來對$n" HIY "的教導大有所悟。\n\n"
                     NOR, me, this_object());

        command("buddhi");
        command("say 老衲已將此絕技傳授給你，切記莫走進邪魔歪道！");
        tell_object(me, HIC "你學會了「陽關三疊」。\n" NOR);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("jingluo-xue"))
                me->improve_skill("jingluo-xue", 1500000);
        if (me->can_improve_skill("jingluo-xue"))
                me->improve_skill("jingluo-xue", 1500000);
        if (me->can_improve_skill("jingluo-xue"))
                me->improve_skill("jingluo-xue", 1500000);
        if (me->can_improve_skill("finger"))
                me->improve_skill("finger", 1500000);
        if (me->can_improve_skill("finger"))
                me->improve_skill("finger", 1500000);
        if (me->can_improve_skill("finger"))
                me->improve_skill("finger", 1500000);
        if (me->can_improve_skill("sun-finger"))
                me->improve_skill("sun-finger", 1500000);
        if (me->can_improve_skill("sun-finger"))
                me->improve_skill("sun-finger", 1500000);
        if (me->can_improve_skill("sun-finger"))
                me->improve_skill("sun-finger", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/sun-finger/die", 1, me);
        addn("family/gongji", -2500, me);

        return 1;
}
mixed ask_skill2()
{
        object me;

        me = this_player();
        if( query("can_perform/xiantian-gong/jian", me) )
                return "你先天功的乾陽劍氣練到這種境界，老衲已沒什麼可教的了。";

        if( query("family/family_name", me) != query("family/family_name") )
                return "施主與老衲素不相識，不知施主此話從何說起？";

        if (me->query_skill("sun-finger", 1) < 1)
                return "你連一陽指訣都沒學，還談什麼絕招可言？";

        if (me->query_skill("xiantian-gong", 1) < 1)
                return "這招暫時不能傳授于你，等你學會先天功再來找我吧。";

        if( query("family/gongji", me)<2500 )
                return "你為段氏所作出的貢獻還不夠，這招老衲暫時還不能傳你。";

        if( query("shen", me)<50000 )
                return "你的俠義正事還做得不夠，這招老衲暫時還不能傳你。";

        if (me->query_skill("force") < 600)
                return "你內功的修為還不夠，練高了再來吧。";

        if( query("max_neili", me)<5000 )
                return "你的內力修為還不夠，練高點再來吧。";

        if (me->query_skill("xiantian-gong", 1) < 600)
                return "你的先天功功力還不夠，練高了再說吧。";

        message_sort(HIY "\n$n" HIY "凝視了$N" HIY "好一會兒，隨即點了點"
                     "頭，將$N" HIY "招至身邊，在耳旁低聲細說良久，$N" HIY
                     "聽後會心的一笑，看來對$n" HIY "的教導大有所悟。\n\n"
                     NOR, me, this_object());

        command("buddhi");
        command("say 這本是中神通的絕技，現老衲已將此絕技傳授給你，切記莫走進邪魔歪道！");
        tell_object(me, HIC "你學會了「乾陽劍氣」。\n" NOR);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("finger"))
                me->improve_skill("finger", 1500000);
        if (me->can_improve_skill("finger"))
                me->improve_skill("finger", 1500000);
        if (me->can_improve_skill("finger"))
                me->improve_skill("finger", 1500000);
        if (me->can_improve_skill("xiantian-gong"))
                me->improve_skill("xiantian-gong", 1500000);
        if (me->can_improve_skill("xiantian-gong"))
                me->improve_skill("xiantian-gong", 1500000);
        if (me->can_improve_skill("sun-finger"))
                me->improve_skill("sun-finger", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/xiantian-gong/jian", 1, me);
        addn("family/gongji", -2500, me);

        return 1;
}

string ask_recover()
{
        object me;
        me = this_player();

        if (environment(me)!=find_object("/d/heizhao/houyuan"))
                return "施主問的是什麼？貧僧不知道啊。\n";
        if( query_temp("yideng_asked", me) )
                return "你需要治療嗎？\n";
        else {
                if( query("family/family_name", me) == "段氏皇族" )
                {
                        set_temp("yideng_asked", 1, me);
                        return "你虔心向佛，老衲自然有義務為你治療，但不知你是否需要？\n";
                }
                else {
                        set_temp("yideng_asked", 1, me);
                        return "施主既然有緣到來舍下，貧僧自有義務盡地主之宜為閣下治療，不知閣下是否需要？\n";
                }
        }
}

int do_answer(string arg)
{
        object me;
        me=this_player();

        if( arg == "需要治療" && query_temp("yideng_asked", me) )
        {
                tell_object(me, "你請求一燈大師為你運功治療。\n");
                delete_temp("yideng_asked", me);
                if( query("dali/yideng_rewarded", me) )
                {
                        // command("look "+getuid(me));
                        command("say 由老衲治療一次，你已經得盡天緣了，唉。。。");
                        command("say 為人豈可貪得無厭，唉，請你離開這裡吧。");
                        message_vision("$N羞愧難當，面色通紅，灰溜溜地離開了。\n", me);
                        me->move("/d/heizhao/maze1");
                        return 1;
                }
                if( query("family/family_name", me) == "段氏皇族" )
                {
                        command("pat "+getuid(me));
                        command("smile");
                        command("say 好的，老衲這就給你治療。你隨我到禪房來。");
                        set_temp("yideng_waitreward", 1, me);
                        delete_temp("yideng_asked", me);
                        this_object()->move("/d/heizhao/chanfang");
                        me->move("/d/heizhao/chanfang");
                        command("say 你準備好了就告訴我。");
                        return 1;
                }
                if( query("kar", me)>random(30) )
                {
                        // command("look "+getuid(me));
                        command("smile");
                        command("say 好的，老衲這就給你治療。你隨我到禪房來。");
                        set_temp("yideng_waitreward", 1, me);
                        delete_temp("yideng_asked", me);
                        this_object()->move("/d/heizhao/chanfang");
                        me->move("/d/heizhao/chanfang");
                        command("say 你準備好了就告訴我。");
                        return 1;
                }
                else {
                        // command("look "+getuid(me));
                        command("sigh");
                        command("say 實在抱歉，施主您緣分不夠，老衲不能為你治療。");
                        command(":(");
                        delete_temp("yideng_asked", me);
                        set("dali/yideng_rewarded", 1, me);
                        return 1;
                }
        }
        if (arg == "我準備好了"
                 && query_temp("yideng_waitreward", me )
                && environment(me)==find_object("/d/heizhao/chanfang"))
        {
                command("nod");
                command("say 你坐正，我這就開始為你治療了。");
                write("一燈當即閉目垂眉，入定運功，忽的躍起，左掌捂胸，右手伸出 \n");
                write("食指，緩緩的向你頭頂百會穴點去。你身不由幾的微微一跳，\n");
                write("只覺的一股熱氣從頂門直透下來。\n");
                write("一燈一指點過，立即縮回，第二指已向點向你的百會穴後一寸五\n");
                write("分處的後頂穴，接著強間，腦戶，風府，大錐，陶道，身柱，\n");
                write("神道，靈台一路點將下來。一支香燃了一半，已將你督脈的三十 \n");
                write("大穴順次點到。\n");
                message_vision(HIR "$N突然覺得一股暖流自頂而入，眼前一黑就什麼也看不見了！\n" NOR, me );
                me->unconcious();

                // if (me->query("family/family_name") == "段氏皇族")
                {
                        addn("con", 2, me);
                        addn("dex", 1, me);
                        addn("str", 1, me);
                }
                addn("max_neili", 150, me);
                addn("combat_exp", 15000, me);
                set("dali/yideng_rewarded", 1, me);
                delete_temp("yideng_waitreward", me);
                this_object()->move("/d/heizhao/houyuan");
                me->move("/d/heizhao/houyuan");
                return 1;
        }
        write("你想回答什麼(你的回答好像不對)\n");
        return 1;
}
