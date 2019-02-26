// block.c
// By Find.

#include <ansi.h>

string head="\t---- "+"用户賬號管理器"+" ----";

nomask int main(object me, string arg)
{
        string wiz_status;

        if (me != this_player(1)) 
                return 0;
        
        if (! SECURITY_D->valid_grant(me, "(arch)"))
                return notify_fail("只有(arch)以上的巫師才能執行對用户賬號的管理\n");
                
        seteuid(ROOT_UID);

        write("\n" + head + "\n\n\n\t1> 封鎖一個用户賬號。");
        write("\n\n\t2> 將一個已封鎖的用户賬號解封。");
        write("\n\n\t3> 查詢一個用户賬號是否被封鎖。");
        write("\n\n\t4> 列出所有被封鎖的用户賬號。\n\n\n");

        write("選擇數字(1-4)，[return] 返回上級，q 退出>");
        input_to("do_select", 0, me);
        return 1;
}

protected void do_select(string arg,object me)
{
        int s;
        string promot;

        if( arg == "" || arg == "q" )
        {
                write("ok.\n");
                return;
        }

        s = to_int(atoi(arg));
        if( (s<1) || (s>4) )
        {
                printf(CUP(2));
                write(HIY"<可選擇的數字範圍(1-4)>                                \n"NOR);
                write("選擇數字(1-4)，[return] 返回上級，q 退出>");
                input_to("do_select",0,me);
                return;
        }

        switch (s)
        {
                case 1:
                        promot = "請輸入你要封鎖的用户賬號：";
                        break;
                case 2:
                        promot = "請輸入你要解封的用户賬號：";
                        break;
                case 3:
                        promot = "請輸入你要查詢的用户賬號：";
                        break;
                case 4:
                        me->start_more(AHACK_D->blocked_list());
                        write("\n[按任意鍵繼續]\n");
                        input_to("break_point",0,me);
                        return;
                default:
                        return;
        }

        printf(CUP(1)+DELLINE);
        write(promot);
        input_to("do_process",0,s,me);
        return;
}

protected void do_process(string arg,int s,object me)
{
        if( (s<1) || (s>3) )
        {
                write("執行項目錯誤。\n");
                return;
        }

        if(arg == "")
        {
                write("\n"+head+"\n\n\n\t1> 封鎖一個用户賬號。");
                write("\n\n\t2> 將一個已封鎖的用户賬號解封。");
                write("\n\n\t3> 查詢一個用户賬號是否被封鎖。");
                write("\n\n\t4> 列出所有被封鎖的用户賬號。\n\n\n");
                write("選擇數字1-4，[return] 返回上級，q 退出>");
                input_to("do_select",0,me);
                return;
        }

        if(arg == "q")
        {
                write("ok.\n");
                return;
        }

        switch (s)
        {
                case 1:
                        printf(CUP(2));
                        if(wiz_level(me) < wiz_level(arg))
                                write(HIR"<你沒有權力封鎖一個巫師級別比你高的賬號。>\n"NOR);
                        else if(AHACK_D->block_account(arg))
                        {
                                write(HIG"<賬號 "+arg+" 已經被成功封鎖。>\n"NOR);
                                log_file("block",sprintf("%s(%s) 將賬號 %s >>>封鎖，時間 %s。\n",
                                        query("name", me),query("id", me),arg,ctime(time())));
                        }
                        else
                                write(HIY"<賬號 "+arg+" 已在封鎖列表，不能再次封鎖。>\n"NOR);
                        write("選擇數字1-4，[return] 返回上級，q 退出>");
                        input_to("do_select",0,me);
                        return;

                case 2:
                        printf(CUP(2));
                        if(AHACK_D->unblock_account(arg))
                        {
                                write(HIG"<賬號 "+arg+" 已經被成功被解封。>\n"NOR);
                                log_file("block",sprintf("%s(%s) 將賬號 %s 解封，時間 %s。\n",
                                        query("name", me),query("id", me),arg,ctime(time())));
                        }
                        else
                                write(HIY"<賬號 "+arg+" 沒有被封鎖，無法解封。>\n"NOR);
                        write("選擇數字1-4，[return] 返回上級，q 退出>");
                        input_to("do_select",0,me);
                        return;
                case 3:
                        printf(CUP(2));
                        if(AHACK_D->query_block(arg))
                                write(HIY"<賬號 "+arg+" 目前處於被封鎖狀態。>\n"NOR);
                        else
                                write(HIY"<賬號 "+arg+" 沒有被封鎖。>\n"NOR);
                        write("選擇數字1-4，[return] 返回上級，q 退出>");
                        input_to("do_select",0,me);
                        return;
                default:
                        return;
        }
}

protected void break_point(string arg,object me)
{
        write("\n"+head+"\n\n\n\t1> 封鎖一個用户賬號。");
        write("\n\n\t2> 將一個已封鎖的用户賬號解封。");
        write("\n\n\t3> 查詢一個用户賬號是否被封鎖。");
        write("\n\n\t4> 列出所有被封鎖的用户賬號。\n\n\n");

        write("選擇數字1-4，[return] 返回上級，q 退出>");
        input_to("do_select",0,me);
        return;
}


int help(object me)
{
        write(@HELP
指令格式 : block

對賬户的禁止登陸的管理。

HELP
    );
    return 1;
}