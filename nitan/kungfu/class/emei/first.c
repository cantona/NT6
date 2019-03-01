

#include <ansi.h>
inherit F_FIRST;

void create()
{
        set("master_dir",CLASS_D("emei")+"/miejue");
        set("start_room","/d/emei/hcaguangchang");
        ::create();
}

string zm_apply()
{
        object ob = this_player();
        if (query("gender",ob) != "女性" || query("class",ob) != "bonze")
        {
                return "本門歷來由女尼接任掌門！\n";
        }
        return ::zm_apply();
}

