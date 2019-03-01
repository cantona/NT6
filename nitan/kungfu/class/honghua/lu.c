#include <ansi.h>

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;

mixed ask_jian();
mixed ask_zhen();
mixed ask_skill1();
mixed ask_skill2();
mixed ask_skill3();

#define BAILONG    "/clone/lonely/bailongjian"

void create()
{
        object ob;
        set_name("陸菲青", ({ "lu feiqing", "lu", "feiqing" }));
        set("long", "陸菲青，乃武當派大俠，壯年時在大江南北\n"
                    "行俠仗義，端的名震江湖。至屠龍幫瓦解冰\n"
                    "消，陸菲青遠走邊疆，當時清廷曾四下派人\n"
                    "追拿，但他為人機警，兼之武功高強，得脫\n"
                    "大難，但清廷繼續嚴加查緝。\n");
        set("nickname", HIW "綿裡針" NOR);
        set("gender", "男性");
        set("class", "scholar");
        set("age", 62);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("per", 23);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        
        set("max_qi", 6000);
        set("max_jing", 5000);
        set("neili", 7000);
        set("max_neili", 7000);
        set("jiali", 200);
        set("combat_exp", 4000000);
        set("score", 500000);

        set_skill("force", 260);
        set_skill("taiji-shengong", 260);
        set_skill("unarmed", 240);
        set_skill("xuangong-quan", 240);
        set_skill("dodge", 240);
        set_skill("tiyunzong", 240);
        set_skill("sword", 240);
        set_skill("rouyun-jian", 240);
        set_skill("taiji-jian", 240);
        set_skill("parry", 240);
        set_skill("throwing", 240);
        set_skill("furong-jinzhen", 240);
        set_skill("martial-cognize", 220);
        set_skill("literate", 220);

        map_skill("force"  , "taiji-shengong");
        map_skill("sword"  , "rouyun-jian");
        map_skill("unarmed" , "xuangong-quan");
        map_skill("dodge"  , "tiyunzong");
        map_skill("parry"  , "taiji-jian");
        map_skill("throwing"  , "furong-jinzhen");

        prepare_skill("unarmed", "xuangong-quan");

        set("inquiry", ([
                "芙蓉金針"   : (: ask_zhen :),
                "白龍劍"     : (: ask_jian :),
                "金針現影"   : (: ask_skill1 :),
                "三環套月"   : (: ask_skill2 :),
                "玄功無極勁" : (: ask_skill3 :),
        ]));

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "unarmed.xuan" :),
                (: perform_action, "sword.tao" :),
                (: perform_action, "throwing.xian" :),
                (: exert_function, "shield" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }) );

        create_family("武當派", 17, "掌門");

        set("zhen_count", 3);

        setup();

        if (clonep())
        {
                ob = find_object(BAILONG);
                if (! ob) ob = load_object(BAILONG);
                if (! environment(ob))
                {
                        ob->move(this_object());
                        ob->wield();
                } else
                {
                        ob = new("/clone/weapon/changjian");
                        ob->move(this_object());
                        ob->wield();
                }
        }

        carry_object("/d/wudang/obj/greyrobe")->wear();
        set_temp("handing", carry_object("/d/kaifeng/npc/obj/jinzhen"));
}

void attempt_apprentice(object ob)
{
        command("sigh");
        command("say 我不收徒，若要拜師你直接去武當山好了。");
}

int recognize_apprentice(object ob, string skill)
{
        if( query("family/family_name", ob) != "紅花會" && 
           query("family/family_name", ob) != "武當派" )
        {
                command("hmm");
                command("say 貧道與閣下素無淵源，何談傳授二字？\n");
                return -1;
        }

        if( query("family/family_name", ob) == "武當派" )
        {
                command("sigh");
                command("say 我已經說過我不收徒了，這些你還是去找你師父學吧。\n");
                return -1;
        }

        if( query("family/master_id", ob) != "chenjialuo" && 
           query("family/master_id", ob) != "wuchendaozhang" && 
           query("family/master_id", ob) != "zhaobanshan" )
        {
                command("say 貧道與閣下不甚相熟，功夫還是找你師父學去吧。\n");
                return -1; 
        }

        if( query("shen", ob)<50000 )
        {
                command("hmm");
                command("say 我素來敬佩紅花會的好漢，但閣下的德行似乎不怎麼樣。");
                return -1;
        }

        if (skill != "sword" && skill != "rouyun-jian" &&
           skill != "unarmed" && skill != "xuangong-quan" &&
           skill != "throwing" && skill != "furong-jinzhen")
        {
                command("shake");
                command("say 我只傳授你一些劍法、拳腳和暗器的功夫，其它還是找你師父學吧。");
                return -1;
        }

        if (skill == "sword" && ob->query_skill("sword", 1) > 179)
        {
                command("say 你的劍法造詣已經非同凡響了，剩下就自己去練吧。");
                return -1;
        }

        if (skill == "unarmed" && ob->query_skill("unarmed", 1) > 179)
        {
                command("say 你的拳腳功夫已經非同凡響了，剩下就自己去練吧。");
                return -1;
        }

        if (skill == "throwing" && ob->query_skill("throwing", 1) > 179)
        {
                command("say 你的暗器手法已經非同凡響了，剩下就自己去練吧。");
                return -1;
        }

        if( !query_temp("can_learn/lufeiqing", ob) )
        {
                command("say 現在大敵當前，我也顧不了武當派的什麼門規了。");
                command("say 這柔雲劍法、無極玄功拳及芙蓉金針是我生平絕學，就傳給你好了。");
                set_temp("can_learn/lufeiqing", 1, ob);
        }
        return 1;
}

mixed ask_skill1()
{
        object me;

        me = this_player();
        if( query("can_perform/furong-jinzhen/xian", me) )
                return "自己下去練，能教的我都盡數教給你了。";

        if( query("family/family_name", me) != "紅花會" && 
           query("family/family_name", me) != "武當派" )
                return "貧道與閣下素無淵源，不知閣下這話從何而來？";

        if (me->query_skill("furong-jinzhen", 1) < 1)
                return "你連芙蓉金針都沒學，還談什麼絕招可言？";

            if( query("family/gongji", me)<300 )
                return "嗯，你對"+query("family/family_name", me)+CYN
                       "所作的貢獻不夠，這招我不傳你。";

        if( query("shen", me)<30000 )
                return "你俠義正事做得不夠，這招我不能傳你。";

        if (me->query_skill("force") < 120)
                return "你的內功火候不足，用不了這一招！";

        if (me->query_skill("furong-jinzhen", 1) < 80)
                return "你芙蓉金針尚未修煉得精深，難以運用此招。";

        message_vision(HIY "$n" HIY "對$N" HIY "笑了笑，俯身從腰囊"
                       "中拈出一根金針，輕輕彈出，頓時只\n聽“颼”"
                       "的一聲，金針化作一道金芒，沒入$N" HIY "腳"
                       "跟前的青石地，只留\n下一個小孔。\n" NOR,
                       me, this_object());

        command("nod");
        command("say 要訣都記住了嗎？剩下就靠你自己練了。");
        tell_object(me, HIC "你學會了「金針現影」。\n" NOR);

        if (me->can_improve_skill("throwing"))
                me->improve_skill("throwing", 1500000);
        if (me->can_improve_skill("furong-jinzhen"))
                me->improve_skill("furong-jinzhen", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/furong-jinzhen/xian", 1, me);
          addn("family/gongji", -300, me);
        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();
        if( query("can_perform/rouyun-jian/tao", me) )
                return "這招你不是已經學會了嗎？";

        if( query("family/family_name", me) != "紅花會" && 
           query("family/family_name", me) != "武當派" )
                return "貧道與閣下素無淵源，不知閣下這話從何而來？";

        if (me->query_skill("rouyun-jian", 1) < 1)
                return "你連柔雲劍法都沒學，還談什麼絕招可言？";

            if( query("family/gongji", me)<700 )
                return "嗯，你對"+query("family/family_name", me)+CYN
                       "所作的貢獻不夠，這招我不傳你。";

        if( query("shen", me)<60000 )
                return "你俠義正事做得不夠，這招我不能傳你。";

        if (me->query_skill("force") < 180)
                return "你的內功修行太淺，用不了這一招！";

        if (me->query_skill("dodge") < 180)
                return "你的輕功修為不夠，用不了這一招！";

        if (me->query_skill("rouyun-jian", 1) < 140)
                return "你柔雲劍法尚未修煉得精深，難以運用此招。";

        message_vision(HIY "$n" HIY "微微一笑，從懷中輕輕取出了一本"
                       "劍譜，指著其中一段對$N" HIY "細\n說良久，$N"
                       HIY "一邊聽一邊點頭。\n" NOR, me, this_object());

        command("nod");
        command("say 這些全都是三環套月的精妙所在，你下去慢慢練吧。");
        tell_object(me, HIC "你學會了「三環套月」。\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("rouyun-jian"))
                me->improve_skill("rouyun-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/rouyun-jian/tao", 1, me);
          addn("family/gongji", -700, me);
        return 1;
}

mixed ask_skill3()
{
        object me;

        me = this_player();
        if( query("can_perform/xuangong-quan/xuan", me) )
                return "這招我已經教過你了，自己下去練吧。";

        if( query("family/family_name", me) != "紅花會" && 
           query("family/family_name", me) != "武當派" )
                return "貧道與閣下素無淵源，不知閣下這話從何而來？";

        if (me->query_skill("xuangong-quan", 1) < 1)
                return "你連無極玄功拳都沒學，還談什麼絕招可言？";

            if( query("family/gongji", me)<400 )
                return "嗯，你對"+query("family/family_name", me)+CYN
                       "所作的貢獻不夠，這招我不傳你。";

        if( query("shen", me)<50000 )
                return "你俠義正事做得不夠，這招我不能傳你。";

        if (me->query_skill("force") < 160)
                return "你的內功修行太淺，用不了這一招！";

        if (me->query_skill("xuangong-quan", 1) < 120)
                return "你無極玄功拳尚未修煉得精深，難以運用此招。";

        message_vision(HIY "$n" HIY "點了點頭，將$N" HIY "招至"
                       "身邊，在耳旁低聲細說良久，$N" HIY "聽"
                       "後會心\n的一笑，看來大有所悟。\n" NOR, me,
                       this_object());

        command("nod");
        command("say 剛才的話你都需記牢了，自己下去慢慢練吧。");
        tell_object(me, HIC "你學會了「玄功無極勁」。\n" NOR);

        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1500000);
        if (me->can_improve_skill("xuangong-quan"))
                me->improve_skill("xuangong-quan", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/xuangong-quan/xuan", 1, me);
          addn("family/gongji", -400, me);
        return 1;
}

mixed ask_zhen()
{
        object me;
        object ob;

        me = this_player();

        if (me->is_bad())
                return "你這邪魔外道，還不快快給貧道滾開。";

        if( query("family/family_name", me) != "紅花會" && 
           query("family/family_name", me) != "武當派" )
                return RANK_D->query_respect(me) + "與貧道素不相識，不知"
                       "此話何解？";

        if (me->query_skill("furong-jinzhen", 1) < 80)
                return "你芙蓉金針的手法還不到家，拿了芙蓉金針也沒什麼用。";

        if (query("zhen_count") < 1)
                return "我又不是賣這個的，哪裡帶得了這麼多。";

        addn("zhen_count", -1);
        ob = new("/d/kaifeng/npc/obj/jinzhen");
        message_vision("$N拿出五十根" HIY "芙蓉金針" NOR "(Furong jinzhen)給$n。\n",
                       this_object(), me);
        ob->move(me, 1);
        return "既然這樣，我這兒的芙蓉金針你就先拿去用吧。";
}

mixed ask_jian()
{
        object me;
        object ob;
        object owner;

        me = this_player();
        if (me->is_bad())
        {
                if( query("family/family_name", me) == "紅花會" )
                        message_vision(CYN "$N" CYN "冷哼一聲，對$n" CYN "道："
                                       "“你若再敢在我面前說三道四，小心我替紅"
                                       "花會清除你這個敗類！”\n" NOR,
                                       this_object(), me);
                else
                if( query("family/family_name", me) == "武當派" )
                        message_vision(CYN "$N" CYN "冷哼一聲，對$n" CYN "道："
                                       "“你身在武當，行為卻如此不恥，竟還敢在"
                                       "我面前說三道四！”\n" NOR,
                                       this_object(), me);
                else
                        message_vision(CYN "$N" CYN "冷笑一聲，對$n" CYN "說道"
                                       "：“閣下什麼來頭？居然敢打聽陸某的配劍"
                                       "？”\n" NOR,
                                       this_object(), me);
                return 1;
        }

        if( query("family/family_name", me) == "武當派" )
                return "你雖和我同在武當，但這配劍是我隨身之物，現大敵當前，不便交予。";

        if( query("family/family_name", me) != "紅花會" )
                return "貧道與閣下素不相識，不知閣下無故打聽在下的配劍究是為何？";

        if( query("family/master_id", me) != "chenjialuo" && 
           query("family/master_id", me) != "wuchendaozhang" && 
           query("family/master_id", me) != "zhaobanshan" )
                return "我與你師父不熟，這白龍劍不能交給你。";

        if( query("shen", me)<30000 )
                return "學武之人，自應以德義為先。我的配劍不會隨便給人，你走吧。";

        if (me->query_skill("rouyun-jian", 1) < 150)
                return "你還是先在貧道這裡把柔雲劍法練成之後再說吧。";

        ob = find_object(BAILONG);
        if (! ob) ob = load_object(BAILONG);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "嗯？貧道的白龍寶劍不就在你身上嗎？";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "你來晚了一步，我的配劍已經讓別人取去了。";

                if( query("family/family_name", owner) == "武當派" )
                        return "我的配劍現在在我武當門人"+query("name", owner)+
                               "手中，你要用就去找他吧。";
                else
                if( query("family/family_name", owner) == "紅花會" )
                        return "我的配劍被你們紅花會的"+query("name", owner)+
                               "取去了，你要用就去找他吧。";
                else
                        return "我的配劍現在落到了"+query("name", owner)+
                               "手中，你去找他吧！";
        }
        ob->move(this_object());

        ob = new("/clone/weapon/changjian");
        ob->move(this_object());
        ob->wield();

        message_vision(CYN "$N" CYN "嘆道：“配劍你拿去吧，但切記行走"
                       "江湖俠義為重，莫壞了紅花會的名聲。”\n" NOR,
                       this_object(), me);
        command("givebailongjianto"+query("id", me));
        return 1;
}
