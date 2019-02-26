// zhou.c 周伯通
#include <ansi.h>
inherit NPC;
int jie_bai();
void create()
{
        set_name("周伯通", ({ "zhou botong", "zhou", "bo tong" }));
        set("gender", "男性");
        set("nickname", CYN "老頑童" NOR ) ;
        set("age", 45);
        set("long",
        "他就是人稱「老頑童」的周伯通。\n"
        "他本來是全真教掌門人的師弟，武功高強，但現在卻被人囚禁在\n"
        "這小小山洞之中，頭髮鬍子長長的，毛茸茸的象一個野人。\n",
        );
        set("combat_exp", 64000000);
        set("shen", 10000);
        set("max_neili", 3000);
        set("neili", 500000);
        set_skill("force", 250);
        set_skill("sword", 250);
        set_skill("unarmed", 250);
        set_skill("dodge", 250);
        set_skill("parry", 250);
        set_skill("zuoyou-hubo" ,1100);
        set_skill("kongming-quan",250);
        map_skill("unarmed","kongming-quan");
        map_skill("parry","kongming-quan");
        set("inquiry", ([
                "九陰真經" : "「九陰真經」就在我牀上，你有本事殺了我\n"
                              " 或把我逼出山洞就可以取走！\n",
                "黃藥師" : "他囚了我十五年，總想把我逼出山洞"
                           "以取「九陰真經」，\n可他每次來都是掃興而歸！\n",
                "瑛姑" :   "我、我、、我不認識她！",
                "蛇" :     "不要嚇我，我最怕蛇了！\n",
                "結拜" :   (: jie_bai :),
        ]) );
        create_family("全真教", 11, "弟子");
        set_temp("apply/attack", 50);
        set_temp("apply/defense", 50);
        set_temp("apply/damage", 15);
        setup();
        carry_object("/clone/cloth/cloth")->wear();
}
int jie_bai()
{
        object ob ;
        ob = this_player ( ) ;
        if( query("gender", ob) != "男性" )
        {
                message_vision("\n老頑童上上下下打量了$N一番，説到：我生平不喜同兩種人\n"
                "打交道：一是女人，二是太監。我看你還是趁早請罷！”\n", ob);
                return 1;
        }
      if( query("character", ob) == "心狠手辣" || query("character", ob) == "陰險奸詐" )
  {
              say("老頑童哼了一聲説：就憑你這種惡人也配與我稱兄道弟？！\n");
              return 1;
      }
        if( query("shen", ob)<-1000 )
        {
                say("老頑童哼了一聲説：就憑你這種惡人也配與我稱兄道弟？！\n");
                return 1;
        }
        say("老頑童高興地説：好！以後我們就是好兄弟了！\n");
        tell_object(ob,GRN "周伯通悄悄對你説：老哥哥有一套「雙手互搏之術」和一路\n"
        "「空明拳」可以傳給你作為見面禮喲！\n" NOR );
        set_temp("wantong/兄弟", 1, this_player());
        return 1;
}
int recognize_apprentice(object ob, string skill)
{
        if( !query_temp("wantong/兄弟", ob) )
                return 0; 

        if (skill != "kongming-quan" && skill != "zuoyou-hubo")
                return 0; 
        return 1;
}
int accept_object(object who, object ob)
{    
        if ( (string)ob->name() == "毒蛇")
        {
                message_vision("$N拿出一條毒蛇在老頑童的眼前晃了晃．．．．．．\n"
                "老頑童嚇得跳了起來，衝出洞外！邊跑邊喊：咬死了，咬死了！\n\n\n"
                "聲音漸漸遠去，終於不復耳聞。\n" ,who);
            call_out("dest",1,this_object());
                return 0;
        }
        return 0;
}
void dest(object me)
{
    if (me)  destruct(me);
}
