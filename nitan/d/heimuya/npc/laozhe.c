//NPC:  laozhe.c

inherit NPC;
 
void create()
{
        set_name("老者", ({ "lao zhe", "oldman" }) );
        set("gender", "男性" );
        set("age", 70);
        set("long",
"這個老頭正抽旱煙抽得上癮呢,怎樣才能和他搭上話呢?\n");
        set("combat_exp", 1000);
        set("attitude", "friendly");
        set("rank_info/respect", "老大爺");
       set("inquiry", ([
                
                "黑木崖" : "黑木崖上有一個穿女人衣裳的吃人惡魔，你可千萬不能去！\n",
               "旱煙"   : "青年人,難得你有這份孝心,你若替我買包上好的煙草,我就給你一樣東西\n",
                "東西"   : "我所說的東西就是上黑木崖的令牌啦,快去買上好煙草,我等不及了...\n",   
        ]) );

        setup();
}
 
void init()
{
        object ob;
 
        ::init();
        ob = this_player();

        if( interactive(ob) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}
 
void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        switch( random(2) ) {
                case 0:
                        say( "老人家頭也不回說道：這位" + RANK_D->query_respect(ob)
                                + "，不要亂跑,小心野獸。\n");
                        break;
                case 1:
                        say( "老人家對你說到:我也一大把年紀了,就好那一口,你就行行好吧。\n");
                        break;
        }
}
 
/*int accept_object(object who, object ob)
{ 
        if( query("money_id", ob) && ob->value() >= 5000 )
        {
                tell_object(who, "老頭對你說:好，好，真是個好孩子。\n");
                
                set_temp("rent_paid", 1, who);
   
                return 1;
        }
 
        return 0;
}*/
