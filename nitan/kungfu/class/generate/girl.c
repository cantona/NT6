// girl for user

#include <ansi.h>

inherit NPC;

#define DEFAULT_NAMR    "丫鬟"

void   set_owner(object owner);
string description();

void create()
{
        set_name(DEFAULT_NAMR, ({ "ya huan" }));
        set("age", 12 + random(8));
        set("attitude", "friendly");
        set("gender", "女性");

        set("max_qi", 1000);
        set("max_jing", 500);

        set("per", 20);
        set("str", 15);

        set("long", "她是一個小丫鬟。\n" + description());

        setup();

        carry_object("/clone/cloth/female" + (random(8) + 1) + "-cloth.c")->wear();        
        carry_object("/clone/cloth/female-shoe.c")->wear();

        if (clonep()) keep_heart_beat();
}

void set_owner(object owner)
{
        object *obs;

        set_temp("owner", owner);
        obs=query_temp("hire", owner);
        if (arrayp(obs))
        {
                obs = obs - ({ 0 }) + ({ this_object() });
                set_temp("hire", obs, owner);
        } else
                set_temp("hire", ({this_object()}), owner);

        if (environment() &&
            environment(owner) == environment())
        {
                // 跟隨主人
                message_vision("$N跟在$n的身後。\n", this_object(), owner);
                set_leader(owner);
        }

        set("title", owner->name(1) + "的丫鬟");
}

string long()
{
        object owner;
        string msg;

        if (! objectp(owner = query_temp("owner")))
                return ::long();

        msg = short() +
              "\n這是"+owner->name(1)+"("+query("id", owner)+
              ")的貼身丫鬟。\n" + description();
        return msg;
}

int do_name(string arg)
{
        string mid;
        string msg;

        if (this_player() != query_temp("owner"))
                return 0;

        if (! stringp(arg))
                return notify_fail("你要起什麼名字？\n");

        if (sscanf(arg, "%s %s", arg, mid) != 2)
                return notify_fail("你想起什麼名字(name 中文名字 英文代號)？\n");

        if (strlen(mid) < 3)
                return notify_fail("你這個英文代號用的也太短了。\n");

        if (strlen(mid) > 8)
                return notify_fail("你這個英文代號用的也太短了。\n");

        if (! is_legal_id(mid))
                return notify_fail("英文代號必須使用英文小寫字母。\n");

        if (! is_chinese(arg))
                return notify_fail("請你用中文起名字。\n");

        if (strlen(arg) < 4)
                return notify_fail("這個名字太短了。\n");

        if (strlen(arg) > 8)
                return notify_fail("你起的這個名字也太長了。\n");

        if (arg == name())
                return notify_fail("人家現在不就是叫這個名字麼？\n");

        if (arg == this_player()->name(1))
                return notify_fail("你怎麼取一個和自己一樣的名字？\n");

        if (msg = NAME_D->invalid_new_name(arg))
        {
                write(msg);
                return 1;
        }

        if (query("name") != DEFAULT_NAMR)
                return notify_fail("人家已經有名字了，你就別費心了。\n");

        message_vision("$N想了一會兒，對$n道：“這樣吧，以後你就叫" +
                       arg + "好了。”\n$n拍手道：“好呀好呀！就依" +
                       RANK_D->query_respect(this_player()) +  "之" +
                       "言，以後我就叫" + arg + "了。”\n",
                       this_player(), this_object());
        set_name(arg, ({ mid }));
        remove_action("do_name", "name");

        return 1;
}

int do_nick(string arg)
{
        if (! arg)
                return notify_fail("你要給" + name() + "一個什麼暱稱？\n");

        if (arg == "none")
        {
                delete("nickname");
                write("你把" + name() + "的綽號取消了。\n");
                return 1;
        }

        if (strlen(arg) > 80)
                return notify_fail("你的綽號佔用的資源過多，請重新設置。\n");

        arg = replace_string(arg, "$BLK$", BLK);
        arg = replace_string(arg, "$RED$", RED);
        arg = replace_string(arg, "$GRN$", GRN);
        arg = replace_string(arg, "$YEL$", YEL);
        arg = replace_string(arg, "$BLU$", BLU);
        arg = replace_string(arg, "$MAG$", MAG);
        arg = replace_string(arg, "$CYN$", CYN);
        arg = replace_string(arg, "$WHT$", WHT);
        arg = replace_string(arg, "$HIR$", HIR);
        arg = replace_string(arg, "$HIG$", HIG);
        arg = replace_string(arg, "$HIY$", HIY);
        arg = replace_string(arg, "$HIB$", HIB);
        arg = replace_string(arg, "$HIM$", HIM);
        arg = replace_string(arg, "$HIC$", HIC);
        arg = replace_string(arg, "$HIW$", HIW);
        arg = replace_string(arg, "$NOR$", NOR);

        if (strlen(filter_color(arg)) > 30)
                return notify_fail("你想的這個綽號太長了，想一個短一點的、響亮一點的。\n");

        set("nickname", arg + NOR);
        write("你為" + name() + "選了一個綽號。\n");
        return 1;
}

mixed accept_ask(object who, string topic)
{
        object me;
        object owner;
        object *obs;
        object cob;
        string nick;

        me = this_object();

        if (! objectp(owner = query_temp("owner")))
                message_vision("$N看看周圍，有些羞澀，沒有回答$n的話。\n",
                               me, who);

        if (topic == "name" || topic == "名字" || topic == "姓名")
        {
                // 詢問名字
                if (who != owner)
                        return "你打聽我名字幹什麼？你是壞人還是好人？";

                if (name() == DEFAULT_NAMR)
                {
                        remove_action("do_name", "name");
                        add_action("do_name", "name");
                        return "我現在還沒有名字呢，你給我起(name)一個好不好？";
                }

                return "我的名字叫" + name() + "呀，你不記得了麼？";
        }

        if (topic == "nick" || topic == "暱稱" || topic == "綽號")
        {
                // 詢問暱稱
                nick = query("nickname");
                if (who != owner)
                {
                        if (! stringp(nick) || strlen(nick) < 1)
                                return "我沒有什麼綽號哦。";

                        return "嗯... 人家都叫我" + nick + "。";
                }

                remove_action("do_nick", "snick");
                add_action("do_nick", "snick");

                if (! stringp(nick))
                        return "我現在沒有綽號呀，是要給我起(snick)一個嗎？";

                return "我現在叫" + nick + NOR CYN "呀，你打算給我換(snick)一個麼？";
        }

        if( topic == owner->name(1) || topic == query("id", owner) )
        {
                if (who == owner)
                {
                        message_vision("$N抿著嘴嘻嘻一笑，對$n道：“你"
                                       "就不要逗我開心拉！”\n", me, who);
                        return 1;
                }

                return "是我主人呀！你找"+gender_pronoun(query("gender", owner))+
                       "有什麼事情麼？";
        }

        if (topic == name() || topic == query("id"))
        {
                if (who == owner)
                        return "哎！我在這兒呢。";
                else

                        return "你找我有事情麼？先問過我的主人吧。";
        }

        if (who != owner)
        {
                // 和主人是夫妻關系
                if( query("id", who) == query("couple/id", owner) )
                {
                        message_vision("$N盈盈對著$n道了一個萬福。\n",
                                       me, who);        
                        return 1;
                }

                // 和主人是結拜兄弟關系
                if (who->is_brother(owner))
                {
                        message_vision("$N嘻嘻一笑，道：“" +
                                       RANK_D->query_respect(who) +
                                       "不要取笑我啦。”\n",
                                       me, who);
                        return 1;
                }

                // 陌生人
                switch (random(5))
                {
                case 0:
                        message_vision("$N眨著大眼睛，無辜的望著$n，一副"
                                       "天真無邪的樣子。\n", me, who);
                        break;
                case 1:
                        message_vision("$N嘻嘻一笑，沒有搭理$n。\n", me, who);
                        break;
                case 2:
                        message_vision("$N道：“" + owner->name(1) +
                                       "說啦，不讓我和你們說話，外面壞人"
                                       "可多了。”\n", me, who);
                        break;
                case 3:
                        message_vision("$N閃了閃，對$n道：“我不懂事的，"
                                       "您別逗我啦。”\n", me, who);
                        break;
                default:
                        message_vision("$N聽了$n的話，什麼也沒有說，只是"
                                       "用那雙清澈的目光掃了$n一眼。\n", me, who);
                        break;
                }

                return 1;
        }

        if (topic == "all")
        {
                string *names;
                int count;

                obs = obs = all_inventory(me);
                obs=filter_array(obs,(:!query("equipped", $1):));
                if (! sizeof(obs))
                        return "我身上現在啥也沒有呀。";

                count = 0;
                names = allocate(sizeof(obs));
                foreach (cob in obs)
                        if (! count || member_array(cob->name(), names) == -1)
                                names[count++] = cob->name();
                tell_object(who, sort_string(name() + "悄悄地告訴你：“我身上現在帶著" +
                                             implode(names, "、") + "呢。”\n", 60));
                return "你現在要用什麼？";
        }

        // 察看詢問的是否是身上攜帶的物品
        obs = all_inventory(me);
        foreach (cob in obs)
        {
                if( query("equipped", cob) )
                        continue;

                if (filter_color(cob->name(1)) != topic && ! cob->id(topic))
                        continue;

                // 找到了
                message_vision("$N道：“等一下，在這兒呢。”說完掏出" +
                               cob->name() + "遞給$n。\n", me, who);
                if (! cob->move(who))
                        message_vision("可是$n身上帶的東西太多，沒能接住$N的" +
                                       cob->name() + "。\n", me, who);
                return 1;
        }

        switch (random(3))
        {
        case 0:
                return "你說什麼？我沒聽清楚呀。";
        case 1:
                return "哦？你是想要東西嗎？要什麼呢？";
        default:
                return "等...等一下，你說什麼？";
        }
}

int accept_object(object who, object ob)
{
        object me;
        object owner;

        me = this_object();
        if (! objectp(owner = query_temp("owner")))
                return 0;

        if( (who != owner) && query("couple/id", who) != query("id", owner) )
        {
                message_vision("$N連忙搖頭，道：“我可不能要您的東西，不然" +
                               (owner ? owner->name() : "主人") +"會責備我的。”\n", me);
                return 0;
        }

        if (ob->is_character() && query("can_speak"))
        {
                message_vision("$N皺皺眉，為難道，“這...這我不方便拿呀。”\n", me);
                return 0;
        }

        if (ob->is_corpse())
        {
                message_vision("$N“呀”了一聲道：“這，這個也要我拿？”\n", me);
                return 0;
        }

        message_vision("$N道：“" + name() + "，你把這" + ob->name() +
                       "收好了。 ”\n", owner);
        if (ob->move(me))
        {
                message_vision("$N點點頭，輕輕把" + ob->name() +
                               "接了過去，穩穩的收好。\n", me);
                return -1;
        }

        message_vision("$N“嗚嗚”道：“這個... 我已經拿不動了。”\n", me);
        return -1;
}

int accept_ansuan(object ob)
{
        return notify_fail("那麼清純的小姑娘，你不忍心下手。\n");
}

int accept_touxi(object ob)
{
        message_vision("然而$N看到那姑娘是如此天真清純，再難忍心下手。\n", ob);
        return -1;
}

int accept_fight(object ob)
{
        message_vision("$N往後一縮，楚楚可憐的望著$n。\n",
                       this_object(), ob);
        return -1;
}

int accept_hit(object ob)
{
        message_vision("$N往後一縮，楚楚可憐的望著$n，讓$n心中不由得一軟。\n",
                       this_object(), ob);
        return -1;
}

int accept_kill(object ob)
{
        object me;
        object *obs;

        me = this_object();
        if (ob == query_temp("owner"))
        {
                message_vision("$N向後一退，委屈的喊道：“為什麼，為什麼"
                               "要這樣對我？\n$n心中一軟，沒有下手，眼睜"
                               "睜的看著$N跑掉了。\n", me, ob);
                obs = all_inventory(me);
                obs=filter_array(obs,(:!query("equipped", $1):));
                if (sizeof(obs))
                {
                        message_vision("$N將身上的東西扔了一地...\n", me);
                        obs->move(environment());
                }
                destruct(me);
                return -1;
        }

        message_vision("$N連忙往後避去，委屈的沖$n喊道：“這位" +
                       RANK_D->query_respect(ob) +"，你認錯人了吧！”\n",
                       me, ob);
        return -1;
}

void relay_emote(object me, string arg)
{
        string my_id;
        object owner;

        if (! objectp(owner = query_temp("owner")))
                return;

        my_id=query("id", me);
        if( me == owner || my_id == query("couple/id", owner) )

        switch (random(5))
        {
        case 0: command("shy");         return;
        case 1: command("shzi");        return;
        case 2: command("xixi");        return;
        case 3: command("@@ " + my_id); return;
        default:command("angry");       return;
        }

        if( query_temp("last_emote_with_girl", me) == time() )
        {
                if( me->add_temp("last_emote_times",1)>2 )
                {
                        message_vision(HIR "$N" HIR "冷笑一聲，飛起一腳將$n"
                                       HIR "踢倒在地！\n", this_object(), me);
                        me->receive_damage("qi", 50, this_object());
                        me->receive_damage("jing", 40, this_object());
                        return;
                }
        } else
        {
                // reset count
                set_temp("last_emote_with_girl", time(), me);
                delete_temp("last_emote_times", me);
        }

        arg = replace_string(arg, "1", "");
        arg = replace_string(arg, "2", "");
        arg = replace_string(arg, "3", "");
        arg = replace_string(arg, "4", "");
        arg = replace_string(arg, "5", "");
        switch (arg)
        {
        case "kiss":    command("rascal " + my_id);     break;
        case "hug":     command("escape " + my_id);     break;
        case "kok":     command("wuwu " + my_id);       break;
        case "kick":    command("killair " + my_id);    break;
        case "kickfly": command("papa");                break;
        case "wuwu":    command("comfort " + my_id);    break;
        case "comfort": command("say 我很好呀。");      break;
        case "killair": command("heng " + my_id);       break;
        case "slap":    command("angry " + my_id);      break;
        case "zhen":    command("pain");                break;
        case "poor":    command("say 你才可憐呢。");    break;
        case "xbc":     command("say 你才是小白菜呢。");break;
        case "flop":    command("standup");             break;
        case "tang":    command("say 不要...我不要！"); break;
        case "faint":   command("standup " + my_id);    break;
        case "break":   command("inn " + my_id);        break;
        case "cat":     command("xixi " + my_id);       break;
        case "lean":    command("shy " + my_id);        break;
        case "tnnd":    command("say 你這人好惡心哦。");break;
        case "wave":    command("say 你快走吧。");      break;
        case "shrug":   command("? " + my_id);          break;
        case "xixi":    command("say 你好不正經。");    break;
        case "laugh":   command("say 怎麼像一個...傻子？");     break;
        case "inn":     command("nopretend " + my_id);  break;
        case "sorry":   command("tang " + my_id);       break;
        case "chaxie":  command("pat " + my_id);        break;
        case "pat":     command("escape");              break;
        case "smile":   command("smile " + my_id);      break;
        case "shzi":    command("say 亂指啥？");        break;
        case "haha":
        case "hehe":
        case "hoho":    command("say 傻笑什麼。");      break;
        case "cut":
        case "knife":
        case "club":    command("say " + owner->name(1) + "救命呀！");          break;
        case "rascal":  command("say 我可天真了。");                            break;
        default:        command("say " + owner->name(1) + "！有壞人呀！");      break;
        }
}

void scan()
{
        object me;
        object ob;
        object env;

        me = this_object();

        if (! objectp(ob = query_temp("owner")))
        {
                if (environment())
                        message_vision("$N看了看四周，走了。\n", me);
                destruct(this_object());
                return;
        }

        env = environment(ob);
        if (environment() == env || ob->is_ghost())
                // 和主人在的地點相同，或是主人處于鬼魂狀態
                return;

        if (is_busy() || is_fighting() || ! living(this_object()))
                // 現在忙
                return;

        if( !sizeof(query("exits", env)) || 
            environment() && ! sizeof(query("exits", environment())))
                return;

        if (environment())
                message_vision("$N輕移蓮步，慢慢走開了。\n", me);

        if (! move(env)) return;

        switch (random(3))
        {
        case 0:
                message_vision("$N慢慢走了過來，站在$n的身邊，一雙清澈"
                               "的眼睛巡視著周圍。\n", me, ob);
                break;

        case 1:
                message_vision("$N三步並作兩步，趕了過來，站到了$n的身"
                               "邊。\n", me, ob);
                break;

        default:
                message_vision("$N悄悄地走了過來，站在$n的身後，望著大"
                               "家。\n", me, ob);
                break;
        }

        set_leader(ob);
}

string description()
{
        int per;

        per = query_per();
        if (per >= 30) return "她有傾國傾城之貌，容色麗鬱，嬌艷絕倫，堪稱人間仙子！\n";
        if (per >= 28) return "她清麗絕俗，風姿動人。俏臉生春，妙目含情，輕輕一笑，不覺讓人怦然心動。\n";
        if (per >= 26) return "她膚如凝脂，眉目如畫，風情萬種，楚楚動人。當真是我見猶憐！\n";
        if (per >= 24) return "她容色秀麗，面帶暈紅，眼含秋波。舉手投足之間，確有一番風韻。\n";
        if (per >= 21) return "她氣質高雅，面目姣好，雖算不上絕世佳人，也頗有幾份姿色。\n";
        return "她相貌平平，還看得過去。\n";
}

string query_autoload()
{
        string nick;

        return sprintf("%s||%s||%d||%s", query("name"), query("id"), query("per"),
                       stringp(nick = query("nickname")) ? nick : "");
}

void autoload(string para, object owner)
{
        string arg, mid, nick;
        int per;

        if (! stringp(para) || sscanf(para, "%s||%s||%d||%s", arg, mid, per, nick) < 3)
        {
                arg = DEFAULT_NAMR;
                mid = "ya huan";
                per = 20;
        }

        if (stringp(nick) && strlen(nick) > 0)
                set("nickname", nick);

        set("per", per);
        set_name(arg, ({ mid }));
        set_owner(owner);
}

void move_or_destruct()
{
        move(VOID_OB);
}
