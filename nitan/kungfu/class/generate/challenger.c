// challenge.c

#include <ansi.h>
#include <command.h>

inherit NPC;

object with_ob = 0;

void competition_with(object ob)
{
        NPC_D->set_from_me(this_object(), ob);
        with_ob = ob;
        command("yun powerup");
        ::competition_with(ob);
}

varargs int receive_damage(string type, int damage, object who)
{
        if (! objectp(with_ob) || objectp(who) && who != with_ob)
                return 0;

        return ::receive_damage(type, damage, who);
}

varargs int receive_wound(string type, int damage, object who)
{
        if (! objectp(with_ob) || objectp(who) && who != with_ob)
                return 0;

        return ::receive_wound(type, damage, who);
}

int accept_fight(object ob)
{
        if (query_competitor() == ob)
                return 1;

        if (ob->is_fightint())
                return notify_fail("人家正在比武呢，你這麼出手不太妥當吧！\n");

        if (query("finished"))
                return notify_fail("人家剛比完武，你上去打算幹什麼？\n");

        return ACCEPT_CMD->main(ob);
}

int accept_hit(object ob)
{
        if (query_competitor() == ob)
                return 1;

        return accept_fight(ob);
}

int accept_kill(object ob)
{
        if( is_killing(query("id", ob)) )
                return 1;

        return notify_fail("我看這種丟中原武林臉的事情你還是別作了。\n");
}

int accept_touxi(object ob)
{
        if( is_killing(query("id", ob)) )
                return notify_fail("你們正在交手呢，偷襲什麼？");

        return notify_fail("我看這種丟中原武林臉的事情你還是別作了。\n");
}

void lost()
{
        object ob;
        object story;
        string msg;
        int expi, poti, weiwangi, scorei;

        if (! objectp(ob = query_competitor()))
                return;

        if (! objectp(story = STORY_D->query_running_story()))
                return;

        story->stop_story();
        msg = query("chat_lost");
        if (! msg) msg = "豈有此理！怎麼... 怎麼可能會這樣？";
        command("chat " + msg);
        CHANNEL_D->do_channel(this_object(), "rumor",
                "聽說" + ob->name() + "打敗了" + name() + "，捍衛了中原武林的尊嚴。");
        scorei = random(query("combat_exp")/500) + 10;
        weiwangi = random(query("combat_exp")/200) + 10;
        expi = random(NPC_D->check_level(this_object()) * 1000) + 10;
        poti = random(200) + 50;
        addn("score", 50+scorei, ob);
        addn("weiwang", weiwangi, ob);
        addn("combat_exp", expi, ob);
        addn("potential", poti, ob);
        addn("family/gongji", poti, ob);
        tell_object(ob, sprintf(HIG "你獲得了%s點經驗、%s點潛能，並增"
                                "加了%s點威望、%s點江湖閱歷和%s點門派功績。\n" NOR,
                        chinese_number(expi),
                        chinese_number(poti),
                        chinese_number(weiwangi),
                        chinese_number(scorei),
                        chinese_number(poti)));
        set("finished", 1);
        call_out("destruct", 0, this_object());
        ::lost();
}

void win()
{
        object ob;
        object story;
        string msg;

        if (! objectp(ob = query_competitor()))
                return;

        if (! objectp(story = STORY_D->query_running_story()))
                return;

        story->stop_story();
        addn("weiwang", -query("weiwang", ob)/25, ob);
        command("chat* haha");
        msg = query("chat_win");
        if (! msg) msg = "中原武林，不堪一擊！";
        command("chat " + msg);
        CHANNEL_D->do_channel(this_object(), "rumor",
                "聽說" + ob->name() + "輸給了" + name() + "，丟盡了中原武林的臉面。");
        set("finished", 1);
        call_out("destruct", 0, this_object());
        ::win();
}