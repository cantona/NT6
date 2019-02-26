// d/yanziwu/npc/susu.c

inherit NPC;

void greeting(object);
void init();
void serve_tea(object);

void create()
{
        set_name("素素", ({"su su", "su"}) );
        set("nickname", "伺茶丫鬟");
        set("gender", "女性" );
        set("age", 14 + random(3));
        set("long",
          "這是個年年齡不大的小丫鬟，但寬鬆的衣服也遮不住她過早發育的身體。\n"
          "一臉聰明乖巧，滿口伶牙俐齒。見有人稍微示意，便過去加茶倒水。\n");
        set("attitude", "friendly");
        set("shen_type", 1);

        set("str", 20);
        set("int", 28);
        set("con", 24);
        set("dex", 20);

        set("max_qi", 150);
        set("max_jing", 100);
        set("neili", 150);
        set("max_neili", 150);

        set("combat_exp", 1000+random(800));
        set("score", 1000);

        set_skill("force", 30);
        set_skill("dodge", 20);
        set_skill("unarmed", 15+random(10));
        set_skill("parry", 20);
        set_temp("apply/attack", 10);
        set_temp("apply/defense", 15);
        set_temp("apply/cdamage", 3);

        setup();

        set("can_supply", 15);
}

void init()
{
        object ob;

        ::init();

        if (interactive(ob = this_player()) && !is_fighting())
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if (! ob || environment(ob) != environment()) return;

        say("素素笑吟吟地説道：這位" + RANK_D->query_respect(ob)
             + "請先入座，" + "我這就給您上茶。\n");
}


void serve_tea(object who)
{
        object obt, obc, obn;
        object room;

        if (! who || environment(who) != environment()) return;

        if( !query_temp("marks/sit", who))return ;

        if (! objectp(room = environment())) return;

        if (query("can_supply") < 1)
        {
                message_vision("素素抱歉的對$N道：現在暫時沒有了，過會"
                               "兒再來吧。\n", who);
                return;
        }
        addn("can_supply", -1);
        obn = new("/d/yanziwu/obj/cha");
        obn->move(room);
        message_vision("素素拿出一個小茶壺，沏上一杯香濃的碧螺春．\n",who);

        obn = new("/d/yanziwu/obj/gao");
        obn->move(room);
        message_vision("素素拿出一碟精緻的四色點心，放在桌上．\n", who);

        return;
}

void reset()
{
        set("can_supply", 15);
}
