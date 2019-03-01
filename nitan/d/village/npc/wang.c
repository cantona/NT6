// wang.c

inherit NPC;
#include <ansi.h>;
int ask_me();

void create()
{
        set_name("王小二", ({ "wang xiaoer", "wang" }) );
        set("gender", "男性" );
        set("age", 21);
        set("long", "這是個典型的關西漢子，一臉彪悍之色。\n");
        set_skill("unarmed", 40);
        set_skill("dodge", 40);
        set("combat_exp", 5000);
        set_temp("apply/attack", 30);
        set_temp("apply/defense", 30);

        set("shen_type", -1);
        set("str", 28);
        set("dex", 25);
        set("con", 20);
        set("int", 17);
        set("book_count", 1);
        set("attitude","heroism");
        set("inquiry", ([
                "王小二" : "那就是我啊...",
                "雞" : (: ask_me :),
                "偷雞" : (: ask_me :),
        ]) );
        setup();
        add_money("silver", 10);
}
void init()
{
        ::init();
        add_action("do_bihua", "bihua");
}

int ask_me()
{
        if( query_temp("marks/王3", this_player()) )
        {
                say(
"王小二眼露兇光，對" + this_player()->name() + "喊道：殺人不過頭點地，我已經\n"
"服了軟，你還不放過我，老子跟你拼了!\n");
                set_temp("apply/attack", 30);
                     set_temp("apply/defense", 30);
                this_object()->kill_ob(this_player());
                return 1;
        } else
        {
        say(
"王小二看了" + this_player()->name() + "一眼，滿不在乎的說道：\n"
"不錯，雞是我偷的，你要怎麼樣！看你也是出來闖江湖的，難道\n" 
"不知江湖上誰的拳頭大誰說話？你不服氣？那好，咱倆練幾招，\n"
"要是你贏了，我馬上按雙倍價賠給老太太。而且我還另外送你點\n"
"東西。你要輸了，就給我爬著出去。怎麼著，敢不敢比劃(bihua)幾下？\n");
set_temp("marks/王2", 1,                 this_player());
                return 1;
        }
}

int do_bihua()
{
        object me, obj, book;
        int current_qi;

        me = this_object();
        obj = this_player();
        if (query("book_count") < 1)
        {
                write("王小二沖著" + obj->name() +
                      "白了白眼：老子沒空，你快給我滾蛋，別攪大爺的清夢。\n");
                return 1;
        }
        addn("book_count", -1);
        book = new("/clone/book/sword_book");
        current_qi=query("qi", me);

        say(obj->name() + "對王小二說：好吧，那" +
            RANK_D->query_self_rude(obj) + "就同你練幾招。\n");
        if( query_temp("marks/王2", obj) )
        {
                set_temp("marks/王2", 0, obj);
                while((query("qi", obj)*100/query("max_qi", obj))>50 )
                {
                        if (! present(obj, environment()))
                                return 1;
                        COMBAT_D->do_attack(obj, me, query_temp("weapon"));
                        if( (query("qi", me)*100/(current_qi+1))<50 )
                        {
                                say("王小二對" + obj->name() +
                                    "說道：今兒您贏了我，您說什麼我都得聽著，"
                                    "我這就把\n錢給老太太送去。另外，這本書也"
                                    "是您的了。這是前些日子華山派從這\n路過，"
                                    "在廟裡歇腳時落下的。\n"
                                );
                                      book->move(obj);
                                      addn("book_count", -1);
set_temp("marks/王3", 1,                                 obj);
                                message_vision("$N交給$n一本書。\n", me, obj);
                                return 1;
                        }
                        COMBAT_D->do_attack(me, obj);
                }
                say("王小二沖著" + obj->name() +
                    "撇了撇嘴，說道：就你這點本事還來\n"
                    "充英雄？給我乖乖的爬出去吧！\n"
                );
                message("vision", obj->name() + "乖乖的趴在地上，從洞裡爬了"
                        "出去。\n", environment(obj), ({obj}) );
                obj->move("/d/village/temple1");
                message("vision", obj->name() + "從洞裡爬了出來。\n",
                        environment(obj), ({obj}) );
                return 1;
        }
        say("王小二不耐煩的對" + obj->name() +
            "說道：要打就動手，羅嗦什麼！\n");
        return 1;
}
