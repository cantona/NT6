#include <ansi.h>

inherit NPC;
int ask_bijian();

void create()
{
        set_name("任我行--虛", ({ "ren woxing shadow", "shadow" }));
        set("title", BLU "日月神教教主"NOR );
        set("long", "只見他一張長長的臉孔，臉色雪白，更無半分血色，眉目清秀，
身材甚高，一頭黑發，穿的是一襲青衫。與前三個人一樣，也是虛幻的。\n");
        set("gender", "男性");
        set("class", "scholar");
        set("age", 55);
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 130);
        set("per", 127);
        set("int", 130);
        set("con", 310);
        set("dex", 130);
        
        set("max_qi", 311000);
        set("max_jing", 100110);
        set("neili", 400110);
      set("max_neili", 4110000);
        set("jiali", 40110);
        set("combat_exp", 201100000);
        set("score", 50001100);

        set_skill("literate", 1100);
        set_skill("force", 2100);
        set_skill("dodge", 2100);
        set_skill("unarmed", 2010);
        set_skill("parry", 2100);
        set_skill("sword", 2100);
        set_skill("changquan", 2010);
        set_skill("kuihua-xinfa", 2100);
        set_skill("lingxu-bu", 2100);
        set_skill("damo-jian", 2100);
        set_skill("taiji-jian", 2100);
        set_skill("huifeng-jian", 2010);
        set_skill("taishan-sword", 2100);
        set_skill("hengshan-jian", 2010);
        set_skill("hengshan-sword", 2100);
        set_skill("huashan-sword", 2010);
        set_skill("songshan-sword", 2010);

        map_skill("dodge", "lingxu-bu");
        map_skill("force", "kuihua-xinfa");
        map_skill("unarmed", "changquan");
        map_skill("sword", "damo-jian");
        map_skill("parry", "damo-jian");

        set("inquiry", ([
                "過關" :  (: ask_bijian :),
                "比劍" :  (: ask_bijian :),
        ]) );
        setup();
    carry_object("/d/wudang/obj/greyrobe")->wear();
        carry_object("/clone/weapon/changjian")->wield();
}

int ask_bijian()
{
        object obj, me = this_player(), ob = this_object();
        object room; 
       message_vision("$N躬身說道：“晚輩想解開封印，領教了。”\n
$n笑道：“不用客氣，你接得下我數招，我自然放你過關。”\n", me, ob );
        say(HIR"任我行大喝一聲：“少林劍法！”"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( query("qi", me)<0 || !present(me,environment()) )
        {
                say("任我行嘆了口氣，說道：“才一招。”\n");
                return 1;
        }
        command("enable sword taiji-jian");
        say(HIR"任我行大喝一聲：“武當劍法！”"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( query("qi", me)<0 || !present(me,environment()) )
        {
                say("任我行嘆了口氣，說道：“才兩招。”\n");
                return 1;
        }
        command("enable sword huifeng-jian");
        say(HIR"任我行大喝一聲：“峨嵋劍法！”"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( query("qi", me)<0 || !present(me,environment()) )
        {
                say("任我行嘆了口氣，說道：“才三招。”\n");
                return 1;
        }
        command("enable sword songshan-sword");
        say(HIR"任我行大喝一聲：“嵩山劍法！”"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( query("qi", me)<0 || !present(me,environment()) )
        {
                say("任我行嘆了口氣，說道：“才四招。”\n");
                return 1;
        }
        command("enable sword taishan-sword");
        say(HIR"任我行大喝一聲：“泰山劍法！”"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( query("qi", me)<0 || !present(me,environment()) )
        {
                say("任我行嘆了口氣，說道：“才五招。”\n");
                return 1;
        }
        command("enable sword huashan-sword");
        say(HIR"任我行大喝一聲：“華山劍法！”"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( query("qi", me)<0 || !present(me,environment()) )
        {
                say("任我行嘆了口氣，說道：“才六招。”\n");
                return 1;
        }
        command("enable sword hengshan-sword");
        say(HIR"任我行大喝一聲：“衡山劍法！”"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( query("qi", me)<0 || !present(me,environment()) )
        {
                say("任我行嘆了口氣，說道：“才七招。”\n");
                return 1;
        }
        command("enable sword hengshan-jian");
        say(HIR"任我行大喝一聲：“恆山劍法！”"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( query("qi", me)<0 || !present(me,environment()) )
        {
                say("任我行嘆了口氣，說道：“還是沒過八招。”\n");
                return 1;
        }
        say("任我行說道：“這位" + RANK_D->query_respect(me)+"不錯，我就放你們過關吧。”\n"); 
          if(!( room = find_object("/d/dragon/spirit5")) )
                  room = load_object("/d/dragon/spirit5");
        if(objectp(room)) 
            { 
                 set("exits/northup", "/d/dragon/spirit6", room);
                message("vision","任我行在牆上按了一按，一道向上的階梯緩緩降了下來。\n\n\n\n",room);
        set_temp("m_success/幻影", 1, me);
      message_vision (HIY"$N走上階梯，光芒乍起，一個小精靈出現在光芒裡，微笑道：你又解開了第六個封印，謝謝你。\n\n"NOR,this_player());   
      message("channel:chat",HBMAG"【精靈神界】"+query("name", me)+"又解開了第六個封印.\n"NOR,users());
      message_vision (HIY"光芒中，任我行--虛也漸漸消失了。\n"NOR,this_player());   
        destruct(this_object());
           }
        return 1;
}
