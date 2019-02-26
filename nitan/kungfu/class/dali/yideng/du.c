// du.c 書生

#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string ask_reply1();
string ask_reply2();
string ask_reply3();

void create()
{
        set_name("朱子柳", ({ "zhu ziliu", "zhu", "ziliu" }));
        set("title",  "大理國大宰相" );
        set("long", 
"他就是大理國的原大宰相，一燈大師的四大弟子之一。
只見他四十來歲年紀，頭戴逍遙巾，手揮摺疊扇，頦下
一叢漆黑的長鬚，確是個飽學宿儒模樣。\n");
        set("gender", "男性");
        set("age", 45);
        set("class", "officer");
        set("attitude", "friendly");
        set("shen_type", 1);
        set("per", 20);
        set("str", 30);
        set("int", 30);
        set("con", 35);
        set("dex", 30);
        
        set("max_qi", 1500);
        set("max_jing", 500);
        set("neili", 1500);
        set("max_neili", 1500);
        set("jiali", 100);
        set("combat_exp", 500000);
        set("score", 10000);

        set_skill("force", 100);
        set_skill("dodge", 100);
        set_skill("parry", 100);
        set_skill("cuff", 100);
        set_skill("strike", 100);
        set_skill("sword", 100);
        set_skill("staff", 100);
        set_skill("finger", 100);
        set_skill("kurong-changong", 100);
        set_skill("tiannan-bu", 150);
        set_skill("jinyu-quan", 150);
        set_skill("wuluo-zhang", 150);
        set_skill("duanjia-jian", 150);
        set_skill("sun-finger", 150);
        set_skill("literate", 100);

        map_skill("force", "kurong-changong");
        map_skill("dodge", "tiannan-bu");
        map_skill("finger", "sun-finger");
        map_skill("cuff", "jinyu-quan");
        map_skill("strike", "wuluo-zhang");
        map_skill("parry", "sun-finger");
        map_skill("sword", "duanjia-jian");
        map_skill("staff", "duanjia-jian");
        prepare_skill("cuff", "jinyu-quan");
        prepare_skill("strike", "wuluo-zhang");        
        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: perform_action, "sword.jingtian" :),        
                (: perform_action, "finger.qiankun" :),                        
                (: exert_function, "powerup" :),                
                (: exert_function, "recover" :),
                (: exert_function, "regenerate" :),
        }) );

        set("inquiry", ([
                "一燈大師"   : "師父他老人家在裏面。你答對了就可以見他了。\n",
                "段智興"     : "那是我師父俗世的名諱。\n",
                "劉瑛姑"     : "她是我師父俗世的妃子。\n",
                "辛未狀元"   : (: ask_reply1 :),
                "霜凋荷葉，獨腳鬼戴逍遙巾"   : (: ask_reply2 :),
                "魑魅魍魎，四小鬼各自肚腸"   : (: ask_reply3 :),
        ]) );

        set("chat_chance", 3);
        set("chat_msg", ({
"朱子柳讀道：“暮春者，春服既成，冠者五六人，童子六七人，浴
乎沂，風乎舞雩，詠而歸。”讀得興高采烈，一誦三歎，確似在春
風中載歌載舞，喜樂無已。\n",
"朱子柳捻鬚吟道：
    “六經藴籍胸中久，一劍十年磨在手。
      杏花頭上一枝橫，恐泄天機莫露口。
      一點累累大如鬥，卻掩半牀無所有。
      完名直待掛冠歸，本來面目君知否？”\n",
"朱子柳揮扇指着一排棕櫚道：“風擺棕櫚，千手佛搖摺疊扇。”\n",
"朱子柳道：“我有一聯，請你對個下聯：‘琴瑟琵琶，八大王一般頭面’。”\n",
        }) );
        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/book/lbook4");
        add_money("silver", 50);

        create_family("大理段家",25,"弟子");
}


void greeting(object ob)
{
        mapping myfam;

        myfam = (mapping)query("family", ob);
        if( myfam["master_name"] == "yideng dashi")
              say ("朱子柳衝着你點了點頭，説：你回來了。\n");
        set_temp("du_allow", 1, ob);
        return;
}

string ask_reply1()
{
        object me = this_player();
        set_temp("yideng_du1", 1, me);
        if( query_temp("yideng_du2", me) && query_temp("yideng_du3", me) )
        {
message_vision("\n朱子柳大驚，站起身來，長袖一揮，向$N一揖到地，説道：“在下拜服。”\n\n", me);
                set_temp("du_allow", 1, me);
                return RANK_D->query_respect(me) + "請。";
        }
        else
                return RANK_D->query_respect(me) + "果然文武全才。不過還有呢？";
}
string ask_reply2()
{
        object me = this_player();
        set_temp("yideng_du2", 1, me);
        if( query_temp("yideng_du1", me) && query_temp("yideng_du3", me) )
        {
message_vision("\n朱子柳大驚，站起身來，長袖一揮，向$N一揖到地，説道：“在下拜服。”\n\n", me);
                set_temp("du_allow", 1, me);
                return RANK_D->query_respect(me) + "請。";
        }
        else
                return RANK_D->query_respect(me) + "果然文武全才。不過還有呢？";
}
string ask_reply3()
{
        object me = this_player();
        set_temp("yideng_du3", 1, me);
        if( query_temp("yideng_du1", me) && query_temp("yideng_du2", me) )
        {
message_vision("\n朱子柳大驚，站起身來，長袖一揮，向$N一揖到地，説道：“在下拜服。”\n\n", me);
                set_temp("du_allow", 1, me);
                return RANK_D->query_respect(me) + "請。";
        }
        else
                return RANK_D->query_respect(me) + "果然文武全才。不過還有呢？";
}
