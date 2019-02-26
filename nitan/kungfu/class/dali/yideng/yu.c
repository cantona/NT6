// yu.c 點蒼漁隱

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("點蒼漁隱", ({ "diancang yuyin", "yu" }));
        set("title",  "大理國水軍都督" );
        set("long", 
"他就是大理國的原水軍都督，一燈大師的四大弟子之一。
他約莫四十來歲年紀，一張黑漆漆的鍋底臉，虯髯滿腮，
根根如鐵。\n");
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
        set_skill("tiannan-bu", 100);
        set_skill("jinyu-quan", 100);
        set_skill("wuluo-zhang", 100);
        set_skill("duanjia-jian", 100);
        set_skill("sun-finger", 100);
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

        set("inquiry", ([
                "一燈大師"   : "師父他老人家在上面。\n",
                "段智興"     : "那是我師父俗世的名諱。\n",
                "劉瑛姑"     : "她是我師父俗世的妃子。\n",
        ]) );

        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/kungfu/class/dali/obj/diaogan")->wield();
        add_money("silver", 50);

        create_family("大理段家",25,"弟子");
}

void init()
{
        object ob;

        ::init();
        if( interactive(ob=this_player()) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        mapping myfam;

        myfam = (mapping)query("family", ob);
        if( myfam["master_id"] == "yideng dashi")
        {
message_vision(HIY"點蒼漁隱對$N説：你回來了。自己上去見師父吧。\n"NOR, ob);
                set_temp("yu_allow", 1, ob);
        }
        return;
}

int accept_object(object who, object ob)
{
        if ( !who || environment(who) != environment() ) return 0;
        if ( !objectp(ob) ) return 0;
        if ( !present(ob, who) ) return notify_fail("你沒有這件東西。\n");

        if( query("id", ob) != "hongbu" )
                return notify_fail("點蒼漁隱不想要這件東西。\n");
        say( "點蒼漁隱衝你點了點頭：進屋去吧。\n");
        set_temp("yu_allow", 1, who);
        return 1;
}
