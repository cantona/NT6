// This program is a part of NITAN MudLIB
// yan.c 俞岱巖

#include <ansi.h>
#include "wudang.h"

inherit NPC;
inherit F_MASTER;

string ask_yao1();
string ask_yao2();
void create()
{
        set_name("俞岱巖", ({ "yu daiyan", "yu" }));
        set("nickname","武當三俠");
        set("long",
                "他就是張三丰的三弟子俞岱巖。\n"
                "身穿一件乾乾淨淨的灰色道袍。\n"
                "他已年過四十，身材瘦長。恬淡沖和，沉默寡言。\n");
        set("gender", "男性");
        set("age",43);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 29);
        set("int", 28);
        set("con", 31);
        set("dex", 25);

        set("max_qi", 4400);
        set("max_jing", 2000);
        set("neili", 5200);
        set("max_neili", 5200);
        set("jiali", 100);
        set("level", 20);
        set("combat_exp", 1450000);
        set("score", 45000);

        set_skill("force", 190);
        set_skill("yinyun-ziqi", 190);
        set_skill("taiji-shengong", 190);
        set_skill("dodge", 165);
        set_skill("tiyunzong", 165);
        set_skill("unarmed", 170);
        set_skill("taiji-quan", 170);
        set_skill("strike", 170);
        set_skill("wudang-zhang", 170);
        set_skill("hand", 170);
        set_skill("paiyun-shou", 170);
        set_skill("parry", 175);
        set_skill("sword", 180);
        set_skill("wudang-jian", 180);
        set_skill("taiji-jian", 180);
          set_skill("taoism", 160);
        set_skill("literate", 100);

        set("no_teach", ([
                "taiji-shengong" : "要想學習太極神功請向張真人請教。",
                "taiji-jian"     : "太極劍必須張真人親傳。",
                "taiji-quan"     : "太極拳必須張真人親傳。",
        ]));

        map_skill("force", "taiji-shengong");
        map_skill("dodge", "tiyunzong");
        map_skill("unarmed", "taiji-quan");
        map_skill("parry", "taiji-quan");
        map_skill("sword", "taiji-jian");
        map_skill("strike", "wudang-zhang");

        prepare_skill("unarmed", "taiji-quan");
        prepare_skill("strike", "wudang-zhang");

        create_family("武當派", 2, "弟子");
        set("master_ob", 4);
        setup();
        carry_object(WEAPON_DIR"changjian")->wield();
        carry_object("/d/wudang/obj/greyrobe")->wear();

}

void init()
{
        object ob;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting",2 , ob);
        }
}

void greeting(object ob)
{
        int i;

        if (! objectp(ob) || environment(ob) != environment())
                return;

        if ((int)ob->query_skill("yinyun-ziqi", 1) == 0)
        {
                message_vision(CYN "五行八卦弟子對$N" CYN "齊聲喝道：你這個"
                               "邪魔外道，敢來真武劍陣？\n\n" NOR, ob);
                set("eff_qi", 1, ob);
                set("qi", 1, ob);
                message_vision(HIR "只見真武劍陣頓時啟動，高台上劍氣縱橫，把$N"
                               HIR "圍在中央。十三\n個五行八卦弟子的十三口長劍"
                               "齊出，瞬間在$N" HIR "身上劃出了十三道\n口子，"
                               "頓時鮮血淋漓。\n\n" NOR, ob);

                say(CYN "俞岱巖臉現怒容，喝道：邪魔外道，也敢闖真武劍陣！\n");
                message_vision(HIY "只見俞岱巖居高臨下，起手一掌把$N" HIY
                                   "劈落高台。\n\n" NOR, ob);
                ob->move("/d/wudang/nanyangong");
                CHANNEL_D->do_channel(this_object(), "chat", sprintf("%s私闖"
                                      "真武劍陣，念其成長不易，暫免一死！",
                                      ob->name(1)));
        }
}

void attempt_apprentice(object me)
{
        if (! permit_recruit(me))
                return;

        if ((int)me->query_skill("yinyun-ziqi", 1) < 30) {
                command("say 我武當派乃內家武功，最重視內功心法。");
                command("say " + RANK_D->query_respect(me) +
                        "是否還應該在太極神功上多下點功夫？");
                return;
        }

        if( query("shen", me)<10000){
                command("say 我武當乃是堂堂名門正派，對弟子要求極嚴。");
                command("say 在德行方面，" + RANK_D->query_respect(me) +
                        "是否還做得不夠？");
                return;
        }

        if ((int)me->query_skill("yinyun-ziqi", 1) < 70)
        {
                command("say 我武當派最注重內功心法" + RANK_D->query_respect(me)+
                        "是否應該在武當心法上多下點功夫啊?");
                return;
        }

        if ((int)me->query_skill("taoism", 1) < 70)
        {
                command("say 習武是為了強身健體，一味的練武是不可取的！");
                command("say 我看你還需要在修身養性方面多鍛鍊鍛鍊，以提"
                        "高你的道德心法。");
                return;
        }

        command("say 好吧，我就收下你了。");
        command("recruit "+query("id", me));
}

string ask_yao1()
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player())) || 
                fam["family_name"] != "武當派")
                return RANK_D->query_respect(this_player()) +"與本派素無來往，不知此話從何談起？";
        if (ob = present("jujing dan", this_player()))
                return "你身上不是帶着本門延年聚精丹？！";
        if (query("yao1_count") < 1)
                return "你來晚了，本門延年聚精丹已盡數給了本派弟子。";
        addn("yao1_count", -1);
        ob = new("/clone/medicine/nostrum/jujingdan");
        ob->move(this_player());
        return "我這裏有本門延年聚精丹，你拿去吧。";
}

string ask_yao2()
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player())) || 
                fam["family_name"] != "武當派")
                return RANK_D->query_respect(this_player()) +
                "與本派素無來往，不知此話從何談起？";
        if (ob = present("jieqi wan", this_player()))
                return "你身上不是帶着本門九轉結氣丸？！";
        if (query("yao2_count") < 1)
                return "你來晚了，本門九轉結氣丸已盡數給了本派弟子。";
        addn("yao2_count", -1);
        ob = new("/clone/medicine/nostrum/jieqiwan");
        ob->move(this_player());
        return "我這裏有本門九轉結氣丸，你拿去吧。";
}
