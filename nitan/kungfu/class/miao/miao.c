// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified
// in any form without the written permission from authors.

#include <ansi.h>
#include "miao.h"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;

mixed ask_skill1();
mixed ask_skill2();
mixed ask_skill3();
mixed ask_skill4();
mixed ask_skill5();

void create()
{
        object ob;
        set_name("苗人鳳", ({ "miao renfeng", "miao", "renfeng" }));
        set("gender", "男性");
        set("nickname", YEL "金面佛" NOR);
        set("title", "打遍天下無敵手");
        set("age", 48);
        set("long", @LONG
他就是號稱打遍天下無敵手的「金面佛」苗人
鳳。只見他臉色透黃，似乎蒙上了一層淡淡的
金紙。他身材高大魁梧，四肢修長，卻是全然
不修篇幅，令人稱奇。
LONG );
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 32);
        set("int", 31);
        set("con", 33);
        set("dex", 31);

        set("qi", 5500);
        set("max_qi", 5500);
        set("jing", 4000);
        set("max_jing", 4000);
        set("neili", 6800);
        set("max_neili", 6800);
        set("jiali", 200);
        set("level", 50);
        set("combat_exp", 4500000);
        set("score", 20000);

        set_skill("force", 600);
        set_skill("lengyue-shengong", 600);
        set_skill("dodge", 600);
        set_skill("taxue-wuhen", 600);
        set_skill("sword", 600);
        set_skill("miaojia-jian", 600);
        set_skill("blade", 600);
        set_skill("hujia-daofa", 600);
        set_skill("strike", 600);
        set_skill("tianchang-zhang", 600);
        set_skill("parry", 600);
        set_skill("literate", 600);
        set_skill("martial-cognize", 600);
        set_skill("daojian-xiaotianwai", 800);

        map_skill("force", "lengyue-shengong");
        map_skill("dodge", "taxue-wuhen");
        map_skill("sword", "miaojia-jian");
        map_skill("blade", "hujia-daofa");
        map_skill("parry", "miaojia-jian");
        map_skill("strike", "tianchang-zhang");

        prepare_skill("strike", "tianchang-zhang");

        set("no_teach", ([
                "hujia-daofa"     : "胡家刀法乃是我當年從胡世兄處習得，不便外傳。",
        ]));

        create_family("中原苗家", 6, "傳人");

        set("inquiry", ([
                "雲邊摘月" : (: ask_skill1 :),
                "黃龍吐珠" : (: ask_skill2 :),
                "劍舞千秋" : (: ask_skill3 :),
                "流星趕月" : (: ask_skill4 :),
                "金面生蓮" : (: ask_skill5 :),
                "胡家刀法" : "胡家刀法乃是我當年從胡世兄處習得，當真精妙無比。",
                "胡一刀"   : "當年我中了姦人毒計殺害了他，令我遺憾終生！",
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.zhai" :),
                (: perform_action, "sword.zhu" :),
                (: perform_action, "sword.jian" :),
                (: perform_action, "sword.gan" :),
                (: perform_action, "strike.zhan" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob",5);
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

void attempt_apprentice(object ob)
{
        command("say 中原苗家暫不開放！");
        return;

        if (! permit_recruit(ob))
                return;

        if (ob->name(1) == "苗人鳳")
        {
                command("hmm");
                command("say 你怎麼也取這個名字？");
                return;
        }

        if (ob->name(1) == "苗若蘭")
        {
                command("hmm");
                command("say 你就不能換個別的名字？");
                return;
        }

        if (ob->name(1) == "苗鬼鳳" || ob->name(1) == "苗人龍")
        {
                command("hmm");
                command("say 你安心要和我作對是不是？");
                return;
        }

        command("sigh");
        command("recruit "+query("id", ob));
        command("say 我本已打算不收徒弟，讓我田家與胡、苗、范三家的紛爭得以平息。");
        command("say 可是這祖傳三十七勢苗家劍就在我處失傳，未免太過不孝。");
        return;
}

int recognize_apprentice(object me, string skill)
{
        if( query("family/family_name", me) != "關外胡家" )
        {
                command("say 你是誰？快點滾開！");
                return -1;
        }

        if( query("shen", me)<0 )
        {
                command("sigh");
                command("say 你怎能走上邪路？我可不能教你苗家劍。");
                return -1;
        }

        if( query("combat_exp", me)<400000 )
        {
                command("say 你此時功力太淺，還是先打好基礎再說吧。");
                return -1;
        }

        if (skill != "miaojia-jian" && skill != "sword")
        {
                command("say 我只教你基本劍法和苗家劍法，別的就不要來煩我了！");
                return -1;
        }

        if (me->query_skill(skill, 1) >= 600)
        {
               command("say 夠了！我就教你到這裡吧，武功還是"
                       "要靠自己多研究才是！");
               return -1;
        }

        command("say 看在當年我中了姦人毒計殺害了胡一刀，令我遺憾終生的事上，我就傳你苗家劍法。");
        return 1;
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/miaojia-jian/zhai", me) )
                return "自己下去練！還多說什麼？";

        if (me->query_skill("miaojia-jian", 1) < 1)
                return "你連苗家劍法都未學，何談絕招可言？";

        if( query("family/gongji", me)<400 )
                return "你在胡家無所作為，這招我先不忙傳你。";

        if( query("shen", me)<13000 )
                return "你俠義正事做得不夠，這招我先不忙傳你。";

        if (me->query_skill("force") < 120)
                return "你的內功火候不足，學不成這招。";

        if( query("max_neili", me)<800 )
                return "你的內力修為不足，學不成這招。";

        if (me->query_skill("miaojia-jian", 1) < 100)
                return "你的苗家劍法火候未到，還得多練習練習。";

        message_vision(HIY "$n" HIY "對$N" HIY "點了點頭，隨手從桌上"
                       "拈起一根筷子，慢慢的\n演示劍招。$N" HIY "只見"
                       "$n" HIY "劍勢舒張，吞吐不定，瞬時之間\n已連換"
                       "數種劍勢，劍法之巧妙，當真前所未聞。\n" NOR,
                       me, this_object());

        command("nod");
        command("say 此招看似復雜，其實並不難練，你下去後自己體會吧。");
        tell_object(me, HIC "你學會了「雲邊摘月」。\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("miaojia-jian"))
                me->improve_skill("miaojia-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/miaojia-jian/zhai", 1, me);
        addn("family/gongji", -400, me);
        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_perform/miaojia-jian/zhu", me) )
                return "自己下去練！還多說什麼？";

        if (me->query_skill("miaojia-jian", 1) < 1)
                return "你連苗家劍法都未學，何談絕招可言？";

        if( query("family/gongji", me)<600 )
                return "你在胡家無所作為，這招我先不忙傳你。";

        if( query("shen", me)<15000 )
                return "你俠義正事做得不夠，這招我先不忙傳你。";

        if (me->query_skill("force") < 150)
                return "你的內功火候不足，學不成這招。";

        if( query("max_neili", me)<1200 )
                return "你的內力修為不足，學不成這招。";

        if (me->query_skill("miaojia-jian", 1) < 120)
                return "你的苗家劍法火候未到，還得多練習練習。";

        message_vision(HIY "$n" HIY "對$N" HIY "笑了笑，隨即伸出右手，"
                       "中食二指並攏，捏作\n劍訣，“嗤”的一聲空點而出"
                       "，霎時破空之聲驟響，一股\n氣勁從指尖迸發，將$N"
                       HIY "身旁的木幾穿透出一個小孔。\n" NOR, me,
                       this_object());

        command("nod");
        command("say 此招不外乎是以劍作媒，以氣傷人。");
        tell_object(me, HIC "你學會了「黃龍吐珠」。\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("miaojia-jian"))
                me->improve_skill("miaojia-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/miaojia-jian/zhu", 1, me);
        addn("family/gongji", -600, me);
        return 1;
}

mixed ask_skill3()
{
        object me;

        me = this_player();

        if( query("can_perform/miaojia-jian/qian", me) )
                return "自己下去練！還多說什麼？";

        if (me->query_skill("miaojia-jian", 1) < 1)
                return "你連苗家劍法都未學，何談絕招可言？";

        if( query("family/gongji", me)<1000 )
                return "你在我胡家無所作為，這招我先不忙傳你。";

        if( query("shen", me)<18000 )
                return "你俠義正事做得不夠，這招我先不忙傳你。";

        if (me->query_skill("force") < 220)
                return "你的內功火候不足，學不成這招。";

        if( query("max_neili", me)<1800 )
                return "你的內力修為不足，學不成這招。";

        if (me->query_skill("miaojia-jian", 1) < 160)
                return "你的苗家劍法火候未到，還得多練習練習。";

        message_vision(HIY "$n" HIY "長嘆一聲，當下也不答話，從$N" HIY
                       "處接過配劍，將三\n十七勢苗家劍連環施出，霎時劍"
                       "光逼人，氣芒縱橫，龍吟\n不止。只見$n" HIY "所"
                       "施的三十七勢劍法竟如一勢，交替連\n環，一氣呵成"
                       "，並無任何破綻，$N" HIY "只看得目瞪口呆。\n"
                       NOR, me, this_object());

        command("nod");
        command("say 你自己下去練習吧。");
        tell_object(me, HIC "你學會了「劍舞千秋」。\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("miaojia-jian"))
                me->improve_skill("miaojia-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/miaojia-jian/qian", 1, me);
        addn("family/gongji", -1000, me);
        return 1;
}

mixed ask_skill4()
{
        object me;

        me = this_player();

        if( query("can_perform/miaojia-jian/gan", me) )
                return "自己下去練！還多說什麼？";

        if (me->query_skill("miaojia-jian", 1) < 1)
                return "你連苗家劍法都未學，何談絕招可言？";

        if( query("family/gongji", me)<2200 )
                return "你在胡家無所作為，這招我先不忙傳你。";

        if( query("shen", me)<35000 )
                return "你俠義正事做得不夠，這招我先不忙傳你。";

        if (me->query_skill("force", 1) < 100)
                return "你的內功火候不足，學不成這招。";

        if( query("max_neili", me)<3000 )
                return "你的內力修為不足，學不成這招。";

        if (me->query_skill("miaojia-jian", 1) < 200)
                return "你的苗家劍法火候未到，還得多練習練習。";

        message_vision(HIY "$n" HIY "凝視了$N" HIY "半天，緩緩地點了"
                       "點頭。當下拔出腰間配\n劍，劍走龍蛇，白光如虹"
                       "，凝重處如山岳巍峙，輕靈處若\n清風無跡，神劍"
                       "之威，當真神鬼難測。舞到急處，$n" HIY "\n一聲"
                       "大喝，手中配劍竟然離手射出，化作一道流星，直"
                       "沒\n至柄插入$N" HIY "對面的牆壁中。\n" NOR,
                       me, this_object());

        command("nod");
        command("say 這招是我苗家劍法的精髓，可要勤加練習。");
        tell_object(me, HIC "你學會了「流星趕月」。\n" NOR);

        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);

        if (me->can_improve_skill("parry"))
                me->improve_skill("parry", 1500000);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);

        if (me->can_improve_skill("miaojia-jian"))
                me->improve_skill("miaojia-jian", 1500000);

        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/miaojia-jian/gan", 1, me);
        addn("family/gongji", -2200, me);
        return 1;
}

mixed ask_skill5()
{
        object me;

        me = this_player();

        if( query("can_perform/miaojia-jian/lian", me) )
                return "自己下去練！還多說什麼？";

        if (me->query_skill("miaojia-jian", 1) < 1)
                return "你連苗家劍法都未學，何談絕招可言？";

        if( query("family/gongji", me)<1000 )
                return "你在我胡家無所作為，這招我先不忙傳你。";

        if( query("shen", me)<18000 )
                return "你俠義正事做得不夠，這招我先不忙傳你。";

        if (me->query_skill("force") < 220)
                return "你的內功火候不足，學不成這招。";

        if( query("max_neili", me)<1800 )
                return "你的內力修為不足，學不成這招。";

        if (me->query_skill("miaojia-jian", 1) < 160)
                return "你的苗家劍法火候未到，還得多練習練習。";

        message_sort(HIY "$n哈哈一笑，對$N" HIY "讚道：不"
                     "錯，不錯。依照你現在苗家劍法的造詣，"
                     "我便傳授你金面生蓮又有何妨？說完便只"
                     "見$n從懷中摸出一本頗為古舊的小冊子，"
                     "指著其中一段對$N" HIY "仔細講解。$N"
                     HIY "聽後沉思良久，若有所悟。" NOR,
                     me, this_object());

        command("nod");
        command("say 你自己下去練習吧。");
        tell_object(me, HIC "你學會了「金面生蓮」。\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("miaojia-jian"))
                me->improve_skill("miaojia-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/miaojia-jian/lian", 1, me);
        addn("family/gongji", -1000, me);
        return 1;
}
