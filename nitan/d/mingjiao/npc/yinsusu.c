// Yinsusu.c

inherit NPC;
inherit F_MASTER;
inherit F_UNIQUE;
int ask_me();
int decide();
void goto_wpsd1(object me);
void goto_wpsd2(object me);
#include <ansi.h>

void create()
{
        set_name("殷素素", ({ "yin susu", "yin", "susu", }));
        set("long","她是白眉鷹王的獨生女。手白勝雪，玉頰微瘦，眉彎鼻挺，一笑時
左頰上淺淺一個梨渦。\n"
        );

        set("gender", "女性");
        set("attitude", "friendly");
        set("class", "fighert");

        set("age", 18);
        set("shen_type", 1);
        set("per", 29);
        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 25);
        set("max_qi", 1000);
        set("max_jing", 1000);
        set("neili", 1000);
        set("max_neili", 1000);
        set("jiali", 100);
        set("combat_exp", 100000);
        set("score", 5000);

        set_skill("force", 85);
        set_skill("hunyuan-yiqi", 85);
        set_skill("dodge", 85);
        set_skill("shaolin-shenfa", 85);
        set_skill("cuff", 95);
        set_skill("jingang-quan", 95);
        set_skill("parry", 85);
        set_skill("buddhism", 85);
        set_skill("literate", 85);

        map_skill("force", "hunyuan-yiqi");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("cuff", "jingang-quan");
        map_skill("parry", "jingang-quan");

        set("inquiry", ([
                "謝遜"      : (: ask_me :),
                "冰火島"    : (: ask_me :),
                "屠龍刀"    : (: ask_me :),
                "金毛獅王"  : (: ask_me :),
                "白眉鷹王"  : "那是我爹。",
        ]));
        prepare_skill("cuff", "jingang-quan");

        set("party/party_name",HIG"明教"NOR);
        set("party/rank",HIM "紫微堂" NOR "堂主");
        create_family("明教", 35, "弟子");
        setup();

        carry_object("/d/yanziwu/npc/obj/green_cloth")->wear();
}

void init()
{
        add_action("do_decide", "decide");
}

int ask_me()
{
        object me;
        me = this_player ( ) ;
        message_vision(
"殷素素上上下下打量了$N一下，道：這位"+RANK_D->query_respect(me)+"，你不過是想屠龍刀吧。\n這小船也經不起海浪，我正要去王盤山島，你看看快點決定(decide)要不要去。\n",me);

        set_temp("yinsusu", 1, me);
        return 1;
}

int do_decide()
{
        object me;
        me = this_player ( ) ;
        if( query_temp("yinsusu", me) != 1 )
                return notify_fail("殷素素問：你決定什麼呀？\n");

        message_vision("殷素素對$N説道：“好，你可別後悔，坐穩了。”\n\n", me);
        message_vision("殷素素升起帆，小舟輕輕漂向江口。\n\n", me);
        me->move ("/d/binghuo/jiangmian1");
        call_out("goto_wpsd1",10,me) ;
               return 1;
}

void goto_wpsd1(object me)
{
        message_vision("風帆帶風，小舟在劇顛中漂出江口。\n\n", me);
        me->move ("/d/binghuo/jiangmian2");
        call_out("goto_wpsd2",10,me) ;
}

void goto_wpsd2(object me)
{
        tell_object(me , "片刻間坐船靠岸，白龜壽親自鋪上跳板。你走下舟來。\n" ) ;
        me->move ("/d/binghuo/wangpanshan") ;
}
