// yideng.c
#include <ansi.h>
inherit NPC;
inherit F_MASTER;

void consider();

void create()
{
    set_name("一燈大師", ({"yideng-dashi", "dashi", "yideng"}));
    set("nickname", HIG "南帝" NOR );
    set("gender", "男性");
    set("age", 52);
    set("long", 
        "他就是號稱「南帝」的一燈大師，俗名段智興，現已遜位為僧。\n"
        "大師一生行善，積德無窮。\n");
    set("attitude", "peaceful");
    set("class", "scholar");
        
    set("str", 21);
    set("int", 30);
    set("con", 26);
    set("dex", 30);

    set("qi", 3000);
    set("max_qi", 3000);
    set("jing", 3000);
    set("max_jing", 3000);
    set("neili", 3500);
    set("max_neili", 3500);
    set("jiali", 100);
        
    set("combat_exp", 1500000);
    set("score", 0);
         
    set_skill("force", 150);             // 基本內功
    set_skill("finger", 170);            // 基本指法
    set_skill("dodge", 150);             // 基本躲閃
    set_skill("parry", 150);             // 基本招架
    set_skill("six-finger", 200);        // 六脈神劍
    set_skill("taixuan-gong", 200);      // 太玄神功
    set_skill("lingxu-bu", 200);         // 凌虛步
    set_skill("literate",150);           // 讀書識字
        
    map_skill("force"  , "taixuan-gong");
    map_skill("finger" , "six-finger");
    map_skill("dodge"  , "lingxu-bu");
    map_skill("parry"  , "six-finger");

    prepare_skill("finger", "six-finger");

    create_family("大理段家", 17, "弟子");
    setup();

    carry_object("/clone/misc/cloth")->wear();
}
void init()
{
        object ob;

        ::init();
        if( interactive(ob=this_player()) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 2, ob);
        }
}

void greeting(object ob)
{
        object *obj, me=this_object();
        int i;

        obj = all_inventory(environment(me));
//一燈大師哈哈大笑，對着黃藥師拱了拱手道：老爺子過獎了!
        command("nali huang");
        command("say 勁力內含，發之無形，傷人與不覺之中。");
        for(i=0; i<sizeof(obj); i++)
        {
                if( query("id", obj[i]) == "huang-yaoshi" )
                {
                    COMBAT_D->do_attack(me,obj[i],query_temp("weapon", me),0);
                    COMBAT_D->do_attack(me,obj[i],query_temp("weapon", me),0);
                }
        }
        return;
}
