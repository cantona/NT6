#include <ansi.h>

#define CH_ID           (1<<0)
#define CH_NAME         (1<<1)

#define DEFAULT         CH_ID | CH_NAME
#define HELP            "/cmds/usr/color"

inherit F_CLEAN_UP;

string help = @HELP
更改使用者資訊

此指令可用來更改使用者資訊如下：

-i      修改玩家英文代號色彩
-n      修改玩家中文名稱及色彩

如不加參數則表示全部修改

指令格式:
changeinfo [-i] [-n]

相關指令: finger, nick
HELP;

protected void change_prompt(object me, int flag);
protected void change_input(object me, int flag, string arg);

int main(object me, string arg)
{
        int flag;
        
#ifndef NO_FEE
        if ( !me->is_vip() )
                return notify_fail("你不是會員,無權使用該指令。\n");
#endif
                
        if( arg )
        {
                if( sscanf(arg, "%*s-i%*s", arg) == 2 ) flag |= CH_ID;
                if( sscanf(arg, "%*s-n%*s", arg) == 2 ) flag |= CH_NAME;
        }
        if( !flag ) flag = DEFAULT;
        tell_object(me, "跳過請輸入 [ENTER]，取消請輸入 '~q'，色彩協助請輸入 '~h'\n");
        tell_object(me, WHT"["HIW"Change Information"NOR + WHT"]————————————————\n"NOR);
        change_prompt(me, flag);
        return 1;
}
protected void change_prompt(object me, int flag)
{
        if( flag & CH_ID )
        {
                tell_object(me,"\nID-["+query("id", me)+"]\n");
                tell_object(me, "請輸入你的彩色英文代號：");
                input_to( (: change_input, me, flag :), 2 );
        }
        else if( flag & CH_NAME )
        {
                tell_object(me,"\nNAME-["+query("name", me)+"]\n");
                tell_object(me, "請輸入你的彩色中文名稱：");
                input_to( (: change_input, me, flag :), 2 );
        }

        return;
}
protected void change_input(object me, int flag, string arg)
{
        string *res;
        string text;
        
        text = arg;
        arg = filter_color(arg);

#ifdef CONFIG_NON_UTF8
        if( arg && query_temp("big5", me) )
                text = LANGUAGE_D->Big52GB(text);
#endif

        if( !arg ) arg = "";

        if( arg == "~q" )
        {
                tell_object(me, "取消輸入。\n");
                return;
        }
        if( arg == "~h" )
        {
                HELP->main(me);
                return change_prompt(me, flag);
        }
        if( flag & CH_ID )
        {
                if( arg == "" )
                        tell_object(me, "跳過彩色英文代號設定。\n");
                else
                {
                        if( !(res = me->set_idname(text, 0)) )
                        {
                                tell_object(me, "新設定的英文代號與原有英文代號不同，請重新設定。\n");
                                return change_prompt(me, flag);
                        }
                        tell_object(me, "彩色英文代號 '"+ res[0] +"' 設定完成。\n");
                }
                flag ^= CH_ID;
        }
        else if( flag & CH_NAME )
        {
                int len;

                if( arg == "" )
                        tell_object(me, "跳過彩色中文名稱設定。\n");
                else
                {
                        arg = filter_color(trans_color(text,3),1);
                        len = strlen(arg);
                        if( len > 10 || len < 2 )
                        {
                                tell_object(me, "中文名稱必須在 1 到 5 箇中文字之間，請重新設定。\n");
                                return change_prompt(me, flag);
                        }
                        if (! is_chinese(filter_color(arg)))
                        {
                                tell_object(me, "請使用「中文」取名字，請重新設定。\n");
                                return change_prompt(me, flag);
                        }

                        if( !(res = me->set_idname(0, text)) )
                        {
                                tell_object(me, "新設定的中文名稱與原有中文名稱不同，請重新設定。\n");
                                return change_prompt(me, flag);
                        }
                        tell_object(me, "彩色中文名稱 '" + res[1] + "' 設定完成。\n");
                }
                flag ^= CH_NAME;
        }

        if( flag ) return change_prompt(me, flag);
        return;
}

int help()
{
        write(@HELP
更改使用者資訊

此指令可用來更改使用者資訊如下：

-i      修改玩家英文代號色彩
-n      修改玩家中文名稱及色彩

如不加參數則表示全部修改

指令格式:
changeinfo [-i] [-n]

相關指令: finger, nick
HELP);
        return 1;
}
