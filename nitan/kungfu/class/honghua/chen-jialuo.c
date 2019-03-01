#include <ansi.h>
#include "honghua.h"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;
inherit F_QUESTER;

mixed ask_jiansuo();
mixed ask_skill1();
mixed ask_skill2();
mixed ask_skill3();
mixed ask_skill4();
mixed ask_skill5();
mixed ask_skill6();

#define JIANSUO    "/clone/lonely/jiansuo"

int try_to_learn_quan();
string ask_me();
string ask_ling();
int count=1;
void create()
{
        object ob;
        set_name("陳家洛", ({ "chen jialuo", "chen","jialuo" }));
        set("title", "紅花會少總舵主");
        set("long", "他一副模樣直是個富貴人家的紈褲子弟，豐\n"
                    "姿如玉，目朗似星，輕袍緩帶，手中搖著一\n"
                    "柄折扇，神採飛揚，氣度閒雅，吐屬斯文。\n"
                    "服飾儼然是個貴介公子。\n");
        set("nickname", HIW "玉面神龍" NOR);
        set("gender", "男性");
        set("class", "scholar");
        set("age", 22);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 40);
        set("int", 40);
        set("con", 40);
        set("dex", 40);
        set("max_qi", 5000);
        set("max_jing", 4000);
        set("neili", 6000);
        set("max_neili", 6000);
        set("jiali", 200);
        set("combat_exp", 4000000);
        set("score", 5000000);

        set_skill("force", 600);
        set_skill("zhanshen-xinjing", 600);
        set_skill("tianchi-neigong", 600);
        set_skill("honghua-xinfa", 600);
        set_skill("dodge", 600);
        set_skill("zhuangzi-wu", 600);
        set_skill("yanzi-chuanyun", 600);
        set_skill("parry", 600);
        set_skill("unarmed", 600);
        set_skill("baihua-cuoquan", 600);
        set_skill("claw", 600);
        set_skill("finger", 600);
        set_skill("strike", 600);
        set_skill("cuff", 600);
        set_skill("blade", 600);
        set_skill("hanwang-qingdao", 600);
        set_skill("sword", 600);
        set_skill("sanfen-jianshu", 600);
        set_skill("whip", 600);
        set_skill("jiandun-zhusuo", 600);
        set_skill("martial-cognize", 600);
        set_skill("literate", 600);

        map_skill("dodge", "zhuangzi-wu");
        map_skill("force", "zhanshen-xinjing");
        map_skill("unarmed", "baihua-cuoquan");
        map_skill("parry", "baihua-cuoquan");
        map_skill("sword", "sanfen-jianshu");
        map_skill("whip", "jiandun-zhusuo");
        map_skill("blade", "hanwang-qingdao");

        prepare_skill("unarmed", "baihua-cuoquan");

        set("no_teach", ([
                "sanfen-jianshu"  : "這劍法乃是我承蒙翠羽黃衫霍姑娘所授，並不外傳。",
                "hanwang-qingdao" : "嗯，這刀法你找文夫人駱冰學去吧，我不便教授。",
                "baihua-cuoquan"  : (: try_to_learn_quan :),
        ]));

        create_family("紅花會", 4, "少總舵主");

        set("inquiry", ([
                "紅花會" : (: ask_me :),
                "劍盾珠索"   : (: ask_jiansuo :),
                "縛字訣"     : (: ask_skill1 :),
                "千頭萬緒"   : (: ask_skill2 :),
                "化蝶"       : (: ask_skill3 :),
                "百花錯亂"   : (: ask_skill4 :),
                "百花錯易"   : (: ask_skill5 :),
                "戰神轟天訣" : (: ask_skill6 :),
        ]));

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "unarmed.luan" :),
                (: perform_action, "unarmed.yi" :),
                (: perform_action, "unarmed.hong" :),
                (: perform_action, "whip.qian" :),
                (: perform_action, "whip.fu" :),
                (: perform_action, "dodge.hua" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
                (: exert_function, "recover" :),
        }) );

        setup();

        if (clonep())
        {
                ob = find_object(JIANSUO);
                if (! ob) ob = load_object(JIANSUO);
                if (! environment(ob))
                {
                        ob->move(this_object());
                        ob->wield();
                }
        }

         carry_object(WEAPON_DIR"changjian")->wield();
        carry_object(__DIR__"obj/yaodai")->wear();
        carry_object(__DIR__"obj/bluecloth")->wear();
        add_money("gold", 2);
}
void init()
{
        object ob = this_player();

        ::init();

        add_action("do_say", "say");
}

int do_say(string arg)
{
        if( !arg || arg=="" ) return 0;

        if( arg=="青葉紅花白蓮藕")
        {
                write("陳家洛說道：天下英雄是一家。\n");
                message("vision", "陳家洛低聲道：原來是自家弟兄，不知有何見教？\n", this_player());
                set("inquiry", ([
                        "紅花令" : (: ask_ling :),
                ]));
        }
}
string ask_me()
{
        return RANK_D->query_respect(this_player())+ "，我紅花會乃天下第一大幫，專與清狗作對，哈...哈...";
}
string ask_ling()
{
        object ob,me;

        if (count == 0) return "紅花令已經傳出去了！\n";
        message_vision(HIR"陳家洛說道：“想要紅花令嗎？，先接我三招！\n"NOR,this_player());
        ob = this_object();
        me = this_player();
        COMBAT_D->do_attack(ob, me, query_temp("weapon") );
        COMBAT_D->do_attack(ob, me, query_temp("weapon") );
        COMBAT_D->do_attack(ob, me, query_temp("weapon") );

        set_temp("fighter", 1, me);
        ob->fight_ob(me);
        me->fight_ob(ob);
        command("halt");

        if( (query("qi", me)*100/query("max_qi", me)) >= 30 )
        {
                ob = new(__DIR__"obj/honghua-ling");
                ob->move(this_player());
                count=0;
                message_vision(HIY"陳家洛交給$N一支紅花令！\n"NOR, me);
                return "好，這是紅花令，兄弟你要好好保管！\n";
        }
        else return "你這樣武功怎能掌管紅花令？";
}


void attempt_apprentice(object me)
{
        if (! permit_recruit(me))
                return;

        if( query("shen", me)<65000 )
        {
                command("say 我紅花會乃為救天下蒼生而建，所做的一切無不"
                        "以俠義為重。");
                command("say 閣下在德行方面，似乎還做得不夠。");
                return;
        }

        if( query("combat_exp", me)<400000 )
        {
                command("say 你的江湖經驗太淺，我就算收了你，恐怕你也難"
                        "有所作為。");
                return;
        }

        if ((int)me->query_skill("honghua-xinfa", 1) < 100)
        {
                command("say 你本門的內功心法都未練透，如何跟我習高深的"
                        "武學？");
                return;
        }

        if( query("max_neili", me)<2000 )
        {
                command("say 我的武功全需強大的內功為輔，閣下似乎應該多"
                        "練練內力。");
                return;
        }

        command("nod");
        command("say 不錯，不錯。念在你如此有心，又乃我俠義中人，今日我便收下你。");
        command("say 希望閣下日後多行善事，為我紅花會發揚壯大。");
        command("recruit "+query("id", me));
}

int try_to_learn_quan()
{
        object me;
        object sob;
        int i;
        int flag;
        string *sub_skills;

        me = this_player();

        if( !query("can_learn/chen/baihua-cuoquan", me) && 
            query("family/master_id", me) != query("id") )
        {
                command("say 等你成為我的弟子後再說吧。");
                return -1;
        }

        if( query("shen", me)<100000 )
        {
                command("heng");
                command("say 我們紅花會在江湖上行走，講的就是“俠義”二字。");
                command("say 你連這都忘了，叫我如何敢傳功于你？");
                return -1;
        }

        sob = find_object(SKILL_D("baihua-cuoquan"));
        if (! sob) sob = load_object(SKILL_D("baihua-cuoquan"));
        if (! sob->valid_learn(me))
                return 0;
        if (me->query_skill("baihua-cuoquan", 1))
        {
                command("say 咦？你不是已經會了麼？自己下去好好練吧。");
                return -1;
        }

        sub_skills = keys(sob->query_sub_skills());
        flag = 0;
        for (i = 0; i < sizeof(sub_skills); i++)
        {
                if (me->query_skill(sub_skills[i], 1) >= 10)
                        continue;
                me->set_skill(sub_skills[i], 10);
                if (! flag)
                {
                        flag = 1;
                        command("say 不錯！我現在將這套百花錯拳傳授與你，"
                                "下去後要好好練習，他日必能融會貫通！");
                }
                write(HIC "你對" + to_chinese(sub_skills[i]) + "有了一"
                      "些領悟。\n" NOR);
        }

        if (! flag)
        {
                command("say 嗯？我不是叫你下去後自己練習嗎？");
                command("say 等你融會貫通之後再來找我吧。");
                return -1;
        }

        command("say 你自己下去練習吧，且記行走江湖，一切以俠義為重！");
        notify_fail("你自己下去好好練習吧。\n");
        return -1;
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/jiandun-zhusuo/fu", me) )
                return "這招我不是早就傳授給你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本會素無瓜葛，何出此言？";

        if (me->query_skill("jiandun-zhusuo", 1) < 1)
                return "你連劍盾珠索都沒學，還談什麼絕招可言？";

            if( query("family/gongji", me)<200 )
                return "你在會中所作的貢獻還不夠，這招我不忙傳你。";

        if( query("shen", me)<60000 )
                return "你俠義正事做得不夠，這招我不能傳你。";

        if( query("max_neili", me)<600 )
                return "你的內力修為不夠，學不成這招。";

        if (me->query_skill("jiandun-zhusuo", 1) < 50)
                return "你的劍盾珠索還練得不到家，自己下去練練再來吧！";

        message_vision(HIY "$n" HIY "點了點頭，將$N" HIY "招至"
                       "身邊，在耳旁低聲細說良久，$N" HIY "\n聽"
                       "後會心的一笑，看來大有所悟。\n" NOR, me,
                       this_object());

        command("nod");
        command("say 這招很簡單，稍微加以練習便成。");
        tell_object(me, HIC "你學會了「縛字訣」。\n" NOR);

        if (me->can_improve_skill("whip"))
                me->improve_skill("whip", 1500000);
        if (me->can_improve_skill("jiandun-zhusuo"))
                me->improve_skill("jiandun-zhusuo", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/jiandun-zhusuo/fu", 1, me);
          addn("family/gongji", -200, me);

        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_perform/jiandun-zhusuo/qian", me) )
                return "這招我不是早就傳授給你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本會素無瓜葛，何出此言？";

        if (me->query_skill("jiandun-zhusuo", 1) < 1)
                return "你連劍盾珠索都沒學，還談什麼絕招可言？";

            if( query("family/gongji", me)<1200 )
                return "你在會中所作的貢獻還不夠，這招我不忙傳你。";

        if( query("shen", me)<100000 )
                return "你俠義正事做得不夠，這招我不能傳你。";

        if (me->query_skill("force") < 180)
                return "你的內力修為不夠，學不成這招。";

        if (me->query_skill("jiandun-zhusuo", 1) < 120)
                return "你的劍盾珠索還練得不到家，自己下去練練再來吧！";

        message_vision(HIY "$n" HIY "對$N" HIY "讚許地點了點頭，道：“既"
                       "然你如此有心，今日\n我便傳你此招。”$n" HIY "招"
                       "了招手，$N" HIY "連忙走上前去，只見\n$n" HIY "輕"
                       "聲在$N" HIY "說了些話，接著手中長索一抖，登時幻"
                       "出漫\n天鞭影，宛如蛟龍通天，無數鞭影向四面八方勁"
                       "點而去。\n" NOR, me, this_object());

        command("smile");
        command("say 這招最是注重腕部的力道，下去後需勤加練習。");
        tell_object(me, HIC "你學會了「千頭萬緒」。\n" NOR);

        if (me->can_improve_skill("whip"))
                me->improve_skill("whip", 1500000);
        if (me->can_improve_skill("jiandun-zhusuo"))
                me->improve_skill("jiandun-zhusuo", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/jiandun-zhusuo/qian", 1, me);
          addn("family/gongji", -1200, me);

        return 1;
}

mixed ask_skill3()
{
        object me;

        me = this_player();

        if( query("can_perform/zhuangzi-wu/hua", me) )
                return "這招我不是已經教給你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本會素無瓜葛，何出此言？";

        if (me->query_skill("zhuangzi-wu", 1) < 1)
                return "你連莊子舞都沒學，還談什麼絕招可言？";

            if( query("family/gongji", me)<1000 )
                return "你在會中所作的貢獻還不夠，這招我不忙傳你。";

        if( query("shen", me)<100000 )
                return "你俠義正事做得不夠，這招我不能傳你。";

        if ((int)me->query_dex() < 32)
                return "你的身法靈動性不足，學不成這招。";

        if( query("max_neili", me)<2000 )
                return "你的內力修為不夠，學不成這招。";

        if (me->query_skill("zhuangzi-wu", 1) < 150)
                return "你的莊子舞還練得不到家，自己下去練練再來吧！";

        message_vision(HIY "$n" HIY "微微一笑，對$N" HIY "點頭道："
                       "“你今日有此造詣，傳你這\n招，又有何難？”"
                       "說話隨即一聲清嘯，身形一展，舞步宛如\n行雲"
                       "流水、彩蝶飛揚般，速度變得異常敏捷。$N" HIY
                       "見得如此神\n妙的舞步，不禁讚嘆不已。\n" NOR,
                       me, this_object());

        command("smile");
        command("say 這套莊子舞如有聲樂配合施展，效果更佳。");
        tell_object(me, HIC "你學會了「化蝶」。\n" NOR);

        if (me->can_improve_skill("dodge"))
                me->improve_skill("dodge", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("zhuangzi-wu"))
                me->improve_skill("zhuangzi-wu", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/zhuangzi-wu/hua", 1, me);
          addn("family/gongji", -1000, me);

        return 1;
}

mixed ask_skill4()
{
        object me;

        me = this_player();

        if( query("can_perform/baihua-cuoquan/luan", me) )
                return "這招我不是已經教給你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本會素無瓜葛，何出此言？";

        if (me->query_skill("baihua-cuoquan", 1) < 1)
                return "你連百花錯拳都沒學，還談什麼絕招可言？";

            if( query("family/gongji", me)<400 )
                return "你在會中所作的貢獻還不夠，這招我不忙傳你。";

        if( query("shen", me)<80000 )
                return "你俠義正事做得不夠，這招我不能傳你。";

        if( query("max_neili", me)<2000 )
                return "你的內力修為不夠，學不成這招。";

        if (me->query_skill("baihua-cuoquan", 1) < 120)
                return "你的百花錯拳還練得不到家，自己下去練練再來吧！";

        message_vision(HIY "$n" HIY "對$N" HIY "點了點頭，說道：“我給"
                       "你演示一遍，可要仔細\n看好了。”說罷只見$n" HIY
                       "頓步沉身，雙掌交錯打出，掌鋒\n拳影重重疊疊，虛"
                       "實難辨。\n" NOR, me, this_object());

        command("smile");
        command("say 這一招便是百花錯亂，是以快打慢的上層拳術。");
        tell_object(me, HIC "你學會了「百花錯亂」。\n" NOR);

        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1500000);
        if (me->can_improve_skill("baihua-cuoquan"))
                me->improve_skill("baihua-cuoquan", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/baihua-cuoquan/luan", 1, me);
          addn("family/gongji", -400, me);

        return 1;
}

mixed ask_skill5()
{
        object me;

        me = this_player();

        if( query("can_perform/baihua-cuoquan/yi", me) )
                return "這招我不是已經教給你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本會素無瓜葛，何出此言？";

        if (me->query_skill("baihua-cuoquan", 1) < 1)
                return "你連百花錯拳都沒學，還談什麼絕招可言？";

            if( query("family/gongji", me)<1000 )
                return "你在會中所作的貢獻還不夠，這招我不忙傳你。";

        if( query("shen", me)<100000 )
                return "你俠義正事做得不夠，這招我不能傳你。";

        if( query("max_neili", me)<3000 )
                return "你的內力修為不夠，學不成這招。";

        if ((int)me->query_skill("force") < 280)
                return "你的內功修為不夠，學不成這招。";

        if (me->query_skill("baihua-cuoquan", 1) < 150)
                return "你的百花錯拳還練得不到家，自己下去練練再來吧！";

        message_vision(HIY "$n" HIY "對$N" HIY "微微一笑，說道：“看"
                       "好了！”只聽$n" HIY "話音\n剛落，隨即大喝一"
                       "聲，雙掌紛飛，擒拿手中夾著鷹爪功，左\n手查拳"
                       "，右手綿掌。攻出去八卦掌，收回時已是太極拳，"
                       "諸\n家雜陳，毫無規律，舖天蓋地連續貫出。氣勢"
                       "恢弘，無與倫\n比。只看得$N" HIY "呆立當場，"
                       "不知所措。\n" NOR, me, this_object());

        command("smile");
        command("say 這百花錯易的精妙便是一個“錯”字，你下去後慢慢體會吧。");
        tell_object(me, HIC "你學會了「百花錯易」。\n" NOR);

        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1500000);
        if (me->can_improve_skill("baihua-cuoquan"))
                me->improve_skill("baihua-cuoquan", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/baihua-cuoquan/yi", 1, me);
          addn("family/gongji", -1000, me);

        return 1;
}

mixed ask_skill6()
{
        object me;

        me = this_player();

        if( query("can_perform/baihua-cuoquan/hong", me) )
                return "我已將拳訣盡數傳予了你，還有什麼疑問？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本會素無瓜葛，何出此言？";

        if (me->query_skill("baihua-cuoquan", 1) < 1)
                return "你連百花錯拳都沒學，還談什麼絕招可言？";

            if( query("family/gongji", me)<2500 )
                return "你在會中所作的貢獻還不夠，這招我不忙傳你。";

        if( query("shen", me)<150000 )
                return "你俠義正事做得不夠，這招我不能傳你。";

        if( query("max_neili", me)<5000 )
                return "你的內力修為不夠，學不成這招。";

        if (me->query_skill("baihua-cuoquan", 1) < 250)
                return "你的百花錯拳還練得不到家，自己下去練練再來吧！";

        if (me->query_skill("zhanshen-xinjing", 1) < 250)
                return "你的戰神心經修為不夠，自己下去練練再來吧！";

        message_vision(HIY "$n" HIY "對$N" HIY "微微一笑，嘆道：“你"
                       "今日造詣非凡，確有能力\n繼承我這拳法，我先將"
                       "總訣說予你聽罷。方今之時，臣以神\n遇，而不以"
                       "目視，官知止而神欲行，依乎天理，批大卻，導\n"
                       "大竅，因其固然……”$N" HIY "聽得滿臉迷茫，問"
                       "道：“師父，這\n…不是《莊子》中庖丁解……”"
                       "$n" HIY "笑道：“起初我也是\n這般的懷疑，但破"
                       "敵秘訣，卻盡都在此。”說完便接著沉吟\n道：“"
                       "行為遲，動刀甚微，孑然已解，如土委地，提刀而"
                       "立，\n為之四顧，為之躊躇滿志……”良久，良久"
                       "……。\n" NOR, me, this_object());

        command("smile");
        command("say 這本是我在玉峰上領悟的拳訣，今日傳給了你，望你好自為之。");
        tell_object(me, HIC "你學會了「戰神轟天訣」。\n" NOR);

        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1500000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1500000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1500000);
        if (me->can_improve_skill("baihua-cuoquan"))
                me->improve_skill("baihua-cuoquan", 1500000);
        if (me->can_improve_skill("baihua-cuoquan"))
                me->improve_skill("baihua-cuoquan", 1500000);
        if (me->can_improve_skill("baihua-cuoquan"))
                me->improve_skill("baihua-cuoquan", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("zhanshen-xinjing"))
                me->improve_skill("zhanshen-xinjing", 1500000);
        if (me->can_improve_skill("zhanshen-xinjing"))
                me->improve_skill("zhanshen-xinjing", 1500000);
        if (me->can_improve_skill("zhanshen-xinjing"))
                me->improve_skill("zhanshen-xinjing", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/baihua-cuoquan/hong", 1, me);
          addn("family/gongji", -2500, me);

        return 1;
}

mixed ask_jiansuo()
{
        object me;
        object ob;
        object owner;

        me = this_player();
        if (me->is_bad())
        {
                if( query("family/family_name", me) == "紅花會" )
                        message_vision(CYN "$N" CYN "冷哼一聲，對$n" CYN "道："
                                       "“你行為如此不恥，居然還敢來問我要劍盾"
                                       "珠索？”\n" NOR, this_object(), me);
                else
                        message_vision(CYN "$N" CYN "冷笑一聲，對$n" CYN "說道"
                                       "：“好一個姦惡之徒，竟敢貪圖我的隨身利"
                                       "器！”\n" NOR, this_object(), me);
                return 1;
        }

        if( query("family/family_name", me) != "紅花會" )
                return "你又不是我們紅花會的兄弟，打聽它幹什麼？";

        if( query("family/master_id", me) != query("id") )
                return "只有我的弟子才能用我這劍盾珠索。";

        if( query("shen", me)<80000 )
                return "你俠義正事做得還不夠，這劍盾珠索我不能教給你。";

        if (me->query_skill("jiandun-zhusuo", 1) < 120)
                return "你連劍盾珠索都沒學好，就算用也是白搭。";

        ob = find_object(JIANSUO);
        if (! ob) ob = load_object(JIANSUO);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "劍盾珠索現在不就在你手裡嗎？";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "你來晚了一步，劍盾珠索我已經借出去了。";

                if( query("family/family_name", owner) == "紅花會" )
                        return "劍盾珠索現在是我們紅花會的"+query("name", owner)+
                               "在用，你要用就去找他吧。";
                else
                        return "我的劍盾珠索現在落入了"+query("name", owner)+
                               "之手，你去把它取回來吧！";
        }

        ob->move(this_object());
        message_vision(CYN "$N" CYN "微微一笑，道：“這劍盾珠索你就"
                       "拿去，多用它行俠仗義，懲姦除惡。”\n" NOR,
                       this_object(), me);
        command("givejiandunzhusuoto"+query("id", me));
        return 1;
}
