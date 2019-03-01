// move.c
// Written by Lonely@chinamud.cn

#pragma optimize
#pragma save_binary

#include <ansi.h>
#include <command.h>

nosave int weight = 0;
nosave int encumb = 0, max_encumb = 0;
nosave int magic_move = 0;
nosave int in_temp =0;

nomask int query_encumbrance() { return encumb; }
nomask int over_encumbranced() { return encumb > max_encumb; }

nomask int query_max_encumbrance() { return max_encumb; }
nomask void set_max_encumbrance(int e) { max_encumb = e; }
nomask void add_encumbrance(int w)
{
        object env;
        encumb += w;
        if( encumb < 0 )
                log_file("move.bug", sprintf("%O encumbrance underflow.\n", this_object()));
        if( encumb > max_encumb ) this_object()->over_encumbrance();
        if( env = environment() ) env->add_encumbrance(w);
}

void over_encumbrance()
{
        if( !interactive(this_object()) )return;
        tell_object(this_object(), "你的負荷過重了！\n");
}

nomask int query_weight() { return weight; }
nomask void set_weight(int w)
{
        if( !environment() ) {
                weight = w;
                return;
        }
        if( w != weight )environment()->add_encumbrance(w - weight);
        weight = w;
}


// This is the "current" weight of an object, which is used on weight
// checking in move().
nomask int weight() { return weight + encumb; }

// Magic move flag: the wizard may use it
nomask int is_magic_move() { return magic_move; }
nomask int set_magic_move() { magic_move = 1; }

varargs int move(mixed dest, int raw)
{
        object ob, env;
        object me;
        int is_char;
        mixed old_target;
        mixed *guards;
        object user;
        object *users;

        me = this_object();

        // If we are equipped, unequip first.
        if( !(is_char = me->is_character()) &&
            query("equipped") && !me->unequip() )
                return notify_fail("你沒有辦法取下這樣東西。\n");

        // Find the destination ob for moving.
        if( objectp(dest))
                ob = dest;
        else
        if( stringp(dest) ) {
                call_other(dest, "???");
                ob = find_object(dest);
                if( !ob) return notify_fail("move: destination unavailable.\n");
        } else  return notify_fail(sprintf("move: invalid destination %O.\n", dest));

        if( !is_char && query("bind_owner", me) && base_name(ob) != VOID_OB &&
            (!userp(ob) || query("bind_owner", me) != query("id", ob)) ) {
                write(sprintf("%s已經綁定，無法移動。\n",
                              me->name()));
                return 0;
        }

        // Check if the destination ob can hold this object.
        // Beforce checking it, we check if the destination is environment of
        // this_object() (or environment of its environment). If it is, then
        // this could be like get something from a bag carried by the player.
        // Since the player can carry the bag, we assume he can carry the this
        // object in the bag and encumbrance checking is unessessary.
        // ----------------------
        // 檢查目標是否能夠包容住該物品
        // 在檢查前，我們先檢查是否目標OBJ是該物件的環境（或者是它的環境的環境），如果是，那就好象是
        // 從一個玩家身上背著的包裡取出一個物品，既然玩家可以背起這個包，那麼我們可以想當然的認為他也
        // 可以背起這個OBJ並且超重檢查是不必要的。 By JackyBoy@TOMUD 2001/5/6
        env = me;
        while( env = environment(env) )
                if( env == ob ) break;
        if( !env && (int) ob->query_encumbrance() + weight() >
            (int) ob->query_max_encumbrance() ) {
                if( raw && environment(ob) && !query("bindable", me) ) {
                        message_vision("由于$n對于$N而言是在"
                                       "是太重了，只好先扔在一旁。\n",
                                       ob, this_object());
                        ob = environment(ob);
                } else if( ob == this_player() ) {
                        return notify_fail(this_object()->name() +
                                           "對你而言太重了。\n");
                } else {
                        return notify_fail(this_object()->name() +
                                           "對" + ob->name() +
                                           "而言太重了。\n");
                }
        }

        // Leave environment
        // Move the object and update encumbrance
        env = environment();
        if( env ) {
                if( env != ob && magic_move && userp(env) ) {
                        if( env->visible(me) )
                                tell_object(env, HIM "你忽然覺得身上好像輕了一"
                                                 "些。\n" NOR);
                        if( userp(me) ) {
                                addn_temp("person_in_you", -1, env);
                                if( query_temp("person_in_you", env) <= 0)
                                        delete_temp("person_in_you", env);
                        }
                }
                // The owner should remove handing
                if( !is_char && query_temp("handing", env) == me )
                        delete_temp("handing", env);
        }

        // remove the thing I am guarding
        old_target = query_temp("guardfor");

        if( objectp(old_target) && !old_target->is_character() ) {
                if( arrayp(guards = query_temp("guarded", old_target)) ) {
                        guards -= ({ me });
                        if( !sizeof(guards) ) {
                                delete_temp("guarded", old_target);
                        } else
                                set("guarded", guards, old_target);
                }
                delete_temp("guardfor", me);
        } else if( stringp(old_target) ) {
                guards = query_temp("guarded/" + old_target, env);
                if( arrayp(guards) ) {
                        guards -= ({ me });
                        if( !sizeof(guards) ) {
                                delete_temp("guarded/"+old_target, env);
                        } else
                                set("guarded/"+old_target, guards, env);
                }
                delete_temp("guardfor", me);
        }

        // If we are players, try look where we are.
        if( is_char && interactive(me) &&       // are we linkdead?
            living(me) &&                       // are we still concious?
            !raw ) {
                // look before move, because the init may be kick me
                // to ...
                LOOK_CMD->look_room(me, ob, query("env/brief"));
        }

        // Enter environment
        if( magic_move && userp(ob) ) {
                if( ob->visible(this_object()) )
                        tell_object(ob, HIM "你忽然覺得身上好像重了一"
                                         "些。\n" NOR);
                if( userp(this_object()) )
                        addn_temp("person_in_you", 1, ob);
        }
        magic_move = 0;

        // Modify By JackyBoy@TOMUD      2001/5/6
        if( !wizardp(this_object()) || !query("env/invisible") ) {
                if( env ) {
                        env->add_encumbrance(-weight());
                        if( userp(env) && query_temp("tomud", env) )
                                tell_object(env, REM1(this_object())); //如果是從玩家身上移動走，則應該是REM1
                        else if( !living(env) ) {
                                users = filter_array(all_inventory(env),
                                                     (: (userp($1) && query_temp("tomud", $1)) :)) -
                                                     ({ this_object() });
                                if( sizeof(users) > 0 )
                                foreach( user in users )
                                        tell_object(user, REM0(this_object()));

                                // tell_room(env,REM0(this_object()),this_object() );
                                // 如果是從房間裡移動走，則應該是REM0
                        }
                        // else log_file("move.log",ctime(time())+"：不知道如何顯示REM消息---"+base_name(env)+"\n");
                }
                if( ob ) {
                        ob->add_encumbrance(weight());
                        if( (userp(ob)|| interactive(ob)) && query_temp("tomud", ob) )
                                tell_object(ob, ADD1(this_object()) );
                                // 如果是移動到玩家身上，則應該是ADD1
                        else if( !ob->is_character() ) {
                                users = filter_array(all_inventory(ob),
                                                     (: (userp($1) && query_temp("tomud", $1)) :)) -
                                                     ({ this_object() });
                                if( sizeof(users) > 0 )
                                foreach( user in users )
                                        tell_object(user, ADD0(this_object()));
                                // tell_room(ob, ADD0(this_object()),this_object() );
                                // 如果是移動到房間裡，則應該是ADD0
                        }
                }
        }
        // Move & run INIT function
        move_object(ob);

        // bindable == 2 拾取綁定
        if( me && !is_char && query("bindable", me) &&
            query("bindable", me) == 2 && userp(ob) ) {
                set("bind_owner", query("id", ob), me);
                set("set_data", 1, me);
                tell_object(ob, HIM "你內心深處隱隱約約的感應到" + me->name() +
                                HIM "與你融為一體。\n" NOR);
        }


        return 1;
}

void remove(string euid)
{
        object me;
        object ob;
        object default_ob;
        object user;
        object *users;

        if( !previous_object() ||
            base_name(previous_object()) != SIMUL_EFUN_OB )
                error("move: remove() can only be called by destruct() simul efun.\n");

        me = this_object();
#ifdef DB_SAVE
        if( userp(me) && sizeof(query("id", me)) )
                DATABASE_D->db_set_player(query("id", me), "online", 0);
#endif

        if( userp(me) && euid != ROOT_UID ) {
                if( euid != getuid(me) ) {
                        // Failed to destruct
                        log_file("destruct", sprintf("%s attempt to destruct user object %s (%s)\n",
                                 euid, query("id"),
                                 ctime(time())));
                        error("你(" + euid + ")不能摧毀其他的使用者。\n");
                }
                log_file("destruct", sprintf("%s in %O destruct on %s.\n",
                                             query("id", me),
                                             environment(me),
                                             ctime(time())));
                error("只有ROOT才能摧毀玩家。\n");
        } else if( query("equipped", me) ) {
                // Failed to unequip, only log but continue
                if( !me->unequip() )
                        log_file("destruct", sprintf("Failed to unequip %s when destructed.\n",
                                                     file_name(me)));
        }

        if( me->is_ob_saved() )
                me->save();

        // Leave environment
        if( objectp(ob = environment()) ) {
                ob->add_encumbrance(-weight());

                if( ob->is_character() && query_temp("handing", ob) == me )
                        // remove handing when destruct the object
                        delete_temp("handing", ob);

                //Add By JackyBoy@TOMUD      2001/5/27
                if( userp(ob) && query_temp("tomud", ob) )
                        tell_object(ob, REM1(me) ); //如果是從玩家身上移動走，則應該是REM1
                else if( !living(ob) && !ob->is_character() ) {
                        users = filter_array(all_inventory(ob),
                                            (: (userp($1) && query_temp("tomud", $1)) :)) -
                                            ({ me });
                        if( sizeof(users) > 0 )
                        foreach( user in users )
                                tell_object(user, REM0(me));
                        // tell_room(ob, REM0(me), me );//如果是從房間裡移動走，則應該是REM0
                }

                if( is_magic_move() && userp(ob) ) {
                        if( ob->visible(this_object()) )
                                tell_object(ob, HIM "你忽然覺得身上好像輕了一些。\n" NOR);

                        if( userp(me) ) {
                                // One user enter another user
                                addn_temp("person_in_you", -1, ob);
                                if( query_temp("person_in_you", ob) <= 0 )
                                        delete_temp("person_in_you", ob);
                        }
                }
        }

        // We only care about our own weight here, since remove() is called once
        // on each destruct(), so our inventory (encumbrance) will be counted as
        // well.

        if( objectp(me->query_default_object()) ) {
                default_ob = me->query_default_object();
                addn("no_clean_up", -1, default_ob);
        }

        me->end_log();
}

void move_or_destruct(object dest)
{
        if( userp(this_object()) ) {
                tell_object(this_object(), "一陣時空的扭曲將你傳送到另一個地方....\n");
                move(VOID_OB);
        } else if( this_object()->is_ob_saved() )
                this_object()->save();
}
