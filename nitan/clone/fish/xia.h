// fish.h

int is_fish() { return 1; }

int has_died = 0;

void setup()
{
        set_weight(500 + random(1000));
        set("value", query_weight() / 50);

        ::setup();
        if (clonep())
                call_out("die", 60 + random(60));
}

void die()
{
        remove_call_out("die");

        if (! environment())
        {
                destruct(this_object());
                return;
        }

        message("vision", name() + "彎了彎身子，死了。\n", environment());
        set("long", "這是一隻" + name() + "，它已經死了。\n");
        set_name("死" + name(), ({ "si xia", "sixia" }));
        has_died = 1;
        call_out("decay", 30 + random(30));
        set("value", query("value") / 2);
}

void decay()
{
        remove_call_out("decay");

        if (! environment())
        {
                destruct(this_object());
                return;
        }

        message("vision", name() + "腐爛了，發出一陣陣臭味。\n", environment());
        set("long", "這是一隻" + name() + "，它已經開始腐爛了。\n");
        set_name("爛蝦", ({ "lan xia", "lanxa" }));
        set("value", 0);
        call_out("vanish", 20 + random(20));
}

void vanish()
{
        if (environment())
        {
                message("vision", "一陣風吹過，把" + name() +
                        "給吹散了。\n", environment());
        }

        destruct(this_object());
}

void sold()
{
        destruct(this_object());
}

int broil(object me, object ob)
{
        object fob;

        if (query("value") == 0)
        {
                write("這麼一條爛蝦還烤什麼！\n");
                return 1;
        }

        me = this_player();
        if (me->is_busy())
        {
                write("你現在忙着呢，過會兒再烤吧。\n");
                return 1;
        }

        message_vision("$N把" + name() + "放在" + ob->name() +
                       "上細細的烤着，只聽畢啵畢啵的聲音，" + name() +
                       "慢慢的變成了紅色，散發出陣陣誘人的香味。\n", me);

        write(HIY "你把蝦烤好了！\n" NOR);
        fob = new("/clone/food/xia");
        fob->move(me, 1);
        destruct(this_object());
        me->start_busy(1);
        return 1;
}