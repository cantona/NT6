//查詢遊戲交費時間的命令，直接從數據庫取數據，應該禁止頻繁讀取
//Write By JackyBoy@XAJH 2001/5/15
#include <ansi.h>

inherit F_CLEAN_UP;

class channel_class
{
        int level, number;
        string msg;
        mapping extra;
}
mapping channels;
string *chann;
string cmdhelp=
"選單命令格式：<"HIR"頻道"HIG">   <"HIR"命令"HIG">\n"+
"其中頻道為你可以設置和使用的頻道的英文名，比如"HIC"chat"HIG","HIM"rumor"HIG"等\n"+
"而命令為"HIR"public"HIG","HIR"main"HIG"或者"HIR"none"HIG"，其中：\n"+
HIR"public"HIG"表示開啟頻道並將信息顯示到公共信息窗口\n"+
HIR"main  "HIG"表示開啟頻道並將信息顯示到主信息窗口中\n"+
HIR"none  "HIG"表示將頻道關閉，不再接收頻道信息\n"+
"你也可以輸入"HIR"exit"HIG"退出命令選單，或輸入"HIR"help/?"HIG"獲取本信息！\n";

int do_chan(string,object,int);
int show_main(object);

int main(object me,string arg)
{
        channels=CHANNEL_D->query_chann();
        chann=keys(channels);
        //非巫師就過濾掉這些巫師頻道設置
        if(!wizardp(me)) chann -= ({"wiz","sys","debug","nch"});
        chann -= ({"shout"});
        
        if(arg)
                return do_chan(arg,me,1);
        show_main(me);
        return 1;
}

int show_main(object me)
{
        class channel_class ch;
        string *tuned_ch;
        string s,str,state;
        
        ch = new(class channel_class);
        //tuned_ch=query("channels", me);
        tuned_ch = CHANNEL_D->query_using_channel(me, 1);

        str=me->name()+"的頻道設置為：\n"HIC"≡"HIY"──────────────────────────────"HIC"≡\n"NOR;
        str+=sprintf(HIC" %-10s        %-8s         %-8s\n\n","頻道命令","頻道名稱","頻道狀態");
        foreach(s in chann)
        {
                ch = copy(channels[s]);
                if( !pointerp(tuned_ch) || !sizeof(tuned_ch) ) state=HIG"關閉";
                else if(member_array(s,tuned_ch)==-1) state=GRN"關閉";
                else if( query("chann/"+s, me))state=HIC"主窗口";
                else state=HIY"公共窗口";
                str+=sprintf(WHT"[%-10s]       [%-8s]        %-8s\n",s,ch->msg,state);
        }
        str+="\n"HIC"≡"HIY"──────────────────────────────"HIC"≡\n"NOR;
        str+="請輸入命令("HIY"help"NOR"看幫助，"HIY"exit"NOR"退出)：";
        write(str);
        input_to( (: do_chan :) ,me);
        return 1;
}


void open_ch(object me,string arg)
{
        class channel_class ch; 
        mapping channels = fetch_variable("channels", get_object(CHANNEL_D)); 
        int my_channels = query("channels", me);
        
        if( undefinedp(ch = channels[arg]) || !classp(ch) ) 
                return;
        
        set("channels", my_channels | ch->number, me); 
        CHANNEL_D->register_channel(me, ch->number); 
}

int do_chan(string arg,object me,int once)
{
        string ch,cmd;
        int tmp;
        
        if(!arg)
        {
                write("\n請輸入命令("HIY"help"NOR"看幫助，"HIY"exit"NOR"退出)：");
                input_to( (: do_chan :) ,me);
                return 1;
        }               
        arg=lower_case(arg);
        arg=me->remove_leading_space(arg);
        while(strsrch(arg,"  ")!=-1) arg=replace_string(arg,"  "," ");
        switch(arg)
        {
                case "?":
                case "help":
                        //顯示幫助信息
                        write(HIG+cmdhelp+NOR);
                        break;
                case "q":
                case "quit":
                case "exit":
                        write(HIG"退出頻道設置程序。。。\n"NOR);
                        once=1;break;
                default:
                        //進行程序處理
                        tmp=0;
                        if(sscanf(arg,"%s %s",ch,cmd)==2)
                        {
                                switch(cmd)
                                {
                                        case "public":
                                                if(member_array(ch,chann)!=-1)
                                                {
                                                        open_ch(me,ch);
                                                        delete("chann/"+ch, me);
                                                        write(HIG"你打開了" + channels[ch]["name"] + "頻道。\n"NOR);
                                                }
                                                else write(HIG"頻道錯誤！沒有"+HIY+"ch"+HIG+"這個頻道！\n"NOR);
                                                break;
                                        case "main":
                                                if(member_array(ch,chann)!=-1)
                                                {
                                                        open_ch(me,ch);
                                                        set("chann/"+ch, 1, me);
                                                        write(HIG"你打開了" + channels[ch]["name"] + "頻道。\n"NOR);
                                                }
                                                else write(HIG"頻道錯誤！沒有"+HIY+"ch"+HIG+"這個頻道！\n"NOR);
                                                break;
                                        case "none":
                                                if(member_array(ch,chann)!=-1)
                                                {
                                                        set("channels",query("channels",  me)-({ch}), me);
                                                        write(HIG"你關閉了" + channels[ch]["name"] + "頻道。\n"NOR);
                                                }
                                                else write(HIG"頻道錯誤！沒有"+HIY+"ch"+HIG+"這個頻道！\n"NOR);
                                                break;
                                        default:
                                                tmp=1;
                                }
                        }
                        else tmp=1;
                        if(tmp)
                                write(HIG+cmdhelp+NOR);
        }
        if(!once) show_main(me);
        return 1;
}

int help()
{
        write(@HELP
指令格式 : chann                         (菜單模式)
           chann    <命令串>             (直接指定)

這個指令可以讓你自由設置頻道信息的顯示，關閉或者顯示位置。
顯示位置有main（主窗口）和public（公共信息窗口）兩個選擇。
如果位置設置為沒有（none），則表示要關閉該頻道。

命令串格式為：<頻道> < main | public | none>
頻道為你要進行操作的頻道名稱，後面跟著的是none表示要關閉該
頻道，跟著main表示要打開頻道並將信息顯示在主區域窗口，如果
是public則顯示到公共信息區域窗口。

直接指定的命令模式例子：
chann chat none    ── 此操作為將chat頻道關閉
chann chat main    ── 此操作將打開chat頻道並顯示到主窗口
chann rumor public ── 此操作將在公共窗口打開rumor頻道
HELP );
    return 1;
}

