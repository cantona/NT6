//shenshe.c
inherit ITEM;
void create()
{
        set_name("引路神蛇", ({ "shen she", "snake"}));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一條有識路能力的神蛇，可以把主人帶到白"
                            "駝山。(鍵入home即可)\n");
                set("unit", "條");
                set("value", 0);
        }
}

void init()
{
        add_action("do_home", "home");
}

int do_home()
{
        string dir;
        object me = this_player();
        object env;

        env = environment(me);

        if (env->short() != "大沙漠")
                return notify_fail("使用引路神蛇必須在西域沙漠。\n");

        if( query("family/family_name", me) != "歐陽世家" )
                return notify_fail("你撓撓腦袋，不知道怎麼使用「引路神蛇」。\n");

        message_vision("$N從懷中掏出「引路神蛇」，口裡不知念了些什麼，\n"
                       "就見「引路神蛇」吐吐芯子，搖頭擺尾地把$N往白駝山帶去～～～\n",me);
        me->move("/d/baituo/damen");
        return 1;
}