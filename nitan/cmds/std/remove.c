// remove.c

#include <ansi.h>

inherit F_CLEAN_UP;

int do_remove(object me, object ob);

int main(object me, string arg)
{
        object ob, *inv;
        int i;
        int count;

        if (! arg) return notify_fail("你要脫掉什麼？\n");

        if (arg == "all")
        {
                inv = all_inventory(me);
                for (count = 0, i = 0; i < sizeof(inv); i++)
                        count += do_remove(me, inv[i]);
                if (count)
                        write("你脫完了。\n");
                else
                        write("你什麼都沒有脫下來。\n");
                return 1;
        }

        if (! objectp(ob = present(arg, me)))
                return notify_fail("你身上沒有這樣東西。\n");

        if( query("equipped", ob) != "worn" )
        {
                inv = all_inventory(me);
                for (count = 0, i = 0; i < sizeof(inv); i++) {
                        if( !inv[i]->id(arg) )
                                continue;

                        if( query("equipped", inv[i]) != "worn" )
                                continue;

                        ob = inv[i];
                        count++;
                        break;
                }

                if (! count)
                        return notify_fail("你並沒有裝備這樣東西。\n");
        }

        return do_remove(me, ob);
}

int do_remove(object me, object ob)
{
        string str;

        if( query("equipped", ob) != "worn" )
                return notify_fail("你並沒有裝備這樣東西。\n");

        if (ob->unequip())
        {
                if( !stringp(str=query("remove_msg", ob)) )
                        switch(query("armor_type", ob)){
                                case "cloth":
                                case "armor":
                                case "surcoat":
                                case "boots":
                                        str = YEL "$N將$n" YEL "脫了下來。\n" NOR;
                                        break;
                                case "bandage":
                                        str = YEL "$N將$n" YEL "從傷口處拆了下來。\n" NOR;
                                        break;
                                default:
                                        str = YEL "$N卸除$n" YEL "的裝備。\n" NOR;
                        }
                if( query_temp("no_wear", ob) )
                        str += "脫下" + ob->name() + "以後你覺得舒服多了。\n";
                message_vision(str, me, ob);
                return 1;
        } else
                return 0;
}

int help(object me)
{
        write(@HELP
指令格式 : remove all | <物品名稱>
 
這個指令讓你脫掉身上某件防具.
 
HELP );
        return 1;
}
 