// miao.c 苗人鳳

#include <ansi.h>;

inherit NPC;

string ask_me();
string ask_book();
string ask_hujia_book();

void create()
{
        set_name("苗人鳳", ({ "miao renfeng", "miao" }));
        set("gender", "男性");
        set("nickname", YEL "金面佛" NOR);
        set("age", 37);
        set("long", @LONG
他看上去臉色透黃，似乎蒙了一層淡淡的金紙。身材高大魁梧，確
是全然不修篇幅，令人稱奇。
LONG );
        set("attitude", "peaceful");
        set("str", 32);
        set("int", 31);
        set("con", 33);
        set("dex", 31);
    
        set("qi", 4500);
        set("max_qi", 4500);
        set("jing", 2200);
        set("max_jing", 2200);
        set("neili", 4800);
        set("max_neili", 4800);
        set("jiali", 120);
        set("combat_exp", 2200000);

        set_skill("force", 220);
        set_skill("hunyuan-yiqi", 220);
        set_skill("sword", 230);
        set_skill("miaojia-jian", 230);
        set_skill("dodge", 210);
        set_skill("feiyan-zoubi", 210);
        set_skill("strike", 225);
        set_skill("tianchang-zhang", 225);
        set_skill("parry", 230);

        map_skill("force", "hunyuan-yiqi");
        map_skill("sword", "miaojia-jian");
        map_skill("dodge", "feiyan-zoubi");
        map_skill("parry", "miaojia-jian");
        map_skill("strike", "tianchang-zhang");

        prepare_skill("strike", "tianchang-zhang");

        set("inquiry", ([
                "胡一刀": (: ask_me :),
                "打遍天下無敵手" : "這話説説而已，豈能當真？",
        ]));

        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

string ask_me()
{
        object ob, me;

        me = this_player();
        if( query("family/family_name", me) != "關外胡家" )
                return "這人真是一條漢子！可惜啊可惜！\n";

        return "當年不幸中了奸人毒計傷了他，令人遺憾終生！你既然是"
               "胡家的後人，可對我苗家劍法感興趣？";
}

int recognize_apprentice(object ob, string skill)
{
        if( query("family/family_name", ob) != "關外胡家" )
        {
                command("say 你這算是什麼意思？要是比劃就放馬過來！");
                return -1;
        }

        if (skill != "miaojia-jian" && skill != "sword")
        {
                command("say 我只傳你劍法，你如果不感興趣就不要浪費時間了。");
                return -1;
        }

        if( !query_temp("can_learn/miao", ob) )
        {
                command("say 好！你既然感興趣，那就要看仔細了！");
                set_temp("can_learn/huyizhi", 1, ob);
        }

        return 1;
}