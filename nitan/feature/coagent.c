// coagent.c

#include <ansi.h>

nosave int helping = 0;
int is_coagent() { return 1; }
int is_helping() { return helping; }

int start_help(object env, object helper, object ob)
{
        object me;

        command("yun powerup");
        me = this_object();
        if( !living(me) ) return 0;

        if( env == environment() ) {
                if( this_object()->is_killing(ob->query("id")) )
                        return 1;

                message_vision(HIW + "$N冷笑不止：“好個" +
                               RANK_D->query_rude(ob) + "！你也來添亂？”\n",
                               me);
        } else {
                if( helping || me->is_fighting() )
                        return 0;

                message_vision(HIC + me->name() + "微微一愣，似乎聽到了什麼，"
                               "雙足一點，撲了出去。\n" NOR, me);

                me->move(env);
                if( objectp(helper) ) {
                        message_vision(random(2) ? HIW + "$N高聲應道：“$n！不必驚慌，我$N來了！”\n" NOR :
                                                   HIW + "$N一聲長吟：“且慢，還有我$N呢，接招！”\n",
                                       me, helper);
                }
        }

        me->kill_ob(ob);
        helping = 1;
        return 1;
}

void finish_help()
{
        string startroom;
        object me;

        me = this_object();
        if( !helping )
                return;

        startroom = query("startroom", me);
        if( !stringp(startroom) || startroom == "" )
                return;

        if( base_name(environment()) != startroom ) {
                message_vision("$N看了看四周，匆匆地離開了。\n", me);
                me->move(startroom);
                message_vision("$N匆匆地趕了過來，拍了拍塵土，彷彿什麼"
                               "都沒有發生似的。\n", me);
        }

        helping = 0;
}
