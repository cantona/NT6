// bbb 1997/06/11
// Modify By River 98/12
// Modify by tangfeng 2004

#include <ansi.h>
int get_object(object ob);
inherit ROOM;
#define QUESTDIR1 "quest/天龍八部/凌波微步篇/"

string look_down();
void create()
{
	set("short", "白龍峰");
	set("long", @LONG
走出十余裡，你來到無量山主峰的後山，已來到無量劍派禁地，任何外人
不得擅入。這裡叢林密布，山石怪異。旁邊就是一深不見底的懸崖(cliff)。
LONG
	);
	set("exits", ([
		"northwest" : __DIR__"pubu",
	]));
        set("outdoors", "大理");
        set("objects", ([
           "/d/dali/wuliang/obj/yeguo" : 2,
        ]));

	set("item_desc",([
	   "cliff" : (: look_down :),
	   "down" : "下面白茫茫的什麼也看不見。\n"
	]));
	setup();
}

void init()
{
	add_action("do_jump", "tiao");
        add_action("do_jump", "jump");
}

int get_object(object ob)
{
        if(userp(ob))
        return 1;
        return 0;
}

int do_jump(string arg,object *obj)
{
	      object me= this_player();
        if (!arg || (arg !="down" && arg !="cliff")) return 0;
        if(sizeof(obj)){
         message_vision(HIR "$N腳下踩一個空，「啊～～～」發出一聲慘叫，向下直墜下去。\n"NOR, me);
         me->receive_wound("qi", 20);
         me->unconcious();
         me->move("/d/dali/shanlu3");
         return 1;
         }
	      if(me->query_condition("killer")) return 0;
        if (me->query(QUESTDIR1+"start") 
           && me->query(QUESTDIR1+"over"))
        {
	       message_vision(HIR "$N腳下踩一個空，「啊～～～」發出一聲慘叫，向下直墜下去。\n" 
                            "$N墜下百余丈，撞到崖邊一棵古鬆上，彈了幾彈，下墜的巨力卻也消了。\n" NOR, me);
         me->move(__DIR__"bankong");
         tell_object(me,HIY"\n你已不是第一次跳躍，看似危險，其實你早看好了方向，你半空一個凌身翻，\n"
                           "抓住古鬆，再次借力又一個飛身，已經安全到達一棵樹頂。你緩緩躍了下來。\n"NOR);
         me->move(__DIR__"banshan1");
	       return 1;
         }
        if ((me->query(QUESTDIR1+"start") && (random((int)me->query("kar")) >8))
        ||(me->query(QUESTDIR1+"start") && me->query_temp(QUESTDIR1+"jianying")) 
        || (random((int)me->query("kar")) >20)
        || me->query("marks/xiaoyao")
)
        {
	       message_vision(HIR "$N腳下踩一個空，「啊～～～」發出一聲慘叫，向下直墜下去。\n" 
         "$N墜下百余丈，撞到崖邊一棵古鬆上，彈了幾彈，下墜的巨力卻也消了。\n" NOR, me);
         me->move(__DIR__"bankong");
	       return 1;
         }
         message_vision(HIR "$N腳下踩一個空，「啊～～～」發出一聲慘叫，向下直墜下去。\n"NOR, me);          
         me->receive_wound("qi", 20);
         me->unconcious();
         me->move("/d/dali/shanlu3");
         return 1;
}

string look_down()
{
	return  "下面(down)深不可測，根本看不到底，如果你要自殺，這到是個好地方。\n";
}
