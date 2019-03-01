#include <ansi.h>

inherit ROOM;

string look_kong();
void create()
{
        set("short", "潭底石窟");
        set("long", @LONG
此處是個天然生成的石窟，深不見盡頭，頂上有個圓徑丈
許的大孔(kong)，日光從孔中透射進來，只是那大孔離地一百
餘丈，石窟深處地底，縱在窟中大聲呼叫，上面有人經過也未
必聽見。石窟中日光所及處生了不少大棗樹(tree)。
LONG);

         set("exits", ([
               "enter" : __DIR__"hole2",
         ]));

         set("item_desc", ([
               "kong" : (: look_kong :),
               "tree" : HIC "\n但見棗樹參天聳立，竟有百丈之高。\n" NOR,
         ]));

         set("objects", ([
               CLASS_D("jueqing") + "/chi" : 1,
         ]));     
       
        set("no_clean_up", 0);

        setup();

}

string look_kong()
{
       string msg;
       msg = HIW "\n抬頭向頭頂透光的洞穴望去，只見那洞離地少說也有一百來丈，"
             "樹下雖長著一株大棗樹，但不過四五丈高，就算二十株棗樹疊起，也到"
             "不了頂，凝思半晌，實是束手無策。\n" NOR;

      return sort_msg(msg); 
}

void init()
{       
        add_action("do_climb", ({ "climb", "pa" }));
}

int do_climb(string arg)
{
        object me = this_player();
        object ob;

        if (! arg || arg != "tree" )
                return notify_fail("你要往哪兒爬？\n");

        if (! ob = find_object(__DIR__"ontree1"))
                ob = load_object(__DIR__"ontree1");

        if (me->is_busy())
                return notify_fail("你現在正忙著呢！\n");

        if (me->is_fighting())
                return notify_fail("你還是先把你面前這個家伙解決了再說。\n");

        tell_room(ob, HIC + me->name() + "從下面爬了上來。\n" NOR, me);

        me->move(ob);

        return 1;

}

