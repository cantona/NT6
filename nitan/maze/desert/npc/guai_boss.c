#include <ansi.h>

inherit BOSS;

void create()
{
        set_name(HIY"賊盜頭領"NOR, ({"zeidao touling", "touling", "zeidao"}) );
        set("title", HIY "綠林豪傑" NOR);
        set("gender", "男性" );
        set("age", random(30)+20);
        set("long", "無盡大漠邊緣活動的賊盜小頭目，佔著一身武藝經常領著一幫小嘍羅搶劫過往行人。\n");
        set("attitude", "aggressive");
        set("class", "lvlin");
        set("str", 30);
        set("con", 30);
        set("int", 30);
        set("dex", 30);
        set("max_qi", 50000);
        set("max_jing", 50000);
        set("neili", 150000);
        set("max_neili", 50000);
        set("no_suck",1);
        set("jiali", 3000);
        set("shen", 0);
        set_temp("apply/attack",  50);
        set_temp("apply/defense", 30);
        set("combat_exp", 500000);
        set_skill("force", 150);
        set_skill("unarmed", 150);
        set_skill("blade", 150);
        set_skill("dodge", 150);
        set_skill("parry", 150);
        set_skill("jiuyin-baiguzhao", 150);
        set_skill("wuhu-duanmendao", 150);
        set_skill("taiji-shengong", 150);
        set_skill("tiyunzong", 150);
        map_skill("force", "taiji-shengong");
        map_skill("unarmed","jiuyin-baiguzhao");
        map_skill("parry", "jiuyin-baiguzhao");
        map_skill("blade", "wuhu-duanmendao");
        map_skill("dodge", "tiyunzong");
        create_family("綠林暴風盟", 3, "弟子");
        set("auto_perform", 1); 

        set("drops", ([
                "RA&RANDOM30" : 30,
                "RA&RANDOM20" : 40,
        ]));
        set("rewards", ([
                "exp"  : 200,
                "pot"  : 70,
                "mar"  : 10,
        ]));

        set_temp("apply/armor", 1000+random(1000));
        set_temp("apply/reduce_damage", 30);

        setup();

        if( random (10) > 5 )
                carry_object("/d/city/obj/blade")->wield();
        else
                carry_object("/d/city/obj/gangjian")->wield();

        carry_object("/clone/misc/cloth")->wear();
        add_money("gold",random(5));
}

void init()
{
        object ob, me;

        me = this_player();
        ob = this_object();

        ::init();
        if( interactive(me) && visible(me) &&
            !is_fighting()) {
                NPC_D->copy_from_me(ob, me, 70, 1);
                kill_ob(me);
        }
}
