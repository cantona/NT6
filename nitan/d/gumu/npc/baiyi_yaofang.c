// longnv.c 白衣少女
// by April 01/09/26

#include <ansi.h>
inherit NPC;
int ask_aoyao();

void create()
{
        object bj;

        set_name("白衣少女", ({ "baiyi girl", "girl"}));
        set("long", 
                "她披著一襲輕紗般的白衣，面容秀美絕俗。\n");
        set("gender", "女性");
        set("age", 26);
        set("attitude", "peaceful");
        set("shen_type", 1);

        set("str", 20);
        set("int", 25);
        set("con", 25);
        set("dex", 30);

        set("max_qi", 4000);
        set("max_jing", 5500);
        set("jiali", 200);
        set("neili", 6000);
        set("max_neili", 6000);
        set("jingli",4000);
        set("eff_jingli",4000);
        set("max_jingli",4000);

        set("combat_exp", 500000);
        set("score", 5000);

        set_skill("force", 150);
        set_skill("yunv-jian", 150);
        set_skill("cuff", 150);
        set_skill("meinv-quan", 150);
        set_skill("sword", 150);
        set_skill("yunv-jian", 150);
        set_skill("finger", 150);
        set_skill("parry", 150);
        set_skill("dodge", 150);
        set_skill("yunv-shenfa", 150);
        set_skill("qufeng",150);
        set_skill("parry",150);
        set_skill("suxin-jue",150);
        set_skill("zuoyou-hubo",150);
        set_skill("throwing",150);
        set_skill("whip",150);
        set_skill("jueqing-bian",150);
        // set_skill("finger",150);
        // set_skill("suhan-zhi",150);

        map_skill("force", "yunv-jian");
        map_skill("dodge", "yunv-shenfa");
        map_skill("cuff", "meinv-quan");
        map_skill("parry", "yunv-jian");
        map_skill("sword", "yunv-jian");

        prepare_skill("cuff", "meinv-quan");

        create_family("古墓派", 5, "弟子");

    set("chat_chance_combat", 50);

        set("inquiry", ([
            "配藥" : (: ask_aoyao :),
            "煉藥" : (: ask_aoyao :),
            "製藥" : (: ask_aoyao :),
            "熬藥" : (: ask_aoyao :),
        ]));

        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/gumu/npc/obj/white_silk")->wear();
        
}

void init()
{
        object ob;

        ::init();
        return;
}

int ask_aoyao()
{
        object me = this_player();
        message_vision(query("name")+"向$N解釋道：\n",me);
        message_vision("你先將蓋子打開[open lip]，然後加入所需的藥材[add **** in lu]\n",me);
        message_vision("記着適量倒一些玉蜂蜜[pour mi]，這是我古墓聖藥的藥引。再扣好蓋子[close lip]\n",me);
        message_vision("把炭盆點燃[burn coal]，等爐火旺起來了。就可以熬藥了[aoyao]。\n",me);
        message_vision("熬藥時要隨時控制火候，還要不停攪拌，很累人的。藥熬好了之後，\n",me);
        message_vision("記得先滅了火[mie huo]再取藥[qu yao]，以免被燙傷。\n",me);
        return 1;
}