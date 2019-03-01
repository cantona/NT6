// npc: /d/xingxiu/npc/maimaiti.c

inherit NPC;
inherit F_DEALER;

void create()
{
        set_name("買賣提", ({ "maimaiti", "seller" }) );
        set("title", "雜貨舖老板");
        set("shen_type", 1);

        set("gender", "男性" );
        set("age", 43);
        set("long",
"買賣提是個中年維吾爾族商人，去過幾次中原，能講一點兒漢話。\n");
        set_skill("unarmed", 50);
        set_skill("dodge", 50);
        set_temp("apply/damage", 15);

        set("combat_exp", 50000);
        set("attitude", "friendly");
        set("rank_info/respect", "大叔");

        set("vendor_goods", ({
                __DIR__"obj/hu",
                __DIR__"obj/nang",
                __DIR__"obj/fire",
                __DIR__"obj/hamigua",
                __DIR__"obj/wandao",
                __DIR__"obj/dongbula",
                __DIR__"obj/liuhuang",
                __DIR__"yangpi",
        }) );

        set("inquiry", ([
                "馬" : "要說好馬還得數咱們伊犁馬。",
                "伊犁馬" : "嗨，都讓賽馬的那幫姑娘小伙買光了。",
        ]) );

        setup();
        carry_object(__DIR__"obj/wcloth")->wear();
        add_money("coin", 100);
}
void init()
{
        object ob;
        ::init();
        add_action("do_buy", "buy");
        add_action("do_list", "list");
        if( interactive(ob = this_player()) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}
void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        switch( random(2) )
        {
                case 0:
                        say( "買賣提笑嘻嘻地說道：色蘭姆阿裡空。\n");
                        break;
                case 1:
                        say( "買賣提右手放在胸前，淺鞠一躬說道：阿裡空色蘭姆。\n");
                        break;
        }
}
