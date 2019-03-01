// hongchou.c
inherit ITEM;
void setup()
{}

void init()
{
        add_action("do_tear", "tear");
}

void create()
{
        set_name("紅綢", ({"hong chou", "chou"}));
        set_weight(800);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一塊很完整的紅綢，但已經開始變色了。\n");
                set("unit", "件");
                set("material", "cloth");
                set("no_get", "這塊紅綢已經被牢牢的釘住了。\n");
                set("cloth_count",1);

        }
        setup();
}

int do_tear(string arg)
{
        object me , ob;
        me = this_player();
        if (arg == "hong chou" && !present("zhanyi", me) && query("cloth_count")>= 1)
        {
                addn("cloth_count", -1);
                ob=new("/clone/book/zhanyi");
                ob->move("/d/meizhuang/dingduan");
                message_vision("$N把紅綢撕開，發現裏面包着一件衣服。\n", me);
                return 1;
        }
        else {
                message_vision("$N把紅綢撕開，但裏面什麼都沒有。\n", me);
                return 1;
             }
}
