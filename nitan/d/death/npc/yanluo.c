// This program is a part of NITAN MudLIB

#include <ansi.h>
inherit NPC;

mixed ask_quest();
mixed ask_reborn();

void create()
{
        set_name("十殿閻羅", ({ "shidian yanluo", "shidian", "yanluo", "shi", "yan"}));
        set("long", "一位面如鍋底，須若鋼針，身穿紅袍的大漢。\n"
                    "這就是陰間的十殿閻羅。\n");
        set("title", HIR "冥府地藏王殿前" NOR);
        set("nickname", HIY "陰司總管" NOR);
        set("gender", "男性");
        set("age", 3000);
        set("attitude", "friendly");
        set("str", 50);
        set("int", 50);
        set("con", 50);
        set("dex", 50);

        set("max_qi", 30000);
        set("max_jing", 30000);
        set("neili", 50000);
        set("max_neili", 50000);
        set("jiali", 1000);

        set("combat_exp", 50000000);

        set_skill("unarmed", 1000);
        set_skill("finger", 1000);
        set_skill("claw", 1000);
        set_skill("strike", 1000);
        set_skill("hand", 1000);
        set_skill("cuff", 1000);
        set_skill("parry", 1000);
        set_skill("dodge", 1000);
        set_skill("force", 1000);
        set_skill("jiuyin-shengong", 1000);
        set_skill("magic", 1000);
        set_skill("literate", 1000);

        map_skill("parry", "jiuyin-shengong");
        map_skill("force", "jiuyin-shengong");
        map_skill("dodge", "jiuyin-shengong");
        map_skill("unarmed", "jiuyin-shengong");
        map_skill("finger", "jiuyin-shengong");
        map_skill("strike", "jiuyin-shengong");
        map_skill("hand", "jiuyin-shengong");
        map_skill("cuff", "jiuyin-shengong");
        map_skill("claw", "jiuyin-shengong");

        prepare_skill("claw", "jiuyin-shengong");
        prepare_skill("cuff", "jiuyin-shengong");

        set("chat_chance", 1);
        set("chat_msg",({
                CYN "十殿閻羅深深的嘆了口氣。\n" NOR,
                CYN "十殿閻羅嘆道：玄武甲殼和朱雀羽毛還好點，可是青龍膽和白虎骨難弄啊……\n" NOR,
                CYN "十殿閻羅嘆道：武甲、朱羽、龍膽還有虎骨，這可真難辦啊。\n" NOR,
                CYN "十殿閻羅嘆道：期限就要到了，地藏老大要我煉制的鎖陽丹原料還沒備齊，這可如何是好啊。\n" NOR,
                CYN "十殿閻羅嘆道：地藏老大的任務可真是要命啊。\n" NOR,
                CYN "十殿閻羅抱怨道：平白無故的要什麼鎖陽丹，老大也真是的。\n" NOR,
        }));

        set("inquiry", ([
                "鎖陽丹"   : (: ask_quest :),
                "煉制"     : (: ask_quest :),
                "煉丹"     : (: ask_quest :),
                "任務"     : (: ask_quest :),
                "交差"     : (: ask_quest :),
                "期限"     : (: ask_quest :),
                "原料"     : (: ask_quest :),
                "藥引"     : (: ask_quest :),
                "轉世"     : (: ask_reborn :),
                "重生"     : (: ask_reborn :),
                "轉生"     : (: ask_reborn :),
                "轉世重生" : (: ask_reborn :),
                "地藏王"   : "他是這裡的老大，沒人惹得起他。",
                "龍膽"     : "龍膽就是神獸青龍的膽，凡人吃了可以平增功力，我也正需要一個來煉丹。",
                "青龍膽"   : "龍膽就是神獸青龍的膽，凡人吃了可以平增功力，我也正需要一個來煉丹。",
                "虎骨"     : "我正需要一根白虎的骨頭來煉鎖陽丹，怎麼，你有麼？",
                "白虎骨"   : "我正需要一根白虎的骨頭來煉鎖陽丹，怎麼，你有麼？",
                "朱雀羽毛" : "那東西本身是沒什麼用的，可卻是我制作鎖陽丹的原料。",
                "朱羽"     : "那東西本身是沒什麼用的，可卻是我制作鎖陽丹的原料。",
                "玄武甲殼" : "那殼用來鑄盔甲倒是挺好，可難弄啊！我找了好久都沒找到。",
                "武甲"     : "玄武甲殼用來鑄盔甲倒是挺好，可難弄啊！我找了好久都沒找到。",
                "甲殼"     : "玄武甲殼用來鑄盔甲倒是挺好，可難弄啊！我找了好久都沒找到。",
                "青龍"     : "神獸青龍有時候會在碧水寒潭出沒，不過我去捉時卻沒見到。",
                "碧水寒潭" : "碧水寒潭就在奈河橋下面，你站在橋上往下跳就到了，不過你下去最好帶上「地陰血脈」。",
                "地陰血脈" : "這東西可以在地府輪回司裡尋找到。…嗯…要決是‘三三逢緣’。",
                "白虎"     : "那大蟲就棲息在寂滅司後面的黑森林裡，我派了好幾個手下去捉它，結果全都掛了。",
                "黑森林"   : "黑森林裡全是陰霧，除非有「指南車」，要不根本沒法辨認方向。",
                "指南車"   : "那是黃帝流傳下來的法寶之一，後來流落到了這裡，不過我沒見過。",
                "寂滅司"   : "寂滅司就在閻羅殿的東邊。",
                "輪回司"   : "輪回司就在閻羅殿的東邊。",
                "閻羅殿"   : "這個你也問我？你是笨死的啊？",
                "朱雀"     : "有人在陰陽塔頂見到過神獸朱雀，不過聽說那扁毛畜生不落無寶之地，要尋它身上必須要帶有寶物。",
                "寶物"     : "地府有個神石名曰「七色瓔珞」，倒是個不得多見的寶物。",
                "七色瓔珞" : "聽傳聞，這東西好象是落在了秦廣王的手裡。",
                "秦廣王"   : "他和我一樣，也是陰間十王之一。",
                "陰陽塔"   : "就是西邊的那座塔，是地府裡最高的建築，平時由馬面看守。",
                "馬面"     : "和看守奈河橋的牛頭一樣，是地府的守衛。",
                "玄武"     : "那臭烏龜整年躲在血池地獄裡吃死人肉，怎麼弄都不出來。",
                "死人肉"   : "我操，這個你也問我？你去稱兩斤吃吃看就知道了。",
                "血池地獄" : "血池地獄就在閻羅殿的北邊，你要下去必須得穿上「麒麟靴」。",
                "麒麟靴"   : "那是地藏王的東西，我也只瞧見過一次。",
        ]));

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "finger.zhi" :),
                (: perform_action, "strike.zhang" :),
                (: perform_action, "cuff.quan" :),
                (: perform_action, "hand.shou" :),
                (: perform_action, "claw.zhua" :),
                (: exert_function, "recover" :),
                (: exert_function, "shield" :),
        }) );

        set("count", 1);
        create_family("陰司", 0, "總管");

        setup();
        carry_object(__DIR__"obj/cloth2")->wear();
}

mixed ask_quest()
{
        object ob;
        object me;
        me = this_player();

        if( query_temp("to_answer", me) )
                return "你這人怎麼這麼羅嗦，到底幹還是不幹啊？";

        if( query("over_quest/hell_quest/鎖陽丹", me) )
                return "上次的事情真是多謝謝你了。";

        if( query("hell_quest/鎖陽丹", me) )
                return "我要的原料你都備齊了嗎？你這人怎麼這麼羅嗦？";

        if( !me->is_ghost() && !wizardp(me) && !query("reborn_offer", me) )
                return "咦？陽人怎麼到這裡來了？";

        /*
        if (query("over") > 1)
                return "東西我都已經準備好了，不需要你的幫忙了。";

        if (query("count") < 1)
                return "夠了，我已經派人做去了。";
        */

        if( query("combat_exp", me)<2000000000 )
                return "……唉……你能力太低了，是幫不了我的。";

        message_vision(HIC "\n十殿閻羅仔細的打量了$N" HIC "好一陣。\n" NOR, me);
        command("say 不錯，不錯。");
        command("whisper"+query("id", me)+"你是剛從陽間來的吧？看你的樣子似乎"
                "武功不壞，能夠幫我個忙嗎？地藏\n王限我在今年內為他煉制鎖陽丹，煉制這"
                "鎖陽丹的千魂和萬魄我已經準備齊了，可是尚差龍膽、虎骨、朱\n羽和玄武甲"
                "殼來做藥引，你能幫我去弄嗎？事成之後自然有你的好處。");

        remove_call_out("answer");
        call_out("answer", 0, me);
        set_temp("to_answer", 1, me);
        add_action("do_accept", "accept");
        return 1;
}

void answer(object me)
{
        tell_object(me, HIR "\n你願意接受(accept)十殿閻羅的請求嗎？\n" NOR);
}

int do_accept()
{
        object me = this_player();
        if( query_temp("to_answer", me) )
        {
                tell_object(me, HIR "\n你決定幫助十殿閻羅尋找鎖陽丹的"
                                "四種原料。\n" NOR);
                message_vision( CYN "\n十殿閻羅「哈哈哈」大笑幾聲。\n"
                                NOR, me);
                message_vision( CYN "十殿閻羅對$N" CYN "說道：那老夫就"
                                "多謝謝你了。\n"NOR, me);
                set("hell_quest/鎖陽丹", 1, me);
                set("wang_get/龍膽", 1, me);
                set("wang_get/虎骨", 1, me);
                set("wang_get/朱羽", 1, me);
                set("wang_get/武甲", 1, me);
                delete_temp("to_answer", me);
                remove_call_out("give_gold");
                call_out("give_gold", 2, me);
                addn("count", -1);
        }
        return 1;
}

int give_gold(object me)
{
        message_vision(HIW "\n十殿閻羅隨手一揮，登時變出一大堆金子，遞"
                       "給$N" HIW "。\n"NOR, me);
        message_vision(CYN "十殿閻羅說道：你陽間的武器在這裡召喚不回"
                       "來，這裡的黃金足夠你購買武具。\n"NOR, me);
        tell_object(me, HIC "\n你獲得了一千兩" NOR + YEL "黃金" NOR +
                        HIC "。\n" NOR);
        MONEY_D->pay_player(me, 10000000);
        return 1;
}

int accept_object(object me, object ob)
{
        object obn;

        int exp, pot, mp;

        exp = 150000 + random(20000);
        pot = 5000 + random(5000);
        mp = 15 + random(10);

        if( !me || environment(me) != environment() ) return 0;
        if ( !objectp(ob) ) return 0;
        if ( !present(ob, me) ) return notify_fail("你沒有這件東西。\n");

         if( query("id", ob) != "long dan"
         && query("id", ob) != "hu gu"
     && query("id", ob) != "zhu yu"
     && query("id", ob) != "xuanwu jiake" )
        {
                message_vision(CYN "十殿閻羅搖了搖頭，道：你給我這個幹什麼？\n" NOR, me);
                        return 0;
        }

        if( query("over_quest/hell_quest/鎖陽丹", me) )
        {
                message_vision(CYN "十殿閻羅對$N" CYN "笑道：你已經替我備齊所有的原料"
                               "了，這個還是你留著自己用吧。\n" NOR, me);
                        return 0;
        }

        if( !query("hell_quest/鎖陽丹", me) )
        {
                message_vision(CYN "十殿閻羅道：無功不受祿，這個你還是自己留著吧。\n"
                               NOR, me);
                        return 0;
        }

       if( query("id", ob) == "long dan" )
        {
                if( query("over_quest/hell_quest/原料/虎骨", me )
                   && query("over_quest/hell_quest/原料/朱羽", me )
                   && query("over_quest/hell_quest/原料/武甲", me) )
                {
                        message_vision(HIW "十殿閻羅見是龍膽，大喜道：“這下四種原料都"
                                       "已備齊，終于可以開始煉制老大要的鎖陽丹了！多"
                                       "虧有你的\n幫助啊，這個是以前我從蓬萊仙山得來"
                                       "的寶物，留著也沒用，就當是酬勞好了。”\n"
                                       NOR, me);

                        addn("combat_exp", exp, me);
                        addn("potential", pot, me);
                        addn("magic_points", mp, me);
                        /*
                        if( query("potential", me)>me->query_potential_limit() )
                                set("potential", me->query_potential_limit(), me);
                        */
                        tell_object(me, HIR "\n你成功的為十殿閻羅備齊了鎖陽丹原料。\n"
                                        NOR);

                        tell_object(me, HIC "\n你獲得了一塊" NOR + HIW "寰宇天晶" NOR +
                                        HIC "。\n"
                                        NOR);

                        tell_object(me, HIC "你獲得了" + chinese_number(exp) + "點"
                                        "經驗、" + chinese_number(pot) + "點潛能以"
                                        "及" + chinese_number(mp) + "點靈慧。\n" NOR);

                        set("over_quest/hell_quest/鎖陽丹", 1, me);
                        delete("hell_quest/鎖陽丹", me);
                        delete("over_quest/hell_quest/原料/虎骨", me);
                        delete("over_quest/hell_quest/原料/朱羽", me);
                        delete("over_quest/hell_quest/原料/武甲", me);
                        obn = new("/d/death/obj/tianjing");
                        obn->move(me);
                        destruct(ob);
                        addn("over", 1);
                        return 1;
                }
           else {
                        if( query("over_quest/hell_quest/原料/龍膽", me) )
                        {
                                message_vision( HIY "十殿閻羅見是龍膽，對$N" HIY "搖"
                                                "頭道：龍膽你已經給過我了，你還是快去"
                                                "尋找其它原料吧。\n" NOR, me);
                                return 0;
                        }
                   else {
                                message("vision", HIY "十殿閻羅看見龍膽，大喜道：太好"
                                                  "了，這青龍膽到底還是讓我得到了。\n"
                                                  NOR, environment(me));
                                set("over_quest/hell_quest/原料/龍膽", 1, me);
                                destruct(ob);
                                return 1;
                        }
                }
        }

         if( query("id", ob) == "hu gu" )
        {
                if( query("over_quest/hell_quest/原料/龍膽", me )
                   && query("over_quest/hell_quest/原料/朱羽", me )
                   && query("over_quest/hell_quest/原料/武甲", me) )
                {
                        message_vision(HIW "十殿閻羅見是虎骨，大喜道：“這下四種原料都"
                                       "已備齊，終于可以開始煉制老大要的鎖陽丹了！多"
                                       "虧有你的\n幫助啊，這個是以前我從蓬萊仙山得來"
                                       "的寶物，留著也沒用，就當是酬勞好了。”\n"
                                       NOR, me);

                        addn("combat_exp", exp, me);
                        addn("potential", pot, me);
                        addn("magic_points", mp, me);
                        /*
                        if( query("potential", me)>me->query_potential_limit() )
                                set("potential", me->query_potential_limit(), me);
                        */
                        tell_object(me, HIR "\n你成功的為十殿閻羅備齊了鎖陽丹原料。\n"
                                        NOR);

                        tell_object(me, HIC "\n你獲得了一塊" NOR + HIW "寰宇天晶" NOR +
                                        HIC "。\n"
                                        NOR);

                        tell_object(me, HIC "你獲得了" + chinese_number(exp) + "點"
                                        "經驗、" + chinese_number(pot) + "點潛能以"
                                        "及" + chinese_number(mp) + "點靈慧。\n" NOR);

                        set("over_quest/hell_quest/鎖陽丹", 1, me);
                        delete("hell_quest/鎖陽丹", me);
                        delete("over_quest/hell_quest/原料/龍膽", me);
                        delete("over_quest/hell_quest/原料/朱羽", me);
                        delete("over_quest/hell_quest/原料/武甲", me);
                        obn = new("/d/death/obj/tianjing");
                        obn->move(me);
                        destruct(ob);
                        addn("over", 1);
                        return 1;
                }
           else {
                        if( query("over_quest/hell_quest/原料/虎骨", me) )
                        {
                                message_vision( HIY "十殿閻羅見是虎骨，對$N" HIY "搖"
                                                "頭道：虎骨你已經給過我了，你還是快去"
                                                "尋找其它原料吧。\n" NOR, me);
                                return 0;
                        }
                   else {
                                message("vision", HIY "十殿閻羅見是虎骨，大喜道：太好"
                                                  "了，那白虎再厲害還不是得乖乖的把骨"
                                                  "頭送上來。\n"
                                                  NOR, environment(me));
                                set("over_quest/hell_quest/原料/虎骨", 1, me);
                                destruct(ob);
                                return 1;
                        }
                }
        }

     if( query("id", ob) == "zhu yu" )
        {
                if( query("over_quest/hell_quest/原料/虎骨", me )
                   && query("over_quest/hell_quest/原料/龍膽", me )
                   && query("over_quest/hell_quest/原料/武甲", me) )
                {
                        message_vision(HIW "十殿閻羅見是朱羽，大喜道：“這下四種原料都"
                                       "已備齊，終于可以開始煉制老大要的鎖陽丹了！多"
                                       "虧有你的\n幫助啊，這個是以前我從蓬萊仙山得來"
                                       "的寶物，留著也沒用，就當是酬勞好了。”\n"
                                       NOR, me);

                        addn("combat_exp", exp, me);
                        addn("potential", pot, me);
                        addn("magic_points", mp, me);
                        /*
                        if( query("potential", me)>me->query_potential_limit() )
                                set("potential", me->query_potential_limit(), me);
                        */
                        tell_object(me, HIR "\n你成功的為十殿閻羅備齊了鎖陽丹原料。\n"
                                        NOR);

                        tell_object(me, HIC "\n你獲得了一塊" NOR + HIW "寰宇天晶" NOR +
                                        HIC "。\n"
                                        NOR);

                        tell_object(me, HIC "你獲得了" + chinese_number(exp) + "點"
                                        "經驗、" + chinese_number(pot) + "點潛能以"
                                        "及" + chinese_number(mp) + "點靈慧。\n" NOR);

                        set("over_quest/hell_quest/鎖陽丹", 1, me);
                        delete("hell_quest/鎖陽丹", me);
                        delete("over_quest/hell_quest/原料/虎骨", me);
                        delete("over_quest/hell_quest/原料/龍膽", me);
                        delete("over_quest/hell_quest/原料/武甲", me);
                        obn = new("/d/death/obj/tianjing");
                        obn->move(me);
                        destruct(ob);
                        addn("over", 1);
                        return 1;
                }
           else {
                        if( query("over_quest/hell_quest/原料/朱羽", me) )
                        {
                                message_vision( HIY "十殿閻羅見是朱羽，對$N" HIY "搖"
                                                "頭道：朱羽你已經給過我了，你還是快去"
                                                "尋找其它原料吧。\n" NOR, me);
                                return 0;
                        }
                   else {
                                message("vision", HIY "十殿閻羅看見朱羽，大喜道：不錯，"
                                                  "不錯。這的確是朱雀羽毛，真是謝謝你了。\n"
                                                  NOR, environment(me));
                                set("over_quest/hell_quest/原料/朱羽", 1, me);
                                destruct(ob);
                                return 1;
                        }
                }
        }

      if( query("id", ob) == "xuanwu jiake" )
        {
                if( query("over_quest/hell_quest/原料/虎骨", me )
                   && query("over_quest/hell_quest/原料/龍膽", me )
                   && query("over_quest/hell_quest/原料/朱羽", me) )
                {
                        message_vision(HIW "十殿閻羅見是玄武甲殼，大喜道：“這下四種"
                                       "原料都已備齊，終于可以開始煉制老大要的鎖陽丹"
                                       "了！多虧有\n你的幫助啊，這個是以前我從蓬萊仙"
                                       "山得來的寶物，留著也沒用，就當是酬勞好了。”\n"
                                       NOR, me);

                        addn("combat_exp", exp, me);
                        addn("potential", pot, me);
                        addn("magic_points", mp, me);
                        /*
                        if( query("potential", me)>me->query_potential_limit() )
                                set("potential", me->query_potential_limit(), me);
                        */
                        tell_object(me, HIR "\n你成功的為十殿閻羅備齊了鎖陽丹原料。\n"
                                        NOR);

                        tell_object(me, HIC "\n你獲得了一塊" NOR + HIW "寰宇天晶" NOR +
                                        HIC "。\n"
                                        NOR);

                        tell_object(me, HIC "你獲得了" + chinese_number(exp) + "點"
                                        "經驗、" + chinese_number(pot) + "點潛能以"
                                        "及" + chinese_number(mp) + "點靈慧。\n" NOR);

                        set("over_quest/hell_quest/鎖陽丹", 1, me);
                        delete("hell_quest/鎖陽丹", me);
                        delete("over_quest/hell_quest/原料/虎骨", me);
                        delete("over_quest/hell_quest/原料/龍膽", me);
                        delete("over_quest/hell_quest/原料/朱羽", me);
                        obn = new("/d/death/obj/tianjing");
                        obn->move(me);
                        destruct(ob);
                        addn("over", 1);
                        return 1;
                }
           else {
                        if( query("over_quest/hell_quest/原料/武甲", me) )
                        {
                                message_vision( HIY "十殿閻羅見是玄武甲殼，對$N" HIY "搖"
                                                "頭道：這東西你已經給過我了，你還是快去"
                                                "尋找其它原料吧。\n" NOR, me);
                                return 0;
                        }
                   else {
                                message("vision", HIY "十殿閻羅看見玄武甲殼，大喜道：好！"
                                                  "太好了，那臭烏龜被你幹掉了吧？\n"
                                                  NOR, environment(me));
                                set("over_quest/hell_quest/原料/武甲", 1, me);
                                destruct(ob);
                                return 1;
                        }
                }
        }

}

mixed ask_reborn()
{
        object who;
        object *all;

        who = this_player();

        /*
        if( query("reborn/times", who) )
        {
                message_vision("$N對$n一拱手，道：你已經轉世輪回過了，我看就不用了吧！\n",
                               this_object(), who);
                return 1;
        }
        */

        if( query("reborn_lunhui", who) )
        {
                message_vision("$N對$n一拱手，道：你已經挑戰過六道守衛佛了，我送你找地藏王吧！\n",
                               this_object(), who);
                who->move("/d/death/yanluodian");
                return 1;
        }

        if( !query("reborn_offer", who) || query("reborn_offer", who) != "finish" )
        {
              message_vision("$N對$n一拱手，道：我沒有收到你的閻王契，你是否並沒有完成五岳獻祭的契約？\n",
                               this_object(), who);
                return 1;
        }

        if( !query("over_quest/hell_quest/鎖陽丹", who) )
        {
                message_vision("$N對$n一拱手，道：你先幫我找到鎖陽丹的藥引，才能得到轉世的機緣。\n",
                               this_object(), who);
                return 1;
        }

        all = deep_inventory(who);
        foreach( object user in all )
                if( userp(user) )
                        return notify_fail("你先把你身上背著的人放下來再說。\n");

        message_vision("$N雙手拍了一下，$n腳下突然陷了下去。。。\n",
                       this_object(), who);

        switch(random(6))
        {
        case 0:
                tell_object(who, BLU "\n你覺得自己不斷下降，周圍景物如彩蝶翻飛，不可注目。\n" NOR);
                who->move("/d/death/liudaolunhui/tiandao");
                break;
        case 1:
                tell_object(who, BLU "\n你覺得自己不斷下降。\n" NOR);
                who->move("/d/death/liudaolunhui/chushengdao");
                break;
        case 2:
                tell_object(who, BLU "\n你覺得自己不斷下降，天地似乎沒了界限。。。\n" NOR);
                who->move("/d/death/liudaolunhui/eguidao");
                break;
        case 3:
                tell_object(who, BLU "\n你覺得自己不斷下降，周圍一切都在旋轉。。。\n" NOR);
                who->move("/d/death/liudaolunhui/rendao");
                break;
        case 4:
                tell_object(who, BLU "\n你覺得自己不斷下降，下降，似乎落向了無盡的深淵。\n" NOR);
                who->move("/d/death/liudaolunhui/diyudao");
                break;
        default:
                tell_object(who, BLU "\n你覺得自己不斷下降，墜向無盡的黑暗。。。\n" NOR);
                who->move("/d/death/liudaolunhui/xiuluodao");
                break;
        }
        return 1;
}

void attempt_apprentice(object ob)
{
        command("say 這裡再怎麼說也是俠客行底層改過來的，要拜地府玩西遊記去。 ");
        return;
}
