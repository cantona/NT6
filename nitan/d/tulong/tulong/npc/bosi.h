void init()
{
        object me = this_player();

        if (! interactive(me)
           || me->is_fighting()
           || ! living(this_object()))
                return;

        if( query_temp("have_yitianjian", me )
           || present("yitian jian", me))
        {
                command("say 咦？倚天劍怎麼會在你手裏，看來"
                        "這次中原之行沒白跑了！");
                this_object()->kill_ob(me);
                return;
        }

        if( query_temp("have_tulongdao", me )
           || present("tulong dao", me))
        {
                command("say 哼，把屠龍刀交出來，我們已經守"
                        "侯多時了！");
                this_object()->kill_ob(me);
                return;
        }

        if (present("shenghuo ling", me))
        {
                command("say 咦？你怎麼會拿着有我教的聖火令"
                        "，快還給我！");
                this_object()->kill_ob(me);
                return;
        }
}

int recognize_apprentice(object me, string skill)
{
        if( query("shen", me)>1000 )
        {
                command("say 嘰哩古拉，花不魯魯，你這人看上"
                        "去不象是好人，開滾。");
                return -1;
        }

        if (skill != "sanscrit")
        {
                command("say 教你點我在印度學的一點東西，你"
                        "還不知足啊？");
                return -1;
        }
        return 1;
}
