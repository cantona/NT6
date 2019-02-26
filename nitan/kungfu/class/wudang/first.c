#include <ansi.h>
inherit F_FIRST;

void create()
{
        set("master_dir",CLASS_D("wudang")+"/zhang");
        set("start_room","/d/wudang/guangchang");
        ::create();
}

string zm_apply()
{
        object ob = this_player();
        if( query("class", ob) != "taoist" )
        {
                return "本門修真之士，方能執掌門户！";
        }       
        return ::zm_apply();
}
