// /d/obj/miling.c 密令

#include <ansi.h>
inherit ITEM;

string * help_str=({
"這封密令是要你去保護一位人質，將之送到安全的地點去。在途中，
不斷會有各種殺手截殺人質，而人質本身是不堪一擊的。途中會遇到
各種各樣的狀況，需要靠你自己的智慧去解決。\n",
"對人質而言：提供瞭如下命令以便保護者（你）使用：",
"baohu : 這條命令可以使人質處於“被保護”狀態，而你將成為“保
        護者”，任何施加於人質的攻擊都會自動地轉施加在你身上
        （當然，需要你和人質在同一房間內）；",
"order ：這條命令可以“命令”人質做某件事；",
"        比如：order go east “命令”人質往東方走；",
"        具體可採用的命令可在實踐中得到；\n",
"在護送過程中，當然你需要不斷地用hp來查看人質的健康情況。一旦
人質到達目的地後，你將得到很高的獎勵（具體獎勵值視途中艱苦情
況而定）。",
});

string * search = get_dir("/d/");

int find_outdoor(string);

void init()
{
        add_action("do_read", "readling");
        add_action("do_help", "helpling");
        add_action("do_where", "whereis");
}

void create()
{
        set_name(HIY"密令"NOR, ({"mi ling", "ling", "ml"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long",
                "這是一張已經發黃的紙，上面歪歪曲曲地寫着一些字，\n你可以用指令(readling)來讀取，\n用指令(helpling)來看幫助，\n用指令(whereis)看地點説明。\n");
                set("value", 0);
                set("material","paper");
                set("unit", "紙");
//                set("no_get", 1);
//                set("no_put", 1);
//                set("no_drop", 1);
                set("describe","");
                set("src_add","");
                set("src_des","");
                set("dest_add","");
                set("dest_des","");
        }
}

int do_read()
{
        object me = this_player();

        tell_object(me,HIG"你這次的任務是："+query("describe")+"。\n"NOR);
        return 1;
}

int do_help()
{
        object me = this_player();
        int i;

        for (i=0;i<sizeof(help_str);i++)
                tell_object(me,HIY + help_str[i] +"\n"+NOR);
        return 1;
}

int do_where()
{
        object me = this_player();
        int i;
        string where;

        i = find_outdoor(query("src_des"));
        where = i < sizeof(search) ? to_chinese(search[i]) : "哪個地方的";
        tell_object(me,HIG"人質好像在"+where+"的"+query("src_add")+"\n"NOR);
        i = find_outdoor(query("dest_des"));
        where = i < sizeof(search) ? to_chinese(search[i]) : "哪個地方的";
        tell_object(me,HIG"要護送到好像在"+where+"的"+query("dest_add")+"\n"NOR);
        return 1;
}

int find_outdoor(string arg)
{
        int i = 0;

        while ( i < sizeof(search) ) {
                if (search[i] == arg)
                        return i;
                i ++;
        }
        return i;
}
