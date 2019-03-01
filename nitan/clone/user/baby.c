// baby.c

#include <ansi.h>
inherit BABY;
inherit F_NOCLONE;

void consider();
void provide();
mixed ask_father();
mixed ask_mother();
int check_legal_name(string name, int max_len);

int is_baby(){ return 1; }

// override set function
varargs mixed set(string idx, mixed para, object ob)
{
        int i, j, lvl, level;

        if( !ob ) ob = this_object();

        if (idx == "combat_exp" && para)
        {
                if (para > (int)query("combat_exp")) {
                        level = (int)query("level");
                        if (! level || level < 1) level = 1;

                        for (i = level; ;i++) {
                                if ((i + 1) * (i + 1) * (i + 1) > (para / 10000))
                                {
                                        lvl = i;
                                        break;
                                }
                        }

                        if (lvl > level)
                        {
                                j = lvl - level;
                                set("level", lvl);
                                addn("points", 4 * j);
                                addn("improve/int", j);
                                addn("improve/str", j);
                                addn("improve/con", j);
                                addn("improve/dex", j);
                                addn("experience", 20 * j);
                                addn("potential", 200 * j);
                                addn("magic_points", 20 * j);
                                tell_object(ob, HIY "只見一道紅光飛進你的體內，你的人物等級提升了！\n" +
                                        "此次升級，你獲得了" + chinese_number(4 * j) +
                                        "點技能點、" + chinese_number(200 * j) +
                                        "點潛能、" + chinese_number(20 * j) +
                                        "點實戰體會和" + chinese_number(20 * j) +
                                        "點靈慧！\n" NOR);
                        }
                }
                return efun::set(idx, para);
        } else
                return efun::set(idx, para);
}
// override add function by Lonely
varargs mixed addn(string prop, mixed data, object ob)
{
        string para;
        mixed old;

        if( !ob ) ob = this_object();

        if (prop == "combat_exp")
        {
                if (! (old = query(prop)))
                        return set(prop, data);

                return set(prop, old + data);
        } else
                return efun::addn(prop, data, ob);
}

void create()
{
        set_name("寶寶", ({"xiao baobao", "baby"}) );
        set("long", "一個白白拚胖的乖寶寶，不知道是誰家的孩子。\n");
        set("gender", "女性");
        set("age", 1);
        set("attitude", "friendly");
        set("no_clean_up", 1);
        set("env/halt_age", 1);
        set("combat_exp", 10000);

        setup();
        carry_object("/clone/cloth/cloth")->wear();

        remove_call_out("check_me");
        call_out("check_me", 2, this_object());
}

void check_me(object me)
{
        if( me && !mapp(query("parents", me)) )
                destruct(me);
        return;
}

int load_baby(object me)
{
        string file, info, name, id;

        if (! userp(me)) return 0;

        if( query("gender", me) == "女性" )
                file = "/data/baby/" + query("id", me) + ".o";
        else
        if( query("couple/couple_id", me) )
                file = "/data/baby/" + query("couple/couple_id", me) + ".o";

        if (! file || file_size(file) < 0) return 0;

        if (stringp(read_file(file)))
        {
                restore_object(file);
                reset_action();

                    /*
                set("max_neili", query_skill("force") * 20 + query("combat_exp") / 1000);
                set("neili", query("max_neili"));
                set("max_jingli", query_skill("magic") * 10 + query_skill("taoism") * 10 + query("combat_exp") / 3000);
                set("jingli", query("max_jingli"));
                    */
                set("max_qi", 150 + query("max_neili") / 2 + query("age") * query("con"));
                set("eff_qi", query("max_qi"));
                set("qi", query("max_qi"));
                set("max_jing", 100 + query("max_jingli") / 3 + query("age") * query("con"));
                set("eff_jing", query("max_jing"));
                set("jing", query("max_jing"));
                set_name(query("name"), ({query("id"), "baby"}));

                set("chat_chance", query("int") / 10);
                set("chat_chance_combat", query("con") / 5 * 10);

                set("chat_msg", ({
                        (: consider :),
                        (: provide :),
                }));

                set("inquiry", ([
                        "父親" : (: ask_father :),
                        "爹爹" : (: ask_father :),
                        "爸爸" : (: ask_father :),
                        "母親" : (: ask_mother :),
                        "媽媽" : (: ask_mother :),
                ]));

                set("perform_skills", 0);

                setup();

                UPDATE_D->check_user(this_object());
                remove_call_out("consider");
                call_out("consider", 10);
        } else
                return 0;
}

void init()
{
        add_action("do_kill", ({"kill", "fight", "hit", "steal"}));
        add_action("do_get", "get");
        add_action("do_drop", "drop");
        add_action("do_home", "home_baby");
        add_action("do_nick", "nick_baby");
        add_action("do_changename", "name_baby");
}

int do_nick(string arg)
{
        object ob = this_object();
        object me = this_player();

        if( query("parents/father") != query("id", me) &&
            query("parents/mother") != query("id", me) )
                return notify_fail("看清楚了，他可不是你的孩子！\n");

        if (! arg)
                return notify_fail("你要替孩子取什麼綽號？\n");

        if (arg == "none")
        {
                delete("nickname");
                write("你的孩子綽號取消了。\n");
                ob->save();
                return 1;
        }

        if (strlen(arg) > 80)
                return notify_fail("你為孩子取的綽號佔用的資源過多，請重新設置。\n");

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
                return notify_fail("你為孩子取的綽號太長了，想一個短一點的、響亮一點的。\n");

        set("nickname", arg+NOR, ob);
        ob->save();
        write("你為孩子取好了綽號。\n");
        return 1;
}

int do_changename(string arg)
{
        object ob = this_object();
        object me = this_player();
        string  arg_old;

        if( query("parents/father") != query("id", me) &&
            query("parents/mother") != query("id", me) )
                return notify_fail("看清楚了，他可不是你的孩子！\n");

        if (! arg)
                return notify_fail("你要替孩子取什麼名字？\n");

        arg_old = arg;

        arg = replace_string(arg, "$BLK$", "");
        arg = replace_string(arg, "$RED$", "");
        arg = replace_string(arg, "$GRN$", "");
        arg = replace_string(arg, "$YEL$", "");
        arg = replace_string(arg, "$BLU$", "");
        arg = replace_string(arg, "$MAG$", "");
        arg = replace_string(arg, "$CYN$", "");
        arg = replace_string(arg, "$WHT$", "");
        arg = replace_string(arg, "$HIR$", "");
        arg = replace_string(arg, "$HIG$", "");
        arg = replace_string(arg, "$HIY$", "");
        arg = replace_string(arg, "$HIB$", "");
        arg = replace_string(arg, "$HIM$", "");
        arg = replace_string(arg, "$HIC$", "");
        arg = replace_string(arg, "$HIW$", "");
        arg = replace_string(arg, "$NOR$", "");

        if (! check_legal_name(arg, 8))
                return notify_fail("請重新設定你的孩子名字！\n");

        arg = arg_old;

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

        set("name", arg+NOR, ob);
        ob->save();
        write("你為孩子取好了姓名。\n");
        return 1;
}

int check_legal_name(string name, int max_len)
{
        int i;
        string  *legalname;             //not implemented..may add later

        i = strlen(name);
        if ((strlen(name) < 4) || (strlen(name) > max_len ))
        {
                write(sprintf("對不起，姓名必須是 2 到 %d 箇中文字。\n",
                      max_len / 2));
                return 0;
        }

        if (max_len < 13 && strsrch(NAME_D->who_is(name), "泥") >= 0)
        {
                write("對不起，孩子的名字不能和玩家的名字重複。\n");
                return 0;
        }

        if (max_len < 13 && ! is_chinese(name))
        {
                write("對不起，請您用「中文」為孩子取名字或描述。\n");
                return 0;
        }
        return 1;
}

int do_home(string arg)
{
        object me = this_object(), who = this_player();

        if (! arg) return 0;
        if (! this_object()->id(arg)) return 0;

        if( query("id", who) == query("parents/father" )
         || query("id", who) == query("parents/mother") )
        {
                message_vision("$N對着$n輕聲説道：現在我有些事情，你先回家去吧。\n", who, me);
                me->save();
                destruct(me);
                return 1;
        } else
                command("say 你是誰啊，為什麼要聽你的話？\n");
        return 1;
}

int do_drop(string arg)
{
        object me = this_object(), who = this_player();

        if (! arg || ! this_object()->id(arg)) return 0;

        if (! present(query("id",me), who))
                return notify_fail("你身上沒有這個孩子。\n");

        if (me->move(environment(who)))
        {
                message_vision("$N把$n從懷裏放了下來。\n", who, me);
                return 1;
        }
        return 0;
}

int do_get(string arg)
{
        object  me = this_object(), who = this_player();
        object  ob1, ob2;
        string  fid, mid;
        mapping bro;
        string *ids;

        if (! arg) return 0;
        if (! this_object()->id(arg)) return 0;

        if (environment(me) != environment(who))
                return notify_fail("這裏沒有這個孩子。\n");

        fid=query("parents/father", me);
        mid=query("parents/mother", me);

        ob1 = UPDATE_D->global_find_player(fid);
        ob2 = UPDATE_D->global_find_player(mid);

        if( query("id", who) == fid
         || query("id", who) == mid )
        {
                if (query("age") < 15 && me->move(who))
                {
                        message_vision("$N彎下腰把$n抱了起來，摟在懷裏。\n", who, me);
                }
                else
                {
                        message_vision("$N彎下腰一抱卻沒把$n抱起來，小傢伙好沉哪！\n", who, me);
                }
        } else
        if( mapp(bro=query("brothers", ob1)) && sizeof(bro)>0 )
        {
                ids = keys(bro);
                if( member_array(who->query("id", who), ids) != -1 )
                {
                        if (query("age") < 15 && me->move(who))
                        {
                                message_vision("$N彎下腰把$n抱了起來，摟在懷裏。\n", who, me);
                        }
                        else
                        {
                                message_vision("$N彎下腰一抱卻沒把$n抱起來，小傢伙好沉哪！\n", who, me);
                        }
                }
        } else
        if( mapp(bro=query("brothers", ob2)) && sizeof(bro)>0 )
        {
                ids = keys(bro);

                if (member_array(query("id", who), ids) != -1)
                {
                        if (query("age") < 15 && me->move(who))
                        {
                                message_vision("$N彎下腰把$n抱了起來，摟在懷裏。\n", who, me);
                        }
                        else
                        {
                                message_vision("$N彎下腰一抱卻沒把$n抱起來，小傢伙好沉哪！\n", who, me);
                        }
                }
        }
        else
        {
                message_vision("$N蹲下身朝$n伸開雙手，$n卻一下子閃開了．．．\n",who,me);
        }

        UPDATE_D->global_destruct_player(ob1, 1);
        UPDATE_D->global_destruct_player(ob2, 1);

        return 1;
}

int do_kill(string arg)
{
        object me, who;
        string name, verb, what, obj;

        if (! arg) return 0;

        verb = query_verb();
        me = this_player();

        if (verb == "steal")
        {
                if (sscanf(arg, "%s from %s", what, obj) != 2)
                        return 0;
        }
        else obj = arg;

        if (! objectp(who = present(obj, environment(me)))
        ||  ! living(who))
                return 0;

        if (who == this_object())
        {
                switch(verb)
                {
                case "kill":
                        // command("chat* " +
                        tell_object(environment(this_object()),
                                    query("name", who)+"拼命地哭了起來：爹～～，娘～～，"+
                                    query("name", me)+"要殺我．．．快回來呀！\n");
                        break;
                case "hit":
                        //  command("chat* " +
                        tell_object(environment(this_object()),
                                    query("name", who)+"大哭了起來：爹～～，娘～～，"+
                                    query("name", me)+"欺負我．．．快回來呀！\n");
                        break;
                case "fight":
                        // command("chat* " +
                        tell_object(environment(this_object()),
                                    query("name", who)+"哭了起來：爹～～，娘～～，"+
                                    query("name", me)+"要搶我的糖吃．．．快回來呀！\n");
                        break;
                case "steal":
                        // command("chat* " +
                        tell_object(environment(this_object()),
                                    query("name", who)+"哭了起來：爹～～，娘～～，"+
                                    query("name", me)+"要偷吃我的糖！\n");
                        break;
                case "beg":
                        // command("chat* " +
                        tell_object(environment(this_object()),
                                    query("name", who)+"小嘴一歪哭了起來：爹～～，娘～～，"+
                                    query("name", me)+"要騙我的糖吃！\n");
                        break;
                }
        }
        command(verb);
        return 0;
}

void relay_emote(object ob, string verb)
{
        if (! userp(ob)) return;

        switch(verb)
        {
        case "kick":
                command("say爹～～，娘～～，"+query("name", ob)+"踢我耶！");
                command("kick"+query("id", ob));
                 break;
        case "slap":
                command("say爹～～，娘～～，"+query("name", ob)+"打我耶，好痛啊～～～～");
                command("slap"+query("id", ob));
                break;
        case "hit":
                command("pain"+query("id", ob));
                break;
        case "bite":
                command("face"+query("id", ob));
                break;
        case "papaya":
                command("angry");
                break;
        }
}

void relay_whisper(object me, string msg)
{
        if( query("id", me) != query("parents/father" )
         && query("id", me) != query("parents/mother") )
        {
                message_vision(query("name", this_object())+"疑惑地看着$N。\n",me);
                return;
        }

        /*
        // note, do not allow the order contain "chat", "tell"...
        // may need disable more later...
        if (strsrch(msg, "chat") != -1 ||
            strsrch(msg, "tell") != -1 ||
            strsrch(msg, "sos")  != -1 ||
            strsrch(msg, "recruit") != -1)
                return;
        */

        if (msg)
        {
                remove_call_out ("relaying");
                call_out ("relaying", random(2), msg);
        }
}

void relaying (string msg)
{
        // execute the order.
        if (command(msg))
                return;
        else
                command("say 好像不行呀。。。\n");
        return;

}

mixed ask_father()
{
        object me, ob;
        string id, name;

        me = this_object();

        id=query("parents/father", me);
        ob = UPDATE_D->global_find_player(id);

        if (! objectp(ob))
                return notify_fail(me->name() + "露出痛苦的表情道：“家父已經去世了，你問家父有何貴幹？！”\n");

        name=query("name", ob);
        command("say 我的父親是個頂天立地的大英雄，" + name + "(" + id + ")就是他的尊號，你聽説過他嗎？");
        UPDATE_D->global_destruct_player(ob, 1);
        return 1;
}

mixed ask_mother()
{
        object me, ob;
        string id, name;

        me = this_object();

        id=query("parents/mother", me);
        ob = UPDATE_D->global_find_player(id);

        if (! objectp(ob))
                return notify_fail(me->name() + "露出痛苦的表情道：“家母已經去世了，你問家母有何貴幹？！”\n");

        name=query("name", ob);
        command("say 我的母親是武林第一美女，" + name + "(" + id + ")就是他的尊號，你聽説過她嗎？");
        UPDATE_D->global_destruct_player(ob, 1);
        return 1;
}

int accept_ask(object who, string topic)
{
        object  ob, ob1, ob2, me = this_object();
        string  fid, mid, name, fname, mname;
        mapping bro;
        string *ids;
        string  id;

        fid=query("parents/father", me);
        mid=query("parents/mother", me);

        ob1 = UPDATE_D->global_find_player(fid);
        fname=query("name", ob1);

        if( mapp(bro=query("brothers", ob1)) && sizeof(bro)>0 )
        {
                ids = keys(bro);

                foreach (id in ids)
                {
                        ob = UPDATE_D->global_find_player(id);
                        name=query("name", ob);
                        if (topic == id || topic == name)
                        {
                                if( query("gender", ob) == "男性" )
                                {
                                        if (query("mud_age",ob) > query("mud_age",ob1))
                                                command("say 那是家父的結義兄長，也就是我的伯父。");
                                        else
                                                command("say 那是家父的義弟，也就是我的叔叔。");

                                } else
                                {
                                        if (query("mud_age",ob) > query("mud_age",ob1))
                                                command("say 那是家父的義姐，也就是我的大姑。");
                                        else
                                                command("say 那是家父的結義妹子，也就是我的小姑。");
                                }
                                UPDATE_D->global_destruct_player(ob, 1);
                                UPDATE_D->global_destruct_player(ob1, 1);
                                return 1;
                        }
                        UPDATE_D->global_destruct_player(ob, 1);
                }
        }

        UPDATE_D->global_destruct_player(ob1, 1);

        ob2 = UPDATE_D->global_find_player(mid);
        mname=query("name", ob2);

        if( mapp(bro=query("brothers", ob2)) && sizeof(bro)>0 )
        {
                ids = keys(bro);

                foreach (id in ids)
                {
                        ob = UPDATE_D->global_find_player(id);
                        name=query("name", ob);
                        if (topic == id || topic == name)
                        {
                                if( query("gender", ob) == "男性" )
                                {
                                        if (query("mud_age",ob) > query("mud_age",ob1))
                                                command("say 那是家母的結義兄長，也就是我的大舅。");
                                        else
                                                command("say 那是家母的義弟，也就是我的小舅。");

                                } else
                                {
                                        if (query("mud_age",ob) > query("mud_age",ob1))
                                                command("say 那是家母的義姐，也就是我的大姨。");
                                        else
                                                command("say 那是家母的結義妹子，也就是我的小姨。");
                                }
                                UPDATE_D->global_destruct_player(ob, 1);
                                UPDATE_D->global_destruct_player(ob2, 1);
                                return 1;
                        }
                        UPDATE_D->global_destruct_player(ob, 1);
                }
        }

        UPDATE_D->global_destruct_player(ob2, 1);

        if (topic == fid || topic == fname)
        {
                if( query("id", who) == query("parents/father", me) ||
                    query("id", who) == query("parents/mother", me) )
                        command("say 那是父親大人的名諱啊，孩兒怎敢忘！");
                else
                        command("say 那是家父的名諱，你認識家父嗎？");
                return 1;
        }

        if (topic == mid || topic == mname)
        {
                if( query("id", who) == query("parents/father", me) ||
                    query("id", who) == query("parents/mother", me) )
                        command("say 那是母親大人的名諱啊，孩兒怎敢忘！");
                else
                        command("say 那是家母的名諱，你認識家母嗎？");
                return 1;
        }

        switch (topic)
        {
        case "叫爹爹" :
        case "叫爸爸" :
                if( query("id", who) == query("parents/father", me) )
                        command("say 父親大人好！");
                else
                        command("say 想佔我便宜，門都沒有！");
                return 1;

        case "叫母親" :
        case "叫媽媽" :
                if( query("id", who) == query("parents/mother", me) )
                {
                        command("say 母親大人吉祥！");
                        command("cat"+query("id", who));
                }
                else
                        command("say 想佔我便宜，門都沒有！");
                return 1;

        case "叫叔叔" :
                if( query("gender", who) != "男性" )
                        command("say 你不是男人，我怎麼能叫你叔叔呢？");
                else
                        command("say 叔叔好！");
                return 1;
        case "叫阿姨" :
                if( query("gender", who) != "女性" )
                        command("say 你不是女人，我怎麼能叫你阿姨呢？");
                else
                        command("say 阿姨吉祥！");
                return 1;
        case "叫姑姑" :
                if( query("gender", who) != "女性" )
                        command("say 你不是女人，我怎麼能叫你姑姑呢？");
                else
                        command("say 姑姑吉祥！");
                return 1;
        default:
                return 0;
        }
}

void consider()
{
        string *basic = ({ "force", "dodge", "unarmed", "cuff", "strike", "finger",
                           "hand", "claw", "sword", "blade", "staff", "hammer",
                           "club", "whip", "dagger", "throwing", "parry", "magic",
                           "medical", "poison", "chuixiao-jifa", "tanqin-jifa",
                           "guzheng-jifa", "cooking",
        });
        string skill;
        string *chat_chance_combat_here = ({(: exert_function, "powerup" :)}), *my_skill,
               *basic_skill = ({}), *use_skill = ({}), dir;
        mapping skills;
        int i, j, k;
        mixed *file;
        object me = this_object();

        if (! environment())
                return;
        skills = me->query_skills();
        if (sizeof(skills) && sizeof(skills) > query("skills_learned"))
        {
                my_skill = keys(skills);
                for (i = 0; i < sizeof(basic); i++)
                        if (member_array(basic[i], my_skill) != -1)
                                basic_skill += ({basic[i]});

                for (i = 0; i < sizeof(my_skill); i++)
                        if (SKILL_D(my_skill[i])->type() != "knowledge"
                        &&  member_array(my_skill[i], basic) == -1)
                                use_skill += ({my_skill[i]});

                for (i = 0; i < sizeof(basic_skill); i++)
                for (j = 0; j < sizeof(use_skill); j++)
                if (SKILL_D(use_skill[j])->valid_enable(basic_skill[i])
                &&  ! stringp(query_skill_mapped(basic_skill[i])))
                {
                        map_skill(basic_skill[i], use_skill[j]);
                        if (sizeof(me->query_skill_prepare()) < 2)
                        if (basic_skill[i] == "finger"
                        ||  basic_skill[i] == "strike"
                        ||  basic_skill[i] == "hand"
                        ||  basic_skill[i] == "cuff"
                        ||  basic_skill[i] == "claw"
                        ||  basic_skill[i] == "unarmed")
                                prepare_skill(basic_skill[i], use_skill[j]);

                } else
                        continue;

                if (sizeof(skills) > query("skills_learned"))
                        set("perform_skills", 0);

                if (! query("perform_skills"));
                {
                        for (i = 0; i < sizeof(basic_skill); i++)
                        if (basic_skill[i] != "magic" && basic_skill[i] != "medical"
                        &&  basic_skill[i] != "cooking"
                        &&  stringp(query_skill_mapped(basic_skill[i])))
                        {
                                dir = "/kungfu/skill/" + query_skill_mapped(basic_skill[i]) + "/";
                                if (SKILL_D(query_skill_mapped(basic_skill[i]))->valid_enable("force"))
                                        dir += "perform/";
                                if (file_size(dir) != -2)
                                        continue;
                                file = get_dir(dir, -1);
                                if (! sizeof(file))
                                        continue;

                                for (k = 0; k < sizeof(file); k++)
                                {
                                        if (file[k][0][strlen(file[k][0])-2..strlen(file[k][0])] != ".c")
                                                        continue;
                                        file[k][0] = replace_string(file[k][0], ".c", "");
                                        chat_chance_combat_here +=
                                                ({( : perform_action, basic_skill[i] + "." + file[k][0]: )});
                                }
                        } else
                                continue;

                        set("chat_msg_combat", chat_chance_combat_here);
                        set("perform_skills", 1);
                }

                set("chat_msg_combat", chat_chance_combat_here);
                reset_action();
                set("skills_learned", sizeof(skills));
                command("say 嘻嘻，我知道了，我會用了！\n");
        }

        set("jiali", query_skill("force") / 2 + 10);
        save();

        command("say 嘻嘻，都記住了，可以了！\n");
        return;
}

int accept_object(object who, object ob)
{
        if( query("id", who) == query("parents/father" )
         || query("id", who) == query("parents/mother") )
        {
                remove_call_out("provide");
                call_out("provide", 1);
                return 1;
        } else
                return 0;
}

void provide()
{
        object *ilist, ob;
        object weapon, armor;
        int i;

        if (! environment()) return;
        ilist = all_inventory(this_object());
        if (sizeof(ilist) < 1) return;

        for (i = 0; i < sizeof(ilist); i++)
        {
                ob = ilist[i];
                if( query("weapon_prop/damage", ob) )
                {
                        if (objectp(weapon = query_temp("weapon")) && weapon != ob
                         && query("weapon_prop/damage", ob)>
                            query("weapon_prop/damage", weapon) )
                                weapon->unequip();
                        command("wield "+query("id", ob));
                }

                if( query("armor_prop/armor", ob) )
                {
                        if (objectp(armor = query_temp("armor/" + query("armor_type", ob)))
                        &&  armor != ob
                         && query("armor_prop/armor", ob)>
                            query("armor_prop/armor", armor) )
                                armor->unequip();
                        command("wear "+query("id", ob));
                }

                if( query("food_remaining", ob) )
                        command("eat "+query("id", ob));
                else
                if( query("liquid/remaining", ob) )
                        command("drink "+query("id", ob));
        }

        set("jiali", query_skill("force") / 2 + 10);

        command("sweat");
        return;
}

