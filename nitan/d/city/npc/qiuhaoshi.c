//Npc : qiu_haoshi.c

inherit NPC;
#include <ansi.h>

string ask_room1();
string ask_room2();

void create()
{
    set_name( YEL "仇好石" NOR, ({"qiu haoshi", "qiu", "haoshi"}) );
    set( "title", "揚州容膝園主人" );
    set( "age", 52 );
    set( "int", 30 );
    set( "con", 26 );
    set( "per", 18 );
    set( "attribute", "peaceful" );

    set( "long", @LONG
仇好石是揚州的治園名家，據説幾個著名的園子都出自他的手小。
他個子不高，腦袋卻是極大，如墨刷的眉毛，小小的眼睛，大大
的鼻子，生就一副奇相。
LONG
    );
    set( "combat_exp", 10000 );
    set_skill( "literate", 100);

    set( "inquiry", ([
        "小玲瓏山館" : (: ask_room1 :),
        "楊府" : (: ask_room1 :),
        "郡圃" : (: ask_room2 :),
        "官衙後院" : (: ask_room2 :),
        "酒" : "我平生除酒外別無所好。\n",
        "喝酒" : "我平生除酒外別無所好。\n",
        "容膝園" : "呵呵，一個小園子了。\n",
        "揚州" : "天下三分明月夜，無奈二分在揚州，哈哈。。。",
    ]) );
        set("chat_chance", 3);
        set("chat_msg", ({
        "。。。仇好石看了你一眼，卻什麼也不説。",
        "你為何來煩我？",
        "何必把時間浪費在我這樣一個老頭子身上呢？",
        "唉。。仇好石長歎一聲，轉身又開始喝酒了。"
    }) );
    setup();
    carry_object(CLOTH_DIR"jinduan")->wear();
}

int accept_object( object me, object ob )
{
    if ( userp(ob) ) return 0;
    if( query("name", ob) == "通州雪酒" )
    {
        remove_call_out( "accepted" );
        call_out( "accepted", 1, me );
        return 1;
    }
}

void accepted(object me)
{
    command( "haha" );
    command("tell"+query("id", me)+"你是任何得知我最好此酒？\n");
    command( "en" );
    command("tell"+query("id", me)+"對於你的疑惑，我當知無不言。\n");
    command("haha"+query("id", me));
    command( "drink skin" );
    me->set_temp("can_ask_qiu");
}

string ask_room1()
{
    if( query("can_ask_qiu", this_player()) )
    {
        command( "say 小玲瓏山館最有意思的地方就是疏峯館了，不過\n"
         + "在我設計好後據説楊先生有改了一下，我卻沒看出來。\n"  );
        return "別的地方，你可以去看看，看看老夫我的治園手藝如何。";
    }
    else
        return "小玲瓏山館是我設計的。";
}

string ask_room2()
{
    if( query("can_ask_qiu", this_player()) )
    {
        command( "say 郡圃的外牆都用花窗、漏窗，也不高，也不怕賊闖入，呵呵！\n"
         + "不過官衙重地一般的賊子不敢闖入的。\n" );
        return "郡圃一般人可都進不去的。\n";
    }
    else
        return "郡圃乃是前任知州大人託我設計的。\n";
}

