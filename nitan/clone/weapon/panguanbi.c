//Cracked by Roath
// Jay 7/11/96

#include <weapon.h>
inherit CLUB;

void create()
{
    set_name("判官筆", ({"panguan bi", "bi"}));
    set_weight(2000); 
    if( clonep() )
      set_default_object(__FILE__);
    else {
      set("long", "這是一支精鋼所鑄的判官筆，長一尺六寸，"
                "筆頭縛有一簇沾過墨的羊毛。\n");
        set("unit","支");
        set("value",200);
        set("wield_msg","$N把判官筆取在手中，說：你我好朋友，我這禿筆上就不蘸墨了。\n");
        set("unwield_msg","$N把收了起來。\n");
        set("material", "iron");
    }
    init_club(30);

    setup();
}