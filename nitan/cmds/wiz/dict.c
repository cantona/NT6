// dict.c

#define DICT_D  "/adm/daemons/dictd.c"

inherit F_CLEAN_UP;

int help(object me);
int main(object me, string arg)
{
        string sentence, encode;
        
        if( !SECURITY_D->valid_grant(me, "(wizard)") )  
                return 0;  

        if( !arg ||
            sscanf(arg, "%s to %s", sentence, encode) != 2 ) 
                return help(me);
        
        DICT_D->translate(me, sentence, encode);
        return 1;
}

int help(object me)
{
        write(@HELP
即時翻譯指令

利用 Google Translate 作即時 Mud 翻譯

目前可翻譯語言為

指令格式：dict <中文> to en      - 中文翻譯為英文
          dict <英文> to zh-CN   - 英文翻譯為中文

HELP
        );
        return 1;
}
