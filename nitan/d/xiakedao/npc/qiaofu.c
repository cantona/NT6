// qiaofu.c

inherit NPC;
int inquiry_dao();

void create()
{
        set_name("樵夫", ({ "qiao fu","fu" }) );
        set("gender", "男性" );
        set("age", 50);
        set("long", "一個一輩子以砍材為生的老樵夫，由於飽受風霜，顯出與年齡不相稱的衰老。\n");
        set("shen_type",1);
        set("combat_exp", 10000);
        set("str", 17);
        set("dex", 18);
        set("con", 18);
        set("int", 18);
        set("attitude", "friendly");
        set("inquiry" , ([
            "柴刀" : (: inquiry_dao :),
            "刀" : (: inquiry_dao :),
        ]));
        set_temp("buyed", 0);
        setup();
        carry_object("/clone/misc/cloth")->wear();

}

int accept_object(object who, object ob)
{
        command("smile");
        message_vision("謝謝好心的大爺，好人有好報。\n", who);
        if( query("money_id", ob) && ob->value() >= 3000 )
           set_temp("buyed", 1);
        return 1;
}

int inquiry_dao()
{
        object me=this_player();
        object ob;

        if (present("cut knife",me))
        {
            message_vision("你就別尋老頭子開心了，你身上不是也有一把嗎?\n", me);
            return 1;
        }
        if( query_temp("buyed")==0 )
        {
            message_vision("這位大爺，實在不是我捨不得這刀，小人一家就全靠它過\n"
                  "日子了，給了你，叫我怎麼過活啊！\n", me);
            return 1;
        }
        if( query_temp("buyed")==1 )
        {
            message_vision("既然好心人想要，就給你吧，本來史婆婆要我好好保管的，\n"
                  "你可千萬別瞎送給別人，否則她會生氣的。\n", me);
            ob=new("/d/xiakedao/obj/knife");
            ob->move(me);
            message_vision("樵夫遞給你一把柴刀！\n", me);
            set_temp("buyed", 0);
        }
        return 1;
}
