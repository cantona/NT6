

#include <ansi.h>
inherit F_FIRST;

void create()
{
        set("master_dir",CLASS_D("gumu")+"/longnv");
        set("start_room","/d/gumu/qianting");
        ::create();
}

string zm_apply()
{
        object ob = this_player();
/*
        if (query("gender", ob) != "女性")
        {
                return "本派只有女子才能接任掌門弟子一職！";
        }
*/
        return ::zm_apply();
}


