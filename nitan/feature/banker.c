// banker.c
// Rewritten by Lonely@XYZX (16/05/2009)

#include <ansi.h>

#ifndef STORAGE_D
#define STORAGE_D "/adm/daemons/storaged"
#endif


#define REBOOT_CMD      "/cmds/arch/reboot"

int do_check()
{
        // here we use 3 units to display bank infos
        int total = (int)query("balance", this_player());
        if( !total || total < 0) {
                set("balance", 0, this_player());
                write("您在敝商號沒有存錢。\n");
                return 1;
        }
        write(query("name")+"悄悄告訴你：您在弊商號共存有" +
              MONEY_D->money_str(total) + "。\n");
        return 1;
}

int do_convert(string arg)
{
        string from, to;
        int amount, bv1, bv2;
        object from_ob, to_ob;
        object me;

        me = this_player();

        if( me->is_busy() )
                return notify_fail("你還是等有空了再說吧！\n");

        if( this_object()->is_fighting() )
                return notify_fail("喲，抱歉啊，我這兒正忙著呢……您請稍候。\n");

        if( !arg || sscanf(arg, "%d %s to %s", amount, from, to) != 3 )
                return notify_fail("命令格式：convert|duihuan <數量> <貨幣單位> to <新貨幣單位>\n");

        from_ob = present(from + "_money", me);
        to_ob = present(to + "_money", me);

        if( !to_ob && file_size("/clone/money/" + to + ".c") < 0 )
                return notify_fail("你想兌換成什麼？\n");

        if( !from_ob )
                return notify_fail("你身上沒有帶這種錢。\n");

        if( from_ob == to_ob )
                return notify_fail("你有毛病啊？\n");

        if( amount < 1 )
                return notify_fail("你想白賺啊？\n");

        if( (int)from_ob->query_amount() < amount )
                return notify_fail("你帶的" + query("name", from_ob) + "不夠。\n");

        bv1 = query("base_value", from_ob);
        if( !bv1 )
                return notify_fail("這樣東西不值錢。\n");

        bv2 = to_ob ? query("base_value", to_ob)
                    : query("base_value", get_object("/clone/money/" + to));

        if( !bv2 )
                return notify_fail("這樣東西不值錢。\n");

        if( bv1 < bv2 )  amount -= amount % (bv2 / bv1);
        if( amount == 0 )
                return notify_fail("這些" + query("name", from_ob) +
                                   "不夠換。\n ");

        if( bv1 > bv2 && bv1 / bv2 * amount > 20000 )
                return notify_fail("哦呦...我這一下子還拿不出這麼多散錢...\n");

        // allowed to convert now
        me->start_busy(1);

        from_ob->add_amount(-amount);

        if( !to_ob ) {
                to_ob = new("/clone/money/" + to);
                to_ob->set_amount(amount * bv1 / bv2);
                to_ob->move(me, 1);
        } else  to_ob->add_amount(amount * bv1 / bv2);

        message_vision(sprintf("$N從身上取出%s%s%s，換成了%s%s%s。\n",
                chinese_number(amount),
                query("base_unit", from_ob),
                query("name", from_ob),
                chinese_number(amount * bv1 / bv2),
                query("base_unit", to_ob),
                query("name", to_ob)), me);

        return 1;
}

int do_deposit(string arg)
{
        string what;
        int amount;
        object what_ob, me;

        me = this_player();

        if( me->is_busy() )
                return notify_fail("你還是等有空了再說吧！\n");

        if( this_object()->is_fighting() )
                return notify_fail("喲，抱歉啊，我這兒正忙著呢……您請稍候。\n");

        if( !arg || (sscanf(arg, "%d %s", amount, what) != 2 &&
            sscanf(arg, "all %s", what) != 1) )
                return notify_fail("命令格式：deposit:cun <數量>|all <貨幣單位>\n");

        what_ob = present(what + "_money", me);
        if( !what_ob )
                return notify_fail("你身上沒有帶這種錢。\n");

        if( !amount ) amount = what_ob->query_amount();
        if( amount < 1 )
                return notify_fail("你想存多少" + query("name", what_ob) + "？\n");

        if( (int)what_ob->query_amount() < amount )
                return notify_fail("你帶的" + query("name", what_ob) + "不夠。\n");

        // deposit it
        me->start_busy(1);

        addn("balance", query("base_value", what_ob) * amount, me);
        what_ob->add_amount(-amount);
        message_vision(sprintf("$N拿出%s%s%s，存進了銀號。\n",
                chinese_number(amount), query("base_unit", what_ob),
                query("name", what_ob)), me);

        MYGIFT_D->check_mygift(me, "newbie_mygift/cunqian"); 
        return 1;
}

int do_withdraw(string arg)
{
        string what, t;
        int amount;
        object what_ob, me;
        int v;

        me = this_player();

        if( me->is_busy() )
                return notify_fail("你還是等有空了再說吧！\n");

        if( this_object()->is_fighting() )
                return notify_fail("喲，抱歉啊，我這兒正忙著呢……您請稍候。\n");

        if( !arg || sscanf(arg, "%d %s", amount, what) != 2 )
                return notify_fail("命令格式：withdraw|qu <數量> <貨幣單位>\n");

        if( amount < 1 )
                return notify_fail("你想取出多少錢？\n");

        if( amount >= 10000 )
                return notify_fail("這麼大的數目。本店沒這麼多零散現金。\n");

        if( file_size("/clone/money/" + what + ".c") < 0 )
                return notify_fail("你想取出什麼錢？\n");

        t = "/clone/money/" + what;
        if( (v = amount * query("base_value", get_object(t))) > query("balance", me) || v <= 0 )
               return notify_fail("你存的錢不夠取。\n");

        me->start_busy(1);

        what_ob = new(t);
        what_ob->set_amount(amount);
        if( me->query_encumbrance() + what_ob->query_weight() > me->query_max_encumbrance() )
        {
                tell_object(me, "你的負重不夠，無法拿動這麼多錢。\n");
                destruct(what_ob);
                return 1;
        }
        what_ob->move(me, 1);
        addn("balance",  -v, me);
        //MONEY_D->pay_player(me, v, what);

        //message_vision(sprintf("$N從銀號裡取出%s。\n", MONEY_D->money_str(v)), me);
        message_vision(sprintf("$N從銀號裡取出%s%s%s。\n",
                chinese_number(amount), query("base_unit", what_ob),
                query("name", what_ob)), me);

        me->save();
        return 1;
}

int do_transfer(string arg)
{
        string who, what;
        int value;
        object me, ob;
        int amount;

        me = this_player();

        if( me->is_busy() )
                return notify_fail("你還是等有空了再說吧！\n");

        if( this_object()->is_fighting() )
                return notify_fail("喲，抱歉啊，我這兒正忙著呢……您請稍候。\n");

        if( REBOOT_CMD->is_rebooting() )
                return notify_fail("現在本站正在準備重新啟動，本錢莊暫停轉帳功能。\n");

        if( !arg || sscanf(arg, "%d %s to %s", amount, what, who) != 3 )
                return notify_fail("命令格式：transfer|zhuan <數量> <貨幣單位> to <某人>\n");

        if( amount < 1 )
                return notify_fail("你想轉帳多少錢？\n");

        if( amount > 10000000 )
                return notify_fail("這麼大的數目，有洗錢的嫌疑，本店可不敢犯法。\n");

        if( file_size("/clone/money/" + what + ".c") < 0 )
                return notify_fail("你想轉帳錢的單位是？\n");

        what = "/clone/money/" + what;
        value = amount*query("base_value", get_object(what));

        if( value > query("balance", me) || value <= 0 )
               return notify_fail("你存的錢不夠轉帳。\n");

        if( !objectp(ob = UPDATE_D->global_find_player(who)) )
                return notify_fail("沒有這個人！\n");

        me->start_busy(1);

        addn("balance", -value, me);
        addn("balance",  value, ob);
        me->save();
        ob->save();
        tell_object(ob, "\a", 0);
        tell_object(ob, HIR + me->query_idname(1) + HIR "從銀號裡劃轉"+ MONEY_D->money_str(value) + "到你的帳戶上。\n" NOR);
        tell_object(me, HIR "你從銀號裡劃轉"+ MONEY_D->money_str(value) + "到" + ob->query_idname(1) + HIR "的帳戶上。\n" NOR);
        UPDATE_D->global_destruct_player(ob, 1);
        return 1;
}

//儲物櫃業務
int do_cw(string arg)
{
        string cmd;
        object me = this_player();
        if( !arg || arg=="" ) {
                write("請使用cw help來查詢使用幫助。\n");
                return 1;
        }
        arg = lower_case(arg);
        if( arg == "help" || arg == "cancel" || arg == "list" )
                cmd = arg;
        else if( sscanf(arg,"%s %s",cmd,arg) != 2 ) {
                //dohelp2
                write("請使用cw help來查詢使用幫助。\n");
                return 1;
        }
        switch( cmd ) {
        case "open":    //開帳戶
                STORAGE_D->OpenAccount(me,arg);
                break;
        case "put":
                STORAGE_D->PutObject(me,arg);
                break;
        case "get":
                STORAGE_D->GetObject(me,arg);
                break;
        case "fee":
                STORAGE_D->DoFee(me,arg);
                break;
        case "list":
                STORAGE_D->ListObject(me);
                break;
        case "cancel":
                STORAGE_D->CancelAccount(me);
                break;
        case "help":
                STORAGE_D->ShowHelp(me);
                break;
        default:
                write("你想要做什麼啊？還是使用cw help來查看一下幫助吧！\n");
        }
        return 1;
}
