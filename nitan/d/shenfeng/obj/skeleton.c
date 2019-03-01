inherit ITEM;

void create()
{
        set_name("枯乾的骸骨", ({ "Skeleton", "skeleton", "骸骨" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
            else {
                set("unit", "具");
                set("long", "這副骸骨已經躺在這裡很久了。\n");
                set("value", 1);
                set("no_get", "這東西一碰就散，還是別揀吧！\n");
            }
}