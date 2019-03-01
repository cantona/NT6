// baiyubi.c

inherit ITEM;

void create()
{
        set_name("白玉筆", ({ "baiyu bi", "bi" }));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "支");
                set("long", "晶瑩剔透的的漢白玉琢磨的筆形飾物。\n");
                set("value", 3000);
                set("material", "stone");
        }
        setup();
}