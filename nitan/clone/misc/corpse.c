// corpse.c
// Updated by Doing

inherit ITEM;
inherit F_CUTABLE;

int decayed;
nosave int not_cut = 0;

string query_idname()
{
        return query("name") + "(" + query("id") + ")"; 
}

void create()
{
        set_name("無名屍體", ({ "corpse" }));
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("default_clone", "/clone/misc/part");
                set("parts", ([
                        "left arm" : ({ 0, "條", "左臂", "手臂", "arm",
                                        ([ "left hand": "hand" ]),
                                        "剁下", 0 }),
                        "left hand": ({ 1, "只", "左手", "手掌", "hand",
                                        ([ "left thumb"        : "thumb",
                                           "left forefinger"   : "forefinger",
                                           "left middle finger": "middle finger",
                                           "left ring finger"  : "ring finger",
                                           "left little finger": "little finger" ]),
                                        "剁下", 0 }),
                        "left thumb"         : ({ 2, "根", "左手大拇指", "大拇指", "thumb",
                                                  0, 0, 0 }),
                        "left forefinger"    : ({ 2, "根", "左手食指", "食指", "forefinger",
                                                  0, 0, 0 }),
                        "left middle finger" : ({ 2, "根", "左手中指", "中指", "middle finger",
                                                  0, 0, 0 }),
                        "left ring finger"   : ({ 2, "根", "左手無名指", "無名指", "ring finger",
                                                  0, 0, 0 }),
                        "left little finger" : ({ 2, "根", "左手小指", "小指", "little finger",
                                                  0, 0, 0 }),
                        "right arm" : ({ 0, "條", "右臂", "手臂", "arm",
                                        ([ "right hand": "hand" ]),
                                        "剁下", 0 }),
                        "right hand": ({ 1, "只", "右手", "手掌", "hand",
                                        ([ "right thumb"        : "thumb",
                                           "right forefinger"   : "forefinger",
                                           "right middle finger": "middle finger",
                                           "right ring finger"  : "ring finger",
                                           "right little finger": "little finger" ]),
                                        "剁下", 0 }),
                        "right thumb"         : ({ 2, "根", "右手大拇指", "大拇指", "thumb",
                                                   0, 0, 0 }),
                        "right forefinger"    : ({ 2, "根", "右手食指", "食指", "forefinger",
                                                   0, 0, 0 }),
                        "right middle finger" : ({ 2, "根", "右手中指", "中指", "middle finger",
                                                   0, 0, 0 }),
                        "right ring finger"   : ({ 2, "根", "右手無名指", "無名指", "ring finger",
                                                   0, 0, 0 }),
                        "right little finger" : ({ 2, "根", "右手小指", "小指", "little finger",
                                                   0, 0, 0 }),
                        "left leg" : ({ 0, "條", "左腿", "人腿", "leg",
                                        ([ "left foot": "foot" ]),
                                         "剁下", 0 }),
                        "left foot": ({ 1, "只", "左腳", "人腳", "foot",
                                        ([ "left toes"        : "toes", ]),
                                        "剁下", 0 }),
                        "left toes": ({ 2, "根", "左腳趾", "腳趾", "toes",
                                                       0, 0, 0 }),
                        "right leg" : ({ 0, "條", "右腿", "人腿", "leg",
                                        ([ "right foot": "foot" ]),
                                         "剁下", 0 }),
                        "right foot": ({ 1, "只", "右腳", "人腳", "foot",
                                        ([ "right toes"        : "toes", ]),
                                        "剁下", 0 }),
                        "right toes": ({ 2, "根", "右腳趾", "腳趾", "toes",
                                                       0, 0, 0 }),
                        "head"      : ({ 0, "顆", "頭", "人頭", "head",
                                        ([ "left eye"  : "left eye",
                                           "right eye" : "right eye",
                                           "nose"      : "nose",
                                           "left ear"  : "left ear",
                                           "right ear" : "right ear",
                                           "hair"      : "hair",
                                           "tongue"    : "tongue", ]),
                                        "砍下", "/clone/misc/head" }),
                        "left eye"  : ({ 1, "只", "左眼", "眼珠", "eye",
                                         0, "挖出", 0, }),
                        "right eye" : ({ 1, "只", "右眼", "眼珠", "eye",
                                         0, "挖出", 0, }),
                        "left ear"  : ({ 1, "只", "左耳", "耳朵", "ear",
                                         0, 0, 0, }),
                        "right ear" : ({ 1, "只", "右耳", "耳朵", "ear",
                                         0, 0, 0, }),
                        "nose"      : ({ 1, "只", "鼻子", "鼻子", "nose",
                                         0, 0, 0, }),
                        "hair"      : ({ 1, "束", "頭發", "頭發", 0,
                                         0, 0, "/clone/misc/hair", }),
                        "tongue"    : ({ 1, "條", "舌頭", "舌頭", 0,
                                         0, 0, 0, }),
                        "genitals"  : ({ 1, "根", "生殖器", 0, 0,
                                         0, 0, 0, }),
                ]));
                set("no_store", 1);
                set("unit", "具" );
                set("main_part_level", 0);
        }
        
        set("long", "這是一具無名屍體。\n");
        decayed = 0;
        if( clonep(this_object()) ) call_out("decay", 60, 1);
}

int is_corpse() { return decayed < 2; }
int is_character() { return decayed < 1; }
int is_container() { return 1; }

string short() { return name() + "(" + capitalize(query("id")) + ")"; }

string long() { return ::long() + extra_desc(); }

void decay(int phase)
{
        string msg;
        object env;

        env = environment();
        decayed = phase;
        switch (phase)
        {
        case 1:
                set("owner_id", "unknow");
                msg =  name(1) + "開始腐爛了，發出一股難聞的惡臭。\n";
                delete("victim_name");
                delete("owner_id");
                switch (query("gender"))
                {
                case "男性":
                        set_name("腐爛的男屍", ({ "corpse", "屍體" }));
                        break;

                case "女性":
                        set_name("腐爛的女屍", ({ "corpse", "屍體" }));
                        break;

                default:
                        set_name("腐爛的屍體", ({ "corpse", "屍體" }));
                }
                set("long",        "這具屍體顯然已經躺在這裡有一段時間了，正散發著一股腐屍的味道。\n");
                call_out("decay", 60, phase + 1);
                break;
        case 2:
                delete("parts");
                msg = name(1) + "被風吹乾了，變成一具骸骨。\n";
                set_name("枯乾的骸骨", ({ "skeleton", "骸骨" }) );
                set("long", "這副骸骨已經躺在這裡很久了。\n");
                call_out("decay", 5, phase + 1);
                break;
        case 3:
                msg = "一陣風吹過，把" + name(1) + "化成骨灰吹散了。\n";
                if( env )
                        all_inventory(this_object())->move(env);
                tell_room(env, msg);
                destruct(this_object());
                return;
        }

        while (env && env->is_character())
                env = environment(env);

        if (env) tell_room(env, msg);
}

int do_cut(object me, string arg)
{
        object ob;

        if (not_cut)
                return 0;

        if (! ::do_cut(me, arg))
                return 0;

        remove_call_out("decay");
        call_out("decay", 1, 1);

        if (! objectp(ob = query_temp("handing")))
                return 1;

        if (arg != "right hand" &&
            arg != "right thumb" &&
            arg != "right middle finger")
                return 1;

        delete_temp("handing");
        message("vision", "“啪啦”一聲，" + ob->name() + "掉了下來。\n",
                          environment());
        ob->move(environment());
        return 1;
}

int make_corpse(object victim, object killer)
{
        int i;
        object env;
        object aob, dob;
        object *inv;

        set_name(victim->name(1) + "的屍體", ({ "corpse" }));
        set("long", victim->long()
                +"然而，"+gender_pronoun(query("gender", victim) )
                + "已經死了，只剩下一具屍體靜靜地躺在這裡。\n");
        set("class",query("class", victim));
        set("age",query("age", victim));
        set("combat_exp",query("combat_exp", victim));
        set("gender",query("gender", victim));
        set("victim_name", victim->name(1));
        set_weight(victim->query_weight());
        set_max_encumbrance(victim->query_max_encumbrance());
        env = environment(victim);
        if (objectp(env))
        while (environment(env)) env = environment(env);
        move(env);
        set_temp("handing",query_temp("handing", victim));
        if( query("can_speak", victim) )
        {
                set("owner_id",query("id", victim));
                set("is_player", userp(victim));
                set("defeated_by", dob = victim->query_defeated_by());
                set("defeated_by_who", victim->query_defeated_by_who());
                if (objectp(killer))
                {
                        set("killed_by",query("id", killer));
                        set("who_get/id",query("id", killer));
                        set("who_get/time", time() + 5);
                }
                // 這是為了幫手設計的
                if (! objectp(dob)) dob = killer;
                if (objectp(dob) &&
                    objectp(aob=query_temp("quest/assist", dob)) )
                {
                        // 我正在幫助某人(aob)，如果某人的確想殺
                        // 死該人的話，則我記錄之。
                        if( aob->is_killing(query("id", victim)) )
                                // 記錄此人幫助的對象
                                set("assist", aob);
                }
        } else
        {
                // can not cut can_speak object
                not_cut = 1;
        }
 
        if( query("class", victim) == "bonze" )
                set("no_cut/hair", "它沒有頭發啊，等它再長出來好像來不及了。\n");

        switch(query("gender", victim) )
        {
        case "女性":
                set("no_cut/genitals", "看清楚了，這可是一具女屍");
                break;

        case "男性":
                break;

        case "無性":
                set("no_cut/genitals", "看清楚了，這位生前就已經做過"
                                       "手術了，你不必再操心了。\n");
                break;
        default:
                set("no_cut/genitals", "看清楚了，這不是人的屍體。\n");
                break;
        }

        // Don't let wizard left illegal items in their corpses.
        if (! wizardp(victim) && ! query_temp("tianshi_charm", victim))
        {
                inv = all_inventory(victim);
                inv->owner_is_killed(killer);
                //inv = filter_array(inv, (: !query("bind_owner", $1) :));
                inv -= ({ 0 });
                i = sizeof(inv);
                while (i--)
                {
                        if( time()-query("combat/punish", victim) < 3 )
                                delete("bind_owner", inv[i]);
                        if( query("equipped", inv[i]) == "worn" )
                        {
                                inv[i]->move(this_object());
                                if (! inv[i]->wear())
                                        inv[i]->move(environment(victim));
                        } else
                                inv[i]->move(this_object());
                } 
        }
        delete_temp("tianshi_charm", victim);
        return 1;
}
