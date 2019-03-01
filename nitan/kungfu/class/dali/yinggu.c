// This program is a part of NT MudLIB
// yinggu.c

#include <ansi.h>
inherit NPC;

string ask_me();
int do_answer(string);

void create()
{
        set_name("瑛姑", ({ "ying gu", "ying", "gu" }) );
        set("gender", "女性" );
        set("nickname", CYN "神算子" NOR ) ;
        set("age", 48);
        set("long",
                "她頭發花白，身批麻衫，凝視著地上無數的一根根竹片，"
                "顯然正在潛心思索，雖然聽得有人進來，卻不抬頭。\n");

        set("str", 25);
        set("dex", 35);
        set("con", 27);
        set("int", 25);
        set("shen_type", 1);
        set("max_neili",800);
        set("neili",800);
        set("jiali",30);

        set_skill("unarmed", 80);
        set_skill("dodge", 80);
        set_skill("sword",100);
        set_skill("force", 100);
        set("combat_exp", 100000);

        set("attitude", "peaceful");
        set("inquiry", ([
                "段皇爺"  : "你提他作什麼，哼，求他醫傷麼，死了這條心吧。",
                "周伯通"  : "他、他、、他在哪裡！",
                "段智興"  : "這個老和尚，枉稱慈悲！\n",
                "算術"    :  (: ask_me :),
        ]) );

        set("book_count", 1);

        setup();

        carry_object("/clone/cloth/cloth")->wear();
        // carry_object("/clone/weapon/xiuhua.c")->wield();
        carry_object("/clone/weapon/qijue.c")->wield();
}

void init()
{
        ::init();
        add_action("do_answer","answer");
}

string ask_me()
{
        object who=this_player();
        if( query_temp("marks/瑛", who)){
                        write("瑛姑冷冷的說：上一道你還沒答出來呢，急什麼？\n");
                        return "一道一道的來。\n";
        }
        else {
                write("瑛姑抬頭看了你一眼：這位"+RANK_D->query_respect(who)+"懂算術嗎？\n");
                switch(random(2))
                {
                case 0:
                        write("五萬五千二百二十五的平方根為其何\n");
                        set_temp("marks/瑛", 1, who);
                        break;
                case 1:
                        write("百數方陣，縱橫斜正各五百零五數，\n");
                        write("四二，四一，七六各據一角，余角何數? \n");
                        set_temp("marks/瑛", 2, who);
                        break;
                case 2:
                        write("丈許長桿，日取其半，幾日可終? \n");
                        set_temp("marks/瑛", 3, who);
                        break;
                }
                message_vision("瑛姑冷冷地對$N說：解否? \n", who);
                return "你解出來就回答(answer)我。\n";
        }
}

int do_answer(string arg)
{
        int soln,riddle;
        object ob;
        object me = this_player();
        riddle=query_temp("marks/瑛", this_player());

        if (!riddle) {
                write("我又不是你師傅，你用不著回答我。\n");
                return 1;
        }

        if( !arg || arg=="" ) {
                write("想好謎底再回答。\n");
                return 1;
        }
        message("vision", me->name() + "朗聲回答。\n", environment(me), ({me}));

        switch (arg)
        {
        case "二百三十五": soln=1; break;
        case "六十" : soln=2; break;
        case "萬載不終" : soln=3; break;
        default :
                say("瑛姑冷笑道：“班門弄斧。”然後就把"+ me->name() +"趕了出去。\n");
                me->move("/d/heizhao/maze1");
        return 1;
        }

        if (riddle==soln) {
                say ("瑛姑抬頭冷冷的瞥了"+me->name()+"一眼，段智興在東北方向的桃源。\n");
                set_temp("marks/瑛", 0, this_player());
                ob = new("/d/heizhao/npc/obj/whiteobj");
                ob->move(me);
                ob = new("/d/heizhao/npc/obj/yellowobj");
                ob->move(me);
                ob = new("/d/heizhao/npc/obj/redobj");
                ob->move(me);
                say ("你想見他？好吧，這三個囊兒給你，有緣你就去找他吧。\n");
                say ("瑛姑低頭開始研究算術不再理"+me->name()+"。\n");
                return 1;
        }
        else {
                command("slapsb "+getuid(me));
                say("瑛姑怒道：“你到底懂不懂算術？！”把"+ me->name() +"趕了出去。\n");
                me->move("/d/heizhao/maze1");
        return 1;
        }
}
