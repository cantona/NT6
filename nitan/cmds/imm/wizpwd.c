// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// wizpwd.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;
        
        if (! SECURITY_D->valid_grant(me, "(immortal)")) 
                return 0; 

        if( me != this_player(1) ) return 0;

        ob=query_temp("link_ob", me);
        if( !ob ) return 0;
        while(ob && ob->is_character())ob=query_temp("link_ob", ob);

        write("為了安全起見，請先輸入您原來的密碼：");
        input_to("get_old_pass", 1, ob);
        return 1;
}

protected void get_old_pass(string pass, object ob)
{
        string old_pass;

        write("\n");
        old_pass=query("wizpwd", ob);
        if( query("wizpwd", ob) )
        {
            if(crypt(pass, old_pass)!=old_pass ) {
                write("密碼錯誤！\n");
                return;
            }
        }
        write("請輸入新的密碼：");
        input_to("get_new_pass", 1, ob );
}

protected void get_new_pass(string pass, object ob)
{
        write("\n請再輸入一次新的密碼：");
        input_to("confirm_new_pass", 1, ob, crypt(pass,0));
}

protected void confirm_new_pass(string pass, object ob, string new_pass)
{
        write("\n");
        if( crypt(pass, new_pass)!=new_pass ) {
                write("對不起，您輸入的密碼並不相同，繼續使用原來的密碼。\n");
                return;
        }
        seteuid(getuid());
        if( !set("wizpwd",new_pass,ob) ){
                write("密碼變更失敗！\n");
                return;
        }
         
        set("wizpwd", new_pass, ob);
        ob->save();
        write("密碼變更成功。\n");
}

int help(object me)
{
        write(@HELP
指令格式 : passwd
 
這個指令可以修改wiz的第二重密碼。
 
HELP
        );
        return 1;
}
