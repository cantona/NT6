
#include <ansi.h>
inherit F_FIRST;

void create()
{
        set("master_dir",CLASS_D("xueshan")+"/jiumozhi");
        set("start_room","/d/xueshan/dadian");
        ::create();
}

string zm_apply()
{

        object ob = this_player();
        if (query("class", ob) != "bonze")
        {
                return "你非我雪山僧眾，豈能出任掌門弟子一職！";
        }
        return ::zm_apply();
}
