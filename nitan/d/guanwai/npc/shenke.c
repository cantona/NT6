#include <ansi.h>
inherit NPC;

mixed ask_me();

void create()
{
        set_name("參客", ({ "shen ke", "shen", "ke" }));
        set("long", "他是一個參客，常年在關外經營，頗為富有。\n");
        set("age", 65);
        set("combat_exp", 300);
        set("str", 30);
        set("dex", 30);
        set("con", 30);
        set("int", 30);
        set("attitude", "friendly");
        set("inquiry", ([
                "入關" : (: ask_me :),
                "回去" : (: ask_me :),
        ]));
        setup();
        set("startroom", "/d/beijing/majiu");
        carry_object("/clone/misc/cloth")->wear();
}

mixed ask_me()
{
        object ob, me;
        me = this_player();

        if( query("family/family_name", me) != "關外胡家" )
                return "你是誰？請問我認識你麼？";

        if (find_object(query("startroom")) != environment())
                return "我這裏還有事，你就自己走回去吧。";

        command("hehe");
        command("say 既然是平四爺朋友的事，我怎麼可能不幫？");

        message_sort(HIC "\n便見參客指着$N" HIC "對馬伕道「這是我"
                     "朋友，現在要回關外，你找個夥計送他，路費伙食"
                     "全部由我擔負，一切以三倍計算。」馬伕聽後立忙"
                     "連聲稱是，將$N" HIC "送上馬車，絕塵而去。\n"
                     "\n" NOR, me);

        ob = load_object("/d/guanwai/xiaoyuan");
        ob = find_object("/d/guanwai/xiaoyuan");
        me->move("/d/guanwai/xiaoyuan");

        message("vision", HIC "\n遠處一輛馬車急駛而來，車門一開" +
                          query("name", me)+HIC"從裏面鑽了出"
                          "來。\n\n" NOR, environment(me), ({me}));

        tell_object(me, CYN "\n馬伕笑道：這位" + RANK_D->query_respect(me) +
                        CYN "已經到了，請下車吧。\n\n" NOR );
        return 1;

}
