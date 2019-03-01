 // staff.c
#include <weapon.h>
inherit STAFF; 
void create() {
        set_name("骨杖", ({ "bone staff" }) );
        set_weight(2000);
        set("maze_item",1); 
        set("no_put",1);
        if(clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("long", "這是一根不知道什麼的骨頭做成的法杖。");
                set("value", 300);
                set("material", "wood");
                set("wield_msg", "$N把$n緊緊地握在手中。\n");
                set("unwield_msg", "$N鬆開了手中的$n。\n");
        }
        ::init_staff(30);
}