// Code of ShenZhou
// Ryu 4/17/97

inherit ITEM;
inherit F_AUTOLOAD;
#include <ansi.h>;
int is_container() { return 1; }
int do_put(string);
void create()
{
        set_name("玉笛", ({"yu di", "flute", "di"}));
        set_weight(80);
        set_max_encumbrance(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
         set("long", "這玉笛短得出奇，只不來七寸來長、通體潔白，晶瑩可愛。\n");
                set("unit", "支");
                set("value", 1);
                set("no_sell", 1);
                set("fire_source", 30);
                set("no_drop", 1);
                set("no_get", 1);
                set("no_steal", 1);
        }
}
int query_autoload() { return 1; }
void init()
{
        add_action("do_blow", "blow");
        add_action("do_blow", "play");
        add_action("do_put", "put");
}
int do_blow(string arg)
{
        object ob, me=this_player();

        if (!arg && arg != "di" && arg != "yu di") return notify_fail("你要吹什麼？\n");
        
        if (me->is_busy())
        return notify_fail("你前一個動作還沒有做完。\n");

        message_vision("$N把玉笛放到口邊，輕輕一吹，只聽一陣極尖極細的哨子聲遠遠傳了出去。\n", me);

        if( !query("no_fight", environment(me) )
        && query("fire_source") > 0 && me->query_skill("poison", 1) > 99){        

        message_vision(HIR"隨著哨子聲，玉笛裡突然飛出藍印印的一點火星，火星陡地熄滅，隨即大亮，蓬的一聲響，騰向半空，升起有丈許，這才緩緩降落。\n"NOR, me);

        addn("fire_source", -1);
        ob=new("/d/xingxiu/obj/flute_fire");
        ob->move(environment(me));
        }
        return 1;
}
int do_put(string arg)
{
        object ob, obj, me = this_player();
        string item, target;
        int amount;

        if( !arg || sscanf(arg, "%s in %s", item, target) != 2 )
                return notify_fail("你要將什麼東西放進哪裡？\n");
        
        if( !objectp(obj = present(item, me)) )
                return notify_fail("你要給誰什麼東西？\n");

        if (!id(target)) return 0;

        if( item == "all" ) {
                write("還是一樣一樣來吧。\n");
                return 1;
        }
        if( query("id", obj) != "liu huang"){
                write(query("name", obj)+"對玉笛而言太重了。\n");
                return 1;
        }
                message_vision( sprintf(HIY "$N將一%s%s放進%s。\n" NOR,
                        query("unit", obj),obj->name(),
                        this_object()->name()),me );
                destruct(obj);
                addn("fire_source", 1);
        return 1;
}
