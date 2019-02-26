// This program is a part of NITAN MudLIB
// shan.c 張翠山

#include <ansi.h>
#include "wudang.h"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_GUARDER;

mixed ask_me();

void create()
{
        set_name("張翠山", ({ "zhang cuishan", "zhang" }));
        set("nickname","武當五俠");
        set("long",
                "他就是張三丰的五弟子、武當七俠之中的張翠山。\n"
                "身穿一件乾乾淨淨的藍色道袍。\n");
        set("gender", "男性");
        set("age",31);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 28);
        set("int", 35);
        set("con", 28);
        set("dex", 28);
        set("max_qi", 5000);
        set("max_jing", 5000);
        set("neili", 4500);
        set("max_neili", 4500);
        set("jiali", 150);
        set("level", 20);
        set("combat_exp", 1400000);
        set("score", 60000);

        set_skill("force", 180);
        set_skill("yinyun-ziqi", 180);
        set_skill("taiji-shengong", 180);
        set_skill("dodge", 170);
        set_skill("tiyunzong", 170);
        set_skill("unarmed", 180);
        set_skill("taiji-quan", 180);
        set_skill("strike", 180);
        set_skill("yitian-zhang", 180);
        set_skill("wudang-zhang", 170);
        set_skill("hand", 160);
        set_skill("paiyun-shou", 160);
        set_skill("parry", 180);
        set_skill("sword", 175);
        set_skill("wudang-jian", 175);
        set_skill("taiji-jian", 175);
        set_skill("taoism", 160);
        set_skill("literate", 120);

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
        map_skill("strike", "yitian-zhang");

        prepare_skill("strike", "yitian-zhang");

        create_family("武當派", 2, "弟子");

        set("inquiry", ([
                "倚天屠龍掌": (: ask_me :),
                "誰與爭鋒"  : (: ask_me :),
                "絕招"  : (: ask_me :),
        ]));

        set("chat_chance_combat", 40);
        set("chat_msg_combat", ({
                (: perform_action, "strike.zheng" :),
        }) );

        set("coagents", ({
                ([ "startroom" : "/d/wudang/sanqingdian",
                   "id"        : "song yuanqiao" ]),
        }));

        set("master_ob", 4);
        setup();

        carry_object(WEAPON_DIR"changjian")->wield();
        carry_object("/d/wudang/obj/bluecloth")->wear();
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
        if (! ob || environment(ob) != environment())
                return;

        if (find_object(query("startroom")) == environment())
                return;

        if( query("shen", ob)<-1000 )
        {
                say(CYN "\n\n張翠山臉現怒容：“邪魔外道，吃了豹子"
                    "膽了，敢亂闖武當！”\n\n");
                message_vision("張翠山居高臨下，出手一招，$N只"
                               "得硬接，身子晃了一下。\n", ob);
                COMBAT_D->do_attack(this_object(), ob, query_temp("weapon"));
        }
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if (ob->query_int() < 30)
        {
                command("say 你的資質將來到不了鐵劃銀鈎的境界，收你也是白搭。\n");
                return;
        }

        if( query("shen", ob)<5000){
                command("say 我武當乃是堂堂名門正派，對弟子要求極嚴。");
                command("say 在德行方面，" + RANK_D->query_respect(ob) +
                        "是否還做得不夠？");
                return;
        }

        if ((int)ob->query_skill("yinyun-ziqi", 1) < 70)
        {
                command("say 我武當派最注重內功心法" + RANK_D->query_respect(ob)+
                        "是否應該在武當心法上多下點功夫啊?");
                return;
        }

        if ((int)ob->query_skill("taoism", 1) < 70)
        {
                command("say 習武是為了強身健體，一味的練武是不可取的。");
                command("say 我看你還需要在修身養性方面多鍛鍊鍛鍊，以提高你"
                        "的道德心法。");
                return;
        }

        command("say 好吧，我就收下你了。");
        command("recruit "+query("id", ob));
}
mixed ask_me()
{
        object me;

        me = this_player();
        if( query("can_perform/yitian-zhang/zheng", me) )
                return "你不是已經會了嗎？怎麼老是糾纏不休。";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "不是我們武當派的人，何出此言？";

        if (me->query_skill("yitian-zhang", 1) < 1)
                return "你連倚天屠龍掌都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<200 )
                return "你為我武當派效力還不夠，這招我先不忙傳你。";

        if( query("shen", me)<12000 )
                return "你行俠仗義的事情做的還很不夠，我不能傳你絕招！";

        if( query("max_neili", me)<800 )
                return "你的內力修為太淺，修煉高了再來吧。";

        if (me->query_skill("yitian-zhang", 1) < 120)
                return "你的倚天屠龍掌還不到家，要多練練！";

        message_vision(HIY "$n" HIY "點了點頭，運起太極神功，將倚天屠龍"
                       "掌二十四字一氣呵\n成，攜帶着排山倒海之勁一齊施"
                       "展了出來。只見雙掌紛飛，掌風\n凌厲，直颳得$N" HIY
                       "臉龐隱隱生痛。\n" NOR, me, this_object());
        command("nod");
        command("say 將倚天屠龍掌二十四招連續使出，便是新招。你可明白了？");
        tell_object(me, HIC "你學會了「誰與爭鋒」。\n" NOR);
        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("yitian-zhang"))
                me->improve_skill("yitian-zhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/yitian-zhang/zheng", 1, me);
        addn("family/gongji", -200, me);

        return 1;
}


