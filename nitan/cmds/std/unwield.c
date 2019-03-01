// unwield.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob, *inv;
        string str;
        int i;
        int count;

        if( !arg ) return notify_fail("你要放下什麼？\n");

        if( !objectp(ob = present(arg, me)) )
                return notify_fail("你身上沒有這樣東西。\n");

        if( query("equipped", ob) != "wielded"){
                inv = all_inventory(me);
                for (count = 0, i = 0; i < sizeof(inv); i++) {
                        if( !inv[i]->id(arg) )
                                continue;

                        if( query("equipped", inv[i]) != "wielded" )
                                continue;

                        ob = inv[i];
                        count++;
                        break;
                }

                if( !count )
                        return notify_fail("你並沒有裝備這樣東西作為武器。\n");
        }

        if( ob->unequip() ) {
                if( !stringp(str=query("unwield_msg", ob)) && !stringp(str=ob->do_unwield()) )
                        str = "$N放下手中的$n。\n";
                message_vision(str, me, ob);
                return 1;
        } else
                return 0;
}

int help(object me)
{
  write(@HELP
指令格式 : unwield <物品名>
 
這個指令讓你放下手中的武器。
 
HELP
    );
    return 1;
}
 