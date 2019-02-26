inherit ITEM;

#define FEITUO     "/clone/lonely/feituo"

void create()
{
        object ob;
        set_name("枯乾的骸骨", ({ "Skeleton", "skeleton", "骸骨" }));
        set_weight(500);
        set_max_encumbrance(800000);
        set("unit", "副");
        set("long", "這副骸骨已經躺在這裏很久了。\n");
        set("value", 1);
        set("no_get", "這東西一碰就散，還是別揀吧！\n");
        if (clonep())
        {
                set_default_object(__FILE__);
                ob = find_object(FEITUO);
                if (! ob) ob = load_object(FEITUO);
                if (! environment(ob))
                        ob->move(this_object());
            }
}