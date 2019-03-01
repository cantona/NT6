// bajiao.h 群玉八嬌

int accept_fight(object me)
{
        command("say 小女子哪裡是您的對手？");
        return 0;
}

void init()
{
        remove_call_out ("says");
        call_out("says", random(3), this_player());
        add_action("do_sleep","shuijiao");
}

void says(object me)
{
          string *msgs = ({
                    "$N吃吃一笑，抿嘴看著你。\n",
                    "$N含情脈脈地對你說“……你……你還不明白妾身的心意嗎？\n",
                    "看來$N很想跟你(shuijiao)一次\n",
                    "$N很想跟你……\n",
                    "$N對你婉爾一笑。\n",
        });

        string msg;

        if (! me || environment(me) != environment() ||
            ! living(this_object()))
                return;

        if( query("gender", me) != "男性" )
                msg = "$N打了個哈欠，看上去困極了。\n";
        else
                msg = msgs[random(sizeof(msgs))];

          message_vision(msg, this_object());
}

int do_sleep()
{
          object me = this_object();
          object who = this_player();

        switch(query("gender", who) )
        {
        case "男性":
                break;
        case "女性":
                return notify_fail("你還有這愛好？沒看出來。\n");
        default:
                return notify_fail("你似乎沒有這能力吧？\n");
        }

        if (is_busy() || is_fighting())
                return notify_fail("你沒看見人家正忙著呢嗎？\n");

        if (query_temp("makelove_with") == who)
        {
                write("你好好做你的，別三心二意的。\n");
                return 1;
        }

        if (query_temp("makelove_with"))
                return notify_fail("兩個一起上？你還是饒了人家吧！\n");

          message_vision(HIM "$N" HIM "輕輕摟著$n" HIM "柔軟的"
                       "身體，不由得一陣陣發麻的快感傳遍全身，"
                       "不知不覺的開始扭動著……\n\n"NOR, who, me);
          who->command_function("remove all");
          who->start_busy(999);

        // record sex
        addn("sex/"+name(), 1, who);
        addn("sex/times", 1, who);
        if( query("sex/times", who) == 1 )
                set("sex/first", name(), who);

        set_temp("makelove_with", who);

          remove_call_out ("get_fainted");
          call_out ("get_fainted", 1, who, me);
        remove_call_out("says");
        call_out("says", 40, me);
        return 1;
}

void get_fainted(object who, object me)
{
        object *objs = all_inventory(who);
        int i = sizeof(objs);

        delete_temp("makelove_with");

        if (! who || environment(who) != environment())
                return;

        message_vision("$N對$n神秘地一笑。\n", me, who);
        who->unconcious();
        while (i--)
        {
                    object obj = objs[i];
                if (obj->is_character())
                        continue;
                if( !query("money_id", obj) )
                        continue;
                    message_vision("$N從$n身上拿出" +
                               query("name", obj)+
                               "。\n", me, who);
                    destruct(obj);
                break;
        }

        if (i < 0)
                // Get nothing
                command("chat 氣死老娘了，原來是一個窮鬼！");
}

int accept_kill(object me)
{       
        object ob;
        if (is_fighting()) return 1;
        if (query("called")) return 1;
        command("say 要殺人了，快來人救命啊！");
        ob = present("bao biao");
        if (! ob)
        {
                seteuid(getuid());
                ob=new(__DIR__"baobiao");
                ob->move(environment());
        }
        message_vision(HIC "\n忽然從門外沖進來幾個保鏢，對"
                       "$N" HIC "大喊一聲“幹什麼？在這兒鬧"
                       "事，想找死嗎？\n\n"NOR, me);
        ob->kill_ob(me);
        ob->set_leader(me);
        me->kill_ob(ob);
        set("called", 1);
        call_out("regenerate", 200);
        return notify_fail("壞事了！");
}

int regenerate()
{
        set("called", 0);
        return 1;
}