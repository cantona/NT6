inherit ITEM;

void create()
{
        set_name( "桌子",({"table" }));
        set_weight(30000);
        set_max_encumbrance(18000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "張");
                set("material", "wood");
                set("value", 2000);
                set("long", "這張破桌子放在這裏很久了，上面放了一個八卦盤，和一個籤筒。\n" );
                set("no_sell", "這樣東西不能隨便買賣。");
        }
        setup();
}
void init()
{
        add_action("do_look","see");
        add_action("do_get","get");
}
int do_look(string arg)
{
        object ob, who;
        ob = this_object();
        who = this_player();
        if(!arg || arg !="table")
                return notify_fail("你要看什麼? \n");
        else   return notify_fail("賽半仙正趴在桌子上睡覺呢，看來你要（knock）桌子才能叫醒他了。\n");
}
int do_get(string arg)
{
        object ob, me;
        ob = this_object();
        me = this_player();
        if(arg && arg =="table"){
                write ("不要搞惡作劇好不好，那是賽半仙唯一的財產了。\n");
                 return 1;
        }
        return 0;
}

