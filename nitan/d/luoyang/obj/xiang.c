// xiang.c
#include <ansi.h>
inherit ITEM;
int do_chuangli(string arg);

int do_weapon();
object creat_weapon();

void create()
{
        set_name("關帝像", ({ "guandi xiang", "xiang" }) );
        set("gender", "男性" );
        set("unit", "尊");
        set("value", 1);
        set("kar", random(21));
        set("no_get", 1);
        set("no_put", 1);
        set("no_get_from", 1);
        set("long",         
"這是一尊三人像。前坐者"HIG"綠衫"HIR"赤面"NOR"，右手捋髯，左手正執竹簡，正是
關帝夜讀春秋像。後立者，左手一位"HIW"銀甲白面"NOR"，手捧令旗，正是關平。
右手一將，"BLK"黑面皂袍"NOR"，手握"HIC"青龍偃月刀"NOR"的，便是周倉了。\n");
}

/*
void init()
{
        add_action("do_chuangli","chuangli");
        add_action("do_chuangli","kaibang");
}
*/

int do_chuangli(string arg)
{
        string *line, file;
        int i, j;
        object ob, me = this_player();

        if (!arg) return notify_fail("你要創立什麼幫、教、會？\n");

        file = read_file("/log/PARTY");
        line = explode(file, "\n");
        for(j = 0; j < sizeof(line); j ++)
        {
                if (line[j] == arg)
                        return notify_fail(arg+"已經存在，不用你費心創立。\n");
        }
        if( query("age", me)<50 && !wizardp(me) )
                return notify_fail("你還嫩著呢！還想創立幫會？\n");
        if( query("combat_exp", me)<5000000 )
                return notify_fail("憑你這麼點能耐，還想創立幫會？\n");
        if( query("party", me) )
                return notify_fail("你現在還是"+query("party/party_name", me)+"中人。不退出來，不能創立幫會。\n");
        i = strlen(arg);

        if( (strlen(arg) < 4) || (strlen(arg) > 8 ) )
        {
                write("對不起，幫派的中文名字必須是 2 到 4 個中文字。\n");
                return 0;
        }
        while(i--)
        {
                if( arg[i]<=' ' )
                {
                        write("幫派名字不能用控制字元。\n");
                        return 0;
                }
                if( i%2==0 && !is_chinese(arg[i..<0]) )
                {
                        write("幫派名字必須是「中文」。\n");
                        return 0;
                }
        }
        i = strlen(arg);
        if ((arg[i-2..i]=="教") || (arg[i-2..i]=="幫") || (arg[i-2..i]=="門"))
        {
                if( query("kar", me)-query("kar", this_object())<11 )
                {
                        set("party/party_name", arg, me);
                        set("party/rank", arg[i-2..i]+"主", me);
                        set("party/level", 1, me);
                        set("party/player", 1, me);
                        set("party/enter_time", time(), me);
                        seteuid(getuid());
                        ob=new("/d/luoyang/obj/yaopai");
                        ob->move(me);
message_vision("$N點起三柱香，沖著關帝像拜了下去：弟子創立"+arg+"，志在
匡扶正義，除惡揚善。蒙關帝護佑，今日終于開壇。此後當得
約束幫眾，同踐此誓。若有不肖匪類，壞我幫規，天厭之！天
厭之！！\n", me);
                        message_vision("$N獲得一塊腰牌！\n",me);
                        message("channel:chat",HIY"【通告】"HIR+query("name", me)+"于"+NATURE_D->game_time()+"創立"+arg+"！\n"NOR,users());
                        log_file("PARTY", arg+"\n");
                }
                else return notify_fail("關林裡一陣陣陰風吹過，看來今天不是開幫會的黃道吉日。改天再來吧。\n");
        }
        else return notify_fail("幫會名稱只能以教、幫、門結尾。\n");
        return 1;
}
