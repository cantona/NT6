// Code of ShenZhou
// /clone/beast/xbaozi.c
// 小豹子
// sdong 08/98
// Modified by xQin 11/00

#include <ansi.h>
inherit NPC;


void create()
{
                  set_name("小豹子", ({ "xiao baozi", "baozi" }) );
                  set("race", "野獸");
                  set("age", 1);
                  set("long", "一隻身體不大可是很結實的小豹子，它正瞪着眼睛看着你。\n");
                  set("attitude", "aggressive");
        set_weight(200000);
                  set("max_qi", 100);
                  set("max_jing", 100);
                  set("max_jingli", 100);


                  set("str", 30);
                  set("con", 80);
                  set("dex", 30);
                  set("int", 10);

                  set("combat_exp", 20000);

                  set_temp("apply/attack", 10);
                  set_temp("apply/damage", 10);
                  set_temp("apply/armor", 10);

                  setup();
}

void die()
{
                  object ob,ob2=this_object();

                  ob = new(DRUG_D("baodan"));
                  ob->move(environment(this_object()));
                  message_vision("$N慘嚎一聲，死了！\n", this_object());
                  destruct(ob2);
}
