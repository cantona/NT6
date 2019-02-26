// This program is a part of NITAN MudLIB

#include <ansi.h>
#include "wudang.h"

inherit NPC;
inherit F_MASTER;
inherit F_GUARDER;

mixed ask_me();

void create()
{
        set_name("張松溪", ({ "zhang songxi", "zhang" }));
        set("nickname", "武當四俠");
        set("long",
                "他就是張三丰的四弟子張松溪。\n"
                "他今年四十歲，精明能幹，以足智多謀著稱。\n");
        set("gender", "男性");
        set("age", 40);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 26);
        set("int", 33);
        set("con", 26);
        set("dex", 28);

        set("max_qi", 4700);
        set("max_jing", 2400);
        set("neili", 5100);
        set("max_neili", 5100);
        set("jiali", 90);
        set("combat_exp", 1250000);
        set("score", 50000);

        set_skill("force", 170);
        set_skill("yinyun-ziqi", 170);
        set_skill("taiji-shengong", 170);
        set_skill("dodge", 150);
        set_skill("tiyunzong", 150);
        set_skill("unarmed", 160);
        set_skill("taiji-quan", 160);
        set_skill("strike", 160);
        set_skill("wudang-zhang", 160);
        set_skill("hand", 160);
        set_skill("paiyun-shou", 160);
        set_skill("parry", 180);
        set_skill("sword", 160);
        set_skill("wudang-jian", 160);
        set_skill("blade", 160);
        set_skill("xuanxu-dao", 160);
        set_skill("taiji-jian", 160);
        set_skill("taoism", 140);
        set_skill("literate", 150);

        set("no_teach", ([
                "taiji-shengong" : "要想學習太極神功請向張真人請教。",
                "taiji-jian"     : "太極劍必須張真人親傳。",
                "taiji-quan"     : "太極拳必須張真人親傳。",
        ]));

        map_skill("force", "taiji-shengong");
        map_skill("dodge", "tiyunzong");
        map_skill("unarmed", "taiji-quan");
        map_skill("parry", "xuanxu-dao");
        map_skill("sword", "wudang-jian");
        map_skill("blade", "xuanxu-dao");
        map_skill("strike", "wudang-zhang");

        prepare_skill("unarmed", "taiji-quan");
        prepare_skill("strike", "wudang-zhang");

        create_family("武當派", 2, "弟子");

        set("inquiry", ([
                "亂環決": (: ask_me :),
                "絕招"  : (: ask_me :),
        ]));

        set("coagents", ({
                ([ "startroom" : "/d/wudang/houyuan",
                   "id"        : "yu lianzhou" ]),
                ([ "startroom" : "/d/wudang/sanqingdian",
                   "id"        : "song yuanqiao" ]),
        }));

        set("chat_chance_combat", 40);
        set("chat_msg_combat", ({
                (: perform_action, "blade.huan" :),
                (: exert_function, "recover" :),
        }) );

        set("master_ob", 4);
        setup();
        carry_object(WEAPON_DIR"blade")->wield();
        carry_object("/d/wudang/obj/whiterobe")->wear();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("shen", ob)<6000 )
        {
                command("say 我武當乃是堂堂名門正派，對弟子要求極嚴。");
                command("say 在德行方面，" + RANK_D->query_respect(ob) +
                        "是否還做得不夠？");
                return;
        }

        if ((int)ob->query_skill("yinyun-ziqi",1) < 60)
        {
                command("say 我武當派最注重內功心法" + RANK_D->query_respect(ob)+
                        "是否應該在武當心法上多下點功夫啊?");
                return;
        }

        if ((int)ob->query_skill("taoism", 1) < 60)
        {
                command("say 習武是為了強身健體，一味的練武是不可取的。");
                command("say 我看你還需要在修身養性方面多鍛鍊鍛鍊，以提"
                        "高你的道德心法。");
                return;
        }

        command("say 好吧，我就收下你了。");
        command("say 希望你能好好用功，消滅邪魔外道！");
        command("recruit "+query("id", ob));
        if( query("class", ob) != "taoist" )
                set("class", "taoist", ob);
}

mixed ask_me()
{
        object me;

        me = this_player();
        if( query("can_perform/xuanxu-dao/huan", me) )
                return "我都教給你了，自己好好多練習吧！";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "不是我們武當派的人，何出此言？";

        if (me->query_skill("xuanxu-dao", 1) < 1)
                return "你連玄虛刀法都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<150 )
                return "你為我武當派效力還不夠，這招我先不忙傳你。";

        if( query("shen", me)<10000 )
                return "你行俠仗義的事情做的還很不夠，我不能傳你絕招！";

        if (me->query_skill("xuanxu-dao", 1) < 100)
                return "你的玄虛刀法還不到家，要多練練！";

        message_vision(HIY "$n" HIY "點了點頭，隨手揮舞手中鋼刀，畫出一"
                       "個個圓\n圈，每招均是以弧形刺出，弧形收回。刀出成"
                       "環，環\n環相連，直看得$N" HIY "眼花繚亂。\n" NOR,
                       me, this_object());
        command("smile");
        command("say 你可明白了玄虛刀法的要詣？");
        tell_object(me, HIC "你學會了「亂環決」。\n" NOR);
        if (me->can_improve_skill("blade"))
                me->improve_skill("blade", 1500000);
        if (me->can_improve_skill("xuanxu-dao"))
                me->improve_skill("xuanxu-dao", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/xuanxu-dao/huan", 1, me);
        addn("family/gongji", -150, me);

        return 1;
}

