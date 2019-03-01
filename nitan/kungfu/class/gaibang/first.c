
#include <ansi.h>
inherit F_FIRST;

void create()
{
        set("master_dir",CLASS_D("gaibang")+"/hong");
        set("start_room", "/d/gaibang/gbxiaowu");
        ::create();
}

string zm_apply()
{
        object ob = this_player();
        if ( !query("family/beggarlvl", ob) )
                return "非丐幫有袋弟子，不能勝任掌門弟子一職。";
        return ::zm_apply();
}

