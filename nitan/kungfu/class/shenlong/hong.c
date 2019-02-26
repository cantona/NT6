// This program is a part of NT MudLIB

#include <ansi.h>
#include "shenlong.h"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;
inherit F_QUESTER;

mixed ask_fei();
mixed ask_xian();
mixed ask_cui();
string ask_tool();

void create()
{
        set_name("洪安通", ({ "hong antong", "hong" }));
        set("title",  HIY "神龍教" NOR "教主" );
        set("nickname", HIR "永享仙福" NOR);
        set("long", "他就是武功蓋世、令江湖人等談之色變的神龍教教主洪安通。\n");
        set("gender", "男性");
        set("age", 50);
        set("attitude", "friendly");

        set("str", 32);
        set("int", 35);
        set("con", 31);
        set("dex", 32);

        set("max_qi", 6000);
        set("max_jing", 3000);
        set("neili", 6800);
        set("max_neili", 6800);
        set("jiali", 100);
        set("level", 40);
        set("combat_exp", 2200000);
        set("shen_type", -1);

        set_skill("force", 600);
        set_skill("shenlong-xinfa", 600);
        set_skill("dodge", 600);
        set_skill("yixing-bufa", 600);
        set_skill("hand", 600);
        set_skill("shenlong-bashi", 600);
        set_skill("strike", 600);
        set_skill("huagu-mianzhang", 600);
        set_skill("finger", 620);
        set_skill("yingxiong-sanzhao", 600);
        set_skill("parry", 600);
        set_skill("staff", 600);
        set_skill("sword", 600);
        set_skill("shedao-qigong", 600);
        set_skill("unarmed", 600);
        set_skill("literate", 600);
        set_skill("medical", 600);
        set_skill("shenlong-jian", 600);
        set_skill("busi-shenlong", 600);
        set_skill("shenlong-mixin", 600);
        set_skill("martial-cognize", 600);

        map_skill("force", "shenlong-xinfa");
        map_skill("dodge", "yixing-bufa");
        map_skill("hand", "shenlong-bashi");
        map_skill("strike", "huagu-mianzhang");
        map_skill("parry", "shedao-qigong");
        map_skill("staff", "shedao-qigong");
        map_skill("unarmed", "shedao-qigong");
        map_skill("sword", "shenlong-jian");
//        map_skill("finger", "yingxiong-sanzhao");

        prepare_skill("strike", "huagu-mianzhang");
        prepare_skill("hand", "shenlong-bashi");

        create_family("神龍教", 1, "教主");

        set("inquiry", ([
                "神龍教" : "一般人是入不了我神龍教的(join shenlongjiao)。",
                "入教"   : "一般人是入不了我神龍教的(join shenlongjiao)。",
                "洪安通" : "你不想活了是不是？",
                "教主"   : "我就是神龍教教主。",
                "絕招"   : "你想學什麼絕技啊？",
                "絕技"   : "你想學什麼絕技啊？",
                "飛仙法" : (: ask_fei :),
                "神龍再現" : (: ask_xian :),
                "摧心斷腸" : (: ask_cui :),
                "工具"   : (: ask_tool :),
                "tool"   : (: ask_tool :),
                "鐵鍬"   : (: ask_tool :),
                "神龍鍬" : (: ask_tool :),
                "qiao"   : (: ask_tool :),
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "staff.chang" :),
                (: perform_action, "staff.chang2" :),
                (: perform_action, "staff.chang3" :),
                (: perform_action, "fei" :),
                (: perform_action, "xian" :),
                (: perform_action, "cui" :),
                (: perform_action, "strike.hua" :),
                (: perform_action, "hand.xian" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }));

        set_temp("apply/attack", 150);
        set_temp("apply/defense", 150);
        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob", 5);
        setup();
        carry_object("/clone/weapon/gangzhang")->wield();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver", 35);
}

int do_flatter(string arg)
{
        if( !query_temp("pending/flatter", this_player()) )
        {
                command("say 你想嚷嚷什麼，吵得我心煩意亂的。");
                return 0;
        }

        if (! arg ) return notify_fail("你説我什麼？\n");

        set_temp("pending/flatter", 0, this_player());
        message_vision(CYN "$N大聲説道：" + arg + "\n" NOR,
                       this_player());

        if (strsrch(arg, "萬年不老") >=0 && (strsrch(arg, "永享仙福") >=0 &&
            strsrch(arg, "壽與天齊") >=0 && strsrch(arg, "文武仁聖") >=0))
        {
                command("smile");
                command("say 這還差不多。\n");
                command("recruit "+query("id", this_player()));
        } else
        {
                command("say 你如此不把我放在眼裏，我又怎能容你？!");
                kill_ob(this_player());
        }
        return 1;
}

// 萬年不老,永享仙福,壽與天齊,文武仁聖

void die()
{
        message_vision("\n$N奇道：“咦,居然有人能殺了我,....”"
                       "説完睜着兩眼倒地死了。\n", this_object());
        ::die();
}

void init()
{
        object ob;

        ::init();

        if (interactive(ob = this_player()) && ! is_fighting())
        {
                remove_call_out("greeting");
                call_out("greeting", 4, ob);
        }
        add_action("do_flatter", "flatter");
        add_action("do_join", "join");
}

void greeting(object ob)
{
        object obj;
        if (! objectp(ob)) return;
        if (interactive(ob) && objectp(obj = present("used gao", ob)))
        {
                set("combat_exp", 1000000);
                set("qi", 500);
                set("jing", 500);
        }
}

mixed ask_fei()
{
        object me;

        me = this_player();
        if( query("can_perform/shedao-qigong/fei", me) )
                return "自己多練練，少在我面前羅嗦！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是哪兒來的？找死啊？";

        if( query("shen", me)>-40000 )
                return "你的手段還不夠毒，我可不能傳給你絕招！";

        if( query("family/gongji", me)<800 )
                return "你為我神龍教效力還不夠，這招我先不忙傳你。";

        if (me->query_skill("shedao-qigong", 1) < 100)
                return "你的蛇島奇功學好了麼？還好意思來問我？";

        message_vision(HIM "$n" HIM "點頭道：“看清楚了！”説罷以"
                       "掌為劍“唰唰唰”接連劈出數劍，宛若數把劍在"
                       "手，真是神乎其神！\n" NOR,
                       me, this_object());
        command("say 運用很簡單，不過你懂了沒有？");
        tell_object(me, HIG "你學會了飛仙術。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 90000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/shedao-qigong/fei", 1, me);
        addn("family/gongji", -800, me);
        return 1;
}

mixed ask_xian()
{
        object me;

        me = this_player();
        if( query("can_perform/shedao-qigong/xian", me) )
                return "自己多練練，少在我面前羅嗦！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是哪兒來的？找死啊？";

        if( query("shen", me)>-50000 )
                return "你要好好為我神教效力，手段要更狠更毒。我才能傳你這門絕招！";

        if( query("family/gongji", me)<800 )
                return "你為我神龍教效力還不夠，這招我先不忙傳你。";

        if (me->query_skill("shedao-qigong", 1) < 120)
                return "你的蛇島奇功根基不夠，豈能就窺測其中奧妙？";

        message_vision(HIM "$n" HIM "點頭道：“你且看着，説罷雙掌"
                       "齊推，眼見招式已老，忽然間去勢一變，宛若"
                       "龍行天際，曲折婉轉不留半點痕跡。\n" NOR,
                       me, this_object());
        command("say 你可懂了其中奧妙？");
        tell_object(me, HIG "你學會了神龍再現。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 90000);
        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 90000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 90000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/shedao-qigong/xian", 1, me);
        addn("family/gongji", -800, me);
        return 1;
}

mixed ask_cui()
{
        object me;

        me = this_player();
        if( query("can_perform/shedao-qigong/cui", me) )
                return "自己多練練，少在我面前羅嗦！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是哪兒來的？找死啊？";

        if( query("shen", me)>-50000 )
                return "你要好好為我神教效力，手段要更狠更毒。我才能傳你這門絕招！";

        if( query("family/gongji", me)<800 )
                return "你為我神龍教效力還不夠，這招我先不忙傳你。";

        if (me->query_skill("shedao-qigong", 1) < 120)
                return "你的蛇島奇功根基不夠，豈能就窺測其中奧妙？";

        message_vision(HIM "$n" HIM "點頭道：“你且看着，只聽$n"
                       HIM "大喝一聲，一掌擊出，隱隱然有風雷之聲。\n"
                       "一時間$N" HIM "只覺得呼吸困難，$p" HIM "掌力"
                       "猶如排山倒海一般，撼天動地。\n" NOR,
                       me, this_object());
        command("say 這招不求花巧變化，乃是以力取勝，你可明白？");
        tell_object(me, HIG "你學會了摧心斷腸。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 90000);
        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 90000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 90000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/shedao-qigong/cui", 1, me);
        addn("family/gongji", -800, me);
        return 1;
}

void attempt_apprentice(object ob)
{
        if( query("party/party_name", ob) != "神龍教" )
        {
                command("say 你不是本教教眾, 想來找死啊!");
                return;
        }

        if( query("shen", ob)>-1000 )
        {
                command("say 林沖拜梁山還要投名狀，你不殺兩"
                        "個白道人物怎麼表示真心？！");
                return;
        }

        if( query_temp("pending/flatter", ob) )
        {
                command("say 你如此不把我放在眼裏，我又怎能容你？");
                kill_ob(ob);
                return 0;
        } else
        {
                command("say 我洪安通比起古往今來的聖人怎麼樣啊？");
                message_vision("洪安通微閉雙眼，手捻長鬚，一副"
                               "等人拍馬(flatter)的樣子。\n",
                               this_player());
                set_temp("pending/flatter", 1, ob);
                return 0;
        }
}

/*
void unconcious()
{
        die();
}
*/

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "歷練" :
        case "歷煉" :
        case "鍛鍊" :
                return QUEST_D->accept_ask(this_object(), me, topic);
                break;

        case "辣手化骨" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/huagu-mianzhang/hua",
                           "name"    : "辣手化骨",
                           "sk1"     : "huagu-mianzhang",
                           "lv1"     : 100,
                           "sk2"     : "strike",
                           "lv2"     : 100,
                           "sk3"     : "force",
                           "lv3"     : 100,
                           "gongxian": 1000,
                           "shen"    : -20000, ]));
                break;

        case "英雄三招" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/yingxiong-sanzhao/sanzhao",
                           "name"    : "英雄三招",
                           "sk1"     : "yingxiong-sanzhao",
                           "lv1"     : 200,
                           "sk2"     : "strike",
                           "lv2"     : 200,
                           "sk3"     : "force",
                           "lv3"     : 200,
                           "shen"    : -50000, ]));
                break;

        case "蓋世英雄" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/yingxiong-sanzhao/yingxiong",
                           "name"    : "蓋世英雄",
                           "sk1"     : "yingxiong-sanzhao",
                           "lv1"     : 150,
                           "sk2"     : "force",
                           "lv2"     : 160,
                           "gongxian": 600, 
                           "shen"    : -50000, ]));
                break;

        case "捨身" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/yingxiong-sanzhao/sheshen",
                           "name"    : "捨身",
                           "sk1"     : "yingxiong-sanzhao",
                           "lv1"     : 150,
                           "sk2"     : "force",
                           "lv2"     : 160,
                           "gongxian": 1000, 
                           "shen"    : -50000, ]));
                break;

        case "神龍初現" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/shenlong-bashi/xian",
                           "name"    : "神龍初現",
                           "sk1"     : "shenlong-bashi",
                           "lv1"     : 100,
                           "sk2"     : "hand",
                           "lv2"     : 100,
                           "sk3"     : "force",
                           "lv3"     : 100,
                           "gongxian": 600,
                           "shen"    : -10000, ]));
                break;
        default:
                return 0;
        }
}
string ask_tool()
{
        mapping fam;
        object ob, me = this_player();

        if( !(fam=query("family", me)) || 
                fam["family_name"] != "神龍教")
                return "這位"+RANK_D->query_respect(me)+ "與本教素無來往，不知此話從何談起？";
        if( present("shenlong qiao", me) )
                return "你現在身上不是有鍬了嘛，怎麼又來要了？真是貪得無饜！";
        if( me->query_skill("digging", 1) <= 30)
                return "你拿着東西也沒什麼用，還是留給別人吧！";
        if( query("count") < 1)
                return "來晚啦，你要的東西給別人先拿走了！";
        ob = new(__DIR__"obj/shenlongqiao");
        ob->move(me);
        addn("count", -1);
        return "好吧，這有一把神龍鍬，你就拿去吧。";
}
