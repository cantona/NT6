// privateroom.c

// 凡是繼承這種房屋類型的，都可以保存房屋的描述和房屋中autoload的物品。
// 保存數據的對象，繼承者必須是/data/room/...目錄下面的文件，此時它的
// 存盤文件的名字相同，後綴不同。
//
// KEY_DOOR如果有，將是大門的位置。

#pragma save_binary

#include <ansi.h>

inherit ROOM;
inherit F_OBSAVE;
inherit F_AUTOLOAD;

int do_unlock(string arg);
int do_lock(string arg);
int do_break(string arg);
void this_open_door();
void this_close_door(int silent);
string query_save_file();

int is_private_room() { return 1; }

string room_owner_id()
{
        string rid;

        if (! stringp(rid = query("room_owner_id")))
        {
                if (sscanf(file_name(this_object()),
                           DATA_DIR "room/%s/%*s", rid) != 2)
                        return 0;
        }

        return rid;
}

int is_room_owner(object me)
{
        string rid;

        rid = room_owner_id();
        return (query("id", me) == rid || query("couple/couple_id", me) == rid);
}

int restore()
{
        // this object (/inherit/room/privateroom) doesn't need to save
        if (base_name(this_object()) + ".c" == __FILE__)
                return 0;

        return ::restore();
}

int save()
{
        int res;

        // this object (/inherit/room/privateroom) doesn't need to save
        if (base_name(this_object()) + ".c" == __FILE__)
                return 0;

        this_close_door(1);
        save_autoload();
        res = ::save();
        clean_up_autoload();
        return res;
}

void setup()
{
        ::setup();
        restore();
        //restore_autoload();
}

// the callback function of F_OBSAVE
mixed save_dbase_data()
{
        mapping data;

        data = ([ "long" : query("long"),
                  "short" : query("short"),
                  "autoload" : this_object()->query_autoload_info() ]);

        if (! undefinedp(query("room_key")))
                data += ([ "room_key" : query("room_key") ]);

        return data;
}

// the callback function of F_OBSAVE
int receive_dbase_data(mixed data)
{
        if (! mapp(data))
                return 0;

        if (! undefinedp(data["long"]))
                set("long", data["long"]);

        if (! undefinedp(data["short"]))
                set("short", data["short"]);

        if (! undefinedp(data["room_key"]))
                set("room_key", data["room_key"]);

        if (! undefinedp(data["short"]))
                this_object()->set_autoload_info(data["autoload"]);

        return 1;
}

void remove()
{
        this_close_door(1);
        save();
}

void init()
{
        if (query("KEY_DOOR"))
        {
                add_action("do_knock", "knock");
                add_action("do_unlock", "unlock");
                add_action("do_lock", "lock");
                add_action("do_unlock", "open");
                add_action("do_lock", "close");
                add_action("do_break", "break");
        }

        add_action("do_kickout", "kickout");
}

int do_kickout(string arg)
{
        string entry;
        object me, ob;
        object oob;

        if (! arg)
                return notify_fail("你要把誰踢出去？\n");

        me = this_player();
        ob = present(arg, this_object());

        if (! objectp(ob))
                return notify_fail("你看誰不順眼？\n");

        if (ob == me)
                return notify_fail("你大腦有水？\n");

        if( query("couple/couple_id", me) == query("id", ob) )
        {
                if( query("gender", me) != "女性" )
                        return notify_fail("不要亂打老婆。\n");
                else
                        return notify_fail("你幹啥？這麼兇悍。\n");
        }

        if (! is_room_owner(me))
                return notify_fail("你又不是這兒的主人，想幹什麼？\n");

        if (! query("no_fight"))
                return notify_fail("江湖上拳頭大的說話，你何不施展出真實本領？\n ");

        if( query("couple/couple_id", me) == query("room_owner_id") )
        {
                oob = UPDATE_D->global_find_player(room_owner_id());
                if (! objectp(oob))
                        return notify_fail("數據錯誤：無法查詢玩家。\n");
                entry=query("private_room/entry", oob);
                UPDATE_D->global_destruct_player(oob);
        } else
                entry=query("private_room/entry", me);

        if (! stringp(entry))
                return notify_fail("數據錯誤：無法查詢出口。\n");

        message_vision("$N大喝一聲：“快給" + RANK_D->query_self_rude(me) +
                       "滾出去！”\n說罷，飛起一腳把$n咕嚕咕嚕的踢了出去！\n",
                       me, ob);
        ob->move(entry);
        message("vision", "只聽一陣嘈雜，一人慘叫著從裡面"
                          "飛了出來，重重的落到了地上。\n",
                environment(ob), ob);
        tell_object(ob, HIR "你只覺得渾身劇痛，骨頭都麻了。\n" NOR);
        ob->receive_damage("qi", 150);
        if (! ob->is_busy())
                ob->start_busy(5);
        return 1;
}

int do_knock(string arg)
{
        object me;
        string exit;
        object room;

        if (! arg || arg != "men" && arg != "door")
                return notify_fail("你要敲什麼？\n");

        if (stringp(exit = query("KEY_DOOR/exit")) &&
            query("exits/" + exit))
                return notify_fail("這裡的門是開的，你敲它幹什麼。\n");

        if (! query("room_key"))
                return notify_fail("在這裡開門又不用鑰匙，你亂敲什麼。\n");

        me = this_player();
        message_vision("$N走上前去，“篤篤篤”輕輕敲了幾下門。\n", me);

        if (objectp(room = find_object(query("KEY_DOOR/room"))))
                message("vision", "“篤篤篤”的幾聲輕響，好像有人在外"
                        "面敲門。\n", room);

        return 1;
}

int do_unlock(string arg)
{
        object me;
        string exit;

        if (! arg || arg != "men" && arg != "door" && arg != "gate")
                return notify_fail("你要打開什麼？\n");

        if (! stringp(exit = query("KEY_DOOR/exit")))
                return notify_fail("這裡沒有門需要打開。\n");

        if (query("exits/" + exit))
                return notify_fail("這裡的門是開的，不必多此一舉了。\n");

        me = this_player();
        if (stringp(query("room_key")))
        {
                if (! present(query("room_key"), me) )
                {
                        message("vison", me->name() + "鬼鬼祟祟的在門口搞了"
                                         "半天，不知道在幹什麼。\n",
                                         this_object(), ({ me }));
                        tell_object(me, "你費了半天勁，也沒有打開鎖，看來是"
                                        "鑰匙不對。\n");
                        return 1;
                }

                message_vision("$N走到門前，摸出鑰匙，輕輕一扭，啪的一聲，"
                               "門開了。\n", me);
        } else
                message_vision("$N走到門前，輕輕一轉打開了門。\n", me);

        this_open_door();
        return 1;
}

int do_lock(string arg)
{
        string exit;

        if (! arg || arg != "men" && arg != "door" && arg != "gate")
                return notify_fail("你要鎖上什麼？\n");

        if (! stringp(exit = query("KEY_DOOR/exit")))
                return notify_fail("這裡沒有門需要關上。\n");

        if (! query("exits/" + exit))
                return notify_fail("這裡的門已經鎖上了，不必多此一舉了。\n");

        message_vision("$N隨手一帶門，“□當”一聲門鎖上了。\n",
                       this_player());
        this_close_door(1);
        return 1;
}

int do_break(string arg)
{
        if (! arg || arg != "men" && arg != "door" && arg != "gate")
                return notify_fail("你要破壞什麼？\n");

        if (is_room_owner(this_player()))
                return notify_fail("你有毛病啊？砸自己的門，要是"
                                   "沒了鑰匙配一把。\n");

        write("你膽子不小，居然敢擅闖民宅？\n");
        return 1;
}

void this_open_door()
{
        string exit;
        string room;
        object ob;

        if (! stringp(exit = query("KEY_DOOR/exit")))
                return;

        if (! stringp(room = query("KEY_DOOR/room")))
                return;

        set("exits/" + exit, room);

        if (! (objectp(ob = find_object(room))))
                 catch(ob = load_object(room));

        if (! ob) return;

        message("vision", "\n“卡啦”一聲門從那邊被人打開了。\n", ob);
        ob->set("exits/"+query("KEY_DOOR/exit", ob),
                query("KEY_DOOR/room", ob));

        remove_call_out("this_close_door");
        call_out("this_close_door", 10);
}

void this_close_door(int silent)
{
        string exit;
        string room;
        object ob;

        if (! stringp(exit = query("KEY_DOOR/exit")) ||
            ! query("exits/" + exit))
                return;

        if (! silent)
                message("vision", "\n一陣風吹來，“□當”一聲門關上了。\n",
                        this_object());
        delete("exits/" + exit);

        if (! (room = query("KEY_DOOR/room")))
                return;

        if (ob != find_object(room))
                 catch(ob = load_object(room));

        if (! ob) return;

        message("vision", "\n“□當”一聲門關上了。\n", ob);
        delete("exits/"+query("KEY_DOOR/exit", ob), ob);
}

string query_save_file()
{
        string file;
        string arg;

        file = base_name(this_object());
        if (! file || ! sscanf(file, "/data/room/%s", arg)) return 0;

        return file;
}