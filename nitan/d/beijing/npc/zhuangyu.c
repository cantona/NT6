inherit NPC;
#include <ansi.h>
int ask_weiwang();

void create()
{
        set_name("莊允城", ({ "zhuang yuncheng", "zhuang","yuncheng" }) );
        set("gender", "男性" );
        set("age", 40);
        set("int", 28);
        set("long",
                "這是個飽讀詩書，卻手無搏雞之力的書生。\n"
             +"因編輯‘明史輯略’，被吳之榮告發，全家逮入京中。\n" );

        set("attitude", "peaceful");
        set_skill("literate", 100);
        set("noget", "莊允城嘆道：我不行了，你走吧。唉，我擔心我家裡人啊。\n");
        set("chat_chance", 5);
        set("chat_msg", ({
        "\n莊允城說道：只怪我當初好心，在書中夾了金葉送與他，\n"
        "誰想這狼心狗肺的家伙竟然就去告發了我。唉...\n",
        "\n莊允城說道：誰要把吳之榮抓到莊府就好了。\n",
        "莊允城突然說道: 江湖威望很重要，威望高大有好處啊。\n",
        "\n莊允城嘆了口氣，說道：我知道鰲拜書房的秘密，只可惜我出不去啊。\n",
        "莊允城說道：誰要救了我，我一定把我知道的都告訴他。\n",
        }));
        set("inquiry", ([
                "吳之榮" :  "把他送到莊府去有好處。",
                "威望" :  (: ask_weiwang :),
                "江湖威望" : (: ask_weiwang :),
        ]) );
        setup();
        carry_object( "/d/beijing/npc/obj/cloth")->wear();
}

int ask_weiwang()
{
command("tell"+query("id", this_player())+"你現在的江湖威望是"+(query("weiwang", this_player())));
say("\n莊允城說：如果你威望值很高，有些人見了你不但不會殺你，還會教你武功，送你寶貝。\n"
+"而且你還可以加入幫會，率領會眾去攻打目標，就連去錢莊取錢也會有利息 。。。。。\n");
say("莊允城又說：殺某些壞人或救某些好人可以提高江湖威望。\n");
return 1;
}

void init()
{
        object ob; 
        int i;
        ob = this_player();
        if(!userp(ob)) return;
        if(interactive(ob) && !is_fighting() ) 
        say( "莊允城哈哈笑道：終于有人來救我了！\n這位" + RANK_D->query_respect(ob)
                                + "，鰲府的寶貝可不少啊，你要有什麼不明白的，盡管問我吧。\n");
        i=query("weiwang", this_player());
        if(i<20) 
        {
        i=i+10;
        set("weiwang", i, this_player());
        message_vision(HIC "\n$N的江湖威望提高了！\n" NOR,this_player());
        }
        command("tell"+query("id", this_player())+"你現在的江湖威望是"+(i));
}

int accept_object(object me, object ob)
{
        if( !me || environment(me) != environment() ) return 0;
        if ( !objectp(ob) ) return 0; 
        if ( !present(ob, me) ) return notify_fail("你沒有這件東西。");
        if( query("name", ob) == "明史輯略" )
        {
         write(HIC "\n莊允城笑到：書裡有金葉子，難道你不知道嗎？\n" NOR);
         write(HIC "莊允城說：替我把吳之榮這廝抓到莊府去吧，我不行了。\n" NOR);                
         write("莊允城喘了口氣，又說：莊府在京城東北邊。\n");
        }                
        return 1;
}
