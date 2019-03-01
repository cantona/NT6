// update.c
// updated by doing

#include <runtime_config.h>
#include <getconfig.h>
#include <ansi.h>

inherit F_CLEAN_UP;

protected int update_player(object me);

void create()
{
        seteuid(getuid());
}


int main(object me, string file)
{
        int i;
        object obj, *inv;
        string err;
        string bin_file;

        if (! SECURITY_D->valid_grant(me, "(wizard)"))
                return 0;

        seteuid(geteuid(me));

        if (! file) file = query("cwf", me);
        if (! file)
                return notify_fail("你要重新編譯什麼檔案？\n");

        if ((obj = present(file, environment(me))) && playerp(obj) ||
            (obj = find_player(file)) && playerp(obj))
                return update_player(obj);

        if (file == "me")
                return update_player(me);
        else
        {
                file = resolve_path(query("cwd", me), file);
                if (! sscanf(file, "%*s.c")) file += ".c";
        }

        if (file_size(file) == -1)
                return notify_fail("沒有這個檔案。\n");

        set("cwf", file, me);

        if (obj = find_object(file))
        {
                if (obj == environment(me))
                {
                        if (file_name(obj) == VOID_OB)
                                return notify_fail("你不能在 VOID_OB 裡重新編譯 VOID_OB。\n");
                        inv = all_inventory(obj);
                        i = sizeof(inv);
                        while (i--)
                                if (playerp(inv[i]) || inv[i]->is_chatter() ||
                                    query_temp("owner", inv[i]) )
                                        // 玩家、聊天魂魄、有主的物品或人物
                                        inv[i]->move(VOID_OB, 1);
                                else    inv[i] = 0;
                }

                if (obj == find_object(VERSION_D) &&
                    VERSION_D->is_release_server())
                {
                        // 如果是版本發布的服務器，則刪除
                        // VERSION_D 的 bin 代碼，因為在沒有
                        // VERSION_D 的時候 driver 是不予編譯的。
                        bin_file = "/binaries" + base_name(obj) + ".b";
                        write("Remove: " + bin_file + "\n");
                        rm(bin_file);
                }
                seteuid(getuid());
                destruct(obj);
        }

        if (obj) return notify_fail("無法清除舊程式碼。\n");

        write("重新編譯 " + file + "：");
        err = catch(call_other(file, "???"));
        if (err)
                write(sprintf( "發生錯誤：\n%s\n", err));
        else
        {
                write("成功！\n");
                if ((i = sizeof(inv)) && (obj = find_object(file)))
                        while (i--)
                                if (inv[i]) inv[i]->move(obj, 1);
        }

        return 1;
}

protected int update_player(object me)
{
        object env, link_ob, obj;
        object *ob, *dob;
        mapping equip;
        int i;

        if (me->is_chatter())
                return notify_fail("你不能更新聊天ID。\n");

        if (wiz_level(me) > wiz_level(this_player()))
                return notify_fail("你沒有權限更新這個人物。\n");

        seteuid(getuid());
        env = environment(me);

        // First, create the new body.
        link_ob=query_temp("link_ob", me);
        if (! link_ob)
        {
                link_ob = new(LOGIN_OB);
                set("id",query("id",  me), link_ob);
                if (! link_ob->restore())
                {
                        write("找不到該玩家的存盤數據。\n");
                        return 1;
                }
                if (interactive(me))
                        set_temp("ip_number", query_ip_number(me), link_ob);
        }

        if( query("id", link_ob) != getuid(me) )
        {
                write (sprintf("連接對象的ID(%s)和用戶的ID(%s)不相同，不能"
                       "更新該玩家。\n",query("id", link_ob),getuid(me)));
                return 1;
        }

        obj = LOGIN_D->make_body(link_ob);
        if (! obj) return 0;

        // Save the data and exec the player to his/her link object.
        ob = all_inventory(me);
        equip = ([ ]);
        for (i = 0; i < sizeof(ob); i++)
                equip += ([ ob[i] : query("equipped", ob[i]) ]);
        ob->move(VOID_OB);

        // 保存用戶的進度
        me->save();

        // 如果在線，移動互動對象
        if (interactive(me))
                exec(link_ob, me);
        destruct(me);

        // Restore new body and exec to it via enter_world in LOGIN_D
        obj->restore();
        LOGIN_D->enter_world(link_ob, obj, 1, 1);
        dob = all_inventory(obj);
        for (i = 0; i < sizeof(dob); i++)
                destruct(dob[i]);

        write("身體更新完畢。\n\n");
        obj->move(env);
        ob->move(obj);

        if (! interactive(obj))
                destruct(link_ob);

        for (i = 0; i < sizeof(ob); i++)
        {
                if (equip[ob[i]] == "worn")
                        ob[i]->wear();
                if (equip[ob[i]] == "wielded")
                        ob[i]->wield();
        }
        obj->write_prompt();

        return 1;
}

int help(object me)
{
  write(@HELP
指令格式 : update <檔名|here|me|玩家名>

這個指令可以更新檔案, 並將新檔的內容載入記憶體內. 若目標為
'here' 則更新所在環境. 若目標為 'me' 則更新自己的人物. 若目
標為玩家則可更新玩家物件.

HELP
    );
    return 1;
}