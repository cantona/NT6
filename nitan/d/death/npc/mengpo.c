#include <ansi.h>
inherit NPC;

mixed ask_me();

void create()
{
        set_name("孟婆", ({ "meng po", "meng", "po" }) );
        set("title", HIR "奈河橋渡者" NOR);
        set("gender", "女性");
        set("age", 390);
        set("long",
                "這就是奈河橋的孟婆，她面頰深陷，瘦骨零丁。\n");

        set("attitude", "peaceful");
        set("combat_exp", 2500000);

        set("chat_chance", 1);
        set("chat_msg",({
                CYN "孟婆説道：孩子，喝碗湯吧。\n" NOR,
                CYN "孟婆説道：過了奈河橋，前途就艱難了。\n" NOR,
                CYN "孟婆弓着腰煮着孟婆湯。\n" NOR,
                CYN "孟婆輕輕咳嗽了幾聲。\n" NOR,
        }));

        set("inquiry", ([
                "孟婆湯" : (: ask_me :),
                "湯"     : (: ask_me :),
                "喝湯"   : (: ask_me :),
                "tang"   : (: ask_me :),
        ]));

        set("count", 10);

        setup();

        carry_object(__DIR__"obj/cloth3")->wear();
}

mixed ask_me()
{
        mapping fam;
        object ob;
        object me = this_player();

        if ( ! me->is_ghost() && ! wizardp(me))
                return "陽人喝什麼孟婆湯？";

        if( query("combat_exp", me)<1000000000 )
                return "你還是回去吧，這湯…你不喝也罷。";

        if ( present("mengpo tang", this_player()) )
                return "你身上不是還有一碗嗎？怎麼死了還這麼貪心？";

        if( time()-query_temp("last_eat/mengpo_tang", me)<200 )
                return "你不是剛剛才喝了一碗嗎？";

        if (query("count") < 1)
                return "湯已經舀完了，待我再煮一鍋。";

        ob = new("/d/death/obj/tang");
        ob->move(me);

        addn("count", -1);

        message_vision(HIC "\n孟婆弓下腰，舀了一碗孟婆湯遞給$N" HIC "。\n\n" NOR, me);
                return "孩子，喝了這湯就該上路了。";
}