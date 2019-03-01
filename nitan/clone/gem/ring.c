#include <ansi.h>
#include <armor.h>

inherit S_RING;
inherit F_AUTOLOAD;

void create()
{
        set_name(HIC"魔法戒指"NOR, ({ "magic ring", "ring" }));
        set("long", HIC"這是一個從遠古流傳下來的戒指，上面刻著一些奇怪的咒語。\n"NOR);
        set("weight", 400);
        set("unit", "個");
        set("value", 5000000);
        set("material", "gem");
        set("armor_prop/armor", 10);
        set("armor_type", TYPE_FINGER);
        set("no_put",1);
        set("no_beg",1);
        set("no_steal",1);
        set("no_clone",1);
        set("no_pawn",1);
        set("no_beg",1);
        set("no_steal",1);
        setup();
}        

int query_autoload() { return 1; }
