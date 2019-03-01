// coat.c

#include <ansi.h>
#include <armor.h>

inherit CLOTH;

string do_wear();

void create()
{
        set_name(HIY "棉衣" NOR, ({ "cutton padded", "cutton" }) );
        set_weight(8000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("material", "cloth");
                set("armor_prop/armor", 5);
                set("armor_prop/warm", 20);
                set("value", 2000);
                set("wear_msg", (: do_wear :));
        }
        setup();
}

string do_wear()
{
        object me;
        string msg;
        int per;

        me = this_player();
        per=query("per", me);
        if( query("gender", me) == "女性" )
        {
                if (per >= 30)
                        msg = HIC "$N" HIC "輕輕將一件$n" HIC "披在身上，神態曼妙之極。\n";
                else if (per >= 25)
                        msg = HIG "$N" HIG "把$n" HIG "展開，披在身上。\n";
                else if (per >= 20)
                        msg = YEL "$N" YEL "把$n" YEL "披在身上，縮了縮脖子。\n";
                else    msg = YEL "$N" YEL "毛手毛腳的把$n" YEL "披在身上。\n";
        } else
        {
                if (per >= 30)
                        msg = HIC "$N" HIC "隨手一揮，將$n" HIC "披在身上，姿勢瀟洒之極。\n";
                else if (per >= 25)
                        msg = HIG "$N" HIG "把$n" HIG "展開，披在身上。\n";
                else if (per >= 20)
                        msg = YEL "$N" YEL "把$n" YEL "披在身上，扯了扯衣角，縮了縮脖子。\n";
                else    msg = YEL "$N" YEL "毛手毛腳的把$n" YEL "披在身上，甚是猥瑣。\n";
        }
        return msg;
}

int query_autoload()
{
        return 1;
}