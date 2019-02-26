// Code of LXTX
// pine.c 松樹

inherit ITEM;

int shaking();
int collapse(object);
int do_chop(string);

void create()
{
        set_name("松樹", ({ "pine", "song shu", "tree" }) );
        set_weight(40000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "這是一棵密林裏常見的松樹。\n");
                set("unit", "棵");
                set("no_get", 1);
                set("tree_str", 100);

        }

}

void init()
{
        add_action("do_chop","chop");
}

int do_chop(string arg)
{
        object me=this_player();
        object weapon;
        int str;

        if (!arg) return 0;

        if (me->is_busy() || me->is_fighting() )
                return notify_fail("你正忙着呢。\n");
        
        if (arg != "tree" && arg != "pine")
                return notify_fail("你要砍什麼？\n");
        
        if( !objectp(weapon=query_temp("weapon", me)) || 
                query("id", weapon) != "axe" )
                return notify_fail("你需要一把大斧子。\n");

        if( query("jing", me)<30 || query("qi", me)<50 )
                return notify_fail("你的力氣不夠了。\n");

        message_vision("$N揮動大斧，狠狠地朝松樹幹砍了下去。\n",me);
        addn("jing", -20, me);
        addn("qi", -30, me);
        me->start_busy(3);
        str = me->query_str();
        addn("tree_str",-random(str)/2);
        if (query("tree_str") <=0)
        {
                remove_call_out("collape");
                call_out("collapse",1,me);
        }
        else if (query("tree_str") <= 50)
        {
                remove_call_out("shaking");
                call_out("shaking",1);
        }
        return 1;
}

int shaking()
{
        message_vision("松樹已經搖晃的很厲害了。\n",this_object());
        return 1;
}

int collapse(object me)
{
        object ob=this_object();
        object shugan;
        message_vision("只聽喀嚓一聲，松樹從根處折斷，緊接着轟隆一聲巨響，倒了下來。\n",ob);
        shugan=new("/d/mingjiao/obj/shugan");
        shugan->move(environment(ob));
        set("owner",query("id",  me), shugan);
        destruct(ob);
        return 1;
}