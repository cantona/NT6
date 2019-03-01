// upemote.c
inherit F_CLEAN_UP;
#include <ansi.h>
int main(object me)
{
        mapping emote;
        string *str,arg="";
        int i;                

        if( !SECURITY_D->valid_grant(me, "(admin)") )
                return 0;
                
        str=sort_array(EMOTE_D->query_all_emote(), 1);
        for (i=0;i<sizeof(str);i++){
        emote = EMOTE_D->query_emote(str[i]);
//不指定對象使用這個 emote 時，你自己看到的訊息：
        if( stringp(arg = emote["myself"]) ) {
                arg = replace_string(arg, "$N", "$P");
                arg = replace_string(arg, "$p", "$P");
                arg = replace_string(arg, "你", "$P");
                arg = replace_string(arg, "在下", "$S");
                arg = replace_string(arg, "大爺我", "$s");
                emote["myself"]=arg;
        }
//不指定對象使用這個 emote 時，其他人看到的訊息：
        if( stringp(arg = emote["others"]) ) {
                arg = replace_string(arg, "$P", "$N");
                arg = replace_string(arg, "$p", "$N");
                arg = replace_string(arg, "在下", "$S");
                arg = replace_string(arg, "大爺我", "$s");
                emote["others"]=arg;
        }
//對自己使用這個 emote 時，自己看到的訊息：
        if( stringp(arg = emote["myself_self"]) ) {
                arg = replace_string(arg, "$N", "$P");
                arg = replace_string(arg, "$p", "$P");
                arg = replace_string(arg, "你", "$P");
                arg = replace_string(arg, "在下", "$S");
                arg = replace_string(arg, "大爺我", "$s");
                emote["myself_self"]=arg;
        }
//對自己使用這個 emote 時，其他人看到的訊息：
        if( stringp(arg = emote["others_self"]) ) {
                arg = replace_string(arg, "$P", "$N");
                arg = replace_string(arg, "在下", "$S");
                arg = replace_string(arg, "大爺我", "$s");
                emote["others_self"]=arg;
        }
//對別人使用這個 emote 時，自己看到的訊息：
        if( stringp(arg = emote["myself_target"]) ) {
                arg = replace_string(arg, "$N", "$P");
                arg = replace_string(arg, "$p", "$P");
                arg = replace_string(arg, "你", "$P");
                arg = replace_string(arg, "他", "$n");
                arg = replace_string(arg, "在下", "$S");
                arg = replace_string(arg, "大爺我", "$s");
                emote["myself_target"]=arg;
        }
//對別人使用這個 emote 時，使用對象看到的訊息：
        if( stringp(arg = emote["target"]) ) {
                arg = replace_string(arg, "$n", "$p");
                arg = replace_string(arg, "$P", "$N");
                arg = replace_string(arg, "你", "$p");
                arg = replace_string(arg, "在下", "$S");
                arg = replace_string(arg, "大爺我", "$s");
                emote["target"]=arg;
        }
//對別人使用這個 emote 時，除你自己和使用對象外，其他人看到的訊息：
        if( stringp(arg = emote["others_target"]) ) {
                arg = replace_string(arg, "$P", "$N");
                arg = replace_string(arg, "$p", "$n");
                arg = replace_string(arg, "在下", "$S");
                arg = replace_string(arg, "大爺我", "$s");
                emote["others_target"]=arg;
        }
        EMOTE_D->set_emote(str[i], emote);
        }
        return 1;
}
int help(object me)
{
write(@HELP
指令格式 : upemote
 
這個指令可以自動修正 emote 中的一些錯誤。
HELP
    );
    return 1;
}