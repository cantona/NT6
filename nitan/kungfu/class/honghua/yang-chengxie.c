#include <ansi.h>
#include "honghua.h"

inherit NPC;
inherit F_MASTER;
inherit F_GUARDER;

void create()
{
        set_name("楊成協", ({ "yang chengxie", "yang", "chengxie"}));
        set("title", "紅花會八當家");
        set("nickname", WHT "鐵塔" NOR);
        set("long", "他就是楊成協，只見他又肥又高，手執鋼鞭，\n"
                    "鞭身甚是粗重，看模樣少説也有三十來斤。\n");
        set("gender", "男性");
        set("age", 28);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("per", 21);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("qi", 3500);
        set("max_qi", 3500);
        set("jing", 3000);
        set("max_jing", 3000);
        set("neili", 2000);
        set("max_neili", 2000);
        set("jiali", 80);
        set("combat_exp", 500000);
        set("score", 10000);

        set_skill("force", 120);
        set_skill("honghua-xinfa", 120);
        set_skill("unarmed", 120);
        set_skill("changquan", 120);
        set_skill("dodge", 120);
        set_skill("yanzi-chuanyun", 120);
        set_skill("staff", 140);
        set_skill("fengmo-zhang", 140);
        set_skill("parry", 120);
        set_skill("martial-cognize", 100);
        set_skill("literate", 140);

        map_skill("force"  , "honghua-xinfa");
        map_skill("staff"  , "fengmo-zhang");
        map_skill("unarmed" , "changquan");
        map_skill("dodge"  , "yanzi-chuanyun");
        map_skill("parry"  , "fengmo-zhang");

        prepare_skill("unarmed", "changquan");

        set("coagents", ({
                ([ "startroom" : "/d/kaifeng/hh_jianlou1",
                   "id"        : "wuchen daozhang" ]),
        }));

        set("guarder", ([
                "refuse_other": CYN "$N" CYN "對$n" CYN "冷喝道："
                                "你給我站住！我們紅花會豈是由得外"
                                "人隨便走動地方？" NOR,
                "refuse_carry": CYN "$N" CYN "對$n" CYN "喝道：你"
                                "背上背的是什麼人？給我放下來！" NOR,
        ]));

        create_family("紅花會", 4, "二當家");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "staff.lun" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }) );
        setup();

        carry_object("/clone/misc/cloth")->wear();
        carry_object(__DIR__"obj/tiebian");
}

void attempt_apprentice(object me)
{
        if (! permit_recruit(me))
                return;

        if( query("shen", me)<-1000 )
        {
                command("say 我紅花會不收不義之人，你還是走吧。");
                return;
        }

        command("nod");
        command("say 嗯。那你以後跟着我好了。");
        command("recruit "+query("id", me));
}

void hit_ob(object ob)
{
        object me = this_object();
        object where = environment (me);
        object guard1 = present ("jiang sigen", where);
        object guard2 = present ("honghua dizi", where);
        object guard3 = present ("honghua dizi 2", where);
        object guard4 = present ("honghua dizi 3", where);
        object guard5 = present ("honghua dizi 4", where);

        set_temp("my_killer", ob);
        ::kill_ob(ob);

        if (guard1 && ! guard1->is_fighting())
        {
                message_vision (HIW "\n蔣四根大怒，喝道：居然欺到我們紅花會"
                                "頭上來了，大家併肩子上！\n\n" NOR, guard1);
                guard1->kill_ob(ob);
        }

        if (guard2 && ! guard2->is_fighting())
                guard2->kill_ob(ob);

        if (guard3 && ! guard3->is_fighting())
                guard3->kill_ob(ob);

        if (guard4 && ! guard4->is_fighting())
                guard4->kill_ob(ob);

        if (guard5 && ! guard5->is_fighting())
                guard5->kill_ob(ob);
}

void kill_ob(object ob)
{
        object me = this_object();
        object where = environment (me);
        object guard1 = present ("jiang sigen", where);
        object guard2 = present ("honghua dizi", where);
        object guard3 = present ("honghua dizi 2", where);
        object guard4 = present ("honghua dizi 3", where);
        object guard5 = present ("honghua dizi 4", where);

        set_temp("my_killer", ob);
        ::kill_ob(ob);

        if (guard1 && ! guard1->is_fighting())
        {
                message_vision (HIW "\n蔣四根大怒，喝道：居然欺到我們紅花會"
                                "頭上來了，大家併肩子上！\n\n" NOR, guard1);
                guard1->kill_ob(ob);
        }

        if (guard2 && ! guard2->is_fighting())
                guard2->kill_ob(ob);

        if (guard3 && ! guard3->is_fighting())
                guard3->kill_ob(ob);

        if (guard4 && ! guard4->is_fighting())
                guard4->kill_ob(ob);

        if (guard5 && ! guard5->is_fighting())
                guard5->kill_ob(ob);
}
