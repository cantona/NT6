#include <ansi.h>
#include "wudu.h"

#define DUJING  "/clone/lonely/book/dujing2"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;

mixed ask_skill1();
mixed ask_skill2();
mixed ask_skill3();
mixed ask_me();

void create()
{
        set_name("齊雲敖", ({ "qi yunao", "qi", "yunao" }));
        set("nickname", HIB "錦衣毒丐" NOR);
        set("long", @LONG
他就是五毒教的長老，人稱錦衣毒丐的齊雲
敖。乃是教主的同門師兄，在教中一向飛揚
跋扈，大權獨攬。他長的身材魁梧，面目猙
獰，身穿一件五彩錦衣，太陽穴高高墳起。
LONG);
        set("title","五毒教長老");
        set("gender", "男性");
        set("age", 45);
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 30);
        set("int", 40);
        set("con", 30);
        set("dex", 30);
        set("max_qi", 4500);
        set("max_jing", 4000);
        set("neili", 5000);
        set("max_neili", 5000);
        set("jiali", 120);
        set("combat_exp", 1800000);
        set("score", 10000);

        set_skill("force", 220);
        set_skill("wudu-shengong", 220);
        set_skill("xiuluo-yinshagong", 180);
        set_skill("dodge", 180);
        set_skill("wudu-yanluobu", 180);
        set_skill("strike", 200);
        set_skill("tianchan-zhang", 200);
        set_skill("claw", 200);
        set_skill("wusheng-zhao", 200);
        set_skill("parry", 200);
        set_skill("sword", 200);
        set_skill("jinwu-goufa", 180);
        set_skill("whip", 180);
        set_skill("xiewei-bian", 180);
        set_skill("ruanhong-zhusuo", 180);
        set_skill("throwing", 180);
        set_skill("literate", 100);
        set_skill("poison", 250);
        set_skill("wudu-qishu", 250 );
        set_skill("martial-cognize", 200);

        set("no_teach", ([
                "xiuluo-yinshagong" : "要學修羅陰煞功找那賤人去。",
                "ruanhong-zhusuo"   : "這武功是由那賤人傳授的，要學你找她去。",
        ]));

        map_skill("force", "xiuluo-yinshagong");
        map_skill("dodge", "wudu-yanluobu");
        map_skill("strike", "tianchan-zhang");
        map_skill("claw", "wusheng-zhao");
        map_skill("parry", "wusheng-zhao");
        map_skill("sword", "jinwu-goufa");
        map_skill("whip", "ruanhong-zhusuo");
        map_skill("poison", "wudu-qishu");
        prepare_skill("strike", "tianchan-zhang");
        prepare_skill("claw", "wusheng-zhao");

        create_family("五毒教", 11, "長老");

        set("inquiry", ([
                "毒經"     : "你是要毒經上篇、中篇還是下篇？",
                "上篇"     :   "這個…毒經上篇你去問煉毒室的道人要吧。",
                "毒經上篇" : "這個…毒經上篇你去問煉毒室的道人要吧。",
                "中篇"     : (: ask_me :),
                "毒經中篇" : (: ask_me :),
                "下篇"     : "毒經下篇在教主手裡，你去問她要吧。",
                "毒經下篇" : "毒經下篇在教主手裡，你去問她要吧。",
                "騰蛇訣"   : (: ask_skill1 :),
                "毒蟾掌"   : (: ask_skill2 :),
                "奪命連環" : (: ask_skill3 :),
        ]));

        set("jinshe_count", 1);
        set("chat_chance", 2);
        set("chat_msg",({
                CYN "齊雲敖怒道：這賤婢這樣下去，本教三祖七子辛苦創下的基業"
                "都要毀在她手裡了。\n" NOR,
                CYN "齊雲敖自言自語道：我如能找到天下最厲害的毒聖，這教主之"
                "位就是我的了。\n" NOR,
                CYN "齊雲敖自言自語道：唉…我應該上哪去找龍涎香呢？\n" NOR,
        }));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "claw.lian" :),
                (: perform_action, "strike.chan" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set_temp("apply/unarmed_damage", 200);
        set_temp("apply/armor", 200);

        setup();
        carry_object("/d/wudu/npc/obj/jinyi")->wear();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("shen", ob)>-1000 )
        {
                command("say 我越看你越象六扇門派來的臥底。");
                return;
        }
        if( query("shen", ob)>-15000 )
        {
                command("say 你心慈手軟，我是不會收你的！");
                return;
        }
        if( query("combat_exp", ob)<150000 )
        {
                command("say 你還是先去增長點經驗吧。");
                return;
        }
        if ((int)ob->query_skill("wudu-shengong", 1) < 80)
        {
                command("say 你的五毒心法還學的不夠啊。");
                return;
        }
        if ((int)ob->query_skill("wudu-qishu", 1) < 80)
        {
                command("say 我五毒教弟子以毒殺人，修習毒技是首要的。");
                command("say 你是否還應該多多鑽研本門的絕學？");
                return;
        }

       command("nod");
       command("say 不錯，不錯。");
       command("recruit "+query("id", ob));
       set("title", "五毒教護法", ob);
       return;
}

int accept_object(object who, object ob)
{
        object obn;

        if (! who || environment(who) != environment() ) return 0;
        if (! objectp(ob) ) return 0;
        if (! present(ob, who))
                return notify_fail("你沒有這件東西。\n");

        if( query("id", ob) != "longxianxiang" )
                return notify_fail(CYN "齊雲敖搖頭道：這些破爛東西給我有"
                                   "什麼用？\n" NOR);

        message_vision(CYN "齊雲敖見是龍涎香，大喜道：這…這…就是龍涎香"
                       "嗎？真是太好了。\n" NOR, who);

        if (query("jinshe_count") < 1)
        {
                      command("sigh");
                      command("say 本來我該謝你點什麼的，可手頭實在拿不出東西來。");
                      return 1;
        } else
        {
                obn = new("/d/wudu/obj/jinsheduye");
                obn->move(who);
                addn("jinshe_count", -1);
                command("say 本長老不能白收你的東西，這是一瓶金蛇毒液，送給你吧。");
                message_vision("$N拿出" YEL "金蛇毒液" NOR "(jinshe duye)給$n。\n",
                               this_object(), who);
                      return 1;
        }
}

mixed ask_skill1()
{
        object me;

        me = this_player();
        if( query("can_perform/xiewei-bian/tengshe", me) )
                return "你不是已經會了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "不是我們五毒教的人，何出此言？";

        if (me->query_skill("xiewei-bian", 1) < 1)
                return "你連蠍尾鞭都沒學，還有什麼絕招可言。";

        if( query("shen", me)>-20000 )
                return "像你這樣心慈手軟，就算學了這招也幹不了大事！";

          if( query("family/gongji", me)<100 )
                return "你在教中所作的貢獻還不夠，這招我不忙傳你。";

        if (me->query_skill("xiewei-bian", 1) < 100)
                return "你的蠍尾鞭還不到家，要多練練！";

        message_vision(HIY "$n" HIY "點了點頭，在$N" HIY "耳邊輕聲"
                       "嘀咕了幾句，又拔出腰間長\n索，凌空一個盤旋"
                       "，然後順勢一抖，鞭端猛的拔地而起，宛\n如活"
                       "蛇一般，頗為巧妙。\n" NOR, me,
                       this_object());
        command("nod");
        command("say 這招很簡單，下去多練練便成！");
        tell_object(me, HIC "你學會了「騰蛇訣」。\n" NOR);
        if (me->can_improve_skill("whip"))
                me->improve_skill("whip", 1500000);
        if (me->can_improve_skill("xiewei-bian"))
                me->improve_skill("xiewei-bian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/xiewei-bian/tengshe", 1, me);
          addn("family/gongji", -100, me);
        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();
        if( query("can_perform/tianchan-zhang/chan", me) )
                return "你不是已經會了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "不是我們五毒教的人，何出此言？";

        if (me->query_skill("tianchan-zhang", 1) < 1)
                return "你連天蟾掌法都沒學，何談此言？";

        if( query("shen", me)>-35000 )
                return "像你這樣心慈手軟，就算學了這招也幹不了大事！";

          if( query("family/gongji", me)<200 )
                return "你在教中所作的貢獻還不夠，這招我不忙傳你。";

        if (me->query_skill("force") < 150)
                return "你的內功火候不夠，練不成這招！";

        if (me->query_skill("tianchan-zhang", 1) < 120)
                return "你的天蟾掌法還不到家，要多練練！";

        message_vision(HIY "$n" HIY "微微一笑，招手示意$N" HIY "他到跟"
                       "前，然後在$N" HIY "耳邊輕聲\n嘀咕了半天，$N" HIY
                       "直聽得眉開眼笑，一邊聽一邊點頭。\n" NOR,
                       me, this_object());

        command("grin");
        command("say 用這招對付那些比你強的敵人…嘿…打中就跑，別死纏。");
        tell_object(me, HIC "你學會了「毒蟾掌」。\n" NOR);
        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("tianchan-zhang"))
                me->improve_skill("tianchan-zhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/tianchan-zhang/chan", 1, me);
          addn("family/gongji", -200, me);
        return 1;
}

mixed ask_skill3()
{
        object me;

        me = this_player();
        if( query("can_perform/wusheng-zhao/lian", me) )
                return "我不是已經教會你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "不是我們五毒教的人，何出此言？";

        if (me->query_skill("wusheng-zhao", 1) < 1)
                return "你連五聖毒爪都沒學，何談此言？";

        if( query("shen", me)>-40000 )
                return "像你這樣心慈手軟，就算學了這招也幹不了大事！";

        if( query("family/gongji", me)<300 )
                return "你在教中所作的貢獻還不夠，這招我不忙傳你。";

        if (me->query_skill("force") < 150)
                return "你的內功火候不夠，練不成這招！";

        if (me->query_skill("wusheng-zhao", 1) < 120)
                return "你的五聖毒爪還不到家，要多練練！";

        message_vision(HIY "$n" HIY "微微一笑，陡然探出五指，手出如風，抓"
                       "向$N" HIY "。$N" HIY "不\n由得大驚失色，急忙縱躍躲"
                       "閃，可$n" HIY "五指還是搭在了$N" HIY "\n的肩上。\n"
                       NOR, me, this_object());
        command("say 你懂了嗎？");
        tell_object(me, HIC "你學會了「奪命連環」。\n" NOR);
        if (me->can_improve_skill("claw"))
                me->improve_skill("claw", 1500000);
        if (me->can_improve_skill("wusheng-zhao"))
                me->improve_skill("wusheng-zhao", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/wusheng-zhao/lian", 1, me);
        addn("family/gongji", -300, me);
        return 1;
}

mixed ask_me()
{
        object me;
        object ob;
        object owner;

        me = this_player();

        if( query("family/family_name", me) != "五毒教" )
                return "你是哪裡來的？跑來跟我羅嗦什麼！";

        if( query("shen", me)>-10000 )
                return "你是怎麼搞的？連殺人都不會？";

        if( query("combat_exp", me)<100000 )
                return "你現在經驗太淺，不用忙著去閱讀毒經。";

        if (me->query_skill("poison", 1) > 119)
                return "你用毒的造詣已經不淺了，這毒經不看也罷。";

        ob = find_object(DUJING);
        if (! ob) ob = load_object(DUJING);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "不就是你拿著麼？怎麼反倒問我來了？";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "…嗯…毒經中篇現在不在我手裡。";

                if( query("family/family_name", owner) == "五毒教" )
                        return "毒經現在是你同門"+query("name", owner)+
                               "在看，去找他吧。";
                else
                        return "我教的毒經現落在"+query("name", owner)+
                               "的手中，你去把它奪回來吧！";
        }
        ob->move(this_object());
        message_vision(CYN "$N" CYN "點頭道：你拿去看吧，若有不解之處"
                       "可以來問我。\n" NOR, this_object(), me);
        command("givedujing2to"+query("id", me));
        return 1;
}
