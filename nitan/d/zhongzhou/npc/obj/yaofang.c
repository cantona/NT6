inherit ITEM;

void create()
{
set_name("殘破藥方", ({"yaofang"}));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
set("unit", "張");
set("material", "paper");
        }
setup();
}
