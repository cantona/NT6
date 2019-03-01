// tian.c  田嫂

inherit NPC;

void create()
{
        set_name("田嫂", ({"tian sao","tian","sao"}));
        set("title", "女易牙");
        set("gender", "女性" );
        set("age", 36);
        set("long", "一個白皙豐滿的中年婦人。\n");
        set("combat_exp", 2000);
        set("attitude", "friendly");
        setup();
        carry_object("/d/city/obj/cloth")->wear();

}
void init()
{
::init();
        add_action("do_yao", "yao");
}

int do_yao(string arg)
{
        object m,mm;
        message_vision("$N向田嫂問道：大嫂，開飯了嗎？\n", this_player());

        if( query("food", this_player()) >= 
           (int)this_player()->max_food_capacity()*90/100 )
                return notify_fail("田嫂笑道：沒那，等開飯時再來吧！\n");

        if((present("baozi", this_player())))
        return notify_fail("田嫂笑道：不要拿著手裡的，還看著鍋裡的！\n");
        
        if ( present("baozi", environment()) )
                return notify_fail("田嫂笑道：那不是有一塊呢嘛，吃完再說！\n");

        m=new(__DIR__"obj/baozi2");
        mm=new(__DIR__"obj/baozi2");


        m->move(this_player());
        mm->move(this_player());

        message_vision("田嫂對$N笑道：餓了吧，慢點吃。\n", this_player());
                return 1;
}
