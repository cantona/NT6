// This program is a part of NT MudLIB

#include <ansi.h>
inherit NPC;

inherit F_DEALER;

int ask_xueyi();
string ask_xiao();

void create()
{
        set_name("曲三", ({ "qu san", "san", "qu" }));
        set("title", "酒店老闆");
        set("nickname", "跛子");
        set("gender", "男性");
        set("age", 25);
        set("long",
                "他是最近新搬到此地的一個跛子。他無精打彩地招呼着客人，"
                "眼睛不時呆呆地看着天空。\n");
        set("attitude", "friendly");
        set("class", "scholar");
        set("str", 30);
        set("int", 24);
        set("con", 27);
        set("dex", 23);
        set("shen_type",1);
        set("max_qi", 4500);
        set("max_jing", 2500);
        set("neili", 5000);
        set("max_neili", 5000);
        set("jiali", 120);
        set("level", 20);
        set("combat_exp", 1000000);

        set_skill("force", 200);
        set_skill("bibo-shengong", 200);
        set_skill("unarmed", 180);
        set_skill("xuanfeng-tui", 180);
        set_skill("strike", 180);
        set_skill("luoying-shenzhang", 180);
        set_skill("finger", 200);
        set_skill("throwing", 200);
        set_skill("tanzhi-shentong", 200);
        set_skill("dodge", 200);
        set_skill("luoying-shenfa", 200);
        set_skill("parry", 200);
        set_skill("sword", 200);
        set_skill("luoying-shenjian", 200);
        set_skill("literate", 200);
        set_skill("martial-cognize", 180);

        map_skill("force", "bibo-shenfa");
        map_skill("unarmed", "xuanfeng-tui");
        map_skill("strike", "luoying-shenzhang");
        map_skill("finger", "tanzhi-shengong");
        map_skill("throwing", "tanzhi-shentong");
        map_skill("dodge", "luoying-shenfa");
        map_skill("parry", "luoying-shenjian");
        map_skill("sword", "luoying-shenjian");

        prepare_skill("finger", "tanzhi-shentong");

        set("xiao_count", 1);

        set("attitude", "friendly");
        set("inquiry", ([
                "黃藥師" : "我師…，什麼？我這裏不賣藥。\n",
                "賣藥"   : "不賣藥就是不賣藥。\n",
                "曲靈風" : "啊！我，……你説的人我不認識。\n",
                "生意"   : "這個麼……。\n",
                "學藝"   : (: ask_xueyi :),
                "古玩"   : (: ask_xiao :),
        ]));

        // create_family("桃花島", 2, "弟子");
        set("vendor_goods", ({
                "/d/city/obj/peanut",
        }));

        setup();
        carry_object("/d/city/obj/cloth")->wear();
        carry_object("/d/taohua/obj/bagua");
}

void init()
{
        object ob;

        ::init();
        if (interactive(ob = this_player()) && !is_fighting())
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}

void greeting(object ob)
{
        if (!ob || environment(ob) != environment())
                return;

        say("曲三有氣無力地説道：這位" + RANK_D->query_respect(ob) +
            "，買點五香花生下酒吧。\n");
}

/*
void unconcious()
{
        object ob;
        object who = this_player();

        message_vision("\n突然，只見曲三用盡最後一絲氣力向$N打出一個鐵八卦！\n",
                who);
        who->receive_damage("qi",100);
        who->receive_wound("qi",100);
        ob = new (__DIR__"obj/tiebagua");
        ob->move(environment(this_object()));
        :: unconcious();
}
*/

int accept_object(object me, object obj)
{
        call_out("accept_obj", 1, me, obj);
        return 1;
}

int accept_obj(object me, object obj)
{
        if( query("name", obj) == "黃藥師手諭" )
        {
                command("ah");
                message_vision(CYN "$N雙手顫抖的展開書信，急匆匆的讀了起來。\n", this_object());
                message_vision(CYN "$N一邊讀，一邊熱淚盈眶！\n", this_object());
                command("cry");
                command("say 多謝"+ RANK_D->query_respect(me) + "了。\n");
                set_temp("huang_shouyu", 1, me);
        }

        if( query("name", obj) == "長命鎖" )
        {
                command("ah");
                command("say 這不是我女兒的東西嗎？她現在怎麼樣了？！");
                set_temp("shagu_amulet", 1, me);
        }

        if( query_temp("huang_shouyu", me )
             && query_temp("shagu_amulet", me) )
        {
                command("say 曲某不肖，不為師父分憂，反勞師父日夜牽掛；有勞" +
                        RANK_D->query_respect(me) + "費心奔走了。\n");

                command("thank "+query("id", me));

                if( query("family/family_name", me) == "桃花島" )
                // &&  me->query("family/master_name") != "黃藥師")
                {
                        command("say " + RANK_D->query_respect(me) + "天資不錯，在下身無" +
                                "長物，唯有一身武藝，若不嫌我武功低淺，可點撥" + RANK_D->query_respect(me) + "一二。");
                        command("say " + RANK_D->query_respect(me) + "只需向我詢問『學藝』即可。");
                        set("help_lingfeng", 1, me);
                        delete_temp("huang_shouyu", me);
                        delete_temp("shagu_amulet", me);
                        set_temp("lingfeng_teach", 1, me);
                }
        }
        destruct(obj);
        return 1;
}

int ask_xueyi()
{
        object me, *ob;
        int i, k = 0;

        me = this_player();
        if( !query_temp("lingfeng_teach", me )
         && (query("family/master_name", me) != "曲靈風") )
        {
                command("say " + RANK_D->query_respect(me) + "説笑了，在下只是個窮賣酒的，有啥可教的？");
                return 1;
        }

        if (base_name(environment(me)) != "/d/jiaxing/xiaodian")
        {
                command("say 這得回到酒店再説。");
                return 1;
        }

        ob = all_inventory(environment(me));
        for (i = 0; i < sizeof(ob); i++)
        {
                if (! living(ob[i]))
                        continue;
                k++;
        }

        if (k > 2)
        {
                command("whisper "+query("id", me)+
                        "這裏耳目眾多，實不是傳功授藝之所，還是先打發了周圍閒人再説。");
                return 1;
        }

        command("say " + RANK_D->query_respect(me) + "隨我來。");
        tell_object(me, CYN "曲三脱下破舊的布衣，換上一身青袍，在臉上摸了幾把。\n" NOR);
        tell_object(me, CYN "曲三打開碗櫥，將一隻碗向右旋轉，忽聽得喀喇喇一聲響，"
                        "櫥壁向兩旁分開，露出黑黝黝的一個洞來。\n" NOR);
        set_temp("taohua/master", this_object()->name(), me);
        me->move("/d/jiaxing/mishi");

        return 1;
}


string ask_xiao()
{
        object me = this_player();
        object ob;
        mapping myfam;

        myfam=query("family", me);
        if (! myfam || myfam["family_name"] != "桃花島")
        {
                command("xixi");
                return RANK_D->query_respect(me) + "有什麼古玩要賣給在下？";
        }


        if (query("xiao_count") < 1)
                return "最近生意不好，哪裏有錢買古玩？";

        if( present("tongxiao",this_player()) || query_temp("get_xiao", this_player()) )
                return RANK_D->query_respect(me) + "還沒有把古玩交給黃島主？";

        command("say " + RANK_D->query_respect(me) + "是從桃花島來的？");

        if (me->query_skill("bibo-shengong", 1) < 100)
                return "久聞黃島主收藏奇珍異寶，我有些古玩，想請他老人家鑑賞。";

        if (me->query_skill("yuxiao-jianfa", 1) < 100)
                return "久聞黃島主收藏奇珍異寶，我有些古玩，想請他老人家鑑賞。";


        command("touch"+query("id", me));
        ob = new("/clone/weapon/tongxiao");
        ob->move(this_player());
        addn("xiao_count", -1);
        set_temp("get_xiao", 1, this_player());

        message_vision("曲三遞給$N一支青銅簫。\n", this_player());

        return "我近日得到一件古玩，麻煩你帶給黃島主鑑賞鑑賞。";
}
