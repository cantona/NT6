// Npc: /d/guiyun/npc/lucf.c
// Last Modified by winder on Jul. 9 2001

inherit NPC;

int ask_ci();
int ask_yue();

void create()
{
        set_name("陸乘風", ({"lu chengfeng", "lu", "chengfeng"}) );
        set("nickname", "歸雲莊主");
        set("long",
                "他臉色枯瘦，身材甚高，坐在榻上一動不動，似乎雙腿有殘疾。\n");
        set("gender", "男性" );
        set("age", 42);
        set("attitude", "friendly");
        set("apprentice",1);
        set("str",30);
        set("int",29);
        set("con",28);
        set("dex",5);
        set("max_qi", 1600);
        set("max_jing", 1000);
        set("neili", 1800);
        set("max_neili", 1800);
        set("jiali", 40);
        set("combat_exp", 800000);


        set_skill("force", 100);
        set_skill("bibo-shengong", 90);
        set_skill("dodge", 30);
        set_skill("anying-fuxiang", 85);
        set_skill("parry", 90);
        set_skill("strike", 100);
        set_skill("luoying-shenzhang", 90);
        set_skill("leg", 110);
        set_skill("xuanfeng-tui", 100);
        set_skill("sword", 90);
        set_skill("yuxiao-jianfa", 80);
        set_skill("taoism", 90);
        set_skill("literate", 100);
        set_skill("qimen-wuxing", 140);

        map_skill("force", "bibo-shengong");
        map_skill("dodge", "anying-fuxiang");
        map_skill("strike", "luoying-shenzhang");
        map_skill("leg", "xuanfeng-tui");
        map_skill("parry", "yuxiao-jianfa");
        map_skill("sword", "yuxiao-jianfa");
        prepare_skill("strike", "luoying-shenzhang");
        prepare_skill("leg", "xuanfeng-tui");

        set("rank_info/respect", "莊主");
        set("shen_type", 1);
        set("shen", 100);
        set("vendetta_mark", "桃花島");
        create_family("桃花島", 2, "弟子");
        set("class", "fighter");

        set("inquiry", ([
                "name": "老夫陸乘風，是這裡的莊主。",
                "rumors": "很久沒有曲師兄的消息了，不知他是否出了意外？",
                "here": "這裡是歸雲莊，你隨便轉轉吧，累了請到客房休息。",
                "畫" : "這幅畫上的詞是一位大英雄、大豪傑所作。",
                "詞" : (: ask_ci :),
                "藥" : "靈藥我交付小兒冠英保管了。",
                "三才聚精丹": "靈藥我交付小兒冠英保管了。",
                "六壬集氣丸": "靈藥我交付小兒冠英保管了。",
                "九花玉露丸": "靈藥我交付小兒冠英保管了。",
                "字" : "這幅字是老朽寫的，你看怎麼樣？",
                "大英雄": "你先看看詞再說，難道你沒有讀過這首詞嗎？",
                "大豪傑": "你先看看詞再說，難道你沒有讀過這首詞嗎？",
                "岳飛"  : (: ask_yue :),
                "岳武穆" : (: ask_yue :),
                "東邪": "那是恩師呀，雖然他打斷我們的雙腿，還逐我們出島，但一日為師，終生為父呀！",
                "黃藥師": "那是恩師呀，雖然他打斷我們的雙腿，還逐我們出島，但一日為師，終生為父呀！",
                "恩師" : "就是桃花島主黃藥師了，他聰明絕頂，文才武學，書畫琴棋，算數韜略，醫卜星相，奇門五行，無一不精。",
                "家師" : "就是桃花島主黃藥師了，他聰明絕頂，文才武學，書畫琴棋，算數韜略，醫卜星相，奇門五行，無一不精。",
                "黃蓉": "嗯，那是小師妹，是家師的掌上明珠。",
                "桃花島": "好懷念原來大家在那裡的時光呀，曲師兄臨離島時還畫了海圖呢。",
                "陸乘風": "就是老夫我，有什麼事嗎？",
                "陸冠英": "那是小犬，以前送在仙都派門下習藝，現在師父恩準在我門下學藝了。",
                "冠英": "那是小犬，以前送在仙都派門下習藝，現在師父恩準在我門下學藝了。",
                "歸雲莊": "這裡是花了我無數心血才建起來的，與別的莊院相比如何？",
                "太湖": "就在莊前不遠，是一個煙波浩淼的大湖。",
                "九宮": "九宮之義，法以靈龜。二四為肩，六八為足；左三右七，戴九履一；五居中間。",
                "八卦": "乾三連，坤六段；離中虛，坎中滿；震仰盂，艮覆碗；兌上缺，巽下斷。",
                "五行": "金生水，水生木，木生火，火生土，土生金。金克木，木克土，土克水，水克火，火克金。",
                "易經": "是一本講解伏羲六十四卦的奇書，一般人難得看懂。",
                "周易": "是一本講解伏羲六十四卦的奇書，一般人難得看懂。",
                "九陰真經": "唉，就是這本書連累了我們大家！",
        ]) );

        set("chat_chance", 5);
        set("chat_msg",({
                "陸乘風對著那幅畫長嘆一聲，默然不語，似有滿腹心事。\n",
        }));
        setup();

        carry_object(WEAPON_DIR+"sword/yudi")->wield();
        carry_object("/clone/misc/cloth")->wear();
}

void attempt_apprentice(object ob)
{
        object letter;
        string letter_desc;

        if( !query("thd/receive", ob) )
        {
                command("say 沒有家師的許可，陸某不敢擅自將恩師的武功轉授他人！");
                if( !query("family", ob) && ob->query_int() >= 28 )
                {
                        command("say 不過我看" + RANK_D->query_respect(ob) + "的資質還不錯，這樣吧，我寫一封推薦信，你拿去找家師吧。");
                        letter = new("/d/guiyun/obj/tuijian_xin");
                        set("owner",query("id",  ob), letter);
                        letter_desc="這是陸乘風寫給黃藥師的一封信，上面寫著：\n恩師在上：今有"+query("name", ob)+"一名，欲拜入本派，弟子不敢擅專，又念其資質不錯，特此推薦與恩師定奪。乘風叩首\n";
                        set("long", letter_desc, letter);
                        letter->move(ob);
                        message_vision("陸乘風掏出一封推薦信，寫上$N的名字，交給了$N。\n", ob);
                        command("say 家師是桃花島主黃藥師，你需要從臨安附近坐船上島。至于桃花島的位置嘛，就在...在...讓我想想看...");
                        command("consider");
                        command("doubt chengfeng");
                        command("sigh");
                        command("say 居然想不起來了！你去問我師兄曲靈風吧，他在臨安東南的牛家村開了一間小店。");
                }
                return;
        }
        delete("thd/receive", ob);
        if( query("gender", ob) != "男性" && query("gender", ob) != "女性"){
                command("say 你不男不女的算什麼東西？快滾！");
                return;
        }
        if( query("shen", ob) <= -100000){
                command("say 家師生平最討厭兩種人，你們這種無惡不作的邪魔外道就是其一，再去求家師吧！");
                return;
        }
        if( query("shen", ob) >= 100000){
                command("say 家師生平最討厭兩種人，你們這種自命大俠的沽名釣譽之徒就是其一，再去求家師吧！");
                return;
        }
        if (ob->query_int() < 28) {
                command("say 你的才氣還不夠，再去求家師吧！");
                return;
        }
        if( query("class", ob) == "bonze"){
                command("say 家師比較討厭少林和尚，我可不敢擅自收你。再去求家師吧！");
                return;
        }
        command("say 既然家師有令，我就收你為徒吧。");
        command("recruit"+query("id", ob));
        set("class", "fighter", ob);
}

void init()
{
        object ob = this_player();

        add_action("do_answer","answer");
        add_action("do_answer","huida");
        add_action("do_kill","kill");
        ::init();
        if( query("family/family_name", ob) == "桃花島"){
                if( query("shen", ob) <= -100000){
                        message_vision("陸乘風對$N喝道：你做惡多端，有辱家師清名，還敢來見我？！\n", ob);
                        message_vision("陸乘風對$N喝道：從今天起，你再也不是桃花島的弟子了！\n", ob);
                        delete("family", ob);
                        set("title", "桃花島棄徒", ob);
                }
                else if( query("shen", ob) >= 100000){
                        message_vision("陸乘風對$N喝道：你是大俠，我早就說過，家師最恨沽名吊譽的偽君子。\n", ob);
                        message_vision("陸乘風對$N喝道：從今天起，你再也不是桃花島的弟子了！\n", ob);
                        delete("family", ob);
                        set("title", "桃花島棄徒", ob);
                }
        }
}

int do_kill(string arg)
{
        object ob;
        object me = this_player();
        int perform, payed;

        if (!arg) return 0;
        ob = present(arg, environment(me));
        if (ob == this_object() || ob == me) return 0;
        if (!ob || !ob->is_character()) return 0;
        if( query("family/family_name", ob) == "桃花島"){
                if( query("family/family_name", me) == "桃花島"){
                        message_vision("陸乘風向$N喝道：小奴才，要造反嗎？連自己的同門都殺？！\n", me);
                }
                else {
                        message_vision("陸乘風向$N喝道：大膽狂徒，竟敢來歸雲莊撒野？！\n", me);
                        message_vision("陸乘風對$N說道：你先讓開，讓我來收拾這個" + RANK_D->query_rude(me) + "！\n", ob);
                        kill_ob(me);
                }
                set("vendetta/桃花島", 1, me);
                return 1;
        }
        return 0;
}

int ask_ci()
{
        object ob = this_player();

        command("say 寫這首詞的大英雄、大豪傑就是岳武穆。\n");
        if( !query_temp("guiyun_lutemp", ob) )
                set_temp("guiyun_lutemp", 1, ob);
        return 1;
}

int ask_yue()
{
        object ob = this_player();

        if( query_temp("guiyun_lutemp", ob) >= 1){
                command("say 可惜我的字意有一句與岳武穆原意不太相符，不知" + RANK_D->query_respect(ob) + "能否看出來？\n");
                set_temp("guiyun_lutemp", 2, ob);
        }
        else {
                command("say 岳武穆是我非常敬重的一位大英雄。\n");
        }
        return 1;
}

int do_answer(string arg)
{
        object ob = this_player();

        if( query_temp("guiyun_lutemp", ob) == 2){
                tell_room(environment(ob), ob->name() + "向著陸乘風侃侃而談。\n", ({ob}));
                if (arg == "知音少,弦斷有誰聽?" || arg == "知音少，弦斷有誰聽？" 
                || arg == "知音少,弦斷有誰聽" || arg == "知音少，弦斷有誰聽") {
                        if (!present("tuifa tujie", ob) && query_temp("tuifa_give") < 5) {
                                say("陸乘風長噓一聲：我這番心情，今日才被你看破，可謂平生一知已，這本腿法就送給你吧。\n");
                                new("/d//guiyun/obj/tuifa")->move(ob);
                                delete_temp("guiyun_lutemp", ob);
                                addn_temp("tuifa_give",1);
                        }
                        else {
                                say("陸乘風長噓一聲：我這番心情，今日才被你看破，可謂平生一知已，只可惜老夫我沒有什麼可以相贈的。\n");
                        }
                }
                else {
                        command("?"+query("id", ob));
                        message_vision("陸乘風疑惑地看著$N：" + RANK_D->query_respect(ob) + "似乎應該多學些書法繪畫吧？\n", ob);
                }
                return 1;
        }
//                say("陸乘風說：這一句字透紙背，你可能諶透我的心境？\n");
        return 0;
}
