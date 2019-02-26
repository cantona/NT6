// quit.c

#include <ansi.h>
#include <command.h>
#include <config.h>

inherit F_DBASE;
inherit F_CLEAN_UP;

#define QUITMSG                        "/adm/etc/quitmsg"

int confirm(string yn, object me);

void destruct_ob(object me)
{
        if( !objectp(me) ) return;
        destruct(me);
}

void create()
{
        seteuid(getuid());
        set("name", "離線指令");
        set("id", "quit");
        set("channel_id", "離線精靈");
}

int main(object me, string arg)
{
        int i;
        int find;
        int doing;
        object *inv, link_ob;
        object *users;

        if (LOGIN_D->get_madlock())
                return notify_fail("時空已經封閉，沒有人能夠退出這個時空了。\n");

        if( me->is_busy() && !query("doing", me) )
                return notify_fail("你現在正忙着做其他事，不能退出遊戲！\n");

        if (me->is_fighting())
                return notify_fail("你現在正在打架，怎麼能説走就走？\n");

        if (me->query_competitor())
                return notify_fail("好傢伙，你正在和人比武，怎麼能開溜？\n");

        if (me->dps_count() > 0)
                return notify_fail("好傢伙，你打暈了別人就想開溜？\n");

        if (me->query_condition("killer"))
                return notify_fail("好傢伙，你殺了人就別想開溜！\n");

        if( time()-query("combat/pktime", me)<28800 )
                return notify_fail("好傢伙，你殺了人就別想開溜！\n");

        if (me->over_encumbranced())
                return notify_fail("你身上背的東西太多了，無法離開這個世界。\n");

        if (me->run_override("quit"))
                return 1;

        if( time()-query("birthday", me)<1800 && !query("reborn", me) && !wizardp(me) )
        {
                write(HIG "\n你的賬號是新建的，本站規定新建賬號必須連續在線半小時才能被有效保\n"
                          "留，退出該遊戲將刪除你的賬號，你確定要放棄該帳號而退出嗎？（" HIR "y" HIG "/" HIY "n" HIG "）\n" NOR);
                input_to((: confirm :), me);
                return 1;
        }

        link_ob=query_temp("link_ob", me);

        // We might be called on a link_dead player, so check this.
        if (objectp(link_ob))
        {
                // Are we possessing in others body ?
                if (link_ob->is_character())
                {
                        write("你的魂魄回到" + link_ob->name(1) + "的身上。\n");
                        exec(link_ob, me);
                        link_ob->setup();
                        link_ob->write_prompt();
                        return 1;
                }

                if( query_temp("ip_number", link_ob) )
                {
                        set("last_on", time(), link_ob);
                        set("last_from",
                                     query_temp("ip_number", link_ob), link_ob);
                        set("registerd",
                                     query("registered", me), link_ob);
                        link_ob->save();
                }
                destruct(link_ob);
        }

        if( query("doing", me) )
        {
                if (! interactive(me))
                        return 1;

                write("你暫時離線，人物不退出...\n");
                message("vision", me->name() + "離線了。\n",
                                  environment(me), ({ me }));
                me->save();
                link_ob = new(LOGIN_OB);
                exec(link_ob, me);
                destruct(link_ob);
#ifdef DB_SAVE
                DATABASE_D->db_set_player(query("id", me),"online",2);//離線練功
                DATABASE_D->db_set_user(query("id", me),"online",2);//離線練功
#endif
                return 1;
        }

#if INSTALL_EXAMINE
        EXAMINE_D->examine_player(me);
#endif

        if( me->in_team() )
                me->dismiss_team();

        me->log_command("quit");

/*
#ifndef NO_QUIT_DROP
        if (! wizardp(me))
        {
                int flag;
                flag = 0;
                inv = all_inventory(me);
                for (i = 0; i < sizeof(inv); i++)
                        if( !inv[i]->query_autoload() && !query("equipped", inv[i]) )
                                        flag += DROP_CMD->do_drop(me, inv[i], 1);
                if (flag)
                        message("vision", me->name() + "將身上的東西都丟了下來。\n",
                                environment(me), ({ me }));
        }
#else  // 如果不丟物品則必須判斷某些物品是必須摧毀的
*/
#ifdef NO_QUIT_DROP
        inv = all_inventory(me);
        for (i = 0; i < sizeof(inv); i++)
                if (userp(inv[i]) || inv[i]->query_unique() ||
                    query("maze_item", inv[i]) || 
                    (! clonep(inv[i]) &&
                    ! sscanf(base_name(inv[i]), "/data/%*s/%*s"))) // 如果成立表示此物品是非 /data 目錄下的原件
                {
                        if( query("equipped", inv[i]) )
                                inv[i]->unequip();
                        if( query("no_drop", inv[i]) || query("unique", inv[i]) )
                                destruct(inv[i]);
                        else
                                DROP_CMD->do_drop(me, inv[i], 1);
                }
#endif

        // write("歡迎下次再來！\n");
        color_cat(QUITMSG);
        if (environment(me))
        {
                message("vision", me->name() + "離開遊戲。\n",
                        environment(me), ({ me }));
        }

        CHANNEL_D->do_channel(this_object(), "sys",
                me->name()+"("+query("id", me)+")離開遊戲了。");


        log_file("stat", sprintf("%-8s %-10s %-18s %-18s %-15s.\n",
                                 me->name(1),query("id", me),
                                 ctime(query_temp("logon_time", me)),
                                 ctime(time()),
                                 interactive(me) ? query_ip_number(me) : "unknow"));

        users=filter_array(users(),(:query_temp("tomud", $1):));
        message("system", REM2(me), users);

        if (me->start_room_srv())
                set("startroom", base_name(environment(me)), me);

        set("last_on", time(), me); 
        me->save();
        me->set_magic_move();
        me->end_log();
#ifdef DB_SAVE
        DATABASE_D->db_set_player(query("id", me),"online",0);
#endif
        call_out("destruct_ob", 0, me);
        return 1;
}

int force_quit(object me)
{
        int find;
        object *users;

        if (previous_object() != me ||
            ! playerp(me))
                return notify_fail("你不能摧毀這個對象。\n");

        seteuid(getuid());

        if (me->query_condition("killer"))
                return notify_fail("好傢伙，殺了人就別想開溜！\n");

        if( time()-query("combat/pktime", me)<28800 )
                return notify_fail("好傢伙，你殺了人就別想開溜！\n");

        if( query("mud_age", me)<1800 && !query("reborn", me) )
        {
                UPDATE_D->remove_user(query("id", me));
                return 1;
        }

        if( me->in_team() )
                me->dismiss_team();

        me->save();
        if (environment(me) != find_object(VOID_OB))
                me->move(VOID_OB, 1);

        users=filter_array(users(),(:query_temp("tomud", $1):));
        message("system", REM2(me), users);

#ifdef DB_SAVE
             DATABASE_D->db_set_player(query("id", me),"online",0);//離線練功
#endif
        destruct(me);
        return 1;
}

int confirm(string yn, object me)
{
        object *users;
        if (upper_case(yn) == "Y")
        {
                seteuid(getuid());

                log_file("static/register",
                         sprintf("%s %s commits a suicide from %s\n",
                                    log_time(), log_id(me),
                                    query_ip_number(me)));

                write(HIW "您選擇了放棄該賬號退出泥潭，檔案被刪除。。。。。。\n" NOR);

                users=filter_array(users(),(:query_temp("tomud", $1):));
                message("system", REM2(me), users);

                UPDATE_D->remove_user(query("id", me), 1);
                return 1;
        } else
        {
                write(HIG "您選擇了放棄退出(quit)，繼續遊戲。\n" NOR);
                return 1;
        }
}

int help(object me)
{
        write(@HELP
指令格式 : quit | exit

當你(你)想暫時離開時, 可利用此一指令。
HELP );
    return 1;
}

